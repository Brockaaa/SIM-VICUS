/*	The SIM-VICUS data model library.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  ... all the others from the SIM-VICUS team ... :-)

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

#ifndef VICUS_AbstractDBElementH
#define VICUS_AbstractDBElementH

namespace VICUS {

class AbstractDBElement {
public:
	enum ComparisonResult {
		/*! All parameters are identical (Caution: rounding errors!), except maybe the ID. */
		Equal,
		/*! All critical parameters are identical, yet some metadata (name etc.) may be different. */
		OnlyMetaDataDiffers,
		/*! Objects are completely different (at least one critical parameter differs). */
		Different
	};

	/*! Virtual destructor, definition is in VICUS_Material.cpp. */
	virtual ~AbstractDBElement();

	/*! Comparison of database element by content, without ID. */
	virtual ComparisonResult equal(const AbstractDBElement * other) const = 0;

	/* If true, this is a built-in DB element and cannot be modified/removed. */
	bool m_builtIn = false;
};

} // namespace VICUS

#endif // VICUS_AbstractDBElementH
