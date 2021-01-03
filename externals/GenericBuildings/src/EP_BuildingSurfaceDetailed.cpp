#include "EP_BuildingSurfaceDetailed.h"

#include <IBK_StringUtils.h>
#include <IBK_math.h>

#include "EP_Version.h"

namespace EP {

void BuildingSurfaceDetailed::setSurfaceConditions(const OutsideBoundaryCondition &obc, const std::string &otherBSDName){
	m_outsideBoundaryCondition = obc;

	switch (obc) {
		case OC_Outdoors:	m_windExposed=true;		m_sunExposed=true;		break;
		case OC_Ground:
		case OC_Adiabatic:	m_windExposed=false;	m_sunExposed=false;		break;
		case OC_Surface:	m_windExposed=false;	m_sunExposed=false;		m_outsideBoundaryConditionObject= otherBSDName; break;

		case NUM_OC:	m_windExposed=true;		m_sunExposed=true;
			std::cout<< "Error in setSurfaceCondition. Invalid object: " << m_name << std::endl;
			break;
	}
}


void BuildingSurfaceDetailed::read(const std::vector<std::string> & str, unsigned int version) {
//	FUNCID(BuildingSurfaceDetailed::read);

	//for version 8.3
//	if (version != EP::Version::VN_8_3)
//		throw IBK::Exception("Only version 8.3 supported.", FUNC_ID);


	m_name = str[1];

	if(IBK::tolower_string(str[2]) == "roof")
		m_surfaceType = SurfaceType::ST_Roof;
	else if(IBK::tolower_string(str[2]) == "floor")
		m_surfaceType = SurfaceType::ST_Floor;
	else if(IBK::tolower_string(str[2]) == "ceiling")
		m_surfaceType = SurfaceType::ST_Ceiling;
	else if(IBK::tolower_string(str[2]) == "wall")
		m_surfaceType = SurfaceType::ST_Wall;
	else {
		m_surfaceType = SurfaceType::ST_Wall;
		//warnung rausgeben
	}

	m_constructionName = str[3];
	m_zoneName = str[4];

	if(IBK::tolower_string(str[5]) == "adiabatic")
		m_outsideBoundaryCondition = OutsideBoundaryCondition::OC_Adiabatic;
	else if(IBK::tolower_string(str[5]) == "ground")
		m_outsideBoundaryCondition = OutsideBoundaryCondition::OC_Ground;
	else if(IBK::tolower_string(str[5]) == "surface")
		m_outsideBoundaryCondition = OutsideBoundaryCondition::OC_Surface;
	else if(IBK::tolower_string(str[5]) == "outdoors")
		m_outsideBoundaryCondition = OutsideBoundaryCondition::OC_Outdoors;
	else {
		m_outsideBoundaryCondition = OutsideBoundaryCondition::OC_Outdoors;
		//warnung
	}

	m_outsideBoundaryConditionObject = str[6];

	if(IBK::tolower_string(str[7]) == "sunexposed")
		m_sunExposed = true;
	else
		m_sunExposed = false;

	if(IBK::tolower_string(str[8]) == "windexposed")
		m_windExposed = true;
	else
		m_windExposed = false;

	if(IBK::tolower_string(str[9]) == "autocalculate")
		m_viewFactorToGround = -1;
	else
		m_viewFactorToGround = IBK::string2val<double>(str[9]);

	//ignored number of points str[10]

	//rounding
	int r1 = 1e5;
	for (size_t i=11; i<str.size(); ) {
		IBKMK::Vector3D vec;
		vec.m_x = static_cast<double>(static_cast<int>(IBK::string2val<double>(str[i])*r1))/r1;	++i;
		vec.m_y = static_cast<double>(static_cast<int>(IBK::string2val<double>(str[i])*r1))/r1;	++i;
		vec.m_z = static_cast<double>(static_cast<int>(IBK::string2val<double>(str[i])*r1))/r1;	++i;
		m_polyline.push_back(vec);
	}


}

void BuildingSurfaceDetailed::calcViewFactorToGround()
{
	//NSG::Polygon poly(m_polyline);
	//IBKMK::Vector3D normal = poly.calcNormal();
	//m_viewFactorToGround = (1 - normal.m_z)*0.5;
}

void BuildingSurfaceDetailed::write(std::string & outStr, unsigned int version) const
{

	if(m_polyline.size()<3)
		return;

	if(version != EP::Version::VN_8_3)
		return;

	std::stringstream ss;
	ss << "BuildingSurface:Detailed," << std::endl;
	ss << m_name << "," << std::endl;
	switch (m_surfaceType) {
		case ST_Roof: ss << "Roof" << "," << std::endl; break;
		case ST_Wall: ss << "Wall" << "," << std::endl; break;
		case ST_Ceiling: ss << "Ceiling" << "," << std::endl; break;
		case ST_Floor: ss << "Floor" << "," << std::endl; break;
		default: ss << ","; break;
	}
	ss << m_constructionName << "," << std::endl;
	ss << m_zoneName << "," << std::endl;
	switch (m_outsideBoundaryCondition) {
		case OC_Ground: ss << "Ground" << ",," << std::endl; break;
		case OC_Adiabatic: ss << "Adiabatic" << ",," << std::endl; break;
		case OC_Outdoors: ss << "Outdoors" << ",," << std::endl; break;
		case OC_Surface: ss << "Surface" << "," << m_outsideBoundaryConditionObject << "," << std::endl; break;
		case NUM_OC: ss << "Outdoors" << ",," << std::endl; break; //return;	Warnung ausgeben
		default: ss << "Outdoors" << ",," << std::endl; break;
	}

	if(m_sunExposed)
		ss << "SunExposed" << "," << std::endl;
	else
		ss << "NoSun" << "," << std::endl;

	if(m_windExposed)
		ss << "WindExposed" << "," << std::endl;
	else
		ss << "NoWind" << "," << std::endl;

	ss << m_viewFactorToGround << "," << std::endl;
	ss << m_polyline.size() << "," << std::endl;
	for (size_t i=0; i<m_polyline.size(); ++i) {
		ss << m_polyline[i].m_x << "," << m_polyline[i].m_y << "," << m_polyline[i].m_z;
		if(i== m_polyline.size()-1)
			ss << ";" << std::endl<< std::endl;
		else
			ss << ","<< std::endl ;
	}
	outStr += ss.str();
}


}
