#!/usr/bin/env python

# Solver test suite runner script, used for checking correct (or at least sufficiently similar)
# Jacobian matrixes when running the same test case with Dense and KLU solvers.
#
# This script processes the test suite's directory structure and for each project file it does:
# - run simulation with '--les-solver=Dense -o="<basename>.Dense"' argument
# - run simulation again with '--les-solver=KLU -o="<basename>.KLU"' argument
# - read in both summary files 
# - compare summary files
#
# License: 
#   BSD License
#
# Authors: 
#   Andreas Nicolai <andreas.nicolai@tu-dresden.de>
#
# Syntax:
# > python run_tests.py --path <path/to/testsuite> --solver <path/to/solver/binary> --extension <project file extension>
#
# Example:
# > python run_tests.py --path ../../data/tests --solver ./DelphinSolver --extension d6p
# > python run_tests.py -p ../../data/tests -s ./DelphinSolver -e d6p
#
# Returns:
# 0 - if all tests could be simulated successfully and if all solver results/metrics match those of reference results
# 1 - if anything failed
#
# Note: if run with --run-all option, test cases without reference results will always be accepted.
#

import subprocess		# import the module for calling external programs (creating subprocesses)
import sys
import os
import os.path
import shutil
import filecmp          # for result file comparison
import argparse
import platform         # to detect current OS

from colorama import *
from SolverStats import *
from print_funcs import *
from config import USE_COLORS


def configCommandLineArguments():
	"""
	This method sets the available input parameters and parses them.

	Returns a configured argparse.ArgumentParser object.
	"""

	parser = argparse.ArgumentParser("run_tests.py")
	parser.description = '''
Runs the regression test suite. Can be used for init-tests (--test-init) 
or performance evaluation (--performance) as well.'''

	parser.add_argument('-p', '--path', dest='path', required=True, type=str, 
	                    help='Path to test suite root directory.')
	parser.add_argument('-s', '--solver', dest='solver', required=True, type=str, 
	                    help='Path to solver binary.')
	parser.add_argument('-e', '--extension', dest="extension", required=True, type=str, 
	                    help='Project file extension.')
	parser.add_argument('--no-colors', dest="no_colors", action='store_true', 
	                    help='Disables colored console output.')
	parser.add_argument('--run-all', dest="run_all", action='store_true', 
	                    help='If set (in regression test mode), also the test cases without reference results '
	                    'are simulated (can be used to generate reference results for all cases).')

	return parser.parse_args()


def checkResults(dir1, dir2, evalTimes):
	"""
	Compares two result directories for equal contents.

	Compared are:

	- physical results
	- solver counters (/log/summary.txt)

	This function uses IBK.SolverStats

	Arguments:
	* dir1 (reference results) and dir2 (computed results)
	* evalTimes is a dictionary with filepath (key) and wall clock time (value), 
	  new entries are always added to the dictionary


	Returns: True on success, False on error
	"""
	try:
		# open stat files and compare them
		stats1 = SolverStats()
		if not stats1.read(dir1 + "/log/summary.txt"):
			return False
		stats2 = SolverStats()
		if not stats2.read(dir2 + "/log/summary.txt"):
			return False

		# but skip the LESRHSEvals counter, since this MUST be different
		if not SolverStats.compareStats(stats1, stats2, ['LESRHSEvals']):
			printError("Mismatching statistics.")
			return False

		# compare all result files (d60, tsv), if any reference result files exist
		if os.path.exists(dir1 + "/results"):
			if not SolverStats.compareResults(dir1 + "/results", dir2 + "/results"):
				printError("Mismatching values.")
				return False
		evalTimes[dir2] = stats2.timers['WallClockTime']
	except Exception as e:
		printError("Error comparing simulation results, error: {}".format(e))
	return True




# *** main script ***

args = configCommandLineArguments()

if not args.no_colors:
	init() # init ANSI code filtering for windows
	config.USE_COLORS = True
	printNotification("Enabling colored console output")

# process all directories under test suite directory
currentOS = platform.system()
compilerID = None
if currentOS   == "Linux" :
	compilerID = "gcc_linux"

elif currentOS == "Windows" :
	compilerID = "VC14_win64"

