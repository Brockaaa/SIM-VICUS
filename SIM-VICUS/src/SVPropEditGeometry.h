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

#ifndef SVPropEditGeometryH
#define SVPropEditGeometryH

#include <QWidget>

#include <IBKMK_Vector3D.h>

#include <VICUS_Drawing.h>
#include <Vic3DTransform3D.h>

namespace VICUS {
	class Project;
	class Room;
	class Surface;
	class SubSurface;
	class Building;
	class BuildingLevel;
}

namespace Ui {
	class SVPropEditGeometry;
}

namespace QtExt {
	class ValidatingLineEdit;
}

class QLineEdit;

class SVProjectHandler;
class SVUndoModifySurfaceGeometry;
class ModificationInfo;


/*! This widget is shown when the scene is put into geometry "editing" mode.

	This widget handles all operationes that modify existing geometry.
	Modifying geometry requires a valid selection - hence, this widget is only available when
	there is a valid selection.

	## Interactive Transformations ##

	Whenever an interactive transformation finishes (i.e. user releases mouse button after a drag-operation
	on the local coordinate system), the slow "enableTransformation()" is called. This in turn activates the
	buttons to apply/reject the transformation.

*/
class SVPropEditGeometry : public QWidget {
	Q_OBJECT

public:
	enum ModificationType {
		MT_Translate,
		MT_Rotate,
		MT_Scale,
		MT_Align,
		MT_Trim,
		MT_Copy,
		NUM_MT
	};

	enum OrientationMode {
		OM_Local,
		OM_Global,
		NUM_OM
	};

	enum ScaleUnit {
		SU_Meter,
		SU_Decimeter,
		SU_Centimeter,
		SU_Millimeter,
		NUM_SU
	};

	explicit SVPropEditGeometry(QWidget *parent = nullptr);
	~SVPropEditGeometry() override;

	/*! Enables the "Apply transformation" and "Cancel transformation" buttons.
		This function is called whenever an interactive transformation operation has finished, or when the
		transformation matrix of the wire-frame/selection object has been modified as result of user input.
	*/
	void enableTransformation();

	/*! Switches to the respective transformation page on the widget.
		Calls updateUi() afterwards.
	*/
	void setModificationType(ModificationType modType);

	/*! Sets the Coordinates of the Center of the local Coordinate System
		(called directly from the local coordinate system when its position changes).
	*/
	void setCoordinates(const Vic3D::Transform3D &t);

	/*! Called from SVGeometryView, may react on a global keypress (when focus is in scene or elsewhere).
		Function returns true if keypress was accepted.
	*/
	bool handleGlobalKeyPress(Qt::Key k);

	/*! Applies the Transformation, done by Interactive mode (Translation, Scaling, Rotation).
	*/
	void finishTransformation();

public slots:

	/*! Connected to SVProjectHandler::modified() */
	void onModified(int modificationType, ModificationInfo * );

	/*! Connected to SVViewStateManager::viewStateChanged() and used to enable/disable
		the edit widget when there is no selection.
	*/
	void onViewStateChanged();

	/*! Is called when a line edit fields text has changed. */
	void onLineEditTextEdited(const QString);

	/*! Updated the final rotation of the trimming plane. */
	void onTrimmingRotationFinished();

protected:
	/*! Event Filter: Needed for all scrolling specific inputs */
	bool eventFilter(QObject *target, QEvent *event) override;

	/*! Focus out event.
		Needed for transformation application.
	*/
	void focusOutEvent(QFocusEvent *event) override;

private slots:

	// *** Translation page ***

	void on_radioButtonTranslationAbsolute_toggled(bool checked);
	void on_radioButtonTranslationRelative_toggled(bool checked);
	void on_radioButtonTranslationRelativeLCS_toggled(bool checked);
	void on_lineEditTranslateX_editingFinishedSuccessfully();
	void on_lineEditTranslateY_editingFinishedSuccessfully();
	void on_lineEditTranslateZ_editingFinishedSuccessfully();

	// *** Rotation page ***

	void on_radioButtonRotationAlignToAngles_toggled(bool checked);
	void on_lineEditRotateOrientation_editingFinishedSuccessfully();
	void on_lineEditRotateInclination_editingFinishedSuccessfully();
	void on_lineEditRotateX_editingFinishedSuccessfully();
	void on_lineEditRotateY_editingFinishedSuccessfully();
	void on_lineEditRotateZ_editingFinishedSuccessfully();
	void on_pushButtonThreePointRotation_clicked();

	// *** Scale page ***

	void on_checkBoxKeepAspectRatio_toggled(bool checked);
	void on_radioButtonScaleResize_toggled(bool checked);
	void on_lineEditScaleX_editingFinishedSuccessfully();
	void on_lineEditScaleY_editingFinishedSuccessfully();
	void on_lineEditScaleZ_editingFinishedSuccessfully();

	// *** Alignment page ***

	void on_pushButtonCenterHorizontally_clicked();
	void on_pushButtonCenterVertically_clicked();
	void on_pushButtonFlipNormals_clicked();

	// *** Copy page ***

	void on_pushButtonCopySurface_clicked();
	void on_pushButtonCopySubsurface_clicked();
	void on_pushButtonCopyRoom_clicked();
	void on_pushButtonCopyBuildingLevel_clicked();
	void on_pushButtonCopyBuilding_clicked();

	void on_lineEditCopyX_editingFinishedSuccessfully();
	void on_lineEditCopyY_editingFinishedSuccessfully();
	void on_lineEditCopyZ_editingFinishedSuccessfully();


	// *** Apply + Cancel ***

