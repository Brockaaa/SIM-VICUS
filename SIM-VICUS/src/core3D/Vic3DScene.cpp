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

#include "Vic3DScene.h"

#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QCursor>
#include <QPalette>

#include <VICUS_Project.h>
#include <QtExt_Conversions.h>
#include <VICUS_ViewSettings.h>
#include <VICUS_NetworkLine.h>
#include <QtExt_Conversions.h>

#include <IBKMK_3DCalculations.h>

#include "Vic3DShaderProgram.h"
#include "Vic3DKeyboardMouseHandler.h"
#include "Vic3DPickObject.h"
#include "Vic3DGeometryHelpers.h"
#include "Vic3DConstants.h"
#include "Vic3DSceneView.h"

#include "SVProjectHandler.h"
#include "SVPropEditGeometry.h"
#include "SVViewStateHandler.h"
#include "SVViewState.h"
#include "SVSettings.h"
#include "SVUndoTreeNodeState.h"
#include "SVUndoDeleteSelected.h"
#include "SVPropModeSelectionWidget.h"

const float TRANSLATION_SPEED = 1.2f;
const float MOUSE_ROTATION_SPEED = 0.5f;

// Size of the local coordinate system window
const int SUBWINDOWSIZE = 150;

/// \todo All: adjust the THRESHOLD based on DPI/Screenresolution or have it as user option
const float MOUSE_MOVE_DISTANCE_ORBIT_CONTROLLER = 5;

