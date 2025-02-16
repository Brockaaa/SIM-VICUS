#include "SVLcaLccSettingsDialog.h"
#include "ui_SVLcaLccSettingsDialog.h"

#include "IBKMK_3DCalculations.h"

// SIM-VIUCS
#include "SVSettings.h"
#include "SVDatabase.h"
#include "SVDatabaseEditDialog.h"
#include "SVDBEpdTableModel.h"
#include "SVProjectHandler.h"
#include "SVMainWindow.h"

// IBK
#include <IBK_Parameter.h>
#include <IBK_FileReader.h>
#include <IBK_StopWatch.h>

// VICUS
#include <VICUS_KeywordList.h>
#include <VICUS_Project.h>
#include <VICUS_EpdDataset.h>
#include <VICUS_EpdModuleDataset.h>

// Qt-Ext
#include <QtExt_Conversions.h>

// Qt
#include <QProgressDialog>

// std
#include <fstream>


SVLcaLccSettingsDialog::SVLcaLccSettingsDialog(QWidget *parent,
											   VICUS::LcaSettings & lcaSettings,
											   VICUS::LccSettings & lccSettings) :
	QDialog(parent),
	m_ui(new Ui::SVLcaLccSettingsDialog),
	m_lcaSettings(&lcaSettings),
	m_lccSettings(&lccSettings),
	m_prj(SVProjectHandler::instance().project())
{
	m_ui->setupUi(this);
	// layout()->setMargin(0);

	//	m_lcaSettings->initDefaults();

	m_db = &SVSettings::instance().m_db;

	m_ui->checkBoxA1->setProperty("category", (int)VICUS::EpdModuleDataset::M_A1);
	m_ui->checkBoxA2->setProperty("category", (int)VICUS::EpdModuleDataset::M_A2);
	m_ui->checkBoxA3->setProperty("category", (int)VICUS::EpdModuleDataset::M_A3);
	m_ui->checkBoxA4->setProperty("category", (int)VICUS::EpdModuleDataset::M_A4);
	m_ui->checkBoxA5->setProperty("category", (int)VICUS::EpdModuleDataset::M_A5);
	m_ui->checkBoxB1->setProperty("category", (int)VICUS::EpdModuleDataset::M_B1);
	m_ui->checkBoxB2->setProperty("category", (int)VICUS::EpdModuleDataset::M_B2);
	m_ui->checkBoxB3->setProperty("category", (int)VICUS::EpdModuleDataset::M_B3);
	m_ui->checkBoxB4->setProperty("category", (int)VICUS::EpdModuleDataset::M_B4);
	m_ui->checkBoxB5->setProperty("category", (int)VICUS::EpdModuleDataset::M_B5);
	m_ui->checkBoxB6->setProperty("category", (int)VICUS::EpdModuleDataset::M_B6);
	m_ui->checkBoxB7->setProperty("category", (int)VICUS::EpdModuleDataset::M_B7);
	m_ui->checkBoxC1->setProperty("category", (int)VICUS::EpdModuleDataset::M_C1);
	m_ui->checkBoxC2->setProperty("category", (int)VICUS::EpdModuleDataset::M_C2);
	m_ui->checkBoxC3->setProperty("category", (int)VICUS::EpdModuleDataset::M_C3);
	m_ui->checkBoxC4->setProperty("category", (int)VICUS::EpdModuleDataset::M_C4);
	m_ui->checkBoxD ->setProperty("category", (int)VICUS::EpdModuleDataset::M_D);


	m_ui->checkBoxA1->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_A1));
	m_ui->checkBoxA2->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_A2));
	m_ui->checkBoxA3->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_A3));
	m_ui->checkBoxA4->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_A4));
	m_ui->checkBoxA5->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_A5));

	m_ui->checkBoxB1->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_B1));
	m_ui->checkBoxB2->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_B2));
	m_ui->checkBoxB3->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_B3));
	m_ui->checkBoxB4->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_B4));
	m_ui->checkBoxB5->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_B5));
	m_ui->checkBoxB6->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_B6));
	m_ui->checkBoxB7->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_B7));

	m_ui->checkBoxC1->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_C1));
	m_ui->checkBoxC2->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_C2));
	m_ui->checkBoxC3->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_C3));
	m_ui->checkBoxC4->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_C4));

	m_ui->checkBoxD->setText(VICUS::KeywordList::Description("EpdModuleDataset::Module", VICUS::EpdModuleDataset::M_D));

	connect(m_ui->checkBoxA1, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxA2, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxA3, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxA4, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxA5, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxB1, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxB2, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxB3, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxB4, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxB5, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxB6, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxB7, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxC1, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxC2, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxC3, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxC4, &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);
	connect(m_ui->checkBoxD,  &QCheckBox::stateChanged, this, &SVLcaLccSettingsDialog::setModuleState);

	for(int i=0; i<VICUS::LcaSettings::NUM_CM; ++i)
		m_ui->comboBoxCalculationMode->addItem(VICUS::KeywordList::Description("LcaSettings::CalculationMode", i), i);

	for(int i=0; i<VICUS::LcaSettings::NUM_CS; ++i)
		m_ui->comboBoxCertificationSystem->addItem(VICUS::KeywordList::Description("LcaSettings::CertificationSytem", i), i);

	m_ui->lineEditArea->setup(0, 1e10, "Net usage area of Building(s)", false, true);
	m_ui->lineEditPriceIncreaseEnergy->setup(0, 100, "Energy Price increase", true, true);
	m_ui->lineEditPriceIncreaseGeneral->setup(0, 100, "General Price increase", true, true);

	m_ui->lineEditGasPrice->setup(0, 1e10, "Gas price for evaluation in €/kWh", false, true);
	m_ui->lineEditCoalPrice->setup(0, 1e10, "Coal price for evaluation in €/kWh", false, true);
	m_ui->lineEditElectricityPrice->setup(0, 1e10, "Electricity price for evaluation in €/kWh", false, true);

	m_ui->filepathOekoBauDat->setup(QString(), true, true, tr("ÖKOBAUDAT-csv (*.csv)"),
									SVSettings::instance().m_dontUseNativeDialogs);
	m_ui->filepathOekoBauDat->lineEdit()->setPlaceholderText(tr("<select csv with ÖKOBAUDAT>"));

	updateUi();
}


SVLcaLccSettingsDialog::~SVLcaLccSettingsDialog() {
	delete m_ui;
}


