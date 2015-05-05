import sys
import os
import subprocess
import shutil
import re

import json
import fnmatch
import logging


class Compiler:

    def __init__(self, data):
        self.__compilation_data = data

    @classmethod
    def from_file(cls, fname):
        data = self.__read_compile_commands(fname)
        return cls(data)

    @classmethod
    def from_command(cls, compiler, options=None):
        command = compiler + ' '
        if options: command += options + ' '
        command += '-o *.o -c *.c'
        data = [{'command': command, 'directory': '', 'file': '*.c'}]
        return cls(data)


    def __read_compile_commands(self, fname):
        with open(fname, 'r') as json_data:
            data = json.load(json_data)

        # [{'command': '...', 'directory': '...', 'file': '...'}, {'command': '...', 'directory': '...', 'file': '...'}, ... ]
        return data


    def compile(self, original_fname, object_file, source_file):
        compilation = None
        dirname = os.path.dirname(original_fname)
        fname = os.path.basename(original_fname)
        for file_compilation in self.__compilation_data:
            # we allow wildcards in the 'file' field of the json compile_commands
            if fnmatch.fnmatch(fname, file_compilation['file']):
                if dirname != os.path.dirname(file_compilation['directory']):
                    #TODO: should we cd to dirname???
                    pass

                # replacing -o fname.o
                command = file_compilation['command']
                matching = re.search(r"-o\s+.+\.o", command)
                if matching:
                    (a, b) = matching.span()
                    command = command[:a] + "-o " + object_file + \
                                command[b:]

                # replacing -c fname.c
                matching = re.search(r"-c\s+.+\.c", command)
                if matching:
                    (a, b) = matching.span()
                    command = command[:a] + "-c " + source_file + \
                                command[b:]
                else:
                    command += source_file

                # try to compile it
                try:
                    output = subprocess.check_output(command, \
                                                     stderr=subprocess.STDOUT, \
                                                     shell=True)
                    logging.debug("Compilation of file [%s] was successful with [%s]" \
                                  % (fname, command))
                    return 0
                except subprocess.CalledProcessError as _:
                    logging.debug("Compilation of file [%s] FAILED with command [%s]" \
                                  % (fname, command))
                    return 1
