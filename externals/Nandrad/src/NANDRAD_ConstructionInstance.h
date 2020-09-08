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

#ifndef NANDRAD_ConstructionInstanceH
#define NANDRAD_ConstructionInstanceH

#include <string>

#include "NANDRAD_Interface.h"
//#include "NANDRAD_EmbeddedObject.h"
#include "NANDRAD_CodeGenMacros.h"

namespace IBK {
	class Parameter;
}

namespace NANDRAD {

class ConstructionType;

/*!	Defines a wall/floor/ceiling construction instance.

	A ConstructionInstance contains all information about a wall and possibly embedded objects
	like windows.

	Note that the area parameter stores the gross area of the wall, including all embedded objects.
	Naturally, their area must not exceed the wall area.
	A window area that is equal to the wall area is interpreted as a wall consisting of only windows
	without a construction behind.

	Each construction instance stores its surface information inside interface data structures
	for side A and side B. Side A is besides construction layer with index 0.
	By default, an interface has no boundary condition information (model types are set to undefined)
	and hence no fluxes are calculated.
	There must be at least one interface with valid boundary condition parametrization for a construction
	instance to be valid. Not referenced wall constructions will still be calculated, as they may
	serve as storage medium or provide sensor data. However, if not needed, they should be removed
	to improve performance.
*/
class ConstructionInstance  {
public:

	/*! Construction-specific parameters required by several models. */
	enum para_t {
		/*! Orientation of the wall [deg]. */
		P_ORIENTATION,					// Keyword: Orientation				[Deg]	'Orientation of the wall [deg].'
		/*! Inclination of the wall [deg]. */
		P_INCLINATION,					// Keyword: Inclination				[Deg]	'Inclination of the wall [deg].'
		/*! Gross area of the wall [m2]. */
		P_AREA,							// Keyword: Area					[m2]	'Gross area of the wall [m2].'
		NUM_P
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	NANDRAD_READWRITE

	/*! Checks for valid parameters and stores quick-access pointer to associated construction type.
		\note This function throws an exception if invalid parameters are defined, parameters are missing, or
			the construction type ID is invalid/unknown.
	*/
	void checkParameters(const std::vector<ConstructionType> & conTypes);

	/*! A special form of comparison operator: tests if the construction would yield
		the same results as the other construction when being simulated.
		The test checks for:
		- same construction type ID
		- interface objects for locations A and B result in same behavior
	*/
	bool behavesLike(const ConstructionInstance & other) const;

	// *** PUBLIC MEMBER VARIABLES ***

	/*! Unique id number. */
	unsigned int				m_id = INVALID_ID;				// XML:A:required
	/*! IBK-language encoded name of construction instance. */
	std::string					m_displayName;					// XML:A
	/*! The id number of the corresponding construction type. */
	unsigned int				m_constructionTypeId;			// XML:E:required

	/*! List of parameters. */
	IBK::Parameter				m_para[NUM_P];					// XML:E

	/*! The interface at side A. */
	Interface					m_interfaceA;					// XML:E:tag=InterfaceA
	/*! The interface at side B. */
	Interface					m_interfaceB;					// XML:E:tag=InterfaceB

	/*! All embedded objects. Embedded objects cut out an area of the current construction and substitute
		wall simulation by an explicit simulation model.
	*/
//	std::vector<EmbeddedObject>	m_embeddedObjects;

	// *** Variables used only during simulation ***

	/*! Quick-access pointer to the underlying construction type. */
	const NANDRAD::ConstructionType		*m_constructionType = nullptr;
};


} // namespace NANDRAD

#endif // NANDRAD_ConstructionInstanceH
