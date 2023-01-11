/*	The SIM-VICUS data model library.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Dirk Weiss  <dirk.weiss -[at]- tu-dresden.de>
	  Stephan Hirth  <stephan.hirth -[at]- tu-dresden.de>
	  Hauke Hirsch  <hauke.hirsch -[at]- tu-dresden.de>

	  ... all the others from the SIM-VICUS team ... :-)

	This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This library is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#ifndef VICUS_LCAPeriodH
#define VICUS_LCAPeriodH

#include <QString>
#include <QCoreApplication>

#include <vector>

#include <IBK_Parameter.h>
#include <IBK_MultiLanguageString.h>

#include <NANDRAD_InterfaceLongWaveEmission.h>
#include <NANDRAD_InterfaceSolarAbsorption.h>
#include <NANDRAD_InterfaceVaporDiffusion.h>
#include <NANDRAD_InterfaceAirFlow.h>

#include "VICUS_CodeGenMacros.h"
#include "VICUS_Constants.h"
#include "VICUS_AbstractDBElement.h"
#include "VICUS_InterfaceHeatConduction.h"
#include "VICUS_Schedule.h"


namespace VICUS {

/*! This is a template for boundary conditions, to be referenced by components. */
class LCAPeriod : public AbstractDBElement {
	Q_DECLARE_TR_FUNCTIONS(LCAPeriod)
public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE_OVERRIDE
	VICUS_COMPARE_WITH_ID

	bool isValid(const Database<Schedule> &scheduleDB) const;

	/*! Comparison operator */
	ComparisonResult equal(const AbstractDBElement *other) const override;

	// *** PUBLIC MEMBER VARIABLES ***

	//:inherited	unsigned int					m_id = INVALID_ID;		// XML:A:required
	//:inherited	IBK::MultiLanguageString		m_displayName;			// XML:A

};

} // namespace VICUS


#endif // VICUS_LCAPeriodH
