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

#include "SVDBSubSurfaceComponentEditWidget.h"
#include "ui_SVDBSubSurfaceComponentEditWidget.h"

#include <VICUS_KeywordList.h>
#include <VICUS_KeywordListQt.h>

#include <QtExt_LanguageHandler.h>
#include <QtExt_Conversions.h>

#include "SVSettings.h"
#include "SVDBSubSurfaceComponentTableModel.h"
#include "SVDatabaseEditDialog.h"
#include "SVMainWindow.h"
#include "SVConstants.h"

SVDBSubSurfaceComponentEditWidget::SVDBSubSurfaceComponentEditWidget(QWidget *parent) :
	SVAbstractDatabaseEditWidget(parent),
	m_ui(new Ui::SVDBSubSurfaceComponentEditWidget)
{
	m_ui->setupUi(this);
	m_ui->masterLayout->setMargin(4);

	m_ui->lineEditName->initLanguages(QtExt::LanguageHandler::instance().langId().toStdString(), THIRD_LANGUAGE, true);
	m_ui->lineEditName->setDialog3Caption(tr("Sub-Surface component identification name"));

	// enter categories into combo box
	// block signals to avoid getting "changed" calls
	m_ui->comboBoxSubSurfaceType->blockSignals(true);
	for(int i=0; i<VICUS::SubSurfaceComponent::NUM_CT; ++i)
		m_ui->comboBoxSubSurfaceType->addItem(VICUS::KeywordListQt::Keyword("SubSurfaceComponent::SubSurfaceComponentType", i), i);
	m_ui->comboBoxSubSurfaceType->blockSignals(false);

	// construction group box
	m_ui->lineEditWindowName->setReadOnly(true);

	updateInput(-1);
}


SVDBSubSurfaceComponentEditWidget::~SVDBSubSurfaceComponentEditWidget() {
	delete m_ui;
}


void SVDBSubSurfaceComponentEditWidget::setup(SVDatabase * db, SVAbstractDatabaseTableModel * dbModel) {
	m_db = db;
	m_dbModel = dynamic_cast<SVDBSubSurfaceComponentTableModel*>(dbModel);
}


void SVDBSubSurfaceComponentEditWidget::updateInput(int id) {
	m_current = nullptr; // disable edit triggers

	if (id == -1) {
		// disable all controls
		setEnabled(false);

		// clear input controls
		m_ui->lineEditName->setString(IBK::MultiLanguageString());

		// construction property info fields
		m_ui->comboBoxSubSurfaceType->setCurrentText("");
		m_ui->lineEditWindowName->setText("");

		m_ui->lineEditBoundaryConditionSideAName->setText("");

		m_ui->lineEditBoundaryConditionSideBName->setText("");
		m_ui->pushButtonFalseColor->setColor(Qt::black);

		return;
	}
	// re-enable all controls
	setEnabled(true);

	VICUS::SubSurfaceComponent * comp = const_cast<VICUS::SubSurfaceComponent*>(m_db->m_subSurfaceComponents[(unsigned int)id]);
	m_current = comp;

	// now update the GUI controls
	m_ui->comboBoxSubSurfaceType->blockSignals(true);
	m_ui->lineEditName->setString(comp->m_displayName);
	int typeIdx = m_ui->comboBoxSubSurfaceType->findData(comp->m_type);
	m_ui->comboBoxSubSurfaceType->setCurrentIndex(typeIdx);
	m_ui->comboBoxSubSurfaceType->blockSignals(false);

	m_ui->pushButtonFalseColor->blockSignals(true);
	m_ui->pushButtonFalseColor->setColor(m_current->m_color);
	m_ui->pushButtonFalseColor->blockSignals(false);

	m_ui->lineEditBoundaryConditionSideAName->setEnabled(true);
	m_ui->lineEditBoundaryConditionSideBName->setEnabled(true);

	double surfaceResistanceSideA = 0;
	double surfaceResistanceSideB = 0;

	const VICUS::BoundaryCondition *bcA = m_db->m_boundaryConditions[comp->m_idSideABoundaryCondition];
	if (bcA != nullptr){
		m_ui->lineEditBoundaryConditionSideAName->setText(QtExt::MultiLangString2QString(bcA->m_displayName));
		m_ui->textBrowserBCSideA->setHtml(bcA->htmlDescription());

		if(bcA->m_heatConduction.m_modelType == NANDRAD::InterfaceHeatConduction::MT_Constant){
			double hc = bcA->m_heatConduction.m_para[NANDRAD::InterfaceHeatConduction::P_HeatTransferCoefficient].value;
			surfaceResistanceSideA = hc > 0 ? 1/hc : 0;
		}
	}
	else {
		m_ui->lineEditBoundaryConditionSideAName->clear();
		m_ui->textBrowserBCSideA->clear();
	}

	const VICUS::BoundaryCondition *bcB = m_db->m_boundaryConditions[comp->m_idSideBBoundaryCondition];
	if (bcB != nullptr){
		m_ui->lineEditBoundaryConditionSideBName->setText(QtExt::MultiLangString2QString(bcB->m_displayName));
		m_ui->textBrowserBCSideB->setHtml(bcB->htmlDescription());

		if(bcB->m_heatConduction.m_modelType == NANDRAD::InterfaceHeatConduction::MT_Constant){
			double hc = bcB->m_heatConduction.m_para[NANDRAD::InterfaceHeatConduction::P_HeatTransferCoefficient].value;
			surfaceResistanceSideB = hc > 0 ? 1/hc : 0;
		}
	}
	else {
		m_ui->lineEditBoundaryConditionSideBName->clear();
		m_ui->textBrowserBCSideB->clear();
	}


	// TODO : distinguish between doors/windows etc.
	const VICUS::Window *win = m_db->m_windows[comp->m_idWindow];
	if (win != nullptr) {
		m_ui->lineEditWindowName->setText(QtExt::MultiLangString2QString(win->m_displayName));
	}
	else {
		m_ui->lineEditWindowName->setText("");
	}

	// for built-ins, disable editing/make read-only
	bool isEditable = !comp->m_builtIn;
	m_ui->lineEditName->setReadOnly(!isEditable);
	m_ui->comboBoxSubSurfaceType->setEnabled(isEditable);
	m_ui->toolButtonSelectWindow->setEnabled(isEditable);
	m_ui->toolButtonSelectBoundaryConditionSideAName->setEnabled(isEditable);
	m_ui->toolButtonSelectBoundaryConditionSideBName->setEnabled(isEditable);

	m_ui->lineEditBoundaryConditionSideAName->setReadOnly(!isEditable);
	m_ui->lineEditBoundaryConditionSideBName->setReadOnly(!isEditable);

	m_ui->toolButtonRemoveBoundaryConditionSideA->setEnabled(isEditable);
	m_ui->toolButtonRemoveBoundaryConditionSideB->setEnabled(isEditable);
}