	void on_pushButtonCancel_clicked();
	void on_pushButtonApply_clicked();

	void on_pushButtonTrimGridXY_clicked();
	void on_pushButtonTrimGridYZ_clicked();
	void on_pushButtonTrimGridXZ_clicked();
	void on_pushButtonTrimPolygons_clicked();

	void on_pushButtonTrimGridLocalXY_clicked();
	void on_pushButtonTrimGridLocalYZ_clicked();
	void on_pushButtonTrimGridLocalXZ_clicked();

	void on_lineEditRotateXTrimming_editingFinishedSuccessfully();
	void on_lineEditRotateYTrimming_editingFinishedSuccessfully();
	void on_lineEditRotateZTrimming_editingFinishedSuccessfully();

	void on_lineEditTranslateTrimmingX_editingFinishedSuccessfully();
	void on_lineEditTranslateTrimmingY_editingFinishedSuccessfully();
	void on_lineEditTranslateTrimmingZ_editingFinishedSuccessfully();

	void on_pushButtonApplyRotation_clicked();
	void on_pushButtonApplyTrimmingRotation_clicked();

	void on_comboBoxUnit_currentIndexChanged(int);
	void on_pushButtonFixSurfaceOrientation_clicked();

private:
	/*! Updates the property widget regarding to all geometry data.
		This function is called whenever the selection has changed, and when surface geometry (of selected surfaces)
		has changed.

		This function switches also between AddGeometry and EditGeometry mode, when first selection is made or
		everything is deselected.
	*/
	void updateUi(bool resetLCS = true);

	/*! Depending on currently selected modification type and state, the line edits and labels are updated accordingly.
		This function is called whenever the user switches between transformation operations and options, and hereby
		resets any previous input to the original values. Also, this resets the current preview of the wire-frame
		object to show the unmodified geometry.
	*/
	void updateInputs();

	/*! This function implements a convenience functionality that aligns the local coordinate system automatically
		with the selected surfaces, as long as all surfaces have the same inclination and orientation and
		the rotation mode with "orient to angles" is selected.
		Call this function only when the widget is visible.
	*/
	void adjustLocalCoordinateSystemForRotateToAngle();

	/*! Updates the transformation matrix for translating geometry. */
	void updateTranslationPreview();

	/*! Updates the transformation matrix for rotating geometry. */
	void updateRotationPreview();

	/*! Updates the transformation matrix for rotating the trim grid. */
	void updateTrimGridRotationPreview(bool updateNormal = false);

	/*! Updates the transformation matrix for local scaling.
		The parameter aspectRatioSourceEdit, if not -1, indicates which
		input shall be taken as base for aspect ratio setting (0-x, 1-y, 2-z).
	*/
	void updateScalePreview(int aspectRatioSourceEdit);

	/*! Increases/decreases value in line edit depending on scroll wheel. */
	void onWheelTurned(double offset, QtExt::ValidatingLineEdit * lineEdit);

	/*! Called from onWheelTurned(), relays a change event to the respective editingFinishedSuccessfully() slot. */
	void onLineEditTextChanged(QtExt::ValidatingLineEdit * lineEdit);

	/*! Depending on the selected operation, we change the look of the local coordinate system object. */
	void updateCoordinateSystemLook();

	/*! If Trimming is selected, we create a trimming grid, otherwise delete if necessary. */
	void updateTrimmingPlane(const IBKMK::Vector3D &trans);

	/*! Update Trimming Grid position if LCS changed */
	void updateTrimmingGridLcs();

	/*! Computes the local translation vector from current LCS rotation and m_copyTranslationVector. */
	IBKMK::Vector3D localCopyTranslationVector() const;

	/*! Contains position and rotation of local coordinate system (lcs) object. */
	Vic3D::Transform3D					m_lcsTransform;

	/*! This is the dimension of the bounding box (dx, dy, dz) in local/global coordinate system orientation,
		updated in updateUi() whenever the selection changes.
	*/
	IBKMK::Vector3D						m_bbDim[NUM_OM];

	/*! Cached center point of bounding box in local/global Orientation,
		updated in updateUi() whenever the selection changes.
	*/
	IBKMK::Vector3D						m_bbCenter[NUM_OM];

	/*! Cached normal for align2axis rotation, this is updated in setCoordinates(). */
	IBKMK::Vector3D						m_normal;

	/*! Cached initial values to be used when user had entered invalid values.
		These values depend on current modification type and state and are set initially in
		updateInputs(), and updated whenever a line edit has been edited successfully.
	*/
	IBKMK::Vector3D						m_originalValues;

	/*! Holds the translation components for copy operations.
		This vector is modified when user enters/changes values in the CopyXXX line edits.
	*/
	IBKMK::Vector3D						m_copyTranslationVector;

	std::vector<const VICUS::Building*>			m_selBuildings;
	std::vector<const VICUS::BuildingLevel*>	m_selBuildingLevels;
	std::vector<const VICUS::Room*>				m_selRooms;
	std::vector<const VICUS::Surface*>			m_selSurfaces;
	std::vector<const VICUS::SubSurface*>		m_selSubSurfaces;

	std::vector<const VICUS::Drawing*>			m_selDrawings;

	std::set<QString>					m_subSurfNames;
	std::set<QString>					m_surfNames;
	std::set<QString>					m_roomNames;
	std::set<QString>					m_buildingLevelNames;
	std::set<QString>					m_buildingNames;

	/*! Trimming plane normal. */
	IBKMK::Vector3D						m_trimingPlaneNormal;

	/*! Pointer to UI */
	Ui::SVPropEditGeometry				*m_ui;

};

#endif // SVPropEditGeometryH
