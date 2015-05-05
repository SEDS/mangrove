#!/bin/env python

################################################################################
#
# file : Tool.py
#
# author: Lakshmi Manohar Rao Velicheti - lveliche@iupui.edu
##
################################################################################

# from .DataAbstractions import ResultSet, Weakness, Suite, Flaw, FlawType, Bug
from ..Support import Utilities
import logging

#
# Base class for Tools - To build and analyse
#
class Tool:
  #
  # Name of the tool
  #
  @staticmethod
  def name ():
    return ''

  #
  # A description of the methodology for this Tool
  #
  def methodology (self, args):
    args_dict = Utilities.dictify_args (args)
    results = '''
A SCA tool is used to compile the test suite(s) defined by the Import.  Each
SCA tool may require different arguments and parameters to execute and
retreive the bugs which it found.  These individual processes are performed
and the results are stored in a standardized manner to compare the results
against the ground truth (i.e. import results).

Typically, bugs identified by a SCA tool have an associated checker which
generically describes the problem that was detected.  This checker information
is stored along with any additional information available from the tool
(i.e. filename, function, and/or line number).
'''

    if args_dict['weaknesses'] != None:
      results += '''
This report included all CWEs which were used for the Import process.
'''
    else:
      results += '''
The following CWEs were built for this tool's results:'''
      for cwe in args_dict['weaknesses'].split (','):
        results += '\n%s' % cwe

    return results

  #
  # Initialize the parser
  #
  @staticmethod
  def init_parser (parser):
    pass

  #
  # Initialize the tool
  #
  def init (self, args):
    # self.__threads__ = args.threads
    # if args.weaknesses:
    #   self.__weaknesses__ = args.weaknesses.split (',')
    # else:
    #   self.__weaknesses__ = None
    pass

  # {@ Build hooks

  #
  # Determine if the tool supports a specific weakness
  #
  def supports_weaknesss (self, weakness):
    return True

  #
  # Create the result set to use for a build
  #
  def build_result_set (self):
    return ResultSet ()

  #
  # Reduces the FPs found to snippets
  #
  def reduce_results (self):
    pass

  #
  # Handle cleaning a suite
  #
  def handle_clean (self, suite):
    pass

  #
  # Handle compiling a suite
  #
  def handle_compile (self, suite):
    pass

  #
  # Handle generating the build document for a suite
  #
  def handle_docgen (self, suite):
    pass

  # @}

  # {@ Report hooks

  #
  # Determine if the provided bug has the correct checker for the weakness
  #
  def correct_checker (self, bug, weakness_name):
    return False

  # @}
