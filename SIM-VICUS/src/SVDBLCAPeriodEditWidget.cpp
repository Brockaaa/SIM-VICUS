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

#include "SVDBLCAPeriodEditWidget.h"
#include "ui_SVDBLCAPeriodEditWidget.h"

#include <VICUS_KeywordListQt.h>
#include <NANDRAD_KeywordListQt.h>
#include <NANDRAD_KeywordList.h>

#include <QtExt_LanguageHandler.h>
#include <SVConversions.h>

#include <IBK_FileReader.h>

#include "SVDBLCAPeriodTableModel.h"
#include "SVConstants.h"
#include "SVSettings.h"
#include "SVMainWindow.h"
#include "SVDatabaseEditDialog.h"

void SVDBLCAPeriodEditWidget::readDatabaseLCAPeriods(const IBK::Path & csvPath)
{
	FUNCID(SVDBLCAPeriodEditWidget::readDatabaseLCAPeriods);

	// Read csv
	std::vector< std::string > dataLines;

	// Explode all lines
	if (IBK::FileReader::readAll(csvPath, dataLines, std::vector<std::string>()) == -1)
		throw IBK::Exception("Error reading csv-file with LCA Database!", FUNC_ID);

	// Remove header
	dataLines.erase(dataLines.begin());

	// extract vector of string-xy-pairs
	std::vector<std::string> tokens;

	//std::map<QString, VICUS::EpdDataset> dataSets;




}

SVDBLCAPeriodEditWidget::SVDBLCAPeriodEditWidget(QWidget *parent) :
	SVAbstractDatabaseEditWidget(parent),
	m_ui(new Ui::SVDBLCAPeriodEditWidget)
{

	// initial state is "nothing selected"
	updateInput(-1);
}


SVDBLCAPeriodEditWidget::~SVDBLCAPeriodEditWidget() {
	delete m_ui;
}


void SVDBLCAPeriodEditWidget::setup(SVDatabase * db, SVAbstractDatabaseTableModel * dbModel) {
	m_db = db;
	m_dbModel = dynamic_cast<SVDBLCAPeriodTableModel*>(dbModel);
}


void SVDBLCAPeriodEditWidget::updateInput(int id) {
	m_current = nullptr; // disable edit triggers

}


void SVDBLCAPeriodEditWidget::on_lineEditName_editingFinished() {
	Q_ASSERT(m_current != nullptr);

}


void SVDBLCAPeriodEditWidget::on_pushButtonColor_colorChanged() {
	Q_ASSERT(m_current != nullptr);

}


void SVDBLCAPeriodEditWidget::modelModify() {
	m_db->m_lcaPeriods.m_modified = true;
	m_dbModel->setItemModified(m_current->m_id); // tell model that we changed the data
}

