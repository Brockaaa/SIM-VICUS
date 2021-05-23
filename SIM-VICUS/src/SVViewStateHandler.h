/*	SIM-VICUS - Building and District Energy Simulation Tool.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Dirk Weiss  <dirk.weiss -[at]- tu-dresden.de>
	  Stephan Hirth  <stephan.hirth -[at]- tu-dresden.de>
	  Hauke Hirsch  <hauke.hirsch -[at]- tu-dresden.de>

	  ... all the others from the SIM-VICUS team ... :-)

	This program is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#ifndef SVViewStateHandlerH
#define SVViewStateHandlerH

#include <QObject>

#include "SVViewState.h"

namespace Vic3D {
	class NewGeometryObject;
	class CoordinateSystemObject;
	class WireFrameObject;
}

class SVNavigationTreeWidget;
class SVPropEditGeometry;
class SVPropVertexListWidget;
class SVGeometryView;
class SVPropModeSelectionWidget;
class SVLocalCoordinateView;

/*! This singleton makes the current UI view state available to all.
	Widgets that need to be informed from view state changes, should
	connect to stateChanged() signal.
*/
class SVViewStateHandler : public QObject {
	Q_OBJECT
public:
	SVViewStateHandler(QObject * parent = nullptr);
	~SVViewStateHandler();

	/*! Returns the instance of the singleton. */
	static SVViewStateHandler & instance();

	/*! Returns the current view state. */
	const SVViewState & viewState() const { return m_viewState; }

	/*! Sets/changes a view state.
		This function creates a backup copy of the previous view state, to be restored
		after an interleaving function.
	*/
	void setViewState(const SVViewState & newViewState);

	/*! Restores the last viewstate that was set before the current view state. */
	void restoreLastViewState();

	/*! Call this function after modifying database elements that affect coloring. This is needed since
		scene view and property widgets only listen to project data changes, and database elements do not belong
		to the project.
	*/
	void refreshColors();

	/*! Pointer to geometry view object - so that we can give focus to the scene view when we start a drawing operation. */
	SVGeometryView						*m_geometryView		= nullptr;

	/*! Caches pointer to new geometry object, to allow direct access to object when
		adding/removing vertexes.
		The pointer is set in constructor of Vic3D::NewGeometryObject, object is not owned.
		DO NOT DELETE the object or do any other crazy stuff with this pointer!
	*/
	Vic3D::NewGeometryObject			*m_newGeometryObject = nullptr;

	/*! Caches pointer to the coordinate system object, to allow direct access to object when removing vertexes.
		The pointer is set in constructor of Vic3D::CoordinateSystemObject, object is not owned.
		DO NOT DELETE the object or do any other crazy stuff with this pointer!
	*/
	Vic3D::CoordinateSystemObject		*m_coordinateSystemObject = nullptr;

	/*! Caches pointer to the object containing/showing selected geometry.
		The pointer is set in constructor of Vic3D::WireFrameObject, object is not owned.
		DO NOT DELETE the object or do any other crazy stuff with this pointer!
	*/
	Vic3D::WireFrameObject				*m_selectedGeometryObject = nullptr;

	/*! Pointer to navigation tree widget - can be used to retrieve the currently selected node
		from property widgets.
	*/
	SVNavigationTreeWidget				*m_navigationTreeWidget = nullptr;

	/*! Pointer to geometry edit widget - is needed to set the absolute scale factor ( bounding box) on selection change. */
	SVPropEditGeometry					*m_propEditGeometryWidget = nullptr;

	/*! Pointer to local coordinate system view widget (shown in tool bar), only visible when local coordinate system is shown. */
	SVLocalCoordinateView				*m_localCoordinateViewWidget = nullptr;

	/*! Pointer to "place vertex" widget - is needed to clear the vertex list when a new polygon/geometrical object is being drawn. */
	SVPropVertexListWidget				*m_propVertexListWidget = nullptr;

	/*! Pointer to property mode selection widget - can be used to query required view state properties
		when switching edit modes.
	*/
	SVPropModeSelectionWidget			*m_propModeSelectionWidget = nullptr;

signals:
	/*! Emitted, when the state has changed. */
	void viewStateChanged();

	/*! Signal is emitted when a view should update its content because of color changes (or in the case of network
		properties, also because of geometry changes).
	*/
	void colorRefreshNeeded();

private:
	/*! The global pointer to the SVViewStateHandler object.
		This pointer is set in the constructor, and cleared in the destructor.
	*/
	static SVViewStateHandler			*m_self;

	/*! Contains the current view state. */
	SVViewState							m_viewState;
	/*! Contains the previous view state (so that is can be restored when an interleaving mode has ended). */
	SVViewState							m_previousViewState;
};

#endif // SVViewStateHandlerH