void SVLcaLccSettingsDialog::calculateLCA() {
	FUNCID(SVLcaLccSettingsDialog::calculateLCA);

//	IBK::Path path(m_ui->filepathResults->filename().toStdString());
//	QString filename = m_ui->lineEditResultName->text();
//	IBK::Path file(filename.toStdString());
//	file.addExtension(".txt");
//	path /= file;

//	if(!path.isValid()) {
//		QMessageBox::warning(this, tr("Invalid Result path or file"), tr("Define a valid result path and filename first before calculating LCA."));
//		return;
//	}


	/// 1) Aggregate all used components from project and sum up all their areas
	/// 2) go through all layers and their referenced epds and use the epds reference unit for global calculation
	/// 3) Global calculation means that layer data needs to be converted in a manner that it coresponds to reference unit
	/// 4) Now calculate the final LCA Data for each component and material layer using converted material data and reference unit
	/// 5) Aggregate data for each component type --> such as floor, etc.

	// Reset all LCA Data from previous calculations.
	resetLcaData();

	// First we aggregate all data for used components
	aggregateProjectComponents();

	// Calculate all total EPD Data for Components
	calculateTotalLcaDataForComponents();

	// Calculates all usage specific data
	// calculateUsageSpecificData();

	// Aggregate all data by type of component
	aggregateAggregatedComponentsByType();

	// Write calculation to file
	//writeLcaDataToTxtFile(path);

	{
#if 0
		FUNCID(LCA::calculateLCA);

		/*! Summarize all components with all constructions and material layers.
		Categorize all construction with their surface areas.
	*/

		/* Annahmen: diese Strukturen müssen umbenannt werden. */
		std::map<unsigned int, VICUS::Component>				m_dbComponents;
		std::map<unsigned int, VICUS::Construction>				m_dbConstructions;
		std::map<unsigned int, VICUS::Material>					m_dbOpaqueMaterials;
		std::map<unsigned int, VICUS::EPDDataset>				m_dbEPDs;


		struct MatEpd{
			VICUS::EPDDataset m_epdA;
			VICUS::EPDDataset m_epdB;
			VICUS::EPDDataset m_epdC;
			VICUS::EPDDataset m_epdD;
		};

		std::map<unsigned int, LCAComponentResult>		compRes;
		std::map<unsigned int, LCAComponentResult>		compResErsatz;

		//holds the data for each material
		std::map<unsigned int, MatEpd>					materialIdAndEpd;
		double netFloorArea = m_building.m_netFloorArea;

		/* Calculate all surface areas according to all components. */
		for (auto &bl : m_building.m_buildingLevels) {
			for (auto &r : bl.m_rooms) {
				for (auto &s : r.m_surfaces) {
					const VICUS::Surface &surf = s;

					// get component
					const VICUS::ComponentInstance * compInstance = s.m_componentInstance;
					if (compInstance != nullptr) {
						VICUS::Component comp = elementExists<VICUS::Component>(m_dbComponents, compInstance->m_idComponent,
																				s.m_displayName.toStdString(),"Component", "surface");
						//save surface area
						compRes[comp.m_id].m_area += surf.geometry().area();
					}
					else {
						/// TODO : error handling if component instance pointer is empty (no component associated)
					}
				}
			}
		}

		//calculate all lca for each component
		for (auto &c : compRes) {
			const VICUS::Component &comp = m_dbComponents[c.first];

			//opaque construction
			if(comp.m_idConstruction != VICUS::INVALID_ID){
				//get construction
				///TODO Dirk baufähig gemacht müsste rückgängig gemacht werden
				VICUS::Construction constr;
				//					elementExists<VICUS::Construction>(m_dbConstructions, comp.m_idOpaqueConstruction,
				//													   comp.m_displayName.toStdString(),"Construction",
				//													   "component");

				//calculate each construction
				for(auto l : constr.m_materialLayers){
					//check if material exists
					VICUS::Material mat =
							elementExists<VICUS::Material>(m_dbOpaqueMaterials, l.m_idMaterial,
														   constr.m_displayName.string(),
														   "Material",
														   "construction");

					//material exists already in the new user database
					if(materialIdAndEpd.find(mat.m_id) != materialIdAndEpd.end())
						continue;

					MatEpd &matEpd = materialIdAndEpd[mat.m_id];
					//check each material epd id
					for (auto idEpd : mat.m_idEpds) {
						if(idEpd == VICUS::INVALID_ID)
							continue;

						VICUS::EPDDataset epd = elementExists<VICUS::EPDDataset>(m_dbEPDs, idEpd,
																				 mat.m_displayName.string(),
																				 "EPD",
																				 "material");

						//if we found the right dataset add values A1- A2
						if(epd.m_module == VICUS::EPDDataset::M_A1 ||
								epd.m_module == VICUS::EPDDataset::M_A2 ||
								epd.m_module == VICUS::EPDDataset::M_A1_A2||
								epd.m_module == VICUS::EPDDataset::M_A3 ||
								epd.m_module == VICUS::EPDDataset::M_A1_A3){
							//add all values in a category A
							for (unsigned int i=0;i< VICUS::EPDDataset::NUM_P; ++i) {
								IBK::Parameter para = epd.m_para[i];
								//...
								if(para.value != 0){
									matEpd.m_epdA.m_para[i].set(para.name,
																matEpd.m_epdA.m_para[i].get_value(para.unit())
																+ para.get_value(para.unit()),
																para.unit());
								}
							}
						}
						else if (epd.m_module == VICUS::EPDDataset::M_B6) {
							//add all values in a category B
							for (unsigned int i=0;i< VICUS::EPDDataset::NUM_P; ++i) {
								IBK::Parameter para = epd.m_para[i];
								//...
								if(para.value != 0){
									matEpd.m_epdB.m_para[i].set(para.name,
																matEpd.m_epdB.m_para[i].get_value(para.unit())
																+ para.get_value(para.unit()),
																para.unit());
								}
							}
						}
						else if (epd.m_module == VICUS::EPDDataset::M_C2 ||
								 epd.m_module == VICUS::EPDDataset::M_C2_C4 ||
								 epd.m_module == VICUS::EPDDataset::M_C3 ||
								 epd.m_module == VICUS::EPDDataset::M_C2_C3 ||
								 epd.m_module == VICUS::EPDDataset::M_C3_C4 ||
								 epd.m_module == VICUS::EPDDataset::M_C4) {
							//add all values in a category C
							for (unsigned int i=0;i< VICUS::EPDDataset::NUM_P; ++i) {
								IBK::Parameter para = epd.m_para[i];
								//...
								if(para.value != 0){
									matEpd.m_epdC.m_para[i].set(para.name,
																matEpd.m_epdC.m_para[i].get_value(para.unit())
																+ para.get_value(para.unit()),
																para.unit());
								}
							}
						}
						else if (epd.m_module == VICUS::EPDDataset::M_D) {
							//add all values in a category D
							for (unsigned int i=0;i< VICUS::EPDDataset::NUM_P; ++i) {
								IBK::Parameter para = epd.m_para[i];
								//...
								if(para.value != 0){
									matEpd.m_epdD.m_para[i].set(para.name,
																matEpd.m_epdD.m_para[i].get_value(para.unit())
																+ para.get_value(para.unit()),
																para.unit());
								}
							}
						}
					}
				}
			}
		}



		for (auto &e : compRes) {
			//Component result object
			LCAComponentResult &comp = e.second;
			unsigned int compId = e.first;

			//check if opaque construction is available
			if(m_dbComponents[compId].m_idConstruction != VICUS::INVALID_ID){
				const VICUS::Construction &constr = m_dbConstructions[m_dbComponents[compId].m_idConstruction];

				//get values for all material layers in each category of the lifecycle
				for(auto &l : constr.m_materialLayers){
					MatEpd &matEpd = materialIdAndEpd[l.m_idMaterial];
					double rho = m_dbOpaqueMaterials[l.m_idMaterial].m_para[VICUS::Material::P_Density].get_value("kg/m3");

					//				addEpdMaterialToComponent(matEpd.m_epdA, comp, compResErsatz[compId],
					//							   l.m_lifeCylce, l.m_thickness.get_value("m"),
					//							   rho, 0, m_adjustment);

					addEpdMaterialToComponent(matEpd.m_epdB, comp, compResErsatz[compId],
											  0, l.m_thickness.get_value("m"),
											  rho, 1, m_adjustment);

					//				addEpdMaterialToComponent(matEpd.m_epdC, comp, compResErsatz[compId],
					//							   l.m_lifeCylce, l.m_thickness.get_value("m"),
					//							   rho, 2, m_adjustment);

					//				addEpdMaterialToComponent(matEpd.m_epdD, comp, compResErsatz[compId],
					//							   l.m_lifeCylce, l.m_thickness.get_value("m"),
					//							   rho, 3, m_adjustment);

				}

			}

		}
#endif
	}
}


bool convertString2Val(double &val, std::string &text, unsigned int row, unsigned int column) {
	if(text == "") {
		val = 0.0;
		return true;
	}

	std::replace( text.begin(), text.end(), ',', '.'); // replace all ',' to '.'

	try {
		val = IBK::string2val<double>(text);
	}  catch (IBK::Exception &ex) {
		IBK::IBK_Message(IBK::FormatString("%4\nCould not convert string '%1' of row %2 and column %3")
						 .arg(text).arg(row+1).arg(column+1).arg(ex.what()));
		return false;
	}
		return true;
}


