#ifndef Vic3DSceneH
#define Vic3DSceneH

#include <vector>

#include <QRect>
#include <QVector3D>
#include <QCoreApplication>

#include "Vic3DCamera.h"
#include "Vic3DGridObject.h"
#include "Vic3DOpaqueGeometryObject.h"
#include "Vic3DOrbitControllerObject.h"
#include "Vic3DCoordinateSystemObject.h"
#include "Vic3DSmallCoordinateSystemObject.h"
#include "Vic3DWireFrameObject.h"
#include "Vic3DNewGeometryObject.h"
#include "Vic3DPickObject.h"

class ModificationInfo;

namespace VICUS {
	class Surface;
}

class SVViewState;
class SVPropEditGeometry;

namespace Vic3D {

class ShaderProgram;
class KeyboardMouseHandler;
class SceneView;

/*! Encapsulates all data for drawing a part of the final picture, including the viewport where the
	scene is rendered in.
*/
class Vic3DScene {
	Q_DECLARE_TR_FUNCTIONS(Vic3DScene)
public:

	void create(SceneView * parent, std::vector<ShaderProgram> & shaderPrograms);

	/*! Triggered when SVProjectHandler::modified() is emitted. */
	void onModified( int modificationType, ModificationInfo * data );

	void destroy();

	void resize(int width, int height, qreal retinaScale);

	/*! Returns current size. */
	QSize currentSize() const { return m_viewPort.size(); }

	/*! Compines camera matrix and project matrix to form the world2view matrix. */
	void updateWorld2ViewMatrix();

	/*! Lets the scene handle keyboard/mouse input.
		Note: to retrieve the last mouse down/release positions, query the keyboardHandler directly.
		\param keyboardHandler Contains information on current state of keyboard and mouse (and mouse move/scroll deltas since last call).
		\param localMousePos Contains current mouse position (QCursor::pos() converted to local widget coordinates/viewport coordinates).
		\return Returns true, if input causes change in view and needs repainting.
	*/
	bool inputEvent(const KeyboardMouseHandler & keyboardHandler, const QPoint & localMousePos, QPoint & newLocalMousePos);

	/*! Actually renders to the current OpenGL context. */
	void render();

	/*! Updates the view state based on the current operation.
		\note This function should only be called from Vic3DSceneView::setViewState()!
	*/
	void setViewState(const SVViewState & vs);

	/*! When Escape was pressed, all selected objects become un-selected again. */
	void deselectAll();
	/*! Removes all selected geometry (creates an undo-action on the selected geometry). */
	void deleteSelected();
	/*! Makes all selected geometry. */
	void showSelected();
	/*! Shows all selected geometry. */
	void hideSelected();

	/*! Select all objects like surfaces, rooms, buildings, etc. */
	void selectAll();

	/*! Toggles "align coordinate system" mode on. */
	void enterCoordinateSystemAdjustmentMode();
	/*! Leaves the coordinate system alignment/positioning mode and returns to previous mode. */
	void leaveCoordinateSystemAdjustmentMode(bool abort);

	bool m_smallCoordinateSystemObjectVisible = true;

private:
	void generateBuildingGeometry();
	void generateNetworkGeometry();

	/*! Mouse pick handler: collects all pickable objects/surfaces/planes along the line-of-sight and stores all possible
		pick candidates in pickObject.
	*/
	void pick(PickObject & pickObject);

	/*! Takes the picked objects and applies the snapping rules.
		Once a snap point has been selected, the local coordinate system is translated to the snap point.
	*/
	void snapLocalCoordinateSystem(const PickObject & pickObject);

	/*! Determines a new local mouse position (local to this viewport) such that a mouse passing over a border
		while dragging/rotating the view is avoided through placement of the mouse to the other side of the window.
	*/
	void adjustCurserDuringMouseDrag(const QPoint & mouseDelta, const QPoint & localMousePos,
									 QPoint & newLocalMousePos, PickObject & pickObject);

	/*! Due something with the mouse click, depending on current operation mode. */
	void handleLeftMouseClick(const KeyboardMouseHandler & keyboardHandler, PickObject & o);

	/*! Selects/deselects objects. */
	void handleSelection(const KeyboardMouseHandler & keyboardHandler, PickObject & o);

	/*! Returns the current reference point for relative movement of the local coordinate system.
		In PlaceVertex-mode, the reference point is the last placed vertex.
		In ObjectTranslation-mode, the reference point is the last fixed position of the local coordinate system
		(which is usually first set when selection changes, and changed lateron when the local coordinate system is
		manually translated).
	*/
	IBKMK::Vector3D referencePoint() const;