elif currentOS == "Darwin" :
	compilerID = "gcc_mac"

if compilerID == None:
	printError("Unknown/unsupported platform")
	exit(1)
else:
	print "Compiler ID            : " + compilerID

print "Test suite             : " + args.path
print "Solver                 : " + args.solver
print "Project file extension : " + args.extension

# walk all subdirectories (except .svn) within testsuite and collect project file names
projects = []
for root, dirs, files in os.walk(args.path, topdown=False):
	for name in files:
		if name.endswith('.'+args.extension):
			projectFilePath = os.path.join(root, name)
			projects.append(projectFilePath)

projects.sort()
print("Number of projects     : {}".format(len(projects)))
print "\n"

failed_projects = []
eval_times = dict() # key - file path to project, value - eval time in [s]

for project in projects:
	print project
	path, fname = os.path.split(project)
	#print "Path    : " + path
	#print "Project : " + fname

	# compose path of result folder
	resultsFolder = project[:-(1+len(args.extension))]

	# compose path of 'Dense' and 'KLU' folders
	resultsFolderDense = resultsFolder + ".Dense"
	resultsFolderKLU = resultsFolder + ".KLU"

	# remove entire directory with previous results
	if os.path.exists(resultsFolderDense):
		shutil.rmtree(resultsFolderDense)
	if os.path.exists(resultsFolderKLU):
		shutil.rmtree(resultsFolderKLU)

	cmdline = [args.solver, project]
	if platform.system() == "Windows":
		cmdline.append("-x")
		cmdline.append("--verbosity-level=0")

	try:
		# run solver with Dense matrix solver
		FNULL = open(os.devnull, 'w')
		cmdLineDense = cmdline
		cmdLineDense.append("--les-solver=Dense")
		cmdLineDense.append('-o='+resultsFolderDense)
		if platform.system() == "Windows":
			retcode = subprocess.call(cmdLineDense, creationflags=subprocess.CREATE_NEW_CONSOLE)
		else:
			retcode = subprocess.call(cmdLineDense, stdout=FNULL, stderr=subprocess.STDOUT)
		# check return code
		if retcode != 0:
			# mark project as failed
			failed_projects.append(project)
			# and print error message
			printError("Simulation failed, see screenlog file {}".format(os.path.join(os.getcwd(), 
			                                                                          resultsFolderDense+"/log/screenlog.txt"  ) ) )
			continue # next project
		
		# run solver with KLU matrix solver
		cmdLineKLU = cmdline
		cmdLineKLU.append("--les-solver=KLU")
		cmdLineKLU.append('-o='+resultsFolderKLU)
		if platform.system() == "Windows":
			retcode = subprocess.call(cmdLineKLU, creationflags=subprocess.CREATE_NEW_CONSOLE)
		else:
			retcode = subprocess.call(cmdLineKLU, stdout=FNULL, stderr=subprocess.STDOUT)
		# check return code
		if retcode != 0:
			# mark project as failed
			failed_projects.append(project)
			# and print error message
			printError("Simulation failed, see screenlog file {}".format(os.path.join(os.getcwd(), 
			                                                                          resultsFolderKLU+"/log/screenlog.txt"  ) ) )
			continue # next project
		
		# now read in both summary files
		if not checkResults(resultsFolderDense, resultsFolderKLU, eval_times):
			if not project in failed_projects:
				failed_projects.append(project) # mark as failed
			printError("Mismatching results.")
		
	except OSError as e:
		printError("Error starting solver executable '{}', error: {}".format(args.solver, e))
		exit(1)

print ""
print "Successful projects:"
print ""
print "{:80s} {}".format("Project path", "Wall clock time [s]")
filenames = eval_times.keys()
filenames.sort()
for filename in filenames:
	fname = os.path.basename(filename)
	onedir = os.path.join(os.path.basename(os.path.dirname(filename)), os.path.basename(filename))
	printNotification("{:80s} {:>10.3f}".format(onedir, eval_times[filename]))

if len(failed_projects) > 0:
	print ""
	print "Failed projects:"
	for p in failed_projects:
		printError(p)
	print ""
	printError("*** Failure ***")
	exit(1)


printNotification("*** Success ***")
exit(0)