namespace Vic3D {

void Scene::create(SceneView * parent, std::vector<ShaderProgram> & shaderPrograms) {
	m_parent = parent;
	m_gridShader = &shaderPrograms[SHADER_GRID];
	m_surfaceNormalsShader = &shaderPrograms[SHADER_LINES];
	m_buildingShader = &shaderPrograms[SHADER_OPAQUE_GEOMETRY];
	m_fixedColorTransformShader = &shaderPrograms[SHADER_WIREFRAME];
	m_coordinateSystemShader = &shaderPrograms[SHADER_COORDINATE_SYSTEM];
	m_transparencyShader = &shaderPrograms[SHADER_TRANSPARENT_GEOMETRY];

	// the orbit controller object is static in geometry, so it can be created already here
	m_orbitControllerObject.create(m_fixedColorTransformShader);

	// same for the coordinate system object
	m_coordinateSystemObject.create(m_coordinateSystemShader);

	// and for the small coordinate system object
	m_smallCoordinateSystemObject.create(m_coordinateSystemShader, m_transparencyShader);

	// we create the new geometry object here, but data is added once it is used
	m_newGeometryObject.create(m_fixedColorTransformShader);
	m_newSubSurfaceObject.create(m_buildingShader->shaderProgram());

	// create surface normals object already, though we update vertex buffer object later when we actually have geometry
	m_surfaceNormalsObject.create(m_surfaceNormalsShader);

	m_gridPlanes.push_back( VICUS::PlaneGeometry(VICUS::Polygon3D::T_Triangle,
												 IBKMK::Vector3D(0,0,0), IBKMK::Vector3D(1,0,0), IBKMK::Vector3D(0,1,0)) );
}


void Scene::onModified(int modificationType, ModificationInfo * /*data*/) {

	// no shader - not initialized yet, skip modified event
	if (m_gridShader == nullptr)
		return;

	bool updateGrid = false;
	bool updateNetwork = false;
	bool updateBuilding = false;
	bool updateCamera = false;
	bool updateSelection = false;
	// filter out all modification types that we handle
	SVProjectHandler::ModificationTypes mod = (SVProjectHandler::ModificationTypes)modificationType;
	switch (mod) {
		case SVProjectHandler::AllModified : {
			updateGrid = true;
			updateBuilding = true;
			updateNetwork = true;
			updateCamera = true;
			updateSelection = true;
			// clear new polygon drawing object
			m_newGeometryObject.clear();
			// set scene operation mode to "normal" if we are in place vertex mode
			SVViewState vs = SVViewStateHandler::instance().viewState();
			if (vs.m_viewMode == SVViewState::VM_GeometryEditMode) {
				vs.m_sceneOperationMode = SVViewState::NUM_OM;
				vs.m_propertyWidgetMode = SVViewState::PM_AddEditGeometry;
			}

			// clear selection object, to avoid accessing invalidated pointers
			m_selectedGeometryObject.m_selectedObjects.clear();
			SVViewStateHandler::instance().setViewState(vs);
		} break;

		case SVProjectHandler::BuildingTopologyChanged :
			refreshColors();
		break;

		case SVProjectHandler::BuildingGeometryChanged :
			updateBuilding = true;
			updateSelection = true;
			break;

		case SVProjectHandler::GridModified :
			updateGrid = true;
			break;

		case SVProjectHandler::NetworkModified :
			updateNetwork = true;
			updateSelection = true;
			break;

		case SVProjectHandler::ComponentInstancesModified : {
			const SVViewState & vs = SVViewStateHandler::instance().viewState();
			if (vs.m_viewMode == SVViewState::VM_PropertyEditMode)
				refreshColors();
			return;
		}

		case SVProjectHandler::SubSurfaceComponentInstancesModified : {
			// changes in sub-surface assignments may change the transparency of constructions, hence
			// requires a re-setup of building geometry
			updateBuilding = true;
			break;
		}

		// *** selection and visibility properties changed ***
		case SVProjectHandler::NodeStateModified : {
			// we need to implement the following logic:
			//
			// a) object is visible, but not selected -> draw object with regular geometry shader
			// b) object is visible and selected -> object is hidden from regular geometry shader but shown in wireframe object
			// c) object is not visible and either selected/not selected -> object is hidden
			//
			// In the loop below we first update the colors painted with the opaque regular geometry shaders.
			// All visible and not selected objects/surfaces (option a) will get painted with the
			// current property color.
			// In order to keep the memory transfor to the GPU small, we remember first and last vertex index to be changed
			// and only copy the affected color buffer into GPU memory.
#if 0
			// we need to update the colors of some building elements
			bool updateOpaqueGeometryNeeded = false;
			unsigned int smallestVertexIndexOpaqueGeometry = m_opaqueGeometryObject.m_vertexBufferData.size();
			unsigned int largestVertexIndexOpaqueGeometry = 0;
			bool updateNetworkGeometryNeeded = false;
			unsigned int smallestVertexIndexNetworks = m_networkGeometryObject.m_vertexBufferData.size();
			unsigned int largestVertexIndexNetworks = 0;

			// first decode the modification info object
			// we determine which objects need to be recolored and memory range needs to be pushed to the GPU
			const SVUndoTreeNodeState::ModifiedNodes * info = dynamic_cast<SVUndoTreeNodeState::ModifiedNodes *>(data);
			Q_ASSERT(info != nullptr);

			for (const std::pair<SVUndoTreeNodeState::ModifiedNodes::ObjectType, unsigned int> & modIDs : info->m_nodeIDs) {
				switch (modIDs.first) {
					case SVUndoTreeNodeState::ModifiedNodes::OT_OpaqueBuilding :
						updateOpaqueGeometryNeeded = true;
						smallestVertexIndexOpaqueGeometry = std::min(smallestVertexIndexOpaqueGeometry, modIDs.second);
						largestVertexIndexOpaqueGeometry = std::max(smallestVertexIndexOpaqueGeometry, modIDs.second);
					break;

					case SVUndoTreeNodeState::ModifiedNodes::OT_NetworkElement :
						updateNetworkGeometryNeeded = true;
						smallestVertexIndexNetworks = std::min(smallestVertexIndexNetworks, modIDs.second);
						largestVertexIndexNetworks = std::max(largestVertexIndexNetworks, modIDs.second);
					break;

					// TODO : Transparent windows
				}
			}
#endif
			// finally, transfer only the modified portion of the color buffer to GPU memory
			refreshColors(); // For now, this updates everything - works in all cases but is slow in large models

			// TODO : Andreas, performance upgrade: instead of using refreshColors() above that also
			//        regenerates the entire geometry and pushes everything to the GPU buffer,
			//        we can just modify the affected surfaces and push only the necessary changes to the GPU
#if 0
			if (updateOpaqueGeometryNeeded)
				m_opaqueGeometryObject.updateColorBuffer(smallestVertexIndexOpaqueGeometry, largestVertexIndexOpaqueGeometry-smallestVertexIndexOpaqueGeometry);
			if (updateNetworkGeometryNeeded)
				m_networkGeometryObject.updateColorBuffer(smallestVertexIndexNetworks, largestVertexIndexNetworks-smallestVertexIndexNetworks);
#endif
			// Now check if our new selection set is different from the previous selection set.
			std::set<const VICUS::Object*> selectedObjects;

			project().selectObjects(selectedObjects, VICUS::Project::SG_All, true, true);
			if (selectedObjects != m_selectedGeometryObject.m_selectedObjects)
				updateSelection = true;

			// if we have a selection, switch scene operation mode to OM_SelectedGeometry
			SVViewState vs = SVViewStateHandler::instance().viewState();
			if (vs.m_viewMode == SVViewState::VM_GeometryEditMode) {
				if (selectedObjects.empty()) {
					vs.m_sceneOperationMode = SVViewState::NUM_OM;
					vs.m_propertyWidgetMode = SVViewState::PM_AddEditGeometry;
				}
				else {
					vs.m_sceneOperationMode = SVViewState::OM_SelectedGeometry;
					// Do not modify property widget mode
				}
				SVViewStateHandler::instance().setViewState(vs);
			}

		} break;

		default:
			return; // do nothing by default
	}

	// *** initialize camera placement and model placement in the world ***

	if (updateCamera) {
		QVector3D cameraTrans = QtExt::IBKVector2QVector(SVProjectHandler::instance().viewSettings().m_cameraTranslation);
		m_camera.setTranslation(cameraTrans);
		m_camera.setRotation( SVProjectHandler::instance().viewSettings().m_cameraRotation.toQuaternion() );
	}

	// re-create grid with updated properties
	// since grid object is very small, this function also regenerates the grid line buffers and
	// uploads the data to the GPU
	if (updateGrid)
		m_gridObject.create(m_gridShader);

	if (updateSelection) {
		// update selected objects
		m_selectedGeometryObject.create(m_fixedColorTransformShader);
		m_selectedGeometryObject.updateBuffers();
	}

	if (updateBuilding) {
		// create geometry object (if already existing, nothing happens here)
		m_buildingGeometryObject.create(m_buildingShader->shaderProgram()); // Note: does nothing, if already existing

		// transfer data from building geometry to vertex array caches
		const SVViewState & vs = SVViewStateHandler::instance().viewState();
		if (vs.m_viewMode == SVViewState::VM_PropertyEditMode)
			recolorObjects(vs.m_objectColorMode, vs.m_colorModePropertyID); // only changes color set in objects
		generateBuildingGeometry();
	}

	// create network
	if (updateNetwork) {
		// In PropertyEditMode changes to the Network data usually require recoloring
		// of network objects. Hence, we recolor the objects here. Note, for buildings, re-coloring
		// operations are separate from building geometry modification operations.
		const SVViewState & vs = SVViewStateHandler::instance().viewState();
		if (vs.m_viewMode == SVViewState::VM_PropertyEditMode)
			recolorObjects(vs.m_objectColorMode, vs.m_colorModePropertyID); // only changes color set in objects
		// we use the same shader as for building elements
		m_networkGeometryObject.create(m_buildingShader->shaderProgram()); // Note: does nothing, if already existing

		// Fill vertex, color and index buffer data from network geometry and
		// transfer data to vertex array caches on GPU
		generateNetworkGeometry();
	}

	// update all GPU buffers (transfer cached data to GPU)
	if (updateBuilding || updateSelection) {
		m_buildingGeometryObject.updateBuffers();
		m_surfaceNormalsObject.updateVertexBuffers();
	}

	if (updateNetwork || updateSelection)
		m_networkGeometryObject.updateBuffers();

	// store current coloring mode
	SVViewState vs = SVViewStateHandler::instance().viewState();
	m_lastColorMode = vs.m_objectColorMode;
}


void Scene::destroy() {
	m_gridObject.destroy();
	m_orbitControllerObject.destroy();
	m_buildingGeometryObject.destroy();
	m_networkGeometryObject.destroy();
	m_selectedGeometryObject.destroy();
	m_coordinateSystemObject.destroy();
	m_smallCoordinateSystemObject.destroy();
	m_newGeometryObject.destroy();
	m_newSubSurfaceObject.destroy();
	m_surfaceNormalsObject.destroy();
}


void Scene::resize(int width, int height, qreal retinaScale) {
	float farDistance = 1000;
	// retrieve far viewing distance from project, if one exists
	if (SVProjectHandler::instance().isValid())
		farDistance = (float)SVProjectHandler::instance().viewSettings().m_farDistance;
	// the projection matrix need to be updated only for window size changes
	m_projection.setToIdentity();
	// create projection matrix, i.e. camera lens
	m_projection.perspective(
				/* vertical angle */ 45.0f,
				/* aspect ratio */   width / float(height),
				/* near */           0.1f,
				/* far */            farDistance
		);
	// Mind: do not use 0.0 for near plane, otherwise depth buffering and depth testing won't work!

	// the small view projection matrix is constant
	m_smallViewProjection.setToIdentity();
	// create projection matrix, i.e. camera lens
	m_smallViewProjection.perspective(
				/* vertical angle */ 45.0f,
				/* aspect ratio */   1, // it's a square window
				/* near */           0.1f,
				/* far */            farDistance
		);

	// update cached world2view matrix
	updateWorld2ViewMatrix();

	// update viewport
	m_viewPort = QRect(0, 0, static_cast<int>(width * retinaScale), static_cast<int>(height * retinaScale) );

	m_smallViewPort = QRect(0, 0, static_cast<int>(SUBWINDOWSIZE * retinaScale), static_cast<int>(SUBWINDOWSIZE * retinaScale) );
}


void Scene::updateWorld2ViewMatrix() {
	// transformation steps:
	//   model space -> transform -> world space
	//   world space -> camera/eye -> camera view
	//   camera view -> projection -> normalized device coordinates (NDC)
	m_worldToView = m_projection * m_camera.toMatrix(); // * m_transform.toMatrix();


	// update small coordinate system camera

	// take the current camera
	m_smallCoordinateSystemObject.m_smallViewCamera = m_camera;
	// move it into origin
	m_smallCoordinateSystemObject.m_smallViewCamera.setTranslation(QVector3D(0,0,0));
	// move 10 units backwards
	m_smallCoordinateSystemObject.m_smallViewCamera.translate( -6*m_smallCoordinateSystemObject.m_smallViewCamera.forward());
	// store in m_smallCoordinateSystemMatrix
	m_smallCoordinateSystemObject.m_worldToSmallView = m_smallViewProjection * m_smallCoordinateSystemObject.m_smallViewCamera.toMatrix();
}


bool Scene::inputEvent(const KeyboardMouseHandler & keyboardHandler, const QPoint & localMousePos, QPoint & newLocalMousePos) {
//	QPoint lastLeftButtonPos;
//	if (keyboardMouseHandler.buttonReleased(Qt::LeftButton))
//		lastLeftButtonPos = mapFromGlobal(m_keyboardMouseHandler.mouseReleasePos());
//	else
//		localMousePos = mapFromGlobal(m_keyboardMouseHandler.mouseDownPos());

	// NOTE: In this function we handle only those keyboard inputs that affect the scene navigation.
	//       Single key release events are handled in Vic3DSceneView, since they do not require repeated screen redraws.

	bool needRepaint = false;

	Transform3D oldCameraTransform = m_camera;

	// *** Keyboard navigation ***

	// translation and rotation works always (no trigger key) unless the Ctrl-key is held at the same time
	if (!keyboardHandler.keyDown(Qt::Key_Control)) {

		// Handle translations
		QVector3D translation;
		QVector3D rotationAxis;
		if (keyboardHandler.keyDown(Qt::Key_W)) 		translation += m_camera.forward();
		if (keyboardHandler.keyDown(Qt::Key_S)) 		translation -= m_camera.forward();
		if (keyboardHandler.keyDown(Qt::Key_A)) 		translation -= m_camera.right();
		if (keyboardHandler.keyDown(Qt::Key_D)) 		translation += m_camera.right();
		if (keyboardHandler.keyDown(Qt::Key_F)) 		translation -= m_camera.up();
		if (keyboardHandler.keyDown(Qt::Key_R))			translation += m_camera.up();
		if (keyboardHandler.keyDown(Qt::Key_Q))			rotationAxis = QVector3D(.0f,.0f,1.f);
		if (keyboardHandler.keyDown(Qt::Key_E))			rotationAxis = -QVector3D(.0f,.0f,1.f);

		float transSpeed = TRANSLATION_SPEED;
		if (keyboardHandler.keyDown(Qt::Key_Shift))
			transSpeed = 0.1f;
		m_camera.translate(transSpeed * translation);
		m_camera.rotate(transSpeed, rotationAxis);
	}

	// To avoid duplicate picking operation, we create the pick object here.
	// Then, when we actually need picking, we check if the pick was already executed, and then only
	// retrieve the pick result values
	PickObject pickObject(localMousePos);

	// *** Mouse ***

	newLocalMousePos = localMousePos;
	// retrieve mouse delta
	QPoint mouseDelta = keyboardHandler.mouseDelta(QCursor::pos());
//	qDebug() << mouseDelta << m_navigationMode;
	int mouse_dx = mouseDelta.x();
	int mouse_dy = mouseDelta.y();

	// if right mouse button is pressed, mouse delta is translated into first camera perspective rotations
	if (keyboardHandler.buttonDown(Qt::RightButton)) {
		// only do first-person mode, if not in any other mode
		if (m_navigationMode == NUM_NM) {
			m_navigationMode = NM_FirstPerson;
			qDebug() << "Entering first-person controller mode";
		}
		if (m_navigationMode == NM_FirstPerson) {
			// get and reset mouse delta (pass current mouse cursor position)
			const QVector3D LocalUp(0.0f, 0.0f, 1.0f); // same as in Camera::up()
			m_camera.rotate(-MOUSE_ROTATION_SPEED * mouse_dx, LocalUp);
			m_camera.rotate(-MOUSE_ROTATION_SPEED * mouse_dy, m_camera.right());
			// cursor wrap adjustment
			adjustCursorDuringMouseDrag(mouseDelta, localMousePos, newLocalMousePos, pickObject);
		}
	}

	// middle mouse button moves the geometry (panning)
	if (keyboardHandler.buttonDown(Qt::MidButton)) {
		// only do panning, if not in any other mode
		if (m_navigationMode == NUM_NM) {
			// we enter pan mode
			panStart(localMousePos, pickObject, false);
		}
		if ((mouseDelta != QPoint(0,0)) && (m_navigationMode == NM_Panning)) {

			// get the new far point, the point B'
			IBKMK::Vector3D newFarPoint = calculateFarPoint(localMousePos, m_panOriginalTransformMatrix);

			IBKMK::Vector3D BBDashVec = m_panFarPointStart-newFarPoint;
			IBKMK::Vector3D cameraTrans = m_panCABARatio*BBDashVec;

			// translate camera

			m_camera.setTranslation(QtExt::IBKVector2QVector(m_panCameraStart + cameraTrans));
			// cursor wrap adjustment
			adjustCursorDuringMouseDrag(mouseDelta, localMousePos, newLocalMousePos, pickObject);
		}
	}


	// left mouse button starts orbit controller, or performs a left-click
	if (keyboardHandler.buttonDown(Qt::LeftButton)) {
		// only do orbit controller mode, if not in any other mode
		if (m_navigationMode == NUM_NM) {

			// we may enter orbital controller mode, or start a transform operation

			// configure the pick object and pick a point on the XY plane/or any visible surface
			if (!pickObject.m_pickPerformed)
				pick(pickObject);

			// only enter orbit controller mode, if we actually hit something
			if (!pickObject.m_candidates.empty()) {
				IBKMK::Vector3D nearestPoint = pickObject.m_candidates.front().m_pickPoint;
				// if we hit the a plane, limit the orbit controller to the extends of the grid
				if (pickObject.m_candidates.front().m_snapPointType == PickObject::RT_GridPlane) {
					/// \todo Andreas: add support for several grid planes
					nearestPoint.m_x = std::min(nearestPoint.m_x, m_gridObject.m_maxGrid);
					nearestPoint.m_y = std::min(nearestPoint.m_y, m_gridObject.m_maxGrid);
					nearestPoint.m_x = std::max(nearestPoint.m_x, m_gridObject.m_minGrid);
					nearestPoint.m_y = std::max(nearestPoint.m_y, m_gridObject.m_minGrid);
				}


				// *** enter translation mode? ***
				if (pickObject.m_candidates.front().m_snapPointType == PickObject::RT_CoordinateSystemCenter) {
					m_navigationMode = NM_InteractiveTranslation;
					// Store origin of translation
					m_translateOrigin = m_coordinateSystemObject.translation();
					qDebug() << "Entering interactive translation mode";
				}

				// *** enter rotation or scale mode? ***
				else if (pickObject.m_candidates.front().m_snapPointType == PickObject::RT_AxisEndMarker) {
					// which mode is the coordinate system in?
					if (m_coordinateSystemObject.m_geometryTransformMode == Vic3D::CoordinateSystemObject::TM_RotateMask) {
						m_navigationMode = NM_InteractiveRotation;
						// which axis?
						switch (pickObject.m_candidates.front().m_uniqueObjectID) {
							case 0 :
								// rotate around z
								m_coordinateSystemObject.m_geometryTransformMode = Vic3D::CoordinateSystemObject::TM_RotateZ;
								m_rotationAxis = QtExt::QVector2IBKVector( m_coordinateSystemObject.localZAxis() );
								m_rotationVectorX = QtExt::QVector2IBKVector( m_coordinateSystemObject.localXAxis() );
								m_rotationVectorY = QtExt::QVector2IBKVector( m_coordinateSystemObject.localYAxis() );
							break;

							case 1 :
								m_coordinateSystemObject.m_geometryTransformMode = Vic3D::CoordinateSystemObject::TM_RotateX;
								m_rotationAxis = QtExt::QVector2IBKVector( m_coordinateSystemObject.localXAxis() );
								m_rotationVectorX = QtExt::QVector2IBKVector( m_coordinateSystemObject.localYAxis() );
								m_rotationVectorY = QtExt::QVector2IBKVector( m_coordinateSystemObject.localZAxis() );
							break;

							case 2 :
								m_coordinateSystemObject.m_geometryTransformMode = Vic3D::CoordinateSystemObject::TM_RotateY;
								m_rotationAxis = QtExt::QVector2IBKVector( m_coordinateSystemObject.localYAxis() );
								m_rotationVectorX = QtExt::QVector2IBKVector( m_coordinateSystemObject.localZAxis() );
								m_rotationVectorY = QtExt::QVector2IBKVector( m_coordinateSystemObject.localXAxis() );
							break;
						}

						// store original translation matrix
						m_originalRotation = m_coordinateSystemObject.transform().rotation();
						qDebug() << "Entering interactive rotation mode";
					}
				}
				else {
					// for orbit-controller, we  take the closest point of either
					m_orbitControllerOrigin = QtExt::IBKVector2QVector(nearestPoint);
					m_orbitControllerObject.m_transform.setTranslation(m_orbitControllerOrigin);

					// Rotation matrix around origin point
					m_mouseMoveDistance = 0;

					needRepaint = true;

					// Note: Orbit controller mode is enabled, once a little bit of movement took place
					m_navigationMode = NM_OrbitController;
					qDebug() << "Entering orbit controller mode, rotation around" << m_orbitControllerOrigin;
				}
			}
		}
		else {

			// ** left mouse button held and mouse dragged **
			if (mouseDelta != QPoint(0,0)) {
				// record the distance that the mouse was moved
				m_mouseMoveDistance += mouse_dx*mouse_dx + mouse_dy*mouse_dy;

				switch (m_navigationMode) {
					case Vic3D::Scene::NM_Panning:
					case Vic3D::Scene::NM_FirstPerson:
					case Vic3D::Scene::NUM_NM:
					break; // for these modes, do nothing (can happen for multi-mouse-button-press and dragging)

					case NM_OrbitController : {
						// vector from pick point (center of orbit) to camera position
						QVector3D lineOfSight = m_camera.translation() - m_orbitControllerOrigin;

						// create a transformation object
						Transform3D orbitTrans;

						// mouse x translation = rotation around rotation axis

						const QVector3D GlobalUpwardsVector(0.0f, 0.0f, 1.0f);
						// set rotation around z axis for x-mouse-delta
						orbitTrans.rotate(MOUSE_ROTATION_SPEED * mouse_dx, GlobalUpwardsVector);


						// mouse y translation = rotation around "right" axis
						int mouseInversionFactor = SVSettings::instance().m_invertYMouseAxis ? -1 : 1;

						QVector3D LocalRight = m_camera.right().normalized();
						// set rotation around "right" axis for y-mouse-delta
						orbitTrans.rotate(MOUSE_ROTATION_SPEED * mouse_dy * mouseInversionFactor, LocalRight);

						// rotate vector to camera
						lineOfSight = orbitTrans.toMatrix() * lineOfSight;

						// rotate the camera around the same angles
						m_camera.rotate(MOUSE_ROTATION_SPEED * mouse_dx, GlobalUpwardsVector);
						m_camera.rotate(MOUSE_ROTATION_SPEED * mouse_dy * mouseInversionFactor, LocalRight);

#if 1
						// fix "roll" error due to rounding
						// only do this when we are not viewing the scene from vertically from above/below
						float cosViewAngle = QVector3D::dotProduct(m_camera.forward(), GlobalUpwardsVector);
						if (std::fabs(cosViewAngle) < 0.6f) {
							// up and forward vectors should be always in a vertical plane
							// forward and z-axis form a vertical plane with normal
							QVector3D verticalPlaneNormal = QVector3D::crossProduct(m_camera.forward(), GlobalUpwardsVector);
							verticalPlaneNormal.normalize();

							// the camera right angle should always match this normal vector
							float cosBeta = QVector3D::dotProduct(verticalPlaneNormal, m_camera.right().normalized());
							if (cosBeta > -1 && cosBeta < 1) {
								float beta = std::acos(cosBeta)/3.14159265f*180;
								// which direction to rotate?
								m_camera.rotate(beta, m_camera.forward());
								float cosBeta2 = QVector3D::dotProduct(verticalPlaneNormal, m_camera.right().normalized());
								if (std::fabs(std::fabs(cosBeta2) - 1) > 1e-5f)
									m_camera.rotate(-2*beta, m_camera.forward());
								//						cosBeta2 = QVector3D::dotProduct(verticalPlaneNormal, m_camera.right().normalized());
							}
						}
#endif
						// get new camera location
						QVector3D newCamPos = m_orbitControllerOrigin + lineOfSight;
						//					qDebug() << "Moving camera from " << m_camera.translation() << "to" << newCamPos;

						// move camera
						m_camera.setTranslation(newCamPos);

						// cursor wrap adjustment
						adjustCursorDuringMouseDrag(mouseDelta, localMousePos, newLocalMousePos, pickObject);
					} break; // orbit controller active

					case NM_InteractiveTranslation: {
						// pick a point and snap to some point in the scene
						if (!pickObject.m_pickPerformed)
							pick(pickObject);

						// now we handle the snapping rules and also the locking
						snapLocalCoordinateSystem(pickObject);

				//		qDebug() << localMousePos << QtExt::IBKVector2QVector(o.m_pickPoint) << m_coordinateSystemObject.translation();

						// determine vector to snapped mouse position
						QVector3D newPoint = m_coordinateSystemObject.translation();
						// vector offset from starting point to current location
						QVector3D translationVector = newPoint - m_translateOrigin;
						// now set this in the wireframe object as translation
						m_selectedGeometryObject.m_transform.setTranslation(translationVector);
					} break;// interactive translation active

					case NM_InteractiveRotation: {
						// pick a point and snap to some point in the scene
						if (!pickObject.m_pickPerformed)
							pick(pickObject);

						// store current's coordinate system position
						IBKMK::Vector3D coordinateSystemLocation = QtExt::QVector2IBKVector( m_coordinateSystemObject.translation() );
						// snap it to the new location
						snapLocalCoordinateSystem(pickObject);
						// get point that the mouse snapped to
						IBKMK::Vector3D newPoint = QtExt::QVector2IBKVector( m_coordinateSystemObject.translation() );
						// and restore coordinate systems location
						m_coordinateSystemObject.setTranslation(QtExt::IBKVector2QVector( coordinateSystemLocation) );

						IBKMK::Vector3D projectedVector;
						IBKMK::pointProjectedOnPlane(coordinateSystemLocation, m_rotationAxis, newPoint, projectedVector);

						projectedVector.normalize();
						// now compute rotation angle to rotation x vector
						double cosBeta = m_rotationVectorX.scalarProduct(projectedVector);
						double sinGamma = m_rotationVectorY.scalarProduct(projectedVector);

						double rotAngle = 0;
						if (cosBeta > 1.0)
							rotAngle = 0;
						else if (cosBeta < -1.0)
							rotAngle = 180;
						else
							rotAngle = std::acos(cosBeta)*180/3.141569;
						// adjustment for quadrant 3 and 4
						if (sinGamma < 0)
							rotAngle = 360-rotAngle;

						// the rotation angle
						qDebug() << QtExt::IBKVector2String(newPoint) << QtExt::IBKVector2String(projectedVector) << cosBeta << sinGamma << rotAngle;

						std::vector<const VICUS::Surface*> selSurfaces;

						project().selectedSurfaces(selSurfaces, VICUS::Project::SG_All);

						IBKMK::Vector3D center, newCenter;
						IBKMK::Vector3D boundingBoxDimensions = project().boundingBox(selSurfaces, center);

						QQuaternion q = QQuaternion::fromAxisAndAngle( QtExt::IBKVector2QVector(m_rotationAxis), rotAngle);

						Vic3D::Transform3D trans3D;
						trans3D.setTranslation( QtExt::IBKVector2QVector(center) );

						q = m_originalRotation*q;

						newCenter = QtExt::QVector2IBKVector( q.rotatedVector( QtExt::IBKVector2QVector(center) ) );

						m_coordinateSystemObject.setRotation(q);
//						m_coordinateSystemObject.setTranslation(QtExt::IBKVector2QVector(center-newCenter) );

						// now set this in the wireframe object as translation
						m_selectedGeometryObject.m_transform.setRotation(q);
						m_selectedGeometryObject.m_transform.setTranslation(QtExt::IBKVector2QVector(center-newCenter) );

#if 0
						// we find the rotation axis by taking the cross product of the normal vector and the normal vector we want to
						// rotate to
						IBKMK::Vector3D rotationAxis ( m_normal.crossProduct(newNormal) );

						Vic3D::Transform3D rota;
						// we now also have to find the angle between both normals
						rota.rotate((float)angleBetweenVectorsDeg(m_normal, newNormal), QtExt::IBKVector2QVector(rotationAxis) );

						// we take the QQuarternion to rotate
						QQuaternion centerRota = rota.rotation();
						QVector3D newCenter = centerRota.rotatedVector(QtExt::IBKVector2QVector(m_boundingBoxCenter) );

						// we also have to find the center point after rotation and translate our center back to its origin
						rota.setTranslation(QtExt::IBKVector2QVector(m_boundingBoxCenter) - newCenter );

						// we give our tranfsformation to the wire frame object
						SVViewStateHandler::instance().m_selectedGeometryObject->m_transform = rota;
						const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderNow();
						const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();
#endif

					} break;// interactive translation active
				} // switch
			} // mouse dragged
		}

	} // left button down


	// *** mouse button release ***

	if (keyboardHandler.buttonReleased(Qt::LeftButton)) {

		// check if the mouse was moved not very far -> we have a mouse click
		if (m_mouseMoveDistance < MOUSE_MOVE_DISTANCE_ORBIT_CONTROLLER) {
			handleLeftMouseClick(keyboardHandler, pickObject);
			needRepaint = true;
		}
		if (m_navigationMode == NM_OrbitController) {
			qDebug() << "Leaving orbit controller mode";
			needRepaint = true;
		}
		if (m_navigationMode == NM_InteractiveTranslation) {
			qDebug() << "Leaving interactive translation mode";
			SVViewStateHandler::instance().m_propEditGeometryWidget->translate();
			needRepaint = true;
		}
		if (m_navigationMode == NM_InteractiveRotation) {
			qDebug() << "Leaving interactive rotation mode";
			SVViewStateHandler::instance().m_propEditGeometryWidget->rotate();
			needRepaint = true;
		}
		// clear orbit controller flag
		m_navigationMode = NUM_NM;

	} // left button released

	if (keyboardHandler.buttonReleased(Qt::MidButton)) {
		if (m_navigationMode == NM_Panning) {
			qDebug() << "Leaving panning mode";
			m_navigationMode = NUM_NM;
			m_panObjectDepth = 0.01; // reset pan object depth
		}
	}

	if (keyboardHandler.buttonReleased(Qt::RightButton)) {
		if (m_navigationMode == NM_FirstPerson) {
			qDebug() << "Leaving first-person controller mode";
			m_navigationMode = NUM_NM;
		}
	}


	// scroll wheel does fast zoom in/out
	int wheelDelta = keyboardHandler.wheelDelta();
	if (wheelDelta != 0) {

		// configure the pick object and pick a point on the XY plane/or any visible surface
		if (!pickObject.m_pickPerformed)
			pick(pickObject);

		// move forward along camera's forward vector
#ifdef Q_OS_MAC
		if (wheelDelta > 2)
			wheelDelta = 2;
		if (wheelDelta < -2)
			wheelDelta = -2;
#endif
		double transSpeed = 5.;
		if (keyboardHandler.keyDown(Qt::Key_Shift))
			transSpeed *= 0.1;
		if (!pickObject.m_candidates.empty()) {
			// 2% of translation distance from camera to selected object
			IBKMK::Vector3D moveDist = 0.05*pickObject.m_candidates.front().m_depth*pickObject.m_lineOfSightDirection;
			double transDist = moveDist.magnitude();
			if (transDist < transSpeed) {
				moveDist *= transSpeed/(transDist+1e-8);
			}
			// move camera along line of sight towards selected object
			m_camera.translate(QtExt::IBKVector2QVector(wheelDelta*moveDist));
		}
		else {
			m_camera.translate(wheelDelta * (float)transSpeed * m_camera.forward());
		}
	}

	// store camera position in view settings, but only if we have a project
	// Note: the check is necessary, because the paint event may be called as part of closing the window
	//       and updating the UI to the "no project" state
	if (SVProjectHandler::instance().isValid()) {
		SVProjectHandler::instance().viewSettings().m_cameraTranslation = QtExt::QVector2IBKVector(m_camera.translation());
		SVProjectHandler::instance().viewSettings().m_cameraRotation = m_camera.rotation();
	}
	updateWorld2ViewMatrix();
	// end of camera movement


	// *** adjusting the local coordinate system ***

	QVector3D oldPos = m_coordinateSystemObject.translation();
	// if in "place vertex" mode, perform picking operation and snap coordinate system to grid
	if (SVViewStateHandler::instance().viewState().m_sceneOperationMode == SVViewState::OM_PlaceVertex ||
		SVViewStateHandler::instance().viewState().m_sceneOperationMode == SVViewState::OM_MoveLocalCoordinateSystem)
	{
		// follow line of sign and determine possible objects to hit
		if (!pickObject.m_pickPerformed)
			pick(pickObject);

		// now we handle the snapping rules and also the locking
		snapLocalCoordinateSystem(pickObject);

		needRepaint = true;
//		qDebug() << localMousePos << QtExt::IBKVector2QVector(o.m_pickPoint) << m_coordinateSystemObject.translation();

		// update the movable coordinate system's location in the new polygon object
		QVector3D newPoint = m_coordinateSystemObject.translation();
		if (SVViewStateHandler::instance().viewState().m_sceneOperationMode == SVViewState::OM_PlaceVertex)
			m_newGeometryObject.updateLocalCoordinateSystemPosition(newPoint);
	}

	// if in "align coordinate system mode" perform picking operation and update local coordinate system orientation
	if (SVViewStateHandler::instance().viewState().m_sceneOperationMode == SVViewState::OM_AlignLocalCoordinateSystem) {
		// follow line of sign and determine possible objects to hit
		if (!pickObject.m_pickPerformed)
			pick(pickObject);
		needRepaint = true;


		// get nearest match; look for an object
		IBKMK::Vector3D nearestPoint;
		bool found = false;
		unsigned int uniqueID = 0;
		for (const PickObject::PickResult & r : pickObject.m_candidates) {
			if (r.m_snapPointType == PickObject::RT_Object) {
				nearestPoint = r.m_pickPoint;
				uniqueID = r.m_uniqueObjectID;
				found = true;
				break;
			}
		}
		// no object found, try a plane
		if (!found) {
			for (const PickObject::PickResult & r : pickObject.m_candidates) {
				if (r.m_snapPointType == PickObject::RT_GridPlane) {
					nearestPoint = r.m_pickPoint;
					uniqueID = r.m_uniqueObjectID;
					found = true;
					break;
				}
			}
		}
		// did we hit anything?
		if (found) {
			// object found?
			if (uniqueID != 0) {
				// lookup object
				const VICUS::Object * obj = project().objectById(uniqueID);
				// should be a surface
				const VICUS::Surface * s = dynamic_cast<const VICUS::Surface *>(obj);
				// but maybe a nullptr, if we hit a sphere/cylinder from a network object
				if (s != nullptr) {
					// now get normal vector
					IBKMK::Vector3D n = s->geometry().normal();
					// get also local X and Y vectors
					IBKMK::Vector3D localX = s->geometry().localX();
					IBKMK::Vector3D localY = s->geometry().localY();
					// compose rotation angle from global to local system via the following math:
					// we have local system axes x,y,z and global axes g1, g2, g3
					// and the rotation matrix R should do:
					//  R(g1) = x,  R(g2) = y, R(g3) = z
					//
					// now, if we describe a body axis like:
					//  x = B11.g1 + B21.g2 + B31.g3
					//  y = B11.g1 + B21.g2 + B31.g3
					//  z = B11.g1 + B21.g2 + B31.g3
					//
					// or in matrix writing
					//  R[1,0,0] = [B11, B21, B31]
					//
					// each of the columns of the rotation matrix is the normalized local coordinate axis
					//
					// now build the rotation matrix
		//			QMatrix3x3 R;
		//			float * r = R.data();
		//			*(QVector3D*)r = QtExt::IBKVector2QVector(localX.normalized());
		//			r+=3;
		//			*(QVector3D*)r = QtExt::IBKVector2QVector(localY.normalized());
		//			r+=3;
		//			*(QVector3D*)r = QtExt::IBKVector2QVector(n.normalized());
		//			qDebug() << R;
		//			QQuaternion q = QQuaternion::fromRotationMatrix(R);
		//			qDebug() << q;

					// or use the ready-made Qt function (which surprisingly gives the same result :-)
					QQuaternion q2 = QQuaternion::fromAxes(QtExt::IBKVector2QVector(localX.normalized()),
														   QtExt::IBKVector2QVector(localY.normalized()),
														   QtExt::IBKVector2QVector(n.normalized()));
		//			qDebug() << q2;
					m_coordinateSystemObject.setRotation(q2);
				}
			}
			else {
				// restore to global orientation
				m_coordinateSystemObject.setRotation(QQuaternion());
			}

			m_coordinateSystemObject.setTranslation( QtExt::IBKVector2QVector(nearestPoint) );
		}
	}


	// determine if we actually need a repaint: this is normally only necessary of the camera or
	// the local coordinate system were moved
	if (oldPos != m_coordinateSystemObject.translation() || needRepaint ||
			m_camera.translation() != oldCameraTransform.translation() ||
			m_camera.rotation() != oldCameraTransform.rotation())
	{
		return true;
	}
	return false;
}


void Scene::render() {
	// we must have a valid project to render
	Q_ASSERT(SVProjectHandler::instance().isValid());

	glViewport(m_viewPort.x(), m_viewPort.y(), m_viewPort.width(), m_viewPort.height());

	// set the background color = clear color
	const SVSettings::ThemeSettings & s = SVSettings::instance().m_themeSettings[SVSettings::instance().m_theme];
	QVector3D backgroundColor = QtExt::QVector3DFromQColor(s.m_sceneBackgroundColor);

	glClearColor(backgroundColor.x(), backgroundColor.y(), backgroundColor.z(), 1.0f);

	QVector3D viewPos = m_camera.translation();

	const SVViewState & vs = SVViewStateHandler::instance().viewState();

	// enable depth testing, important for the grid and for the drawing order of several objects
	// needed for all opaque geometry
	glEnable(GL_DEPTH_TEST);
	// enable depth mask update (only disabled for transparent geometry)
	glDepthMask(GL_TRUE);
	// turn off culling
	glDisable(GL_CULL_FACE);


	// --- Fixed Transform Shader Enabled ---

	m_fixedColorTransformShader->bind();
	m_fixedColorTransformShader->shaderProgram()->setUniformValue(m_fixedColorTransformShader->m_uniformIDs[0], m_worldToView);

	// *** selection object ***

	// do not render, if in subsurface mode
	if (vs.m_propertyWidgetMode != SVViewState::PM_AddSubSurfaceGeometry)
		m_selectedGeometryObject.render(); // might do nothing, if nothing is selected

	// *** orbit controller indicator ***

	if (m_navigationMode == NM_OrbitController && m_mouseMoveDistance > MOUSE_MOVE_DISTANCE_ORBIT_CONTROLLER) {
		// Note: uses also m_fixedColorTransformShader, which is already active with up-to-date worldToView matrix
		m_orbitControllerObject.render();
	}

	// *** new geometry object (opqaue lines) ***

	m_newGeometryObject.renderOpaque(); // might do nothing, if no geometry is being edited

	m_fixedColorTransformShader->release();

	// --- Fixed Transform Shader Disabled ---



	// *** opaque background geometry ***

	// tell OpenGL to show only faces whose normal vector points towards us
	glEnable(GL_CULL_FACE);

	// *** opaque building geometry ***

	m_buildingShader->bind();
	m_buildingShader->shaderProgram()->setUniformValue(m_buildingShader->m_uniformIDs[0], m_worldToView);

	// Note: you can't use a QColor here directly and pass it as uniform to a shader expecting a vec3. Qt internally
	//       passes QColor as vec4. Use the converter QtExt::QVector3DFromQColor() for that.
	m_buildingShader->shaderProgram()->setUniformValue(m_buildingShader->m_uniformIDs[2], QtExt::QVector3DFromQColor(m_lightColor));

	// set view position
	m_buildingShader->shaderProgram()->setUniformValue(m_buildingShader->m_uniformIDs[1], viewPos);

//#define FIXED_LIGHT_POSITION
#ifdef FIXED_LIGHT_POSITION
	// use a fixed light position
	m_buildingShader->shaderProgram()->setUniformValue(m_buildingShader->m_uniformIDs[1], m_lightPos);
#else
	// use view position as light position
	m_buildingShader->shaderProgram()->setUniformValue(m_buildingShader->m_uniformIDs[3], viewPos);
#endif // FIXED_LIGHT_POSITION

	// render network geometry
	m_networkGeometryObject.renderOpaque();

	// render opaque part of building geometry
	m_buildingGeometryObject.renderOpaque();

	// render opaque part of new sub-surface object
	if (vs.m_propertyWidgetMode == SVViewState::PM_AddSubSurfaceGeometry)
		m_newSubSurfaceObject.renderOpaque(); // might do nothing, if no sub-surface is being created

	m_buildingShader->release();

	// *** surface normals

	if (m_surfaceNormalsVisible) {
		m_surfaceNormalsShader->bind();
		m_surfaceNormalsShader->shaderProgram()->setUniformValue(m_surfaceNormalsShader->m_uniformIDs[0], m_worldToView);
		m_surfaceNormalsObject.render();
		m_surfaceNormalsShader->release();
	}

	// *** grid ***

	if (m_gridVisible) {
		m_gridShader->bind();
		m_gridShader->shaderProgram()->setUniformValue(m_gridShader->m_uniformIDs[0], m_worldToView);
		m_gridShader->shaderProgram()->setUniformValue(m_gridShader->m_uniformIDs[2], backgroundColor);
		float farDistance = (float)std::max(500., SVProjectHandler::instance().viewSettings().m_farDistance);
		m_gridShader->shaderProgram()->setUniformValue(m_gridShader->m_uniformIDs[3], farDistance);
		m_gridObject.render();
		m_gridShader->release();
	}

	// *** transparent geometry ***

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// tell OpenGL to show all planes
	glDisable(GL_CULL_FACE);
	// disable update of depth test but still use it
	glDepthMask (GL_FALSE);


	// ... windows, ...
	m_buildingShader->bind();
	if (m_buildingGeometryObject.canDrawTransparent() != 0) {
		m_buildingGeometryObject.renderTransparent();
	}
	if (vs.m_propertyWidgetMode == SVViewState::PM_AddSubSurfaceGeometry)
		m_newSubSurfaceObject.renderTransparent(); // might do nothing, if no subsurface is being constructed
	m_buildingShader->release();


	// *** new polygon draw object (transparent plane) ***

	if (m_newGeometryObject.canDrawTransparent() != 0) {
		m_fixedColorTransformShader->bind();
		// Note: worldToView uniform has already been set
		m_newGeometryObject.renderTransparent();
		m_fixedColorTransformShader->release();
	}

	// turn off blending
	glDisable(GL_BLEND);
	// re-enable updating of z-buffer
	glDepthMask(GL_TRUE);
	// tell OpenGL to turn on culling
	glEnable(GL_CULL_FACE);

	// clear depth buffer because we want to paint on top of all
	glClear(GL_DEPTH_BUFFER_BIT);

	// *** movable coordinate system  ***

	bool drawLocalCoordinateSystem = (vs.m_sceneOperationMode == SVViewState::OM_PlaceVertex ||
		vs.m_sceneOperationMode == SVViewState::OM_SelectedGeometry ||
		vs.m_sceneOperationMode == SVViewState::OM_AlignLocalCoordinateSystem ||
		vs.m_sceneOperationMode == SVViewState::OM_MoveLocalCoordinateSystem );

	// do not draw LCS if we are in sub-surface mode
	if (vs.m_propertyWidgetMode == SVViewState::PM_AddSubSurfaceGeometry)
		drawLocalCoordinateSystem = false;
	if (drawLocalCoordinateSystem) {
		m_coordinateSystemShader->bind();

		// When we translate/rotate the local coordinate system, we actually move the world with respect to the camera
		// by left-multiplying the model2world matrix with the coordinate system object.

		// Suppose the local coordinate system shall be located at 20,0,0 and the camera looks at the coordinate
		// system's origin from 20,-40,2. Now, inside the shader, all coordinates are multiplied by the
		// model2world matrix, which basically moves all coordinates +20 in x direction. Now light and view position
		// (the latter only being used to compute the phong shading) are at 40, -40, 2, wheras the local coordinate
		// system is moved from local 0,0,0 to the desired 20,0,0.
		// Consequently, the light and view position cause the phong shader to draw the sphere as if lighted slightly
		// from the direction of positive x.

		// To fix this, we translate/rotate the view/light position inversely to the model2world transformation and
		// this revert the effect introduced by the model2world matrix on the light/view coordinates.
		QVector3D translatedViewPos = m_coordinateSystemObject.inverseTransformationMatrix() * viewPos;
//		qDebug() << viewPos << m_coordinateSystemObject.translation();

		m_coordinateSystemShader->shaderProgram()->setUniformValue(m_coordinateSystemShader->m_uniformIDs[0], m_worldToView);
		m_coordinateSystemShader->shaderProgram()->setUniformValue(m_coordinateSystemShader->m_uniformIDs[1], translatedViewPos); // lightpos
		m_coordinateSystemShader->shaderProgram()->setUniformValue(m_coordinateSystemShader->m_uniformIDs[2], QtExt::QVector3DFromQColor(m_lightColor));
		m_coordinateSystemShader->shaderProgram()->setUniformValue(m_coordinateSystemShader->m_uniformIDs[3], translatedViewPos); // viewpos
		m_coordinateSystemObject.renderOpaque();
		m_coordinateSystemShader->release();
	}

	// clear depth buffer because we want to paint on top of all
	glClear(GL_DEPTH_BUFFER_BIT);
	// turn on blending
	glEnable(GL_BLEND);

	if (m_smallCoordinateSystemObjectVisible) {
		glViewport(m_smallViewPort.x(), m_smallViewPort.y(), m_smallViewPort.width(), m_smallViewPort.height());

		// blending is still enabled, so that should work
		m_smallCoordinateSystemObject.render();
	}
}


void Scene::setViewState(const SVViewState & vs) {
	// if we are currently constructing geometry, and we switch the view mode to
	// "Parameter edit" mode, reset the new polygon object
	bool colorUpdateNeeded = false;
	if (vs.m_viewMode == SVViewState::VM_PropertyEditMode) {
		m_newGeometryObject.clear();
		// update scene coloring if in property edit mode
		if (m_lastColorMode != vs.m_objectColorMode ||
			m_lastColorObjectID != vs.m_colorModePropertyID)
		{
			colorUpdateNeeded = true;
		}
	}
	else {
		Q_ASSERT(vs.m_objectColorMode == SVViewState::OCM_None);
		if (m_lastColorMode != vs.m_objectColorMode) {
			colorUpdateNeeded = true;
		}
	}
	if (colorUpdateNeeded) {

		// different update handling
		bool updateBuilding = false;
		bool updateNetwork = false;
		if (m_lastColorMode > 0 && m_lastColorMode < SVViewState::OCM_Network)
			updateBuilding = true;
		if (vs.m_objectColorMode > 0 && vs.m_objectColorMode < SVViewState::OCM_Network)
			updateBuilding = true;
		if (m_lastColorMode >= SVViewState::OCM_Network)
			updateNetwork = true;
		if (vs.m_objectColorMode >= SVViewState::OCM_Network)
			updateNetwork = true;

		// update the color properties in the data objects (does not update GPU memory!)
		recolorObjects(vs.m_objectColorMode, vs.m_colorModePropertyID);

		if (updateBuilding) {
			qDebug() << "Updating surface coloring of buildings";
			generateBuildingGeometry();
			// TODO : Andreas, Performance update, only update affected part of color buffer
			m_buildingGeometryObject.updateColorBuffer();
		}
		if (updateNetwork) {
			qDebug() << "Updating surface coloring of networks";
			// TODO : Andreas, Performance update, only update and transfer color buffer
			generateNetworkGeometry();
			m_networkGeometryObject.updateBuffers();
		}

		m_lastColorMode = vs.m_objectColorMode;
		m_lastColorObjectID = vs.m_colorModePropertyID;
	}
}


void Scene::refreshColors() {
	Q_ASSERT(SVProjectHandler::instance().isValid()); // must have a valid project

	const SVViewState & vs = SVViewStateHandler::instance().viewState();
	recolorObjects(vs.m_objectColorMode, vs.m_colorModePropertyID);
//	if (vs.m_objectColorMode > SVViewState::OCM_None && vs.m_objectColorMode < SVViewState::OCM_Network) {
		qDebug() << "Updating surface coloring of buildings";
		// TODO : Andreas, Performance update, only update and transfer color buffer
		generateBuildingGeometry();
		m_buildingGeometryObject.updateColorBuffer();
//	}
//	else if (vs.m_objectColorMode >= SVViewState::OCM_Network) {
		qDebug() << "Updating surface coloring of networks";
		// TODO : Andreas, Performance update, only update and transfer color buffer
		generateNetworkGeometry();
		m_networkGeometryObject.updateBuffers();
//	}
}


void Scene::generateBuildingGeometry() {
	QElapsedTimer t;
	t.start();
	// get VICUS project data
	const VICUS::Project & p = project();

	// we rebuild the entire geometry here, so this may be slow

	// clear out existing cache

	m_buildingGeometryObject.m_vertexBufferData.clear();
	m_buildingGeometryObject.m_colorBufferData.clear();
	m_buildingGeometryObject.m_indexBufferData.clear();
	m_buildingGeometryObject.m_vertexStartMap.clear();

	m_buildingGeometryObject.m_vertexBufferData.reserve(100000);
	m_buildingGeometryObject.m_colorBufferData.reserve(100000);
	m_buildingGeometryObject.m_indexBufferData.reserve(100000);

	// we want to draw triangles
	m_buildingGeometryObject.m_drawTriangleStrips = false;

	// we now process all surfaces and add their coordinates and
	// normals

	// recursively process all buildings, building levels etc.

	const SVDatabase & db = SVSettings::instance().m_db;

	unsigned int currentVertexIndex = 0;
	unsigned int currentElementIndex = 0;

	// set collects pointers to all visible, not selected sub-surfaces
	std::vector<std::pair<const VICUS::SubSurface *, const VICUS::PlaneTriangulationData*> > transparentSubsurfaces;

	for (const VICUS::Building & b : p.m_buildings) {
		for (const VICUS::BuildingLevel & bl : b.m_buildingLevels) {
			for (const VICUS::Room & r : bl.m_rooms) {
				for (const VICUS::Surface & s : r.m_surfaces) {

					// remember where the vertexes for this surface start in the buffer
					m_buildingGeometryObject.m_vertexStartMap[s.uniqueID()] = currentVertexIndex;

					// now we store the surface data into the vertex/color and index buffers
					// the indexes are advanced and the buffers enlarged as needed.
					// actually, this adds always two surfaces (for culling).
					addSurface(s, currentVertexIndex, currentElementIndex,
							   m_buildingGeometryObject.m_vertexBufferData,
							   m_buildingGeometryObject.m_colorBufferData,
							   m_buildingGeometryObject.m_indexBufferData);

					// process all subsurfaces, add opaque surfaces but remember transparent surfaces for later
					for (unsigned int i=0; i<s.subSurfaces().size(); ++i) {
						const VICUS::SubSurface & sub = s.subSurfaces()[i];
						if (sub.m_subSurfaceComponentInstance != nullptr &&
							sub.m_subSurfaceComponentInstance->m_subSurfaceComponentID != VICUS::INVALID_ID)
						{
							// lookup subsurface component - if it exists
							const VICUS::SubSurfaceComponent * comp = db.m_subSurfaceComponents[sub.m_subSurfaceComponentInstance->m_subSurfaceComponentID];
							if (comp != nullptr) {
								// now select transparent or opaque surface based on type
								if (comp->m_type == VICUS::SubSurfaceComponent::CT_Window) {
									// only add to transparent subsurfaces if visible and not selected
									if (sub.m_visible && !sub.m_selected)
										transparentSubsurfaces.push_back(std::make_pair(&sub, &s.geometry().holeTriangulationData()[i]) );
									continue; // next surface
								}
							}
						}

						// not a transparent surface, just add surface as opaque surface
						addSubSurface(s, i, currentVertexIndex, currentElementIndex,
								   m_buildingGeometryObject.m_vertexBufferData,
								   m_buildingGeometryObject.m_colorBufferData,
								   m_buildingGeometryObject.m_indexBufferData);
					}
				}
			}
		}
	}

	// now the plain geometry
	for (const VICUS::Surface & s : p.m_plainGeometry) {

		// remember where the vertexes for this surface start in the buffer
		m_buildingGeometryObject.m_vertexStartMap[s.uniqueID()] = currentVertexIndex;

		// now we store the surface data into the vertex/color and index buffers
		// the indexes are advanced and the buffers enlarged as needed.
		// actually, this adds always two surfaces (for culling).
		addSurface(s, currentVertexIndex, currentElementIndex,
				   m_buildingGeometryObject.m_vertexBufferData,
				   m_buildingGeometryObject.m_colorBufferData,
				   m_buildingGeometryObject.m_indexBufferData);
	}

	// done with all opaque planes, remember start index for transparent geometry
	m_buildingGeometryObject.m_transparentStartIndex = m_buildingGeometryObject.m_indexBufferData.size();

	// now add all transparent surfaces
	for (std::pair<const VICUS::SubSurface *, const VICUS::PlaneTriangulationData*> & p : transparentSubsurfaces) {
		QColor col = p.first->m_color;
		addPlane(*p.second, col, currentVertexIndex, currentElementIndex,
				 m_buildingGeometryObject.m_vertexBufferData,
				 m_buildingGeometryObject.m_colorBufferData,
				 m_buildingGeometryObject.m_indexBufferData, false);
	}

	if (t.elapsed() > 20)
		qDebug() << t.elapsed() << "ms for building generation";
}


void Scene::generateNetworkGeometry() {
	QElapsedTimer t;
	t.start();
	// get VICUS project data and database
	const VICUS::Project & p = project();
	const SVDatabase & db = SVSettings::instance().m_db;

	// we rebuild the entire geometry here, so this may be slow

	// clear out existing cache

	m_networkGeometryObject.m_vertexBufferData.clear();
	m_networkGeometryObject.m_colorBufferData.clear();
	m_networkGeometryObject.m_indexBufferData.clear();
	m_networkGeometryObject.m_vertexStartMap.clear();

	m_networkGeometryObject.m_vertexBufferData.reserve(100000);
	m_networkGeometryObject.m_colorBufferData.reserve(100000);
	m_networkGeometryObject.m_indexBufferData.reserve(100000);

	// process all network elements

	unsigned int currentVertexIndex = 0;
	unsigned int currentElementIndex = 0;

	// add cylinders for all pipes
	for (const VICUS::Network & network : p.m_geometricNetworks) {

		// update pointers of network elements, they are only runtime and not part of the project data
		// so they can be modified with const_cast
		const_cast<VICUS::Network &>(network).updateNodeEdgeConnectionPointers();
		// the visualization radius is also only runtime.
		// it is mutable so no const_cast needed
		network.updateVisualizationRadius(db.m_pipes);

		for (const VICUS::NetworkEdge & e : network.m_edges) {
			double radius = e.m_visualizationRadius;
			QColor pipeColor = e.m_color;
			if (!e.m_visible || e.m_selected)
				pipeColor.setAlpha(0);

			m_networkGeometryObject.m_vertexStartMap[e.uniqueID()] = currentVertexIndex;
			addCylinder(e.m_node1->m_position, e.m_node2->m_position, pipeColor, radius,
						currentVertexIndex, currentElementIndex,
						m_networkGeometryObject.m_vertexBufferData,
						m_networkGeometryObject.m_colorBufferData,
						m_networkGeometryObject.m_indexBufferData);
		}

		// add spheres for nodes
		for (const VICUS::NetworkNode & no : network.m_nodes) {
			double radius = no.m_visualizationRadius;
			QColor col = no.m_color;
			if (!no.m_visible || !network.m_visible)
				col.setAlpha(0);

			m_networkGeometryObject.m_vertexStartMap[no.uniqueID()] = currentVertexIndex;
			addSphere(no.m_position, col, radius,
						currentVertexIndex, currentElementIndex,
						m_networkGeometryObject.m_vertexBufferData,
						m_networkGeometryObject.m_colorBufferData,
						m_networkGeometryObject.m_indexBufferData);
		}
	}

	// done with all opaque geometry, remember start index for transparent geometry
	m_networkGeometryObject.m_transparentStartIndex = m_networkGeometryObject.m_indexBufferData.size();

	if (t.elapsed() > 20)
		qDebug() << t.elapsed() << "ms for network generation";
}


void Scene::recolorObjects(SVViewState::ObjectColorMode ocm, unsigned int id) const {
	// Note: the meaning of the filter id depends on the coloring mode

	// get VICUS project data
	const VICUS::Project & p = project();

	// coloring works as follows:
	// - we process all surfaces and sub-surfaces
	// - if we are not in a coloring mode (OCM_None) we select a default color for the surface/sub-surface/node/edge
	//   (this is done always as default initialization step)
	// - if we are in a coloring mode, all surfaces except those we need to color are grayed out

	// process all surfaces and initialize colors
	for (const VICUS::Building & b : p.m_buildings) {
		for (const VICUS::BuildingLevel & bl : b.m_buildingLevels) {
			for (const VICUS::Room & r : bl.m_rooms) {
				for (const VICUS::Surface & s : r.m_surfaces) {

					// update surface opaque color
					// here, it does not matter if the surfaces is selected or invisible -
					// we just update the color that would be used if the surface would be drawn

					if (ocm == SVViewState::OCM_None) {
						// const cast is ok here, since color is not a project property
						const_cast<VICUS::Surface&>(s).updateColor();
					}
					else {
						// set "not interested/not applicable" color
						s.m_color = QColor(64,64,64,255); // dark opaque gray
					}

					// now the subsurfaces
					for (const VICUS::SubSurface & sub : s.subSurfaces()) {
						if (ocm == SVViewState::OCM_None) {
							// const cast is ok here, since color is not a project property
							const_cast<VICUS::SubSurface&>(sub).updateColor();
						}
						else {
							// set "not interested/not applicable" color
							sub.m_color = QColor(72,72,82,192); // will be drawn opaque in most modes
						}
					}
				}
			}
		}
	}

	// initialize network colors, independent of current color mode
	for (const VICUS::Network & net: p.m_geometricNetworks) {
		// updateColor is a const-function, this is possible since
		// the m_color property of edges and nodes is mutable
		net.setDefaultColors();
	}

	const SVDatabase & db = SVSettings::instance().m_db;

	// different handling different color modes
	// Mind: the subsurfaces are drawn either transparent or opaque, depending on the associated
	//       component. Without a subsurface-component assigned, they will be opaque and should
	//       have a different color than regular surfaces without component

	switch (ocm) {
		case SVViewState::OCM_None: break;

		case SVViewState::OCM_SelectedSurfacesHighlighted: {
			for (const VICUS::Building & b : p.m_buildings) {
				for (const VICUS::BuildingLevel & bl : b.m_buildingLevels) {
					for (const VICUS::Room & r : bl.m_rooms) {
						for (const VICUS::Surface & s : r.m_surfaces) {

							// change color of selected surfaces
							if (s.m_selected)
								s.m_color = QColor(255,144,0,255); // nice orange
						}
					}
				}
			}
		} break;

		case SVViewState::OCM_Components:
		case SVViewState::OCM_SubSurfaceComponents:
		case SVViewState::OCM_ComponentOrientation:
		case SVViewState::OCM_BoundaryConditions: {
			// now color all surfaces, this works by first looking up the components, associated with each surface
			for (const VICUS::ComponentInstance & ci : project().m_componentInstances) {
				// lookup component definition
				const VICUS::Component * comp = db.m_components[ci.m_componentID];
				if (comp == nullptr)
					continue; // no component definition - keep default (gray) color
				switch (ocm) {
					case SVViewState::OCM_Components:
						if (ci.m_sideASurface != nullptr)
							ci.m_sideASurface->m_color = comp->m_color;
						if (ci.m_sideBSurface != nullptr)
							ci.m_sideBSurface->m_color = comp->m_color;
					break;
					case SVViewState::OCM_ComponentOrientation:
						// color surfaces when either filtering is off (id == 0)
						// or when component ID matches selected id
						if (id == VICUS::INVALID_ID || ci.m_componentID == id) {
							// color side A surfaces with blue,
							// side B surfaces with orange
							if (ci.m_sideASurface != nullptr)
								ci.m_sideASurface->m_color = QColor(47,125,212);
							if (ci.m_sideBSurface != nullptr)
								ci.m_sideBSurface->m_color = QColor(255, 206, 48);
						}
					break;
					case SVViewState::OCM_BoundaryConditions:
						if (ci.m_sideASurface != nullptr && comp->m_idSideABoundaryCondition != VICUS::INVALID_ID) {
							// lookup boundary condition definition
							const VICUS::BoundaryCondition * bc = db.m_boundaryConditions[comp->m_idSideABoundaryCondition];
							if (bc != nullptr)
								ci.m_sideASurface->m_color = bc->m_color;
						}
						if (ci.m_sideBSurface != nullptr && comp->m_idSideBBoundaryCondition != VICUS::INVALID_ID) {
							// lookup boundary condition definition
							const VICUS::BoundaryCondition * bc = db.m_boundaryConditions[comp->m_idSideBBoundaryCondition];
							if (bc != nullptr)
								ci.m_sideBSurface->m_color = bc->m_color;
						}
					break;

						// the color modes below are not handled here and are only added to get rid of compiler warnins
					case SVViewState::OCM_ZoneTemplates:
					case SVViewState::OCM_SubSurfaceComponents:
					case SVViewState::OCM_None:
					case SVViewState::OCM_Network:
					case SVViewState::OCM_NetworkEdge:
					case SVViewState::OCM_NetworkNode:
					case SVViewState::OCM_NetworkComponents:
					break;
				}
			}

			// now color all sub-surfaces, this works by first looking up the components, associated with each surface
			for (const VICUS::SubSurfaceComponentInstance & ci : project().m_subSurfaceComponentInstances) {
				// lookup component definition
				const VICUS::SubSurfaceComponent * comp = db.m_subSurfaceComponents[ci.m_subSurfaceComponentID];
				if (comp == nullptr)
					continue; // no component definition - keep default (uninterested) color
				switch (ocm) {
					case SVViewState::OCM_SubSurfaceComponents:
						if (ci.m_sideASubSurface != nullptr) {
							ci.m_sideASubSurface->m_color = comp->m_color;
							// TODO : decide upon alpha value based on component type
							ci.m_sideASubSurface->m_color.setAlpha(128);
						}
						if (ci.m_sideBSubSurface != nullptr) {
							ci.m_sideBSubSurface->m_color = comp->m_color;
							ci.m_sideBSubSurface->m_color.setAlpha(128);
						}
					break;
					case SVViewState::OCM_ComponentOrientation:
						// color surfaces when either filtering is off (id == 0)
						// or when component ID matches selected id
						if (id == VICUS::INVALID_ID || ci.m_subSurfaceComponentID == id) {
							// color side A surfaces with blue,
							// side B surfaces with orange
							// colors slightly brighter than components, to allow differntiation
							if (ci.m_sideASubSurface != nullptr)
								ci.m_sideASubSurface->m_color = QColor(92,149,212, 128); // set slightly transparent to have effect on windows
							if (ci.m_sideBSubSurface != nullptr)
								ci.m_sideBSubSurface->m_color = QColor(255, 223, 119, 128); // set slightly transparent to have effect on windows
						}
					break;
					case SVViewState::OCM_BoundaryConditions :
						if (ci.m_sideASubSurface != nullptr && comp->m_idSideABoundaryCondition != VICUS::INVALID_ID) {
							// lookup boundary condition definition
							const VICUS::BoundaryCondition * bc = db.m_boundaryConditions[comp->m_idSideABoundaryCondition];
							if (bc != nullptr) {
								ci.m_sideASubSurface->m_color = bc->m_color.lighter(50);
								ci.m_sideASubSurface->m_color.setAlpha(128);
							}
						}
						if (ci.m_sideBSubSurface != nullptr && comp->m_idSideBBoundaryCondition != VICUS::INVALID_ID) {
							// lookup boundary condition definition
							const VICUS::BoundaryCondition * bc = db.m_boundaryConditions[comp->m_idSideBBoundaryCondition];
							if (bc != nullptr) {
								ci.m_sideBSubSurface->m_color = bc->m_color.lighter(50);
								ci.m_sideBSubSurface->m_color.setAlpha(128);
							}
						}
					break;

						// the color modes below are not handled here and are only added to get rid of compiler warnins
					case SVViewState::OCM_ZoneTemplates:
					case SVViewState::OCM_Components:
					case SVViewState::OCM_None:
					case SVViewState::OCM_SelectedSurfacesHighlighted:
					case SVViewState::OCM_Network:
					case SVViewState::OCM_NetworkEdge:
					case SVViewState::OCM_NetworkNode:
					case SVViewState::OCM_NetworkComponents:
					break;
				} // switch
			}

		} break;

		case SVViewState::OCM_ZoneTemplates: {
			for (const VICUS::Building & b : p.m_buildings) {
				for (const VICUS::BuildingLevel & bl : b.m_buildingLevels) {
					for (const VICUS::Room & r : bl.m_rooms) {
						// skip all without zone template
						if (r.m_idZoneTemplate == VICUS::INVALID_ID)
							continue; // they keep the default gray
						if (id == VICUS::INVALID_ID || r.m_idZoneTemplate == id) {
							// lookup zone template
							const VICUS::ZoneTemplate * zt = db.m_zoneTemplates[r.m_idZoneTemplate];
							if (zt == nullptr)
								continue; // no definition - keep default (gray) color
							// color all surfaces of room based on zone template color
							for (const VICUS::Surface & s : r.m_surfaces)
								s.m_color = zt->m_color;
							// TODO : subsurfaces

						}
					}
				}
			}
		} break;


		case SVViewState::OCM_Network:
		case SVViewState::OCM_NetworkNode:
		case SVViewState::OCM_NetworkEdge:
		case SVViewState::OCM_NetworkComponents:
			for (const VICUS::Network & net: p.m_geometricNetworks){

				switch (ocm) {
					case SVViewState::OCM_NetworkNode: {
						for (const VICUS::NetworkNode & node: net.m_nodes){
							if (node.m_type == VICUS::NetworkNode::NT_Source)
								node.m_color = QColor(230, 138, 0); // orange
							else if (node.m_type == VICUS::NetworkNode::NT_Mixer)
								node.m_color = QColor(119, 179, 0); // green
							else // Building
								node.m_color = QColor(0, 107, 179); // blue
						}
					}
					break;
					case SVViewState::OCM_NetworkEdge: {
						for (const VICUS::NetworkEdge & edge: net.m_edges){
							unsigned int id = edge.m_pipeId;
							if (db.m_pipes[id] != nullptr)
								edge.m_color = db.m_pipes[id]->m_color;
						}
					}
					break;
					case SVViewState::OCM_NetworkComponents: {
						for (const VICUS::NetworkEdge & edge: net.m_edges){
							unsigned int id = edge.m_componentId;
							if (db.m_networkComponents[id] != nullptr)
								edge.m_color = db.m_networkComponents[id]->m_color;
						}
						for (const VICUS::NetworkNode & node: net.m_nodes){
							unsigned int id = node.m_componentId;
							if (db.m_networkComponents[id] != nullptr)
								node.m_color = db.m_networkComponents[id]->m_color;
						}
					}
					break;

						// rest only to avoid compiler warnings
					case SVViewState::OCM_None:
					case SVViewState::OCM_SelectedSurfacesHighlighted:
					case SVViewState::OCM_Components:
					case SVViewState::OCM_SubSurfaceComponents:
					case SVViewState::OCM_ComponentOrientation:
					case SVViewState::OCM_BoundaryConditions:
					case SVViewState::OCM_ZoneTemplates:
					case SVViewState::OCM_Network:
					break;
				}
			}
		break;
	}


}


void Scene::selectAll() {
	std::set<const VICUS::Object *> selObjects;
	// select all objects, wether they are selected already or not, and whether they are visible or not
	project().selectObjects(selObjects, VICUS::Project::SG_All, false, false);

	// get a list of IDs of nodes to be selected (only those who are not yet selected)
	std::set<unsigned int> nodeIDs;
	for (const VICUS::Object * o : selObjects) {
		if (!o->m_selected)
			nodeIDs.insert(o->uniqueID());
	}

	SVUndoTreeNodeState * undo = new SVUndoTreeNodeState(tr("All objects selected"),
														 SVUndoTreeNodeState::SelectedState, nodeIDs, true);
	// select all
	undo->push();
}


void Scene::deselectAll() {
	std::set<unsigned int> objIDs;
	// add all selected objects, whether they are visible or not

	// get VICUS project data
	const VICUS::Project & p = project();
	for (const VICUS::Building & b : p.m_buildings) {
		if (b.m_selected)
			objIDs.insert(b.uniqueID());
		for (const VICUS::BuildingLevel & bl : b.m_buildingLevels) {
			if (bl.m_selected)
				objIDs.insert(bl.uniqueID());
			for (const VICUS::Room & r : bl.m_rooms) {
				if (r.m_selected)
					objIDs.insert(r.uniqueID());
				for (const VICUS::Surface & s : r.m_surfaces) {
					if (s.m_selected)
						objIDs.insert(s.uniqueID());
					for (const VICUS::SubSurface & sub : s.subSurfaces()) {
						if (sub.m_selected)
							objIDs.insert(sub.uniqueID());
					}
				}
			}
		}
	}

	// now the plain geometry
	for (const VICUS::Surface & s : p.m_plainGeometry) {
		if (s.m_selected)
			objIDs.insert(s.uniqueID());
	}

	// now network stuff

	// add cylinders for all pipes
	for (const VICUS::Network & network : p.m_geometricNetworks) {
		for (const VICUS::NetworkEdge & e : network.m_edges) {
			if (e.m_selected)
				objIDs.insert(e.uniqueID());
		}

		// add spheres for nodes
		for (const VICUS::NetworkNode & no : network.m_nodes) {
			if (no.m_selected)
				objIDs.insert(no.uniqueID());
		}
		if (network.m_selected)
			objIDs.insert(network.uniqueID());
	}

	// if nothing is selected, do nothing
	if (objIDs.empty())
		return;
	SVUndoTreeNodeState * undo = new SVUndoTreeNodeState(tr("Selected cleared"),
														 SVUndoTreeNodeState::SelectedState, objIDs, false);
	undo->push();
}


void Scene::deleteSelected() {
	// process all project geometry and keep (in a copy) only those that need to be removed
	std::vector<unsigned int> selectedObjectIDs;
	// generate vector of surfaces
	std::set<const VICUS::Object *> selectedObjects;
	project().selectObjects(selectedObjects, VICUS::Project::SG_All, true, true);

	// nothing selected - nothing to do
	if (selectedObjects.empty())
		return;

	// collect unique IDs of selected objects
	for (const VICUS::Object * o : selectedObjects)
		selectedObjectIDs.push_back(o->uniqueID());

	// clear selected objects (since they are now removed)
	SVUndoDeleteSelected * undo = new SVUndoDeleteSelected(tr("Removing selected geometry"), selectedObjectIDs);
	// clear selection
	undo->push();
}


void Scene::showSelected() {
	std::set<const VICUS::Object*> selectedObjects;
	// process all objects in project, take all objects that are selected, yet invisible
	project().selectObjects(selectedObjects, VICUS::Project::SG_All, true, false);
	std::set<unsigned int> selectedObjectIDs;
	// Note: all objects in m_selectedGeometryObject.m_selectedObjects are required to be visible!
	for (const VICUS::Object * obj : selectedObjects)
		selectedObjectIDs.insert(obj->uniqueID());

	if (selectedObjectIDs.empty())
		return;

	SVUndoTreeNodeState * action = new SVUndoTreeNodeState(tr("Visibility changed"),
														   SVUndoTreeNodeState::VisibilityState,
														   selectedObjectIDs,
														   true);
	action->push();
}


void Scene::hideSelected() {
	// process all project geometry and create data for a state modification undo action
	std::set<unsigned int> selectedObjectIDs;
	// Note: all objects in m_selectedGeometryObject.m_selectedObjects are required to be visible!
	for (const VICUS::Object * obj : m_selectedGeometryObject.m_selectedObjects)
		selectedObjectIDs.insert(obj->uniqueID());

	if (selectedObjectIDs.empty())
		return;

	SVUndoTreeNodeState * action = new SVUndoTreeNodeState(tr("Visibility changed"),
														   SVUndoTreeNodeState::VisibilityState,
														   selectedObjectIDs,
														   false);
	action->push();
}


void Scene::leaveAnySpecialMode() {
	// turn on AlignLocalCoordinateSystem mode
	SVViewState vs = SVViewStateHandler::instance().viewState();
	// leave any mode we are currently in and restore previous state
	switch (vs.m_sceneOperationMode) {
		case SVViewState::OM_AlignLocalCoordinateSystem :
			leaveCoordinateSystemAdjustmentMode(true);
		break;
		case SVViewState::OM_MoveLocalCoordinateSystem :
			leaveCoordinateSystemTranslationMode(true);
		break;
		default: ; // no other modes
	}
}

void Scene::enterCoordinateSystemAdjustmentMode() {
	// store current transformation of local coordinate system object
	m_oldCoordinateSystemTransform = m_coordinateSystemObject.transform();
	// turn on AlignLocalCoordinateSystem mode
	SVViewState vs = SVViewStateHandler::instance().viewState();
	vs.m_sceneOperationMode = SVViewState::OM_AlignLocalCoordinateSystem;
	SVViewStateHandler::instance().setViewState(vs);
	qDebug() << "Entering 'Align coordinate system' mode";
}


void Scene::leaveCoordinateSystemAdjustmentMode(bool abort) {
	// restore original local coordinate system
	if (abort) {
		m_coordinateSystemObject.setTransform(m_oldCoordinateSystemTransform);
		qDebug() << "Aborting 'Align coordinate system' mode (no change)";
	}
	else {
		// finish aligning coordinate system and keep selected rotation in coordinate system
		// but restore origin of local coordinate system object
		m_coordinateSystemObject.setTranslation(m_oldCoordinateSystemTransform.translation());
		qDebug() << "Leaving 'Align coordinate system' mode";
	}
	// switch back to defined view state
	SVViewStateHandler::instance().m_propModeSelectionWidget->setDefaultViewState();
}


void Scene::enterCoordinateSystemTranslationMode() {
	// store current transformation of local coordinate system object
	m_oldCoordinateSystemTransform = m_coordinateSystemObject.transform();
	// turn on AlignLocalCoordinateSystem mode
	SVViewState vs = SVViewStateHandler::instance().viewState();
	vs.m_sceneOperationMode = SVViewState::OM_MoveLocalCoordinateSystem;
	SVViewStateHandler::instance().setViewState(vs);
	qDebug() << "Entering 'Translate coordinate system' mode";
}


void Scene::leaveCoordinateSystemTranslationMode(bool abort) {
	// restore original local coordinate system
	if (abort) {
		m_coordinateSystemObject.setTransform(m_oldCoordinateSystemTransform);
		qDebug() << "Aborting 'Translate coordinate system' mode (no change)";
	}
	else {
		// finish aligning coordinate system
		qDebug() << "Leaving 'Translate coordinate system' mode";
	}
	// switch back to previous view state
	SVViewStateHandler::instance().m_propModeSelectionWidget->setDefaultViewState();
}


void Scene::pick(PickObject & pickObject) {

	// local mouse coordinates
	int my = pickObject.m_localMousePos.y();
	int mx = pickObject.m_localMousePos.x();

	// viewport dimensions
	double Dx = m_viewPort.width();
	double Dy = m_viewPort.height();

	double nx = (2*mx-Dx)/Dx;
	double ny = -(2*my-Dy)/Dy;

	// invert world2view matrix, with m_worldToView = m_projection * m_camera.toMatrix() * m_transform.toMatrix();
	bool invertible;
	QMatrix4x4 projectionMatrixInverted = m_worldToView.inverted(&invertible);
	if (!invertible) {
		qWarning()<< "Cannot invert projection matrix.";
		return;
	}

	// mouse position in NDC space, one point on near plane and one point on far plane
	QVector4D nearPos(float(nx), float(ny), -1, 1.0);
	QVector4D farPos (float(nx), float(ny),  1, 1.0);

	// transform from NDC to model coordinates
	QVector4D nearResult = projectionMatrixInverted*nearPos;
	QVector4D farResult = projectionMatrixInverted*farPos;
	// don't forget normalization!
	nearResult /= nearResult.w();
	farResult /= farResult.w();

	// compute line-of-sight equation
	IBKMK::Vector3D nearPoint = QtExt::QVector2IBKVector(nearResult.toVector3D()); // line offset = nearPoint
	// Note: Since the NearPlane-distance is 1 and thus nearly attached to the camera (distance 0 is not permitted!),
	//       the calculated nearPoint is actually (almost) the camera position, regardless of where one has clicked
	//       on the screen!
	//       So we might actually just take the camera position here and avoid the extra work, but since there may
	//       be later the demand for "zoom" and perspective adjustment, we leave it this way.
	IBKMK::Vector3D farPoint = QtExt::QVector2IBKVector(farResult.toVector3D());
	IBKMK::Vector3D direction = farPoint - nearPoint;	// direction vector of line-of-sight
	pickObject.m_lineOfSightOffset = nearPoint;
	pickObject.m_lineOfSightDirection = direction;

	// *** now do the actual picking ***
	//
	// We collect a list of pick candidates, all with pick points along the line-of-sight.
	// In this function we only collect the pick candidates. The calling function has to
	// pick the right one.

//#define SHOW_PICK_TIME
#ifdef SHOW_PICK_TIME
	QElapsedTimer pickTimer;
	pickTimer.start();
#endif


	// *** intersection with global xy plane ***

	IBKMK::Vector3D intersectionPoint;
	double t;
	// process all grid planes - being transparent, these are picked from both sides
	if (m_gridVisible) {
		for (unsigned int i=0; i< m_gridPlanes.size(); ++i) {
			int holeIndex;
			if (m_gridPlanes[i].intersectsLine(nearPoint, direction, intersectionPoint, t, holeIndex, true, true)) {
				// got an intersection point, store it
				PickObject::PickResult r;
				r.m_snapPointType = PickObject::RT_GridPlane;
				r.m_uniqueObjectID = i;
				r.m_depth = t;
				r.m_pickPoint = intersectionPoint;
				pickObject.m_candidates.push_back(r);
			}
		}
	}

	// now process all surfaces and update p to hold the closest hit
	const VICUS::Project & prj = project();


	// *** surfaces of buildings ***

	for (const VICUS::Building & b : prj.m_buildings) {
		for (const VICUS::BuildingLevel & bl : b.m_buildingLevels) {
			for (const VICUS::Room & r : bl.m_rooms) {
				for (const VICUS::Surface & s : r.m_surfaces) {
					// skip invisible or inactive surfaces
					if (!s.m_visible)
						continue;
					IBKMK::Vector3D intersectionPoint;
					double dist;
					// check if we hit the surface - since we show the surface from both sides, we
					// can also pick both sides
					int holeIndex;
					if (s.geometry().intersectsLine(nearPoint, direction, intersectionPoint, dist, holeIndex, true)) {
						// if a hole was clicked on, that is invisible, ignore this click
						if (holeIndex == -1 || s.subSurfaces()[(unsigned int)holeIndex].m_visible) {
							PickObject::PickResult r;
							r.m_snapPointType = PickObject::RT_Object;
							r.m_depth = dist;
							r.m_pickPoint = intersectionPoint;
							r.m_holeIdx = holeIndex;
							if (holeIndex != -1) {
								// store ID of window/embedded surface
								r.m_uniqueObjectID = s.subSurfaces()[(unsigned int)holeIndex].uniqueID();
							}
							else
								r.m_uniqueObjectID = s.uniqueID();
							pickObject.m_candidates.push_back(r);
						}
					}
				}
			}
		}
	}


	// *** now try plain geometry ***

	for (const VICUS::Surface & s : prj.m_plainGeometry) {
		// skip invisible or inactive surfaces
		if (!s.m_visible)
			continue;
		IBKMK::Vector3D intersectionPoint;
		double dist;
		// dump geometry is rendered front/back facing and also picked from both sides
		int holeIndex;
		if (s.geometry().intersectsLine(nearPoint, direction, intersectionPoint, dist, holeIndex, true)) {
			PickObject::PickResult r;
			r.m_snapPointType = PickObject::RT_Object;
			r.m_depth = dist;
			r.m_pickPoint = intersectionPoint;
			// TODO : Dirk, can "dump geometry" contain sub-surfaces?
			r.m_uniqueObjectID = s.uniqueID();
			pickObject.m_candidates.push_back(r);
		}
	}


	// *** process all networks ***

	for (const VICUS::Network & n : prj.m_geometricNetworks) {

		// process all nodes
		for (const VICUS::NetworkNode & no : n.m_nodes) {

			// skip invisible nodes
			if (!no.m_visible)
				continue;

			// compute closest distance between nodal center point and line
			double dist;
			IBKMK::Vector3D closestPoint;
			double linePointDist = IBKMK::lineToPointDistance(nearPoint, direction, no.m_position, dist, closestPoint);
			// check distance against radius of sphere
			if (linePointDist < no.m_visualizationRadius) {
				PickObject::PickResult r;
				r.m_snapPointType = PickObject::RT_Object;
				r.m_depth = dist; // the depth to the point on the line-of-sight that is closest to the sphere's center point
				r.m_pickPoint = closestPoint; // this
				r.m_uniqueObjectID = no.uniqueID();
				pickObject.m_candidates.push_back(r);
			}
		}

		// process all edges
		for (const VICUS::NetworkEdge & e : n.m_edges) {

			// skip invisible nodes
			if (!e.m_visible)
				continue;

			// compute closest distance between nodal center point and line
			double dist;
			IBKMK::Vector3D closestPoint;
			double lineFactor;
			double line2LineDistance = IBKMK::lineToLineDistance(nearPoint, direction,
																 e.m_node1->m_position, e.m_node2->m_position - e.m_node1->m_position,
																 dist, closestPoint, lineFactor);
			// check distance against cylinder radius
			if (line2LineDistance < e.m_visualizationRadius && lineFactor >= 0 && lineFactor <= 1) {
				PickObject::PickResult r;
				r.m_snapPointType = PickObject::RT_Object;
				r.m_depth = dist;
				r.m_pickPoint = closestPoint;
				r.m_uniqueObjectID = e.uniqueID();
				pickObject.m_candidates.push_back(r);
			}
		}
	}

	// *** local coordinate system pick points ***

	// only do this when not panning/orbiting/first-person-viewing etc.
	if (m_navigationMode == NUM_NM) {

		PickObject::PickResult r;
		if (m_coordinateSystemObject.pick(nearPoint, direction, r))
			pickObject.m_candidates.push_back(r);

	}


	// finally sort the pick candidates based on depth value
	std::sort(pickObject.m_candidates.begin(), pickObject.m_candidates.end());

#ifdef SHOW_PICK_TIME
	qDebug() << "Pick duration = " << pickTimer.elapsed() << "ms";
#endif

	pickObject.m_pickPerformed = true;
}


struct SnapCandidate {
	bool operator<(const SnapCandidate & other) const {
		return m_distToLineOfSight < other.m_distToLineOfSight;
	}