void SVDBSubSurfaceComponentEditWidget::on_lineEditName_editingFinished(){
	Q_ASSERT(m_current != nullptr);

	if (m_current->m_displayName != m_ui->lineEditName->string()) {
		m_current->m_displayName = m_ui->lineEditName->string();
		modelModify();
	}
}


void SVDBSubSurfaceComponentEditWidget::on_comboBoxSubSurfaceType_currentIndexChanged(int /*index*/){
	if (m_current == nullptr) return; // m_current is nullptr, when nothing is selected and controls are defaulted to "empty"

	VICUS::SubSurfaceComponent::SubSurfaceComponentType ct = static_cast<VICUS::SubSurfaceComponent::SubSurfaceComponentType>(
				m_ui->comboBoxSubSurfaceType->currentData().toInt());
	if (ct != m_current->m_type) {
		m_current->m_type = ct;
		modelModify();
	}
}


void SVDBSubSurfaceComponentEditWidget::on_toolButtonSelectWindow_clicked() {
	// get construction edit dialog from mainwindow
	SVDatabaseEditDialog * editDialog = SVMainWindow::instance().dbWindowEditDialog();
	unsigned int winId = editDialog->select(m_current->m_idWindow);
	if (winId != m_current->m_idWindow) {
		m_current->m_idWindow = winId;
		modelModify();
	}
	updateInput((int)m_current->m_id);
}


void SVDBSubSurfaceComponentEditWidget::on_toolButtonSelectBoundaryConditionSideAName_clicked() {
	// get boundary condition edit dialog from mainwindow
	SVDatabaseEditDialog * bcEditDialog = SVMainWindow::instance().dbBoundaryConditionEditDialog();
	unsigned int bcId = bcEditDialog->select(m_current->m_idSideABoundaryCondition);
	if (bcId != m_current->m_idSideABoundaryCondition) {
		m_current->m_idSideABoundaryCondition = bcId;
		modelModify();
	}
	updateInput((int)m_current->m_id);
}


void SVDBSubSurfaceComponentEditWidget::on_toolButtonSelectBoundaryConditionSideBName_clicked() {
	// get boundary condition edit dialog from mainwindow
	SVDatabaseEditDialog * bcEditDialog = SVMainWindow::instance().dbBoundaryConditionEditDialog();
	unsigned int bcId = bcEditDialog->select(m_current->m_idSideBBoundaryCondition);
	if (bcId != m_current->m_idSideBBoundaryCondition){
		m_current->m_idSideBBoundaryCondition = bcId;
		modelModify();
	}
	updateInput((int)m_current->m_id);
}

void SVDBSubSurfaceComponentEditWidget::modelModify() {
	m_db->m_subSurfaceComponents.m_modified = true;
	m_dbModel->setItemModified(m_current->m_id); // tell model that we changed the data

}


void SVDBSubSurfaceComponentEditWidget::on_pushButtonFalseColor_clicked() {
	Q_ASSERT(m_current != nullptr);

	if (m_current->m_color != m_ui->pushButtonFalseColor->color()) {
		m_current->m_color = m_ui->pushButtonFalseColor->color();
		m_db->m_subSurfaceComponents.m_modified = true;
		m_dbModel->setItemModified(m_current->m_id); // tell model that we changed the data
	}
}


void SVDBSubSurfaceComponentEditWidget::on_toolButtonRemoveBoundaryConditionSideA_clicked() {

	m_current->m_idSideABoundaryCondition = VICUS::INVALID_ID;

	modelModify();
	updateInput((int)m_current->m_id);
}


void SVDBSubSurfaceComponentEditWidget::on_toolButtonRemoveBoundaryConditionSideB_clicked() {

	m_current->m_idSideBBoundaryCondition = VICUS::INVALID_ID;

	modelModify();
	updateInput((int)m_current->m_id);
}