	IBKMK::Vector3D calculateFarPoint(const QPoint & mousPos, const QMatrix4x4 & projectionMatrixInverted);

	/*! Initializes the pan operation. */
	void panStart(const QPoint & localMousePos, PickObject & pickObject);

	/*! Cached pointer to parent widget - needed so that we can tell a QObject-based class to send
		out signals.
	*/
	SceneView				*m_parent = nullptr;

	/*! Stores viewport geometry. */
	QRect					m_viewPort;
	/*! Stores minature viewport geometry. */
	QRect					m_smallViewPort;

	/*! Shader program 'Grid' (managed by SceneView). */
	ShaderProgram			*m_gridShader				= nullptr;
	/*! Shader program 'Opaque Surfaces' (managed by SceneView). */
	ShaderProgram			*m_buildingShader			= nullptr;
	/*! Shader program 'Orbit controller' (managed by SceneView). */
	ShaderProgram			*m_fixedColorTransformShader	= nullptr;
	/*! Shader program 'Coordinate system' (managed by SceneView). */
	ShaderProgram			*m_coordinateSystemShader	= nullptr;
	/*! Shader program 'Transparent surfaces' (managed by SceneView). */
	ShaderProgram			*m_transparencyShader		= nullptr;

	/*! The projection matrix, updated whenever the viewport geometry changes (in resizeGL() ). */
	QMatrix4x4				m_projection;
	/*! The projection matrix for the small view (the view is a constant square, so this project matrix does not change over time). */
	QMatrix4x4				m_smallViewProjection;
	/*! World transformation matrix generator. */
	Transform3D				m_transform;
	/*! Camera position, orientation and lens data. */
	Camera					m_camera;
	/*! Cached world to view transformation matrix. */
	QMatrix4x4				m_worldToView;

	/*! Position of light source, currently very far above. */
	QVector3D				m_lightPos = QVector3D(100,200,2000);
	/*! Light color. */
	QColor					m_lightColor = Qt::white;


	// *** Drawable objects ***

	/*! The grid draw object. */
	GridObject				m_gridObject;
	/*! A geometry drawing object (no transparency) for building (room) surfaces.*/
	OpaqueGeometryObject	m_opaqueGeometryObject;
	/*! A geometry drawing object (no transparency) for network elements.*/
	OpaqueGeometryObject	m_networkGeometryObject;
	/*! A geometry for drawing selected primitives with overlayed wireframe. */
	WireFrameObject			m_selectedGeometryObject;
	/*! Indicator for the center of the orbit controller.
		Only visible when m_orbitControllerActive is true.
	*/
	OrbitControllerObject	m_orbitControllerObject;
	/*! The movable coordinate system. */
	CoordinateSystemObject	m_coordinateSystemObject;
	/*! Object to display newly drawn geometry. */
	NewGeometryObject		m_newGeometryObject;

	/*! The small coordinate system at the bottom/left. */
	SmallCoordinateSystemObject	m_smallCoordinateSystemObject;


	// *** Navigation stuff ***

	/*! Struct for exclusive navigation modes.
		While one navigation mode is active, we cannot also start another navigation mode.
	*/
	enum NavigationMode {
		NM_OrbitController,
		NM_Panning,
		NM_FirstPerson,
		NUM_NM
	};

	/*! Identifies the current navigation mode.
		Toggled in inputEvent() and reset when anything changes the scene operation mode (like reloading the project etc.)
	*/
	NavigationMode			m_navigationMode = NUM_NM;

	// *** Orbit controller stuff ***

	/*! Stores the distance that the mouse has been moved in the last "Left-mouse button down ... release" interval. */
	float					m_mouseMoveDistance = 0.f;
	/*! Holds the origin of the orbit controller coordinates. */
	QVector3D				m_orbitControllerOrigin;

	// other members

	/*! Cached "old" transform of the coordinate system object (needed for "align coordinate system" operation). */
	Transform3D				m_oldCoordinateSystemTransform;

	/*! Point A in "perfect panning" algorithm. */
	IBKMK::Vector3D			m_panCameraStart;
	/*! Point B in "perfect panning" algorithm. */
	IBKMK::Vector3D			m_panFarPointStart;
	/*! Point E in "perfect panning" algorithm. */
	IBKMK::Vector3D			m_panObjectStart;
	/*! Mouse position (local coordinate system) when starting move. */
	QPoint					m_panMousePos;

	QMatrix4x4				m_panOriginalTransformMatrix;

	double					m_panCABARatio;

	// vector with drawing helping planes
	std::vector<VICUS::PlaneGeometry>	m_gridPlanes;

};

} // namespace Vic3D


#endif // Vic3DSceneH
