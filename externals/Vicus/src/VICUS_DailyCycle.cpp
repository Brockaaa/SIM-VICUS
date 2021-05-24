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

#include "VICUS_DailyCycle.h"

#include <NANDRAD_Schedule.h>
namespace VICUS {

bool DailyCycle::isValid() const {

	if(m_dayTypes.empty() || m_dayTypes.size()> 7+1)	//Mo, ..., Sun + Holiday
		return false;	// day types not valid

	for( auto dt : m_dayTypes){
		if(!(dt == NANDRAD::Schedule::ST_MONDAY ||
				dt == NANDRAD::Schedule::ST_TUESDAY ||
				dt == NANDRAD::Schedule::ST_WEDNESDAY ||
				dt == NANDRAD::Schedule::ST_THURSDAY ||
				dt == NANDRAD::Schedule::ST_FRIDAY ||
				dt == NANDRAD::Schedule::ST_SATURDAY ||
				dt == NANDRAD::Schedule::ST_SUNDAY ||
				dt == NANDRAD::Schedule::ST_HOLIDAY))
			return false;	// day type is not valid
	}

	if(m_values.size() != m_timePoints.size() || m_values.empty())
		return false;	// empty values or size not same of values and timepoints

	if(m_timePoints[0] != 0)
		return false;	// start point is not 0

	// check time points vector and time point and value vectors have same size
	return true;
}

DailyCycle DailyCycle::multiply(const DailyCycle &other) const {
	DailyCycle dc;

	if(!isValid()){
		///TODO Katja fehlermeldung
		return dc;
	}
	if(!other.isValid()){
		///TODO Katja fehlermeldung
		return dc;
	}

	//check for equal day types
	for(unsigned int i=0; i<m_dayTypes.size(); ++i){
		for(unsigned int j=0; j<other.m_dayTypes.size(); ++j){
			if(m_dayTypes[i] == other.m_dayTypes[j])
				dc.m_dayTypes.push_back(m_dayTypes[i]);
		}
	}
	if(dc.m_dayTypes.empty())
		return dc;

	//make a copy of the other daily cycle to the new daily cycle
	dc.m_timePoints = other.m_timePoints;
	dc.m_values = other.m_values;

	//compare timepoints
	unsigned int j=0;
	unsigned int i=0;
	//for(unsigned int j=0; j<m_timePoints.size();){
	//for(unsigned int i=0; i<dc.m_timePoints.size();){
	while (i<dc.m_timePoints.size()) {

		double timePoint = m_timePoints[j];
		double timePoint2 = dc.m_timePoints[i];
		double val = dc.m_values[i];
		if(IBK::nearly_equal<3>(timePoint, timePoint2)){
			if(j+1 >= m_timePoints.size())
				//fertig
				break;
			//multi
			//dc.m_values[i] *= m_values[j];
			++j;
		}
		else if(timePoint > timePoint2){
			bool haveNext = i+1<dc.m_timePoints.size();

			//insert a time point from this daily cycle in the new daily cycle
			if((haveNext && timePoint < dc.m_timePoints[i+1]) || !haveNext){
				dc.m_timePoints.insert(dc.m_timePoints.begin()+i+1, timePoint);
				dc.m_values.insert(dc.m_values.begin()+i+1, val);
			}
			++i;
		}
	}

	//multi
	i=0;
	j=0;
	//now daily cycle (dc) holds all start times (interval start point)
	//iterate dc time points and check for same or lower time points in dc
	//if true multiply
	//otherwise increment
	while(i<dc.m_timePoints.size()){
		double timePoint = m_timePoints[j];
		double timePoint2 = dc.m_timePoints[i];

		if(IBK::nearly_equal<3>(timePoint, timePoint2) ||
				(timePoint2 > timePoint &&
				j+1<m_timePoints.size() &&
				timePoint2 < m_timePoints[j+1]) ||
				j+1 >= m_timePoints.size()){

			dc.m_values[i] *= m_values[j];
			++i;
		}
		else if(j+1<m_timePoints.size() &&
				timePoint2 >= m_timePoints[j+1]){
			++j;
		}
	}

	return dc;
}

DailyCycle DailyCycle::multiply(double val) const {
	FUNCID(DailyCycle::multiply);
	DailyCycle dc;
	if(!isValid()){
		//Schedule interval '%1' with (id=%2) is not valid.
		return dc;
	}

	if(val<0)
		IBK::Exception(IBK::FormatString("Multiply negative values to a daily cylce is not allowed."), FUNC_ID);

	dc = *this;

	for(unsigned int i=0; i<dc.m_values.size(); ++i)
		dc.m_values[i] *= val;

	return dc;
}


bool DailyCycle::operator!=(const DailyCycle & other) const {
	if (m_values != other.m_values)  return true;
	if (m_dayTypes != other.m_dayTypes)  return true;
	if (m_timePoints != other.m_timePoints)  return true;
	return false;
}


} // namespace VICUS
