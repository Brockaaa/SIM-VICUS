/*	NANDRAD Solver Framework and Model Implementation.

	Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Anne Paepcke     <anne.paepcke -[at]- tu-dresden.de>

	This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
*/

#include <iostream>

#include <IBK_MessageHandler.h>
#include <IBK_MessageHandlerRegistry.h>
#include <IBK_messages.h>

// include solver control framework and integrator
#include <SOLFRA_SolverControlFramework.h>

// include header for command line argument parser
#include <NANDRAD_ArgsParser.h>
#include <NANDRAD_Project.h>

// include model implementation class
#include "NM_NandradModel.h"

const char * const PROGRAM_INFO =
	"NANDRAD Solver\n"
	"All rights reserved.\n\n"
	"The NANDRAD Development Team:\n"
	"Anne Paepcke, Andreas Nicolai\n"
	"Contact: \n"
	"  anne.paepcke [at] tu-dresden.de\n"
	"  andreas.nicolai [at] tu-dresden.de\n\n";

int main(int argc, char * argv[]) {
	FUNCID(main);

	try {
		// a stopwatch to measure time needed for solver initialization
		IBK::StopWatch initWatch;

		// *** Command line parsing ***
		NANDRAD::ArgsParser args;
		args.parse(argc, argv);
		// handle default arguments like help and man-page requests, which are printed to std::cout
		if (args.handleDefaultFlags(std::cout))
			// stop if help/man-page requested
			return EXIT_SUCCESS;
		if (args.flagEnabled(IBK::SolverArgsParser::DO_VERSION)) {
			std::cout << PROGRAM_INFO << std::endl;
			NANDRAD_MODEL::NandradModel::printVersionStrings();
			SOLFRA::SolverControlFramework::printVersionInfo();
			IBK::IBK_Message("\n", IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
			return EXIT_SUCCESS;
		}

		// check if errors are present, error messages are written to std::cerr
		if (args.handleErrors(std::cerr))
			return EXIT_FAILURE;

		// *** create main model instance ***
		NANDRAD_MODEL::NandradModel model;

		// *** create directory structure ***
		model.setupDirectories(args);
		// now we have a log directory and can write our messages to the log file

		// *** setup message handler ***

		unsigned int verbosityLevel = IBK::string2val<unsigned int>(args.option(IBK::SolverArgsParser::DO_VERBOSITY_LEVEL));
		IBK::MessageHandler * messageHandlerPtr = IBK::MessageHandlerRegistry::instance().messageHandler();
		messageHandlerPtr->setConsoleVerbosityLevel((int)verbosityLevel);
		messageHandlerPtr->setLogfileVerbosityLevel((int)verbosityLevel);
		messageHandlerPtr->m_contextIndentation = 48;
		std::string errmsg;

		IBK::Path logfile = model.dirs().m_logDir / "screenlog.txt";
		bool success = messageHandlerPtr->openLogFile(logfile.str(), args.m_restart, errmsg);
		if (!success) {
			IBK::IBK_Message(errmsg, IBK::MSG_WARNING, FUNC_ID);
			IBK::IBK_Message("Cannot create log file, outputs will only be printed on screen.", IBK::MSG_WARNING, FUNC_ID);
		}

		// *** write program/copyright info ***
		IBK::IBK_Message(PROGRAM_INFO, IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
		NANDRAD_MODEL::NandradModel::printVersionStrings();
		SOLFRA::SolverControlFramework::printVersionInfo();
		IBK::IBK_Message("\n", IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);

		// *** OpenMP Info ***
#if defined(_OPENMP)
		IBK::IBK_Message( IBK::FormatString("OpenMP parallelization enabled: using %1 thread(s)\n\n")
						  .arg(args.m_numParallelThreads), IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
		if (!args.hasOption(IBK::SolverArgsParser::GO_PARALLEL_THREADS)) {
			IBK::IBK_Message( IBK::FormatString("Number of threads selected from variable OMP_NUM_THREADS = %1\n\n")
							  .arg(args.m_numParallelThreads), IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
		}
#endif // _OPENMP

		// *** Initialize model. ***

		// init model (first read project, then initialize model)
		model.init(args);
		IBK::IBK_Message( IBK::FormatString("Model initialization complete, duration: %1\n\n").arg(initWatch.diff_str()),
						  IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);

		// *** Run model through solver control framework ***
		IBK::IBK_Message("Creating solver framework\n", IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
		SOLFRA::SolverControlFramework solver(&model);
		solver.m_useStepStatistics = args.flagEnabled(IBK::SolverArgsParser::DO_STEP_STATS);
		solver.m_logDirectory = model.dirs().m_logDir;
		solver.m_stopAfterSolverInit = args.flagEnabled(IBK::SolverArgsParser::GO_TEST_INIT);
		solver.m_restartFilename = model.dirs().m_varDir / "restart.bin";

		// depending on the restart settings, either run from start or continue simulation
		if (args.m_restartFrom) {
			IBK::IBK_Message("Continuing computation from selected check point\n\n", IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
			solver.restartFrom(args.m_restartTime);
		}
		else if (args.m_restart) {
			IBK::IBK_Message("Continuing computation from last recorded check point\n\n", IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
			solver.restart();
		}
		else {
			solver.run();
			if (!solver.m_stopAfterSolverInit)
				solver.writeMetrics();
			else {
				IBK::IBK_Message( IBK::FormatString("Total initialization time: %1\n").arg(initWatch.diff_str()), IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
			}
		}
	}
	catch (IBK::Exception & ex) {
		ex.writeMsgStackToError();
		IBK::IBK_Message("Critical error, simulation aborted.", IBK::MSG_ERROR, FUNC_ID);
		return EXIT_FAILURE;
	}
	catch (std::exception& ex) {
		IBK::IBK_Message(ex.what(), IBK::MSG_ERROR, FUNC_ID);
		IBK::IBK_Message("Critical error, simulation aborted.", IBK::MSG_ERROR, FUNC_ID);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