template<typename T>
void SVLcaLccSettingsDialog::setValue(T &member, const T &value, bool foundExistingEpd) {
	if(!foundExistingEpd)
		member = value;
	else {
		if(member != value) {
			qDebug() << "Error between already defined values of EPD '" << member << "' <> '" << value << "'";
		}
	}
}



void SVLcaLccSettingsDialog::importOkoebauDat(const IBK::Path & csvPath) {
	FUNCID(SVDBEPDEditWidget::importOkoebauDat);

	// Read csv with ÖKOBAUDAT
	std::vector< std::string > dataLines;

	if (SVSettings::instance().showDoNotShowAgainQuestion(this, "reloading-oekobaudat",
														  tr("Reloading ÖKOBAUDAT"),
														  tr("Reloading ÖKOBAUDAT will delete all references to currently existing EPDs in Database. Continue?"),
														  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
		return;

	// Explode all lines
	if (IBK::FileReader::readAll(csvPath, dataLines, std::vector<std::string>()) == -1)
		throw IBK::Exception("Error reading csv-file with ÖKÖBAUDAT!", FUNC_ID);

	// Remove header
	dataLines.erase(dataLines.begin());

	// extract vector of string-xy-pairs
	std::vector<std::string> tokens;

	QProgressDialog *dlg = new QProgressDialog(tr("Importing EPD-Database"), tr("Stop"), 0, (int)dataLines.size(), this);

	std::map<QString, VICUS::EpdDataset> dataSets;

	IBK::StopWatch timer;
	timer.start();

	std::map<std::string, std::string> oekobauDatUnit2IBKUnit;
	oekobauDatUnit2IBKUnit["qm"] = "m2";
	oekobauDatUnit2IBKUnit["pcs."] = "-";
	oekobauDatUnit2IBKUnit["kgkm"] = "kg/m3";
	oekobauDatUnit2IBKUnit["MJ"] = "MJ";
	oekobauDatUnit2IBKUnit["m3"] = "m3";
	oekobauDatUnit2IBKUnit["m"] = "m";
	oekobauDatUnit2IBKUnit["kg"] = "kg";
	oekobauDatUnit2IBKUnit["a"] = "a";
	oekobauDatUnit2IBKUnit[""] = "-";

	unsigned int id = 1090000;

	for (unsigned int row = 0; row<dataLines.size(); ++row) {
		std::string &line = dataLines[row];
		//		IBK::trim(line, ",");
		//		IBK::trim(line, "\"");
		//		IBK::trim(line, "MULTILINESTRING ((");
		//		IBK::trim(line, "))");
		IBK::explode(line, tokens, ";", IBK::EF_KeepEmptyTokens);

		VICUS::EpdDataset *epd = nullptr;
		VICUS::EpdModuleDataset *epdCategoryDataSet = new VICUS::EpdModuleDataset;

		// convert this vector to double and add it as a graph
		std::vector<std::vector<double> > polyLine;
		for (unsigned int col = 0; col < tokens.size(); ++col){

			bool foundExistingEpd = false;
#if defined(win32)
			std::string t = IBK::ANSIToUTF8String(tokens[col]);
#else
			std::string t = tokens[col];

			std::string strOut;
			for (std::string::iterator it = t.begin(); it != t.end(); ++it)
			{
				uint8_t ch = *it;
				if (ch < 0x80) {
					strOut.push_back(ch);
				}
				else {
					strOut.push_back(0xc0 | ch >> 6);
					strOut.push_back(0x80 | (ch & 0x3f));
				}
			}
			t = strOut;
#endif

			if(timer.difference() > 200) {
				dlg->setValue(row);
				qApp->processEvents();
			}

			if(dlg->wasCanceled()) {
				IBK::IBK_Message(IBK::FormatString("EPD-Import has been interrupted by user."));
				return;
			}

			// qDebug() << "Row: " << row << " Column: " << col << " Text: " << QString::fromStdString(t);

			switch (col) {
			// Not imported coloumns
			case ColVersion:
			case ColConformity:
			case ColCountryCode:
			case ColReferenceYear:
			case ColPublishedOn:
			case ColRegistrationNumber:
			case ColRegistrationBody:
			case ColUUIDOfThePredecessor: {
				if(t == "")
					continue;
			} break;

			case ColUUID: {
				if(t == "")
					continue;

				QString uuid = QString::fromStdString(t);

				// do we already have an EPD with the specific UUID
				if(dataSets.find(uuid) != dataSets.end()) { // We found one
					epd = &dataSets[uuid];
					foundExistingEpd = true;
				}
				else { // Create new one
					dataSets[uuid] = VICUS::EpdDataset();
					epd = &dataSets[uuid];
					epd->m_uuid = uuid;
					epd->m_id = id++;
				}

				setValue<QString>(epd->m_uuid, uuid, foundExistingEpd);

			} break;
			case ColNameDe:
				if(t == "")
					continue;
				epd->m_displayName.setString(t, "De");
				break;
			case ColNameEn:
				if(t == "")
					continue;
				epd->m_displayName.setString(t, "En");
			break;
			case ColCategoryDe:
				if(t == "")
					continue;
				epd->m_category.setString(t, "De");
			break;
			case ColCategoryEn:
				if(t == "")
					continue;
				epd->m_category.setString(t, "En");
			break;
			case ColType: {
				if(t == "")
					continue;

				VICUS::EpdDataset::Type type = VICUS::EpdDataset::NUM_T;

				if (t == "average dataset")
					type = VICUS::EpdDataset::T_Average;
				else if (t == "specific dataset")
					type = VICUS::EpdDataset::T_Specific;
				else if (t == "representative dataset")
					type = VICUS::EpdDataset::T_Representative;
				else if (t == "generic dataset")
					type = VICUS::EpdDataset::T_Generic;
				else if (t == "template dataset")
					type = VICUS::EpdDataset::T_Template;

				setValue<VICUS::EpdDataset::Type>(epd->m_type, type, foundExistingEpd);

			} break;
			case ColExpireYear:			epd->m_expireYear = QString::fromStdString(t);			break;
			case ColDeclarationOwner:	epd->m_manufacturer = QString::fromStdString(t);			break;
			case ColReferenceSize: {
				if(t == "" || t == "not available")
					continue;

				double val;
				if(!convertString2Val(val, t, row, col))
					continue;


				setValue<double>(epd->m_referenceQuantity, val, foundExistingEpd);
			} break;
			case ColReferenceUnit: {
				if(t == "")
					continue;

				if (oekobauDatUnit2IBKUnit.find(t) == oekobauDatUnit2IBKUnit.end())
					continue;

				if(!foundExistingEpd) {
					IBK::Unit unit(oekobauDatUnit2IBKUnit[t]);
					epd->m_referenceUnit = unit;
				}
				else {
					if(epd->m_referenceUnit.name() != oekobauDatUnit2IBKUnit[t])
						qDebug() << "Units do not match";
				}

			} break;
			case ColURL: {
				if(t == "")
					continue;

				QString string = QString::fromStdString(t);
				setValue<QString>(epd->m_dataSource, string, foundExistingEpd);
			} break;


			case ColModule: {
				if(t == "")
					continue;

				std::vector<VICUS::EpdModuleDataset::Module> modules;
				std::string moduleType = t.substr(0, 1);

				if(!epd->m_modules.isEmpty()) {
					if(epd->m_modules.indexOf(moduleType.c_str(), 0) == -1)
						epd->m_modules = QString("%1, %2").arg(epd->m_modules).arg(QString::fromStdString(moduleType));
				}
				else
					epd->m_modules = QString::fromStdString(moduleType);

				if (t == "A1")
					modules.push_back(VICUS::EpdModuleDataset::M_A1);
				else if (t == "A2")
					modules.push_back(VICUS::EpdModuleDataset::M_A2);
				else if (t == "A3")
					modules.push_back(VICUS::EpdModuleDataset::M_A3);
				else if (t == "A1-A2") {
					modules.push_back(VICUS::EpdModuleDataset::M_A1);
					modules.push_back(VICUS::EpdModuleDataset::M_A2);
				}
				else if (t == "A1-A3") {
					modules.push_back(VICUS::EpdModuleDataset::M_A1);
					modules.push_back(VICUS::EpdModuleDataset::M_A2);
					modules.push_back(VICUS::EpdModuleDataset::M_A3);
				}
				else if (t == "A4")
					modules.push_back(VICUS::EpdModuleDataset::M_A4);
				else if (t == "A5")
					modules.push_back(VICUS::EpdModuleDataset::M_A5);
				else if (t == "B1")
					modules.push_back(VICUS::EpdModuleDataset::M_B1);
				else if (t == "B2")
					modules.push_back(VICUS::EpdModuleDataset::M_B2);
				else if (t == "B3")
					modules.push_back(VICUS::EpdModuleDataset::M_B3);
				else if (t == "B4")
					modules.push_back(VICUS::EpdModuleDataset::M_B4);
				else if (t == "B5")
					modules.push_back(VICUS::EpdModuleDataset::M_B5);
				else if (t == "B6")
					modules.push_back(VICUS::EpdModuleDataset::M_B6);
				else if (t == "B7")
					modules.push_back(VICUS::EpdModuleDataset::M_B7);
				else if (t == "C1")
					modules.push_back(VICUS::EpdModuleDataset::M_C1);
				else if (t == "C2")
					modules.push_back(VICUS::EpdModuleDataset::M_C2);
				else if (t == "C2-C3") {
					modules.push_back(VICUS::EpdModuleDataset::M_C2);
					modules.push_back(VICUS::EpdModuleDataset::M_C3);
				}
				else if (t == "C2-C4") {
					modules.push_back(VICUS::EpdModuleDataset::M_C2);
					modules.push_back(VICUS::EpdModuleDataset::M_C3);
					modules.push_back(VICUS::EpdModuleDataset::M_C4);
				}
				else if (t == "C3")
					modules.push_back(VICUS::EpdModuleDataset::M_C3);
				else if (t == "C3-C4") {
					modules.push_back(VICUS::EpdModuleDataset::M_C3);
					modules.push_back(VICUS::EpdModuleDataset::M_C4);
				}
				else if (t == "C4")
					modules.push_back(VICUS::EpdModuleDataset::M_C4);
				else if (t == "D")
					modules.push_back(VICUS::EpdModuleDataset::M_D);

				epdCategoryDataSet->m_modules = modules;

			} break;


			case ColWeightPerUnitArea: {
				double val;
				if(!convertString2Val(val, t, row, col))
					continue;

				epdCategoryDataSet->m_para[VICUS::EpdModuleDataset::P_AreaDensity].set("AreaDensity", val, IBK::Unit("kg/m2"));
			} break;
			case ColBulkDensity: {
				double val;
				if(!convertString2Val(val, t, row, col))
					continue;
				epdCategoryDataSet->m_para[VICUS::EpdModuleDataset::P_DryDensity].set("DryDensity", val, IBK::Unit("kg/m3"));
			} break;
			case ColGWP: {
				double val;
				if(!convertString2Val(val, t, row, col))
					continue;

				epdCategoryDataSet->m_para[VICUS::EpdModuleDataset::P_GWP].set("GWP", val, IBK::Unit("kg"));
			} break;
			case ColODP: {
				double val;
				if(!convertString2Val(val, t, row, col))
					continue;
				epdCategoryDataSet->m_para[VICUS::EpdModuleDataset::P_ODP].set("ODP", val, IBK::Unit("kg"));
			} break;
			case ColPOCP: {
				double val;
				if(!convertString2Val(val, t, row, col))
					continue;
				epdCategoryDataSet->m_para[VICUS::EpdModuleDataset::P_POCP].set("POCP", val, IBK::Unit("kg"));

			} break;
			case ColAP: {
				double val;
				if(!convertString2Val(val, t, row, col))
					continue;
				epdCategoryDataSet->m_para[VICUS::EpdModuleDataset::P_AP].set("AP", val, IBK::Unit("kg"));
			} break;
			case ColEP: {
				double val;
				if(!convertString2Val(val, t, row, col))
					continue;
				epdCategoryDataSet->m_para[VICUS::EpdModuleDataset::P_EP].set("EP", val, IBK::Unit("kg"));
			} break;
			case ColPENRT: {
				double val;
				if(!convertString2Val(val, t, row, col))
					continue;
				epdCategoryDataSet->m_para[VICUS::EpdModuleDataset::P_PENRT].set("PENRT", val, IBK::Unit("W/mK"));
			} break;
			case ColPERT: {
				double val;
				if(!convertString2Val(val, t, row, col))
					continue;
				epdCategoryDataSet->m_para[VICUS::EpdModuleDataset::P_PERT].set("PERT", val, IBK::Unit("W/mK"));
			} break;
			}
		}
		epd->m_epdModuleDataset.push_back(*epdCategoryDataSet);

		if(epd->m_manufacturer.isEmpty())
			qDebug() << "Found emtpty epd: " << epd->m_uuid;
	}

	dlg->setValue(dataLines.size());
	// Get pointer to our EPD edit widget
	SVDatabaseEditDialog *conEditDialog = SVMainWindow::instance().dbEpdEditDialog();
	Q_ASSERT(conEditDialog != nullptr);

	// now we import all Datasets
	dynamic_cast<SVDBEpdTableModel*>(conEditDialog->dbModel())->importDatasets(dataSets);
}


void SVLcaLccSettingsDialog::addComponentInstance(const VICUS::ComponentInstance & compInstance) {
	if(m_compIdToAggregatedData.find(compInstance.m_idComponent) == m_compIdToAggregatedData.end())
		m_compIdToAggregatedData[compInstance.m_idComponent] = AggregatedComponentData(compInstance);
	else
		m_compIdToAggregatedData[compInstance.m_idComponent].addArea(compInstance);
}


void SVLcaLccSettingsDialog::aggregateProjectComponents() {
	QStringList lifetime, cost, epd;

	for(const VICUS::ComponentInstance &ci : m_prj.m_componentInstances) {
		// Add CI to aggregated data map
		addComponentInstance(ci);

		const VICUS::Component *comp = m_db->m_components[ci.m_idComponent];
		if(comp == nullptr)
			continue;

		const VICUS::Construction *con = m_db->m_constructions[comp->m_idConstruction];
		if(con == nullptr)
			continue;

		for(const VICUS::MaterialLayer &matLayer : con->m_materialLayers) {
			// Check Cost & lifetime of used Materials
			bool isLifetimeDefined = !matLayer.m_para[VICUS::MaterialLayer::P_LifeTime].empty();
			bool isCostDefined = !matLayer.m_cost.empty();
			// Check EPDs of used Materials
			const VICUS::Material *mat = m_db->m_materials[matLayer.m_idMaterial];

			if(mat == nullptr)
				continue;

			bool isEPDDefined = !mat->m_epdCategorySet.isEmpty();

			if(!isLifetimeDefined)
				lifetime << QString::fromStdString(mat->m_displayName.string());
			if(!isCostDefined)
				cost << QString::fromStdString(mat->m_displayName.string());
			if(!isEPDDefined) {
				epd << QString::fromStdString(mat->m_displayName.string());
				m_idComponentEpdUndefined.insert(comp->m_id);
			}
		}
	}

	lifetime.removeDuplicates();
	cost.removeDuplicates();
	epd.removeDuplicates();


//	QString messageText(tr("Lifetime:\t%1\nCost:\t%2\nEPD:\t%3\n\nProceed and skip all components without needed Data?")
//						.arg(lifetime.join("\n\t\t"))
//						.arg(cost.join("\n\t\t"))
//						.arg(epd.join("\n\t\t")));
//	if(QMessageBox::warning(this, "LCA/LCC Information is missing", messageText) == QMessageBox::Cancel)
//		return;
}

void SVLcaLccSettingsDialog::aggregateAggregatedComponentsByType() {
	for(std::map<unsigned int, AggregatedComponentData>::iterator itAggregatedComp = m_compIdToAggregatedData.begin();
		itAggregatedComp != m_compIdToAggregatedData.end(); ++itAggregatedComp)
	{
		const AggregatedComponentData &aggregatedData = itAggregatedComp->second;
		if(aggregatedData.m_component == nullptr)
			continue;

		if(m_typeToAggregatedCompData.find(aggregatedData.m_component->m_type) == m_typeToAggregatedCompData.end())
			m_typeToAggregatedCompData[aggregatedData.m_component->m_type] = aggregatedData;
		else
			m_typeToAggregatedCompData[aggregatedData.m_component->m_type].addAggregatedData(aggregatedData);
	}
}


void SVLcaLccSettingsDialog::writeDataToStream(std::ofstream &lcaStream, const std::string &categoryText,
											   const VICUS::EpdDataset::Category &category) {

	lcaStream << categoryText + "\t\t\t\t\t\t\t"  << std::endl;

	for(std::map<VICUS::Component::ComponentType, AggregatedComponentData>::iterator itAggregatedComp = m_typeToAggregatedCompData.begin();
		itAggregatedComp != m_typeToAggregatedCompData.end(); ++itAggregatedComp)
	{

		QStringList lcaDataType;
		const AggregatedComponentData &aggregatedTypeData = itAggregatedComp->second;

		std::set<unsigned int> usedCompIds;
		for(const VICUS::Component *comp : aggregatedTypeData.m_additionalComponents) {
			if(m_idComponentEpdUndefined.find(comp->m_id) == m_idComponentEpdUndefined.end()) {
				usedCompIds.insert(comp->m_id);
			}
		}
		if(usedCompIds.empty())
			continue;

		lcaDataType << "";
		lcaDataType << VICUS::KeywordList::Description("Component::ComponentType", aggregatedTypeData.m_component->m_type);
		lcaDataType << "";
		lcaDataType << QString::number(aggregatedTypeData.m_area);
//		lcaDataType << QString::number(aggregatedTypeData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_GWP].get_value());
//		lcaDataType << QString::number(aggregatedTypeData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_ODP].get_value());
//		lcaDataType << QString::number(aggregatedTypeData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_POCP].get_value());
//		lcaDataType << QString::number(aggregatedTypeData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_AP].get_value());
//		lcaDataType << QString::number(aggregatedTypeData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_EP].get_value());

		lcaStream << lcaDataType.join("\t").toStdString() << std::endl;

		for(const VICUS::Component *comp : aggregatedTypeData.m_additionalComponents) {

			const AggregatedComponentData &aggregatedCompData = m_compIdToAggregatedData[comp->m_id];

			if(usedCompIds.find(comp->m_id) == usedCompIds.end())
				continue; // Skip unused ids

			QStringList lcaData;

			lcaData << "";
			lcaData << "";
			lcaData << QtExt::MultiLangString2QString(comp->m_displayName);
			lcaData << QString::number(aggregatedCompData.m_area);
			//			lcaData << QString::number(aggregatedCompData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_GWP].get_value());
			//			lcaData << QString::number(aggregatedCompData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_ODP].get_value());
			//			lcaData << QString::number(aggregatedCompData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_POCP].get_value());
			//			lcaData << QString::number(aggregatedCompData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_AP].get_value());
			//			lcaData << QString::number(aggregatedCompData.m_totalEpdData[category].m_para[VICUS::EpdDataset::P_EP].get_value());

			lcaStream << lcaData.join("\t").toStdString() << std::endl;

		}

	}
}


void SVLcaLccSettingsDialog::setModuleState(int state) {

	QCheckBox *cb = dynamic_cast<QCheckBox*>(sender());

	Q_ASSERT(cb != nullptr);

	VICUS::EpdModuleDataset::Module mod = static_cast<VICUS::EpdModuleDataset::Module>(cb->property("category").toInt());
	m_lcaSettings->m_flags[mod].set(m_lcaSettings->m_flags[mod].name(), state == Qt::Checked);

}

void SVLcaLccSettingsDialog::setCheckBoxState(QCheckBox *cb, int bitmask) {
	cb->blockSignals(true);
	cb->setChecked((m_lcaSettings->m_certificationModules & bitmask) == bitmask);
	cb->blockSignals(false);
}


SVLcaLccResultsDialog *SVLcaLccSettingsDialog::lcaResultsDialog() {
	if(m_lcaResultDialog == nullptr)
		m_lcaResultDialog = new SVLcaLccResultsDialog(this);
	return m_lcaResultDialog;
}


void SVLcaLccSettingsDialog::updateUi() {
	m_ui->groupBoxLcaCalc->blockSignals(true);
	m_ui->groupBoxLccSettings->blockSignals(true);
	m_ui->groupBoxGeneral->blockSignals(true);

	// Note: we expect all units to be valid in all parameters and checked!

	m_ui->lineEditArea->setText(QString("%L1").arg(m_lcaSettings->m_para[VICUS::LcaSettings::P_NetUsageArea].value));

	m_ui->spinBoxTimePeriod->setValue((int)m_lcaSettings->m_para[VICUS::LcaSettings::P_TimePeriod].get_value("a"));

	m_ui->lineEditInterestRate->setText(QString("%L1").arg(m_lccSettings->m_para[VICUS::LccSettings::P_DiscountingInterestRate].get_value("%")));
	m_ui->lineEditPriceIncreaseEnergy->setText(QString("%L1").arg(m_lccSettings->m_para[VICUS::LccSettings::P_PriceIncreaseEnergy].get_value("%")));
	m_ui->lineEditPriceIncreaseGeneral->setText(QString("%L1").arg(m_lccSettings->m_para[VICUS::LccSettings::P_PriceIncreaseGeneral].get_value("%")));

	m_ui->lineEditCoalConsumption->setText(QString("%L1").arg(m_lccSettings->m_para[VICUS::LccSettings::P_CoalConsumption].get_value("kWh/a")));
	m_ui->lineEditGasConsumption->setText(QString("%L1").arg(m_lccSettings->m_para[VICUS::LccSettings::P_GasConsumption].get_value("kWh/a")));
	m_ui->lineEditElectricityConsumption->setText(QString("%L1").arg(m_lccSettings->m_para[VICUS::LccSettings::P_ElectricityConsumption].get_value("kWh/a")));

	// m_ui->filepathResults->setup("Select directory for LCA results", false, true, "", SVSettings::instance().m_dontUseNativeDialogs);

	QObjectList ol;
	ol.push_back(m_ui->checkBoxA1);
	ol.push_back(m_ui->checkBoxA2);
	ol.push_back(m_ui->checkBoxA3);
	ol.push_back(m_ui->checkBoxA4);
	ol.push_back(m_ui->checkBoxA5);
	ol.push_back(m_ui->checkBoxB1);
	ol.push_back(m_ui->checkBoxB2);
	ol.push_back(m_ui->checkBoxB3);
	ol.push_back(m_ui->checkBoxB4);
	ol.push_back(m_ui->checkBoxB5);
	ol.push_back(m_ui->checkBoxB6);
	ol.push_back(m_ui->checkBoxB7);
	ol.push_back(m_ui->checkBoxC1);
	ol.push_back(m_ui->checkBoxC2);
	ol.push_back(m_ui->checkBoxC3);
	ol.push_back(m_ui->checkBoxC4);
	ol.push_back(m_ui->checkBoxD);

	//qDebug() << m_lcaSettings->m_lcaCertificationSystem;

	setCheckBoxState(m_ui->checkBoxA1, VICUS::LcaSettings::M_A1);
	setCheckBoxState(m_ui->checkBoxA2, VICUS::LcaSettings::M_A2);
	setCheckBoxState(m_ui->checkBoxA3, VICUS::LcaSettings::M_A3);
	setCheckBoxState(m_ui->checkBoxA4, VICUS::LcaSettings::M_A4);
	setCheckBoxState(m_ui->checkBoxA5, VICUS::LcaSettings::M_A5);

	setCheckBoxState(m_ui->checkBoxB1, VICUS::LcaSettings::M_B1);
	setCheckBoxState(m_ui->checkBoxB2, VICUS::LcaSettings::M_B2);
	setCheckBoxState(m_ui->checkBoxB3, VICUS::LcaSettings::M_B3);
	setCheckBoxState(m_ui->checkBoxB4, VICUS::LcaSettings::M_B4);
	setCheckBoxState(m_ui->checkBoxB5, VICUS::LcaSettings::M_B5);
	setCheckBoxState(m_ui->checkBoxB6, VICUS::LcaSettings::M_B6);
	setCheckBoxState(m_ui->checkBoxB7, VICUS::LcaSettings::M_B7);

	setCheckBoxState(m_ui->checkBoxC1, VICUS::LcaSettings::M_C1);
	setCheckBoxState(m_ui->checkBoxC2, VICUS::LcaSettings::M_C2);
	setCheckBoxState(m_ui->checkBoxC3, VICUS::LcaSettings::M_C3);
	setCheckBoxState(m_ui->checkBoxC4, VICUS::LcaSettings::M_C4);

	setCheckBoxState(m_ui->checkBoxD, VICUS::LcaSettings::M_D);

	if(m_lcaSettings->m_calculationMode == VICUS::LcaSettings::CM_Detailed) {
		for(int i=0; i<ol.count(); ++i) {
			QCheckBox *cb = dynamic_cast<QCheckBox*>(ol[i]);
			VICUS::LcaSettings::Module mod = static_cast<VICUS::LcaSettings::Module>(cb->property("category").toInt());
			cb->setChecked(m_lcaSettings->m_flags[mod].isEnabled());
		}
	}

	m_ui->groupBoxCatA->setEnabled(m_lcaSettings->m_calculationMode != VICUS::LcaSettings::CM_Simple);
	m_ui->groupBoxCatB->setEnabled(m_lcaSettings->m_calculationMode != VICUS::LcaSettings::CM_Simple);
	m_ui->groupBoxCatC->setEnabled(m_lcaSettings->m_calculationMode != VICUS::LcaSettings::CM_Simple);
	m_ui->groupBoxCatD->setEnabled(m_lcaSettings->m_calculationMode != VICUS::LcaSettings::CM_Simple);

	m_ui->groupBoxLcaCalc->blockSignals(false);
	m_ui->groupBoxLccSettings->blockSignals(false);
	m_ui->groupBoxGeneral->blockSignals(false);

	VICUS::EpdDataset *epdCoal = nullptr;
	VICUS::EpdDataset *epdGas = nullptr;
	VICUS::EpdDataset *epdElectricity = nullptr;

	epdCoal = m_db->m_epdDatasets[m_lcaSettings->m_idUsage[VICUS::LcaSettings::UT_Coal]];
	if(epdCoal != nullptr)
		m_ui->lineEditEpdCoal->setText(QtExt::MultiLangString2QString(epdCoal->m_displayName));
	else
		m_ui->lineEditEpdCoal->setText("-");

	epdGas = m_db->m_epdDatasets[m_lcaSettings->m_idUsage[VICUS::LcaSettings::UT_Gas]];
	if(epdGas != nullptr)
		m_ui->lineEditEpdGas->setText(QtExt::MultiLangString2QString(epdGas->m_displayName));
	else
		m_ui->lineEditEpdGas->setText("-");

	epdElectricity = m_db->m_epdDatasets[m_lcaSettings->m_idUsage[VICUS::LcaSettings::UT_Electricity]];
	if(epdElectricity != nullptr)
		m_ui->lineEditEpdElectricity->setText(QtExt::MultiLangString2QString(epdElectricity->m_displayName));
	else
		m_ui->lineEditEpdElectricity->setText("-");

	m_ui->lineEditCoalPrice->setText( QString( "%L1" ).arg( m_lccSettings->m_intPara[VICUS::LccSettings::IP_CoalPrice].value / 100.0, 7, 'f', 2 ) );
	m_ui->lineEditElectricityPrice->setText( QString( "%L1" ).arg( m_lccSettings->m_intPara[VICUS::LccSettings::IP_ElectricityPrice].value / 100.0, 7, 'f', 2 ) );
	m_ui->lineEditGasPrice->setText( QString( "%L1" ).arg( m_lccSettings->m_intPara[VICUS::LccSettings::IP_GasPrice].value / 100.0, 7, 'f', 2 ) );

}


void SVLcaLccSettingsDialog::writeLcaDataToTxtFile(const IBK::Path &resultPath) {
	std::ofstream lcaStream(resultPath.str());
	// Write header
	lcaStream << "Category\tComponent type\tComponent name\tArea [m2]\tGWP (CO2-Äqu.) [kg/(m2a)\tODP (R11-Äqu.) [kg/(m2a)]\tPOCP (C2H4-Äqu.) [kg/(m2a)]\tAP (SO2-Äqu.) [kg/(m2a)]\tEP (PO4-Äqu.) [kg/(m2a)]" << std::endl;

	lcaStream << "Goal:\t\t\t\t24\t0.0000001010\t0.0063\t0.0662\t0.0086" << std::endl;


	writeDataToStream(lcaStream, "Category A - Production", VICUS::EpdDataset::C_CategoryA);
	// writeDataToStream(lcaStream, "Category A - Production", AggregatedComponentData::C_CategoryA);
	writeDataToStream(lcaStream, "Category C - Disposal", VICUS::EpdDataset::C_CategoryC);
	writeDataToStream(lcaStream, "Category D - Deposit", VICUS::EpdDataset::C_CategoryD);

	lcaStream.close();

}


void SVLcaLccSettingsDialog::calculateTotalLcaDataForComponents() {
	// Go through all used components.
	// Go through all used material layers in components.

	for(std::map<unsigned int, AggregatedComponentData>::iterator itAggregatedComp = m_compIdToAggregatedData.begin();
		itAggregatedComp != m_compIdToAggregatedData.end(); ++itAggregatedComp)
	{
		if(m_idComponentEpdUndefined.find(itAggregatedComp->first) != m_idComponentEpdUndefined.end())
			continue; // we skip components when there are epds not defined

		double area = itAggregatedComp->second.m_area;
		const VICUS::Component *comp = itAggregatedComp->second.m_component;

		if(comp == nullptr)
			continue;

		qDebug() << QString::fromStdString(comp->m_displayName.string());
		qDebug() << comp->m_idConstruction;

		if(comp == nullptr)
			continue;

		const VICUS::Construction *con = m_db->m_constructions[comp->m_idConstruction];
		if(con == nullptr)
			continue;

		for(const VICUS::MaterialLayer &matLayer : con->m_materialLayers) {
			const VICUS::Material &mat = *m_db->m_materials[matLayer.m_idMaterial];
			const VICUS::EpdDataset *epdCatA = m_db->m_epdDatasets[mat.m_epdCategorySet.m_idCategory[VICUS::EpdCategorySet::C_IDCategoryA]];
			const VICUS::EpdDataset *epdCatB = m_db->m_epdDatasets[mat.m_epdCategorySet.m_idCategory[VICUS::EpdCategorySet::C_IDCategoryB]];
			const VICUS::EpdDataset *epdCatC = m_db->m_epdDatasets[mat.m_epdCategorySet.m_idCategory[VICUS::EpdCategorySet::C_IDCategoryA]];
			const VICUS::EpdDataset *epdCatD = m_db->m_epdDatasets[mat.m_epdCategorySet.m_idCategory[VICUS::EpdCategorySet::C_IDCategoryD]];

			// We have to think about renewing our materials as well
			// If no lifetime is defined, we take for now 50 years
			double lifeTime;
			if(matLayer.m_para[VICUS::MaterialLayer::P_LifeTime].empty())
				lifeTime = 50;
			else
				lifeTime = matLayer.m_para[VICUS::MaterialLayer::P_LifeTime].get_value();

			double renewingFactor = m_lcaSettings->m_para[VICUS::LcaSettings::P_TimePeriod].get_value() / lifeTime;


			// We do the unit conversion and handling to get all our reference units correctly managed
			if(epdCatA != nullptr)
				itAggregatedComp->second.m_totalEpdData[VICUS::EpdDataset::C_CategoryA]
						= epdCatA->scaleByFactor( renewingFactor *
							SVLcaLccResultsDialog::conversionFactorEpdReferenceUnit(epdCatA->m_referenceUnit,
															 mat, matLayer.m_para[VICUS::MaterialLayer::P_Thickness].get_value("m"), area));
			if(epdCatB != nullptr) // no renewing period scaling since it is already normated for 1 a
				itAggregatedComp->second.m_totalEpdData[VICUS::EpdDataset::C_CategoryB]
						= epdCatB->scaleByFactor(
							SVLcaLccResultsDialog::conversionFactorEpdReferenceUnit(epdCatB->m_referenceUnit,
															 mat, matLayer.m_para[VICUS::MaterialLayer::P_Thickness].get_value("m"), area));
			if(epdCatC != nullptr)
				itAggregatedComp->second.m_totalEpdData[VICUS::EpdDataset::C_CategoryC]
						= epdCatC->scaleByFactor( renewingFactor *
							SVLcaLccResultsDialog::conversionFactorEpdReferenceUnit(epdCatC->m_referenceUnit,
															 mat, matLayer.m_para[VICUS::MaterialLayer::P_Thickness].get_value("m"), area));
			if(epdCatD != nullptr)
				itAggregatedComp->second.m_totalEpdData[VICUS::EpdDataset::C_CategoryD]
						= epdCatD->scaleByFactor( renewingFactor *
							SVLcaLccResultsDialog::conversionFactorEpdReferenceUnit(epdCatD->m_referenceUnit,
															 mat, matLayer.m_para[VICUS::MaterialLayer::P_Thickness].get_value("m"), area));

		}
	}
}


void SVLcaLccSettingsDialog::resetLcaData() {
	m_compIdToAggregatedData.clear();
	m_typeToAggregatedCompData.clear();
	m_idComponentEpdUndefined.clear();
}


void SVLcaLccSettingsDialog::on_pushButtonImportOkoebaudat_clicked() {
	FUNCID(SVDBEPDEditWidget::on_pushButtonImportOkoebaudat_clicked);

	IBK::Path path(m_ui->filepathOekoBauDat->filename().toStdString());

	if(!path.isValid()) {
		QMessageBox::warning(this, tr("Select ÖKOBAUDAT csv-file"), tr("Please select first a csv-file with valid ÖKOBAUDAT data."));
		return;
	}

	try {
		importOkoebauDat(path);
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception(IBK::FormatString("%1\nCould not import EPD-Database.").arg(ex.what()), FUNC_ID);
	}
}


void SVLcaLccSettingsDialog::on_comboBoxCalculationMode_currentIndexChanged(int mode) {
	m_lcaSettings->m_calculationMode = (mode == 1 ? VICUS::LcaSettings::CM_Detailed : VICUS::LcaSettings::CM_Simple);
	m_ui->comboBoxCertificationSystem->setEnabled(mode == 0);

	updateUi();
}


void SVLcaLccSettingsDialog::on_comboBoxCertificationSystem_currentIndexChanged(int certiSystem) {
	m_lcaSettings->m_certificationSystem = static_cast<VICUS::LcaSettings::CertificationSytem>(certiSystem);

	switch(m_lcaSettings->m_certificationSystem) {
		case (VICUS::LcaSettings::CS_BNB) :	m_lcaSettings->m_certificationModules = VICUS::LcaSettings::CT_BNB;  break;
		case (VICUS::LcaSettings::NUM_CS) : break;
	}

	updateUi();
}



void SVLcaLccSettingsDialog::on_pushButtonAreaDetection_clicked() {
	double area = 0;

	for(const VICUS::Building &b : m_prj.m_buildings) {
		for(const VICUS::BuildingLevel &bl : b.m_buildingLevels) {
			for(const VICUS::Room &r : bl.m_rooms) {
				for(const VICUS::Surface &s : r.m_surfaces) {

					VICUS::Component *comp = m_db->m_components[s.m_componentInstance->m_idComponent];
					if(comp == nullptr)
						continue;

					VICUS::Component::ComponentType ct = comp->m_type;
					qDebug() << "Surface name:" << s.m_displayName;
					if( ct == VICUS::Component::CT_Ceiling || ct == VICUS::Component::CT_FloorToAir || ct == VICUS::Component::CT_FloorToCellar
							|| ct == VICUS::Component::CT_FloorToGround || ct == VICUS::Component::CT_Ceiling ) {
						const IBKMK::Vector3D &n = s.geometry().normal();
						double angle = IBKMK::angleBetweenVectorsDeg(n, IBKMK::Vector3D(0,0,-1) );
						qDebug() << "Angle between vertical and surface: " << angle;
						if(angle < 5) {
							qDebug() << "Surface added.";
							area += s.geometry().area();
						}
					}
				}
			}
		}
	}
	m_ui->lineEditArea->setText(QString("%L1").arg(area, 0, 'f', 2));
	VICUS::KeywordList::setParameter(m_lcaSettings->m_para, "LcaSettings::para_t", VICUS::LcaSettings::P_NetUsageArea, m_ui->lineEditArea->value());
	QMessageBox::information(this, QString(), tr("The net ground floor area calculation is based on all surfaces with inclination angle < 5°."));
}


void SVLcaLccSettingsDialog::on_pushButtonCalculate_clicked() {
	try {
		// TODO : kWh/a  -> Energy/Time -> Power     --> J/s is SI base unit

		// get annual consumptions in kWh/a

		double coalConsumption			= m_lccSettings->m_para[VICUS::LccSettings::P_CoalConsumption].get_value("kWh/a");
		double gasConsumption			= m_lccSettings->m_para[VICUS::LccSettings::P_GasConsumption].get_value("kWh/a");
		double electricityConsumption	= m_lccSettings->m_para[VICUS::LccSettings::P_ElectricityConsumption].get_value("kWh/a");

//		double totalEnergyCost =  gasConsumption * m_lccSettings->m_intPara[VICUS::LccSettings::IP_GasPrice].value
//								+ electricityConsumption * m_lccSettings->m_intPara[VICUS::LccSettings::IP_ElectricityPrice].value
//								+ coalConsumption * m_lccSettings->m_intPara[VICUS::LccSettings::IP_CoalPrice].value ;
//		totalEnergyCost /= 100.0; // Mind we store our Prices in cent --> convert to € by /100

		calculateLCA();

		unsigned int numberOfYears = (unsigned int)m_ui->spinBoxTimePeriod->value();
		m_lcaSettings->m_para[VICUS::LcaSettings::P_TimePeriod].set(numberOfYears, IBK::Unit("a"));

		std::vector<double> investCost(numberOfYears, 0.0);

		lcaResultsDialog()->setup();
		lcaResultsDialog()->setLcaResults(m_typeToAggregatedCompData, m_compIdToAggregatedData, VICUS::EpdDataset::C_CategoryA, *m_lcaSettings, investCost);
        lcaResultsDialog()->setUsageResults(*m_lcaSettings, gasConsumption, electricityConsumption, coalConsumption);
		lcaResultsDialog()->setLcaResults(m_typeToAggregatedCompData, m_compIdToAggregatedData, VICUS::EpdDataset::C_CategoryC, *m_lcaSettings, investCost);
		lcaResultsDialog()->setLcaResults(m_typeToAggregatedCompData, m_compIdToAggregatedData, VICUS::EpdDataset::C_CategoryD, *m_lcaSettings, investCost);

		// Mind: cost values are in ct/kWh and we convert to EUR/kWh
		lcaResultsDialog()->setCostResults(*m_lccSettings, *m_lcaSettings,
				electricityConsumption * m_lccSettings->m_intPara[VICUS::LccSettings::IP_ElectricityPrice].value / 100.0,
				coalConsumption * m_lccSettings->m_intPara[VICUS::LccSettings::IP_CoalPrice].value / 100.0,
				gasConsumption * m_lccSettings->m_intPara[VICUS::LccSettings::IP_GasPrice].value / 100.0,
				investCost);

		m_lcaResultDialog->showMaximized();
	}
	catch (IBK::Exception &ex) {
		QMessageBox::critical(this, tr("Error in LCA Calculcation"), tr("Could not calculcate LCA. See Error below.\n%1").arg(ex.what()));
	}
}


void SVLcaLccSettingsDialog::on_lineEditArea_editingFinishedSuccessfully() {
	if (m_ui->lineEditArea->isValid())
		VICUS::KeywordList::setParameter(m_lcaSettings->m_para, "LcaSettings::para_t", VICUS::LcaSettings::P_NetUsageArea, m_ui->lineEditArea->value());
	else
		m_ui->lineEditArea->setValue(m_lcaSettings->m_para[VICUS::LcaSettings::P_NetUsageArea].value);
}


void SVLcaLccSettingsDialog::on_lineEditTimePeriod_editingFinishedSuccessfully() {
	unsigned int years = (unsigned int)m_ui->spinBoxTimePeriod->value();
	VICUS::KeywordList::setParameter(m_lcaSettings->m_para, "LcaSettings::para_t", VICUS::LcaSettings::P_TimePeriod, years);
}


void SVLcaLccSettingsDialog::on_lineEditPriceIncreaseGeneral_editingFinishedSuccessfully() {
	if(m_ui->lineEditPriceIncreaseGeneral->isValid())
		VICUS::KeywordList::setParameter(m_lccSettings->m_para, "LccSettings::para_t", VICUS::LccSettings::P_PriceIncreaseGeneral, m_ui->lineEditPriceIncreaseGeneral->value());
	else
		m_ui->lineEditPriceIncreaseGeneral->setValue(m_lccSettings->m_para[VICUS::LccSettings::P_PriceIncreaseGeneral].value);
}


void SVLcaLccSettingsDialog::on_lineEditGasConsumption_editingFinishedSuccessfully() {
	if(m_ui->lineEditGasConsumption->isValid())
		VICUS::KeywordList::setParameter(m_lccSettings->m_para, "LccSettings::para_t", VICUS::LccSettings::P_GasConsumption, m_ui->lineEditGasConsumption->value());
	else
		m_ui->lineEditGasConsumption->setValue(m_lccSettings->m_para[VICUS::LccSettings::P_GasConsumption].value);
}


void SVLcaLccSettingsDialog::on_lineEditElectricityConsumption_editingFinishedSuccessfully() {
	if(m_ui->lineEditElectricityConsumption->isValid())
		VICUS::KeywordList::setParameter(m_lccSettings->m_para, "LccSettings::para_t", VICUS::LccSettings::P_ElectricityConsumption, m_ui->lineEditElectricityConsumption->value());
	else
		m_ui->lineEditElectricityConsumption->setValue(m_lccSettings->m_para[VICUS::LccSettings::P_ElectricityConsumption].value);
}


void SVLcaLccSettingsDialog::on_lineEditCoalConsumption_editingFinishedSuccessfully() {
	if(m_ui->lineEditCoalConsumption->isValid())
		VICUS::KeywordList::setParameter(m_lccSettings->m_para, "LccSettings::para_t", VICUS::LccSettings::P_CoalConsumption, m_ui->lineEditCoalConsumption->value());
	else
		m_ui->lineEditCoalConsumption->setValue(m_lccSettings->m_para[VICUS::LccSettings::P_CoalConsumption].value);
}


void SVLcaLccSettingsDialog::on_lineEditPriceIncreaseEnergy_editingFinishedSuccessfully() {
	if(m_ui->lineEditPriceIncreaseEnergy->isValid())
		VICUS::KeywordList::setParameter(m_lccSettings->m_para, "LccSettings::para_t", VICUS::LccSettings::P_PriceIncreaseEnergy, m_ui->lineEditPriceIncreaseEnergy->value());
	else
		m_ui->lineEditPriceIncreaseEnergy->setValue(m_lccSettings->m_para[VICUS::LccSettings::P_PriceIncreaseEnergy].value);

}


void SVLcaLccSettingsDialog::on_toolButtonSelectGas_clicked() {
	// get EPD edit dialog from mainwindow
	SVDatabaseEditDialog * editDialog = SVMainWindow::instance().dbEpdEditDialog();

	unsigned int id = m_lcaSettings->m_idUsage[VICUS::LcaSettings::UT_Gas];

	unsigned int idGas = editDialog->select(id, false, "MJ", 5);
	if (idGas != VICUS::INVALID_ID && idGas != id) {
		m_lcaSettings->m_idUsage[VICUS::LcaSettings::UT_Gas] = idGas;
	}

	updateUi();
}


void SVLcaLccSettingsDialog::on_toolButtonSelectElectricity_clicked() {
	// get EPD edit dialog from mainwindow
	SVDatabaseEditDialog * editDialog = SVMainWindow::instance().dbEpdEditDialog();

	unsigned int id = m_lcaSettings->m_idUsage[VICUS::LcaSettings::UT_Electricity];

	unsigned int idElectricity = editDialog->select(id, false, "MJ", 5);
	if (idElectricity != VICUS::INVALID_ID && idElectricity != id) {
		m_lcaSettings->m_idUsage[VICUS::LcaSettings::UT_Electricity] = idElectricity;
	}

	updateUi();
}


void SVLcaLccSettingsDialog::on_toolButtonSelectCoal_clicked() {
	// get EPD edit dialog from mainwindow
	SVDatabaseEditDialog * editDialog = SVMainWindow::instance().dbEpdEditDialog();

	unsigned int id = m_lcaSettings->m_idUsage[VICUS::LcaSettings::UT_Coal];

	unsigned int idCoal = editDialog->select(id, false, "MJ", 5);
	if (idCoal != VICUS::INVALID_ID && idCoal != id) {
		m_lcaSettings->m_idUsage[VICUS::LcaSettings::UT_Coal] = idCoal;
	}

	updateUi();
}


void SVLcaLccSettingsDialog::on_lineEditCoalPrice_editingFinishedSuccessfully() {
	if(m_ui->lineEditCoalPrice->isValid())
		VICUS::KeywordList::setIntPara(m_lccSettings->m_intPara, "LccSettings::intPara_t", VICUS::LccSettings::IP_CoalPrice, m_ui->lineEditCoalPrice->value()*100);

	updateUi();
}


void SVLcaLccSettingsDialog::on_lineEditGasPrice_editingFinishedSuccessfully() {
	if(m_ui->lineEditGasPrice->isValid())
		VICUS::KeywordList::setIntPara(m_lccSettings->m_intPara, "LccSettings::intPara_t", VICUS::LccSettings::IP_GasPrice, m_ui->lineEditGasPrice->value()*100);

	updateUi();
}


void SVLcaLccSettingsDialog::on_lineEditElectricityPrice_editingFinishedSuccessfully() {
	if(m_ui->lineEditElectricityPrice->isValid())
		VICUS::KeywordList::setIntPara(m_lccSettings->m_intPara, "LccSettings::intPara_t", VICUS::LccSettings::IP_ElectricityPrice, m_ui->lineEditElectricityPrice->value()*100);

	updateUi();
}


