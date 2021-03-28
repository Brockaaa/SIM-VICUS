/*	The NANDRAD data model library.

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

#ifndef NANDRAD_FMIDescriptionH
#define NANDRAD_FMIDescriptionH

#include <vector>
#include "NANDRAD_FMIVariableDefinition.h"

namespace NANDRAD {


/*! Contains all data to generate a modelDescription.xml and configure the NANDRAD FMI Slave.

*/
class FMIDescription {
public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	NANDRAD_READWRITE

	// *** PUBLIC MEMBER VARIABLES ***

	/*! Holds all input variable definitions. */
	std::vector<FMIVariableDefinition>	m_inputVariableDefs;					// XML:E
};

} // namespace NANDRAD

#endif // NANDRAD_FMIDescriptionH
