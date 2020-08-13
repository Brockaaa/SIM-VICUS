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

#include "NANDRAD_Interval.h"
#include "NANDRAD_Constants.h"
#include "NANDRAD_KeywordList.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <IBK_FormatString.h>
#include <IBK_Exception.h>
#include <IBK_messages.h>

#include <tinyxml.h>

namespace NANDRAD {

bool Interval::operator!=(const Interval & other) const {
	for (int i=0; i<NUM_IP; ++i)
		if (m_para[i] != other.m_para[i]) return true;
	return false; // this and other hold the same data
}


void Interval::setStartEnd( double start, double endtime, IBK::Unit u ) {
	m_para[IP_START].set( KeywordList::Keyword("Interval::para_t", IP_START), start, u.name());
	if (endtime == std::numeric_limits<double>::max())
		m_para[IP_END].clear();
	else
		m_para[IP_END].set( KeywordList::Keyword("Interval::para_t", IP_END), endtime, u.name());
}


void Interval::checkParameters() const {
	FUNCID(Interval::checkParameters);

	// check start point
	if (!m_para[Interval::IP_START].name.empty()) {
		// start point is greater than zero
		if (m_para[Interval::IP_START].value < 0)
			throw IBK::Exception( IBK::FormatString("Interval has an invalid Start parameter."), FUNC_ID);
	}

	// check end point
	if (!m_para[Interval::IP_END].name.empty()) {
		double endtime = m_para[Interval::IP_END].value;
		if (endtime < 0)
			throw IBK::Exception( IBK::FormatString("Invalid End time point in Interval."), FUNC_ID);

		// check if end time point preceedes start time point
		if (!m_para[Interval::IP_START].name.empty()
			&& endtime <= m_para[Interval::IP_START].value)
		{
			throw IBK::Exception( IBK::FormatString( "End time point preceedes Start time point "
													 "in Interval, but End time point must be past the Start time."), FUNC_ID);
		}
	}

	// check units for all provided parameters
	unsigned int time_base_id = IBK::Unit("s").base_id();
	for (unsigned int i=0; i<NUM_IP; ++i) {
		if (!m_para[i].name.empty()) {
			if (m_para[i].IO_unit.base_id() != time_base_id)
				throw IBK::Exception( IBK::FormatString( "Parameter '%1' has an invalid unit, should be a time unit.").arg(m_para[i].name), FUNC_ID);
		}
	}
}


bool Interval::isInInterval(double t) const {
	return (IBK::f_fuzzyGTEQ(t, m_para[IP_START].value) && IBK::f_fuzzyLTEQ(t, endTime()) );
}


double Interval::endTime() const {
	if (!m_para[Interval::IP_END].name.empty())
		return m_para[Interval::IP_END].value;
	// interval lasts until the end of simulation
	return std::numeric_limits<double>::max();
}


} // namespace NANDRAD

