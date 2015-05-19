import os
import sys
import shutil

from . import Utilities


class Dirs:
    def __init__(self, source_dir, build_dir, results_dir):
        self.source_dir = source_dir
        self.build_dir = build_dir
        self.results_dir = results_dir

class FileManager:
    def __init__(self, dirs, fname, language, keep_copy=True, package=None):
        """Constructor

        Arguments:
        dirs -- Dirs object containing directories data
        fname -- the filename to analyze
        language -- one of {'java', 'c', 'cpp'}
        package -- the package name (ex. airport) (in java)
        keep_copy -- keeps a copy of every single file
        """
        self.trial_counter = 0
        self.keep_copy = keep_copy
        self.fname = os.path.basename(fname)
        self.fname_no_extension = os.path.splitext(self.fname)[0]
        self.language = language
        self.source_dir = dirs.source_dir

        # build directory doesn't have a directory structure
        self.build_dir = dirs.build_dir
        Utilities.create_directory(self.build_dir)

        # results directory does have a directory structure
        self.results_dir = dirs.results_dir
        Utilities.create_directory(self.results_dir)

        self.package = package

        shutil.copyfile(self.get_original_source_path(), \
                        self.get_trial_source_path())
        self.backup_trial_file()
        Utilities.create_directory(self.build_dir)
        Utilities.create_directory(self.results_dir)

        # TODO: do we keep it in memory?
        with open(self.get_original_source_path()) as fd:
            self.original_file_lines = fd.readlines()

    def _get_source_location(self):
        return self.source_dir

    def _get_package(self):
        return self.package

    def _get_result_directory(self):
        return self.results_dir

    def set_lines_to_trial(self):
        with open(self.get_trial_source_path()) as fd:
            self.original_file_lines = fd.readlines()

    def get_source_path(self):
        """ex : /usr/matias/.../airport.java
        """
        return os.path.join(self._get_source_location(), self.fname)

    def get_source_basename(self):
        """ex : airport.java
        """
        return self.fname

    def _get_source_semipath(self):
        """Concatenates packages as folders.

        Ex. if package = a.b.c, returns a/b/c/file.java
        """
        tmp = ''
        if self.package:
            tmp = os.path.join(*self.package.split('.'))
        tmp = os.path.join(tmp, self.fname)
        return tmp

    def get_trial_source_path(self):
        tmp = os.path.join(self.build_dir)
        tmp = os.path.join(tmp, self._get_source_semipath())
        return tmp

    def get_trial_source_num_lines(self):
        with open(self.get_trial_source_path(), 'r') as fd:
            file_num_lines = sum(1 for _ in fd)
        return file_num_lines

    def write_subset_file(self, indices):
        with open(self.get_trial_source_path(), 'w') as fd:
            for subrange in indices:
                if type(subrange) is list:
                    [a, b] = subrange
                    for i in range(a, b + 1):
                        fd.write(self.original_file_lines[i - 1])
                else:
                    i = subrange
                    fd.write(self.original_file_lines[i - 1])

    def get_original_source_path(self):
        return os.path.join(self.source_dir, self._get_source_semipath())

    def get_original_source_num_lines(self):
        return len(self.original_file_lines)
        # with open(self.get_original_source_path(), 'r') as fd:
        #     file_num_lines = sum(1 for _ in fd)
        # return file_num_lines

    def backup_trial_file(self, append=None):
        prev_fname = self.get_trial_source_path()
        if self.keep_copy:
            new_fname = prev_fname + str(self.trial_counter)
            if append: 
                new_fname += append
            self.trial_counter += 1
            os.rename(prev_fname, new_fname)
            return new_fname
        else:
            return prev_fname

    def force_backup_trial_file(self, append=None):
        tmp = self.keep_copy
        self.keep_copy = True
        fname = self.backup_trial_file(append)
        self.keep_copy = tmp
        return fname

    def get_next_backup_filename(self, append=None):
        new_fname = self.get_trial_source_path() + str(self.trial_counter)
        if append: 
            new_fname += append
        return new_fname


    def move_to_trial_file(self, fname):
        shutil.copyfile(fname, self.get_trial_source_path())

    def get_result_file_path(self):
        return 

    def move_trial_to_result(self, prepend=None, append=None):
        prev_fname = self.get_trial_source_path()
        new_fname = self.get_source_basename()
        if prepend:
            new_fname = prepend + new_fname
        if append:
            new_fname += append
        new_fname = os.path.join(self._get_result_directory(), \
                                 new_fname)
        os.rename(prev_fname, new_fname)
        return new_fname

    def get_result_error_path(self):
        return self.get_result_file_path() + '_ERROR'

    def move_trial_to_result_error(self):
        prev_fname = self.get_trial_source_path()
        new_fname = self.get_result_error_path()
        os.rename(prev_fname, new_fname)
        return new_fname


class CPPFileManager(FileManager):

    def __init__(self, dirs, fname, language, keep_copy=True):
        FileManager.__init__(self, dirs, fname, language, keep_copy)
        # super(CPPFilePaths, self).__init__(config_vals, location, fname, language)

    def get_build_object_path(self):
        tmp = os.path.join(self.build_dir, self.fname_no_extension)
        return tmp + '.o'


class JavaFileManager(FileManager):

    def __init__(self, dirs, fname, language, keep_copy=True, package=None):
        FileManager.__init__(self, dirs, fname, language, keep_copy, package)


    def get_java_compilation_fname(self):
        """if the file is Airport.java in package airport,
        then it returns airport.Airport.
        If it's not in a package, returns just Airport
        """
        if self.package:
            return self.package + '.' + self.fname_no_extension
        else:
            return self.fname_no_extension

    def get_class_semipath(self):
        """
        Concatenates packages as folders and generates class name.
        Ex. if package = a.b.c, returns a/b/c/file.class
        """
        tmp = ''
        if self.package:
            tmp = os.path.join(*self.package.split('.'))
        tmp = os.path.join(tmp, self.fname_no_extension + '.class')
        return tmp

    def get_build_class_path(self):
        return os.path.join(self.build_dir, self.get_class_semipath())

