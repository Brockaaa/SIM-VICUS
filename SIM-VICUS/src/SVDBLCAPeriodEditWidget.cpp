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

void SVDBLCAPeriodEditWidget::importDatabaseLCAPeriods(const IBK::Path & csvPath)
{
	FUNCID(SVDBLCAPeriodEditWidget::importDatabaseLCAPeriods);

	// Read csv
	std::vector< std::string > dataLines;

	// Explode all lines
	if (IBK::FileReader::readAll(csvPath, dataLines, std::vector<std::string>()) == -1)
		throw IBK::Exception("Error reading csv-file with LCA Database!", FUNC_ID);

	// Remove header
	dataLines.erase(dataLines.begin());

	// extract vector of string-xy-pairs
	std::vector<std::string> tokens;

	std::map<QString, VICUS::LCAPeriod> dataSets;

	unsigned int id = 1112500; //See SVDatabase.cpp

	for (unsigned int row = 0; row<dataLines.size(); ++row) {
		std::string &line = dataLines[row];
		IBK::explode(line, tokens, ";", IBK::EF_KeepEmptyTokens);

		VICUS::LCAPeriod *lca = nullptr;

		QString uuid = QString::fromStdString(std::to_string(row));
		dataSets[uuid] = VICUS::LCAPeriod();
		lca->m_id = id++;

		for (unsigned int col = 0; col < tokens.size(); ++col){

			std::string t = IBK::ANSIToUTF8String(tokens[col]);

			switch (col) {
			// Not imported columns
			case ColKg: {
				if(t == "")
					continue;
				unsigned int valKg;
				valKg = IBK::string2val<unsigned int>(t);
				VICUS::KeywordList::setParameter(lca->m_para, "LCAPeriod::para_t", VICUS::LCAPeriod::P_Costgroup, valKg);
				} break;
			case ColCode: {
				if(t == "")
					continue;
				unsigned int valCode;
				valCode = IBK::string2val<unsigned int>(t);
				VICUS::KeywordList::setParameter(lca->m_para, "LCAPeriod::para_t", VICUS::LCAPeriod::P_Code, valCode);
				} break;
			case ColNameDe: {
				if(t == "")
					continue;
				lca->m_displayName.setString(t, "De");
				} break;
			case ColNameEn: {
				if(t == "")
					continue;
				lca->m_displayName.setString(t, "En");
				} break;
			case ColLifetime: {
				if(t == "")
					continue;
				unsigned int valLifetime;
				valLifetime = IBK::string2val<unsigned int>(t);
				VICUS::KeywordList::setParameter(lca->m_para, "LCAPeriod::para_t", VICUS::LCAPeriod::P_Lifetime, valLifetime);
				} break;
			case ColReplacementCycles: {
				if(t == "")
					continue;
				unsigned int valReplacementCycles;
				valReplacementCycles = IBK::string2val<unsigned int>(t);
				VICUS::KeywordList::setParameter(lca->m_para, "LCAPeriod::para_t", VICUS::LCAPeriod::P_ReplacementCycles, valReplacementCycles);
				} break;
			case ColMaintenance: {
				if(t == "")
					continue;
				unsigned int valMaintenance;
				valMaintenance = IBK::string2val<unsigned int>(t);
				VICUS::KeywordList::setParameter(lca->m_para, "LCAPeriod::para_t", VICUS::LCAPeriod::P_Maintenance, valMaintenance);
				} break;
			case ColRepair: {
				if(t == "")
					continue;
				unsigned int valRepair;
				valRepair = IBK::string2val<unsigned int>(t);
				VICUS::KeywordList::setParameter(lca->m_para, "LCAPeriod::para_t", VICUS::LCAPeriod::P_Repair, valRepair);
				} break;
			case ColLCC: {
				if(t == "")
					continue;
				unsigned int valLCC;
				valLCC = IBK::string2val<bool>(t);
				lca->m_flags[VICUS::LCAPeriod::F_LCC].set("LCC", valLCC);
				} break;
			case ColLCAStandard: {
				if(t == "")
					continue;
				unsigned int valLCAStandard;
				valLCAStandard = IBK::string2val<bool>(t);
				lca->m_flags[VICUS::LCAPeriod::F_LCAStandard].set("LCC", valLCAStandard);
				} break;
			case ColLCASimplifiedProcedure: {
				if(t == "")
					continue;
				unsigned int valLCASimplifiedProcedure;
				valLCASimplifiedProcedure = IBK::string2val<bool>(t);
				lca->m_flags[VICUS::LCAPeriod::F_LCASimplifiedProcedure].set("LCC", valLCASimplifiedProcedure);
				} break;
			}

		}
	}

	SVDatabaseEditDialog *lcaEditDialog = SVMainWindow::instance().dbLCAPeriodEditDialog();
	Q_ASSERT(lcaEditDialog != nullptr);

	dynamic_cast<SVDBLCAPeriodTableModel*>(lcaEditDialog->dbModel())->importDatasets(dataSets);
}

SVDBLCAPeriodEditWidget::SVDBLCAPeriodEditWidget(QWidget *parent) :
	SVAbstractDatabaseEditWidget(parent),
	m_ui(new Ui::SVDBLCAPeriodEditWidget)
{
	m_ui->setupUi(this);
	m_ui->verticalLayoutMaster->setMargin(4);


	// initial state is "nothing selected"
	//updateInput(-1);
}


SVDBLCAPeriodEditWidget::~SVDBLCAPeriodEditWidget() {
	//delete m_ui;
}


void SVDBLCAPeriodEditWidget::setup(SVDatabase * db, SVAbstractDatabaseTableModel * dbModel) {
	m_db = db;
	m_dbModel = dynamic_cast<SVDBLCAPeriodTableModel*>(dbModel);
}


void SVDBLCAPeriodEditWidget::updateInput(int id) {
	m_current = nullptr; // disable edit triggers

}


void SVDBLCAPeriodEditWidget::modelModify() {
	m_db->m_lcaPeriods.m_modified = true;
	m_dbModel->setItemModified(m_current->m_id); // tell model that we changed the data
}

// TODO Remove, Debug only during implementation
#include <QtExt_Directories.h>
void SVDBLCAPeriodEditWidget::on_pushButton_clicked() {
	IBK::Path userDbDir(QtExt::Directories::userDataDir().toStdString());
	importDatabaseLCAPeriods(userDbDir / "db_lca_periods.csv");
}

