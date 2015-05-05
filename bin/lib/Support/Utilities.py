################################################################################
#
# file : Utilities.py
#
# author: Matias Marenchino - mlmarenchino@gmail.com, 
# based on code by Lakshmi Manohar Rao Velicheti - lveliche@iupui.edu
##
################################################################################

import sys
import os
import logging
import subprocess
import shutil
import inspect

#
# Imports and returns user-defined classes in the provided
# prefix/imports directory.
#
def import_classes (prefix, imports, required_function = None):
  logging.debug ('Importing classes from %s/%s' % (prefix, imports))
  objects = []

  # Evaluate each of the installed pre-commit hooks.
  for name in os.listdir (os.path.join (prefix, imports)):
    if name.endswith (".py") and name != '__init__.py':
    #
    # Helper method that extracts the modules name from the provided
    # Python script name.
    #
      def get_module_basename (script):
        return script[0:len (script) - 3]

      # Import the modules
      module_basename = get_module_basename (name)
      module_name = imports.replace ('/', '.') + '.' + module_basename
      module = __import__ (module_name, locals (), [], 1)

      # Find the user-defined classes (skip imports)
      for cls_name, cls in inspect.getmembers (module, inspect.isclass):
        if inspect.getmodule (cls) == module:

          # Skip classes which do not have the required function
          if required_function:
            found = False
            for func_name, func_ptr in inspect.getmembers (cls):
              if func_name == required_function:
                found = True
                break
            if not found:
              continue

          objects.append (cls)

  logging.debug ('Found classes: %s' % objects)
  return objects


#
# Imports and returns the Tool classes
#
def get_tools ():
  script_path = os.path.dirname (os.path.abspath(sys.argv[0]))
  return import_classes (script_path, 'lib/Tools', 'init_parser')



def run_cmd (cmd):
  logging.debug ('Executing command: [%s]' % cmd)
  subprocess.call (cmd)


def create_directory(fname):
    if not os.path.exists(fname):
        os.makedirs(fname)


def remove_directory(fname):
    if os.path.exists(fname):
        shutil.rmtree(fname)


def is_subset(list1, list2):
    res = True
    for elem in list1:
        if elem not in list2:
            res = False
            break
    
    return res