	/*! The correspondig snap location. */
	IBKMK::Vector3D		m_pickPoint;
	/*! Distance of this candidate to pick point on line-of-sight. */
	double				m_distToLineOfSight;
};


void Scene::snapLocalCoordinateSystem(const PickObject & pickObject) {
	const SVViewState & vs = SVViewStateHandler::instance().viewState();

	const float SNAP_DISTANCES_THRESHHOLD = 2; // 1 m should be enough, right?

	// if we have axis lock, determine offset and direction
	IBKMK::Vector3D axisLockOffset = referencePoint();
	IBKMK::Vector3D direction;
	// get direction in case of axis lock
	switch (vs.m_locks) {
		case SVViewState::L_LocalX : direction = QtExt::QVector2IBKVector(m_coordinateSystemObject.localXAxis()); break;
		case SVViewState::L_LocalY : direction = QtExt::QVector2IBKVector(m_coordinateSystemObject.localYAxis()); break;
		case SVViewState::L_LocalZ : direction = QtExt::QVector2IBKVector(m_coordinateSystemObject.localZAxis()); break;
		case SVViewState::NUM_L: ; // no lock
	}

	// compute closest point between line-of-sight and locked axis
	double lineOfSightDist, lockedAxisDist;
	IBKMK::Vector3D closestPointOnAxis;
	IBKMK::lineToLineDistance(axisLockOffset, direction,
							  pickObject.m_lineOfSightOffset, pickObject.m_lineOfSightDirection,
							  lockedAxisDist, closestPointOnAxis, lineOfSightDist);


	IBKMK::Vector3D		snapPoint; // default snap point = origin
	std::string snapInfo = "no hit (fall-back to coordinate origin)";

	// *** no snap ***
	//
	if (!vs.m_snapEnabled) {

		// take closest hit and be done
		if (!pickObject.m_candidates.empty()) {
			snapPoint = pickObject.m_candidates.front().m_pickPoint;
			// if we have a locked axis, and the "closest point to axis" is actually closer than the pick point candidate,
			// we take the closest point instead
			if (vs.m_locks != SVViewState::NUM_L && lineOfSightDist < pickObject.m_candidates.front().m_depth) {
				snapPoint = closestPointOnAxis;
				snapInfo = "closest point on locked axis";
			}
			else
				snapInfo = "nearest object/plane hit";
		}
		else {
			// we take the global coordinate origin as point
			snapPoint = IBKMK::Vector3D();
			if (vs.m_locks != SVViewState::NUM_L) {
				snapPoint = closestPointOnAxis;
				snapInfo = "closest point on locked axis";
			}
			else
				snapInfo = "global origin (no snap points found)";
		}

		// now our candidate is stored as snapPoint - if axis lock is enabled, we still project the point
		// towards the locked axis (line) defined via last coordinate's position and locked local axis vector
	}


	// *** with snap ***
	//
	else {

		// by default, we snap to the closest point on a locked axis, if one is locked
		if (vs.m_locks != SVViewState::NUM_L) {
			snapPoint = closestPointOnAxis;
			snapInfo = "closest point on locked axis";
		}

		// we have now several surfaces/objects stored in the pickObject as candidates
		// we take the first hit and process the snap options

		int snapOptions = vs.m_snapOptionMask;
		if (!pickObject.m_candidates.empty()) {
			const PickObject::PickResult & r = pickObject.m_candidates.front();

			QVector3D pickPoint = QtExt::IBKVector2QVector(r.m_pickPoint);

			// depending on type of object, process the different snap options
			if (r.m_snapPointType == PickObject::RT_GridPlane) {
				// use the intersection point with the grid as default snap point (in case no grid point is close enough)
				// but only, if there is no axis lock enabled
				if (vs.m_locks == SVViewState::NUM_L) {
					snapPoint = r.m_pickPoint;
					snapInfo = "intersection point with plane (fall-back if no grid-point is in snap distance)";
				}
				// do we snap to grid?
				if (snapOptions & SVViewState::Snap_GridPlane) {
					// now determine which grid line is closest
					QVector3D closestPoint;
					/// \todo Andreas: add support for several grid objects, or one grid object with several planes
					///		  r.m_uniqueObjectID -> index of plane that we hit.
					if (m_gridObject.closestSnapPoint(QtExt::IBKVector2QVector(r.m_pickPoint), closestPoint)) {
						// this is in world coordinates, use this as transformation vector for the
						// coordinate system
						float dist = (closestPoint - pickPoint).lengthSquared();
						// close enough?
						if (dist < SNAP_DISTANCES_THRESHHOLD) {
							// got a snap point, store it
							snapPoint = QtExt::QVector2IBKVector(closestPoint);
							snapInfo = "snap to grid point";
						}
					}
				}
			}

			if (r.m_snapPointType == PickObject::RT_Object) {
				// We hit an object!

				// find out if this is a surface, a network node or an edge
				const VICUS::Object * obj = project().objectById(r.m_uniqueObjectID);
				Q_ASSERT(obj != nullptr);

				// *** surfaces ***

				const VICUS::Surface * s = dynamic_cast<const VICUS::Surface *>(obj);
				if (s != nullptr) {
					// a surface object might have several snap points which we collect first in a vector
					std::vector<SnapCandidate> snapCandidates;
					float closestDepthSoFar = SNAP_DISTANCES_THRESHHOLD;

					// for now we snap to the vertexes of the outer polygon and all holes
					const std::vector<IBKMK::Vector3D> & sVertexes = s->geometry().triangulationData().m_vertexes;

					// we always add the intersection point with the surface as fall-back snappoint,
					// but with a large distance so that it is only used as last resort
					SnapCandidate sc;
					sc.m_distToLineOfSight = (double)SNAP_DISTANCES_THRESHHOLD*2;
					sc.m_pickPoint = r.m_pickPoint;
					snapCandidates.push_back(sc);

					if (snapOptions & SVViewState::Snap_ObjectVertex) {
						// insert distances to all vertexes of selected object
						for (const IBKMK::Vector3D & v : sVertexes) {
							QVector3D p = QtExt::IBKVector2QVector(v);
							float dist = (p - pickPoint).lengthSquared();
							// Only add if close enough (< SNAP_DISTANCES_THRESHHOLD) and if there isn't yet
							// another snap point that's closer.
							if (dist < closestDepthSoFar && dist < SNAP_DISTANCES_THRESHHOLD) {
								sc.m_distToLineOfSight = (double)dist;
								sc.m_pickPoint = v;
								snapCandidates.push_back(sc);
								closestDepthSoFar = dist;
							}
						}
					}
					if (snapOptions & SVViewState::Snap_ObjectCenter) {
						// insert center point
						IBKMK::Vector3D center(0,0,0);
						for (const IBKMK::Vector3D & v : sVertexes)
							center += v;
						center /= sVertexes.size();
						QVector3D p = QtExt::IBKVector2QVector(center);
						float dist = (p - pickPoint).lengthSquared();
						if (dist < closestDepthSoFar && dist < SNAP_DISTANCES_THRESHHOLD) {
							sc.m_distToLineOfSight = (double)dist;
							sc.m_pickPoint = center;
							snapCandidates.push_back(sc);
							closestDepthSoFar = dist;
						}
					}
					if (snapOptions & SVViewState::Snap_ObjectEdgeCenter) {
						// process all edges
						IBKMK::Vector3D lastNode = sVertexes.front();
						for (unsigned int i=0; i<sVertexes.size()+1; ++i) {
							IBKMK::Vector3D center = lastNode;
							lastNode = sVertexes[i % sVertexes.size()];
							center += lastNode;
							center /= 2;
							QVector3D p = QtExt::IBKVector2QVector(center);
							float dist = (p - pickPoint).lengthSquared();
							if (dist < closestDepthSoFar && dist < SNAP_DISTANCES_THRESHHOLD) {
								sc.m_distToLineOfSight = (double)dist;
								sc.m_pickPoint = center;
								snapCandidates.push_back(sc);
								closestDepthSoFar = dist;
							}
						}
					}

					// now we take the snap point that's closest - even if all the snap options of an object are
					// turned off, we still get the intersection point as last straw to pick.
					std::sort(snapCandidates.begin(), snapCandidates.end());
					snapPoint = snapCandidates.front().m_pickPoint;
					snapInfo = "snap to object";
				} // if (s != nullptr)

				// *** sub-surfaces ***

				const VICUS::SubSurface * sub = dynamic_cast<const VICUS::SubSurface *>(obj);
				if (sub != nullptr) {
					s = dynamic_cast<const VICUS::Surface *>(sub->m_parent);
					IBK_ASSERT(r.m_holeIdx != -1);
					// a sub-surface object might have several snap points which we collect first in a vector
					std::vector<SnapCandidate> snapCandidates;
					float closestDepthSoFar = SNAP_DISTANCES_THRESHHOLD;

					// for now we snap to the vertexes of the outer polygon and all holes
					const std::vector<IBKMK::Vector3D> & sVertexes = s->geometry().holeTriangulationData()[(unsigned int)r.m_holeIdx].m_vertexes;

					// we always add the intersection point with the surface as fall-back snappoint,
					// but with a large distance so that it is only used as last resort
					SnapCandidate sc;
					sc.m_distToLineOfSight = (double)SNAP_DISTANCES_THRESHHOLD*2;
					sc.m_pickPoint = r.m_pickPoint;
					snapCandidates.push_back(sc);

					if (snapOptions & SVViewState::Snap_ObjectVertex) {
						// insert distances to all vertexes of selected object
						for (const IBKMK::Vector3D & v : sVertexes) {
							QVector3D p = QtExt::IBKVector2QVector(v);
							float dist = (p - pickPoint).lengthSquared();
							// Only add if close enough (< SNAP_DISTANCES_THRESHHOLD) and if there isn't yet
							// another snap point that's closer.
							if (dist < closestDepthSoFar && dist < SNAP_DISTANCES_THRESHHOLD) {
								sc.m_distToLineOfSight = (double)dist;
								sc.m_pickPoint = v;
								snapCandidates.push_back(sc);
								closestDepthSoFar = dist;
							}
						}
					}
					if (snapOptions & SVViewState::Snap_ObjectCenter) {
						// insert center point
						IBKMK::Vector3D center(0,0,0);
						for (const IBKMK::Vector3D & v : sVertexes)
							center += v;
						center /= sVertexes.size();
						QVector3D p = QtExt::IBKVector2QVector(center);
						float dist = (p - pickPoint).lengthSquared();
						if (dist < closestDepthSoFar && dist < SNAP_DISTANCES_THRESHHOLD) {
							sc.m_distToLineOfSight = (double)dist;
							sc.m_pickPoint = center;
							snapCandidates.push_back(sc);
							closestDepthSoFar = dist;
						}
					}
					if (snapOptions & SVViewState::Snap_ObjectEdgeCenter) {
						// process all edges
						IBKMK::Vector3D lastNode = sVertexes.front();
						for (unsigned int i=0; i<sVertexes.size()+1; ++i) {
							IBKMK::Vector3D center = lastNode;
							lastNode = sVertexes[i % sVertexes.size()];
							center += lastNode;
							center /= 2;
							QVector3D p = QtExt::IBKVector2QVector(center);
							float dist = (p - pickPoint).lengthSquared();
							if (dist < closestDepthSoFar && dist < SNAP_DISTANCES_THRESHHOLD) {
								sc.m_distToLineOfSight = (double)dist;
								sc.m_pickPoint = center;
								snapCandidates.push_back(sc);
								closestDepthSoFar = dist;
							}
						}
					}

					// now we take the snap point that's closest - even if all the snap options of an object are
					// turned off, we still get the intersection point as last straw to pick.
					std::sort(snapCandidates.begin(), snapCandidates.end());
					snapPoint = snapCandidates.front().m_pickPoint;
					snapInfo = "snap to object";
				} // if (s != nullptr)


				// currently there is such snapping to nodes, yet

				/// \todo Add snapping to nodes (i.e. when drawing edges)

			} // object snap

		} // (!pickObject.m_candidates.empty())

	} // with snapping

//	qDebug() << "Snap to: " << snapInfo.c_str();

	// we now have a snap point
	// if we also have line snap on, calculate the projection of this intersection point with the line

	// compute projection of current snapPoint onto line defined by refPoint and direction
	if (vs.m_locks != SVViewState::NUM_L) {
		double lineFactor;
		IBKMK::Vector3D projectedPoint;
		IBKMK::lineToPointDistance(axisLockOffset, direction, snapPoint, lineFactor, projectedPoint);
		snapPoint = projectedPoint; // update snap point with projected point
	}

	// take closest snap point and snap to it
	QVector3D newCoordinatePoint = QtExt::IBKVector2QVector(snapPoint);
	m_coordinateSystemObject.setTranslation(newCoordinatePoint);
}


void Scene::adjustCursorDuringMouseDrag(const QPoint & mouseDelta, const QPoint & localMousePos,
											 QPoint & newLocalMousePos, PickObject & pickObject)
{
	// cursor position moves out of window?
	const int WINDOW_MOVE_MARGIN = 50;
	if (localMousePos.x() < WINDOW_MOVE_MARGIN && mouseDelta.x() < 0) {
//						qDebug() << "Resetting mousepos to right side of window.";
		newLocalMousePos.setX(m_viewPort.width()-WINDOW_MOVE_MARGIN);
	}
	else if (localMousePos.x() > (m_viewPort.width()-WINDOW_MOVE_MARGIN) && mouseDelta.x() > 0) {
		//						qDebug() << "Resetting mousepos to right side of window.";
		newLocalMousePos.setX(WINDOW_MOVE_MARGIN);
	}

	if (localMousePos.y() < WINDOW_MOVE_MARGIN && mouseDelta.y() < 0) {
		qDebug() << "Resetting mousepos to bottom side of window.";
		newLocalMousePos.setY(m_viewPort.height()-WINDOW_MOVE_MARGIN);
	}
	else if (localMousePos.y() > (m_viewPort.height()-WINDOW_MOVE_MARGIN) && mouseDelta.y() > 0) {
		qDebug() << "Resetting mousepos to top side of window.";
		newLocalMousePos.setY(WINDOW_MOVE_MARGIN);
	}

	// if panning is enabled, reset the pan start positions/variables
	if (m_navigationMode == NM_Panning && newLocalMousePos != localMousePos) {
		pickObject.m_localMousePos = newLocalMousePos;
		pick(pickObject);
		panStart(newLocalMousePos, pickObject, true);
	}
}


void Scene::handleLeftMouseClick(const KeyboardMouseHandler & keyboardHandler, PickObject & o) {
	// do different things depending on current scene operation mode

	switch (SVViewStateHandler::instance().viewState().m_sceneOperationMode) {

		// *** place a vertex ***
		case SVViewState::NUM_OM :
		case SVViewState::OM_SelectedGeometry : {
			// selection handling
			handleSelection(keyboardHandler, o);
			return;
		}

		// *** place a vertex ***
		case SVViewState::OM_PlaceVertex : {
			// get current coordinate system's position
			IBKMK::Vector3D p = QtExt::QVector2IBKVector(m_coordinateSystemObject.translation());
			// append a vertex (this will automatically update the draw buffer) and also
			// modify the vertexListWidget.
			m_newGeometryObject.appendVertex(p);
			return;
		}

		// *** align coordinate system ***
		case SVViewState::OM_AlignLocalCoordinateSystem : {
			// finish aligning coordinate system and keep selected rotation in coordinate system
			// but restore origin of local coordinate system object
			m_coordinateSystemObject.setTranslation(m_oldCoordinateSystemTransform.translation());
			// switch back to previous view state
			leaveCoordinateSystemAdjustmentMode(false);
			return;
		}

		// *** move coordinate system ***
		case SVViewState::OM_MoveLocalCoordinateSystem : {
			// finish moving coordinate system and current local coordinate system location
			leaveCoordinateSystemTranslationMode(false);
			return;
		}
	}

}


void Scene::handleSelection(const KeyboardMouseHandler & keyboardHandler, PickObject & o) {
	// this will be a selection click - execute pick() operation
	pick(o);

	// check if any of the pick candidates is of type object
	unsigned int uniqueID = 0;
	for (const PickObject::PickResult & r : o.m_candidates) {
		if (r.m_snapPointType == PickObject::RT_Object)
		{
			uniqueID = r.m_uniqueObjectID;
			break;
		}
	}

	if (uniqueID != 0) {
		// find the selected object
		const VICUS::Object * obj = project().objectById(uniqueID);

		// if using shift-click, we go up one level, select the parent and all its children
		if (keyboardHandler.keyDown(Qt::Key_Shift)) {
			// check for valid parent - anonymous geometry does not have parents!
			if (obj->m_parent != nullptr) {
				obj = obj->m_parent;
				uniqueID = obj->uniqueID();
			}
		}

		// create undo-action that toggles the selection
		SVUndoTreeNodeState * action = SVUndoTreeNodeState::createUndoAction(tr("Selection changed"),
															   SVUndoTreeNodeState::SelectedState,
															   uniqueID,
															   true, // always select all children
															   !obj->m_selected);
		action->push();
		return;
	}
}


IBKMK::Vector3D Scene::referencePoint() const {
	// for now, return the position of the last added vertex, if any
	if (m_newGeometryObject.vertexList().empty())
		return IBKMK::Vector3D();
	else
		return m_newGeometryObject.vertexList().back();
}


IBKMK::Vector3D Scene::calculateFarPoint(const QPoint & mousPos, const QMatrix4x4 & projectionMatrixInverted) {
	// local mouse coordinates
	int my = mousPos.y();
	int mx = mousPos.x();

	// viewport dimensions
	double Dx = m_viewPort.width();
	double Dy = m_viewPort.height();

	double nx = (2*mx-Dx)/Dx;
	double ny = -(2*my-Dy)/Dy;

	// mouse position in NDC space, one point on near plane and one point on far plane
	QVector4D nearPos(float(nx), float(ny), -1, 1.0);
	QVector4D farPos (float(nx), float(ny),  1, 1.0);

	// transform from NDC to model coordinates
	QVector4D farResult = projectionMatrixInverted*farPos;
	// don't forget normalization!
	farResult /= farResult.w();

	return QtExt::QVector2IBKVector(farResult.toVector3D());
}


void Scene::panStart(const QPoint & localMousePos, PickObject & pickObject, bool reuseDepth) {
	qDebug() << "Entering panning mode";
	m_navigationMode = NM_Panning;

	// configure the pick object and pick a point on the XY plane/or any visible surface
	if (!pickObject.m_pickPerformed)
		pick(pickObject);

	// only enter orbit controller mode, if we actually hit something
	if (pickObject.m_candidates.empty()) {
		// create a virtual pick-point to start panning somewhere in the middle distance
		PickObject::PickResult r;
		r.m_depth = m_panObjectDepth;
		r.m_pickPoint = pickObject.m_lineOfSightOffset + pickObject.m_lineOfSightDirection*r.m_depth;
		pickObject.m_candidates.push_back(r);
	}
	else if (reuseDepth) {
		pickObject.m_candidates.front().m_depth = m_panObjectDepth;
		pickObject.m_candidates.front().m_pickPoint =
				pickObject.m_lineOfSightOffset + pickObject.m_lineOfSightDirection*pickObject.m_candidates.front().m_depth;
	}

	// if pick point is very far away, we limit the depth and adjust the pick point

	// we need to store initial camera pos, selected object pos, far point
	m_panCameraStart = QtExt::QVector2IBKVector(m_camera.translation());	// Point A
	m_panObjectStart = pickObject.m_candidates.front().m_pickPoint;			// Point C
	m_panFarPointStart = pickObject.m_lineOfSightOffset + pickObject.m_lineOfSightDirection;	// Point B
	m_panObjectDepth = pickObject.m_candidates.front().m_depth;
	double BADistance = (m_panFarPointStart - m_panCameraStart).magnitude(); // Same as far distance?
	double CADistance = (m_panObjectStart - m_panCameraStart).magnitude();
	m_panCABARatio = CADistance/BADistance;
	m_panMousePos = localMousePos;

	// invert world2view matrix, with m_worldToView = m_projection * m_camera.toMatrix() * m_transform.toMatrix();
	bool invertible;
	m_panOriginalTransformMatrix = m_worldToView.inverted(&invertible);
	if (!invertible) {
		qWarning()<< "Cannot invert projection matrix.";
		m_panOriginalTransformMatrix = QMatrix4x4();
	}
}

} // namespace Vic3D
