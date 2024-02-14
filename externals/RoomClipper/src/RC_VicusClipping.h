/*	The RoomClipper data model library.

	Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Stephan Hirth     <stephan.hirth -[at]- tu-dresden.de>
	  Dirk Weiß         <dirk.weis     -[at]- tu-dresden.de>

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

#ifndef RCProjectH
#define RCProjectH

#include <VICUS_Project.h>

#include <clipper.hpp>

#include <IBK_NotificationHandler.h>
#include <IBK_StopWatch.h>

#include "RC_ClippingSurface.h"
#include "RC_ClippingPolygon.h"
#include "RC_Constants.h"


namespace RC {

/*! Class for VICUS Clipping. Contains all necessairy data and functionality needed to perform smart clipping. */
class VicusClipper {
public:

	/*! C'tor. */
	VicusClipper(const std::vector<VICUS::Building> &buildings, const std::vector<VICUS::ComponentInstance> &cis,
				 double normalDeviationInDeg, double maxDistanceOfSurfaces, unsigned int lastUnusedID, bool onlySelected = false):
		m_vicusBuildings(buildings),
		m_vicusCompInstances(cis),
		m_normalDeviationInDeg(normalDeviationInDeg),
		m_maxDistanceOfSurfaces(maxDistanceOfSurfaces),
		m_onlySelected(onlySelected),
		m_nextVicusId(lastUnusedID)
	{
		for(VICUS::Building &b : m_vicusBuildings)
			b.updateParents();

		m_vicusBuildingsClipped = m_vicusBuildings;
	}

	/*! Enum to hold all predefined components. */
	enum PredefinedComponentType {
		PDC_Ceiling,
		PDC_Floor,
		PDC_Roof,
		PDC_InteriorWall,
		PDC_ExteriorWall,
		NUM_PDC
	};

	/*! Add Polygons to Main Diffs or Intersections. */
	void addClipperPolygons(const std::vector<ClippingPolygon> &polysTemp, std::vector<ClippingPolygon> &mainDiffsTemp);

	/*! Finds all corresponding parallel surfaces for clipping operations. */
	void findParallelSurfaces(IBK::Notification * notify);

	/*! Finds all corresponding surfaces in range for clipping. */
	void findSurfacesInRange(IBK::Notification * notify);

	/*! Surfaces are clipped by their corresponding surfaces sorted by distance. */
	void clipSurfaces(IBK::Notification *notify);

	/*! Component Instances are beeing created by cutting all produced surfaces by clipper lib. */
	void createComponentInstances(IBK::Notification * notify, bool createConnections = true, bool replaceAllComponentInstances = false);

	/*! Finds the corresponding component instance of specified surface by id. */
	unsigned int findComponentInstanceForSurface(const VICUS::Surface &s, bool coupledSurface = false, bool replaceComponentInstance = false);

	/*! Generates a unique name for every Surface
		Surf01 is cut into 3 pieces --> name will be Surf01 [1] Surf01 [2] Surf01 [3]
	*/
	QString generateUniqueName(QString name);

	/*! Sets the Standard constructions. */
	void setStandardConstruction(PredefinedComponentType pdcType, unsigned int id);

	/*! Returns all clipped vicus buildings. */
	const std::vector<VICUS::Building> vicusBuildings() const;

	/*! Returns all clipped vicus component instances. */
	const std::vector<VICUS::ComponentInstance> *vicusCompInstances() const;

	/*! Set project for handling of surface components. */
	void setPrj(const VICUS::Project &newPrj);

	/*! Returns all clipped vicus buildings. */
	const std::vector<VICUS::SubSurfaceComponentInstance> *vicusSubSurfCompInstances() const;

private:
	/*! Returns the containing Clipping Surface with VICUS Surface from m_clippingSurfaces. */
	ClippingSurface & findClippingSurface(unsigned int id, const std::vector<VICUS::Building> &buildings);

	const VICUS::Surface &findVicusSurface(unsigned int id, const std::vector<VICUS::Building> &buildings);

	/*! Performs the Clipping of the surfaces 'surf' and 'otherSurf' and returns intersection and difference polygons. */
	void doClipperClipping(const ClippingPolygon &surf,
						   const ClippingPolygon &otherSurf,
						   std::vector<ClippingPolygon> &mainDiffs,
						   std::vector<ClippingPolygon> &mainIntersections,
						   bool normalInterpolation = false);


	/*! Find corresponding component. */
	void findCorrespondingComponent();

	/*! Create a clipper lib path from a IBKMK polygon. */
	ClipperLib::Path convertVec2DToClipperPath(const std::vector<IBKMK::Vector2D> &vertexes);

	/*! Check whether the clipper polygon is the same. */
	bool isSamePolygon(const ClipperLib::Path &diff, const ClipperLib::Path &intersection);

	/*! Check whether an intersection is an hole. */
	bool isIntersectionAnHole(const ClipperLib::Path &pathIntersection, const ClipperLib::PolyNodes &diffs);

	/*! Convert Clipper path ti Verctor 2D. */
	std::vector<IBKMK::Vector2D> convertClipperPathToVec2D(const ClipperLib::Path &path);

	/*! Add Surfaces to Clipping Polygons. */
	void addSurfaceToClippingPolygons(const VICUS::Surface &surf, std::vector<ClippingPolygon> &clippingPolygons);

	// ***** PRIVATE MEMBER VARIABLES *****

	VICUS::Project									m_prj;						///< Copy of VICUS Project

	std::vector<VICUS::Building>					m_vicusBuildings;			///< Original VICUS buildings
	std::vector<VICUS::Building>					m_vicusBuildingsClipped;	///< VICUS buildings with newly added data


	std::vector<VICUS::ComponentInstance>			m_vicusCompInstances;		///< VICUS component instances

	std::vector<VICUS::SubSurfaceComponentInstance> m_vicusSubSurfCompInstances;///< VICUS Sub surface component instances

	double											m_normalDeviationInDeg;		///< normal deviation in DEG

	double											m_maxDistanceOfSurfaces;	///< maximal distance of the search radius for clipping in m

	/*! holds all parallel surfaces by id; second element in pair is the distance in m. */
	std::vector<ClippingSurface>					m_clippingSurfaces;

	/*! Take only selected polygons. */
	bool											m_onlySelected = false;

	/*! Name map of surfaces. ID is root-name of surface stripper of any [x] and value is its count. */
	std::map<QString, unsigned int>					m_nameMap;

	/*! Clipping connections
		\param key is vicus surface id
		\param values ids of all other possible vicus surfaces for clipping
	*/
	std::map<unsigned int, std::set<unsigned int>>	m_surfaceConnections;

	unsigned int									m_nextVicusId;				///< last unused id in vicus project

	std::map<unsigned int, unsigned int>			m_compInstOriginSurfId;		///< key is new created surface id, value is old surface ci id

	IBK::StopWatch									m_stopWatch;				///< Stopwatch for updating progress-bar

	/*! Predefined components for all clipping operations.
		Will be taken if surfaces do not contain any component instance prior to
		the clipping process.
	*/
	IDType											m_predefinedComponents[PredefinedComponentType::NUM_PDC];

};
}

#endif // RCProjectH
