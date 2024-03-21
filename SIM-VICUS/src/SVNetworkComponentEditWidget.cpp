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

#include "SVNetworkComponentEditWidget.h"
#include "ui_SVNetworkComponentEditWidget.h"

#include <algorithm>

#include "SVSettings.h"
#include "SVDatabaseEditDialog.h"
#include "SVMainWindow.h"
#include "SVStyle.h"
#include "SVConstants.h"
#include "SVConversions.h"
#include "SVChartUtils.h"
#include "SVNetworkControllerEditDialog.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_plot_zoomer.h>

#include <VICUS_NetworkComponent.h>
#include <VICUS_NetworkController.h>
#include <VICUS_NetworkHeatExchange.h>
#include <VICUS_KeywordListQt.h>
#include <VICUS_utilities.h>

#include <NANDRAD_HydraulicNetworkComponent.h>

#include <IBK_Parameter.h>
#include <IBK_FileUtils.h>
#include <IBK_CSVReader.h>

#include <QScrollBar>
#include <QTemporaryFile>
#include <QPushButton>

#include <QtExt_LanguageHandler.h>
#include <QtExt_Locale.h>



SVNetworkComponentEditWidget::SVNetworkComponentEditWidget(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::SVNetworkComponentEditWidget)
{
	m_ui->setupUi(this);
	m_db = SVSettings::instance().m_db;

	// no headers
	m_ui->tableWidgetParameters->horizontalHeader()->setVisible(false);
	m_ui->tableWidgetParameters->verticalHeader()->setVisible(false);
	m_ui->tableWidgetParameters->setColumnCount(3);
	m_ui->tableWidgetParameters->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	m_ui->tableWidgetParameters->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	m_ui->tableWidgetParameters->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	SVStyle::formatDatabaseTableView(m_ui->tableWidgetParameters);
	m_ui->tableWidgetParameters->setSortingEnabled(false);

	m_ui->tableWidgetPolynomCoefficients->horizontalHeader()->setVisible(false);
	m_ui->tableWidgetPolynomCoefficients->verticalHeader()->setVisible(true);
	SVStyle::formatDatabaseTableView(m_ui->tableWidgetPolynomCoefficients);
	m_ui->tableWidgetPolynomCoefficients->setSortingEnabled(false);

	// create chart and curve
	configureChart(m_ui->widgetPlot1);
	configureChart(m_ui->widgetPlot2);
	configureChart(m_ui->widgetPlotHeatLossSpline);

	// workaround for stubborn layout bug
	m_ui->tableWidgetParameters->setMaximumHeight(0);

	// checks if VICUS::NetworkHeatExchange was changed. stackedWidgetHeatExchange must be adjusted accordingly
	Q_ASSERT(VICUS::NetworkHeatExchange::NUM_T == 9);

	//sets up validating line edit appropriately
	m_ui->lineEditTemperatureConstantHeatTransferCoefficient->setMinimum(0, false);
	m_ui->lineEditTemperatureSplineHeatTransferCoefficient->setMinimum(0, false);

	// set comboBox in pageHeatLossSpline
	for(int i = 0; i < VICUS::NetworkHeatExchange::NUM_BT; i++){
		m_ui->comboBoxHeatLossSplineUserBuildingType->addItem(VICUS::KeywordListQt::Keyword("NetworkHeatExchange::BuildingType", i));
	}
}


SVNetworkComponentEditWidget::~SVNetworkComponentEditWidget() {
	delete m_ui;
}

void SVNetworkComponentEditWidget::updateInput(VICUS::NetworkComponent* component) {
//	FUNCID(SVDBNetworkComponentEditWidget::updateInput);

	// clear input controls
	m_ui->lineEditSchedule1->clear();
	m_ui->lineEditSchedule1->setVisible(false);
	m_ui->lineEditSchedule2->clear();
	m_ui->lineEditSchedule2->setVisible(false);


	// set invisible everything in the polynom group box
	m_ui->groupBoxPolynom->setVisible(false);

	// set invisible everything in the controller group box
	m_ui->groupBoxController->setVisible(false);

	if (component == nullptr) {
		// disable all controls - note: this does not disable signals of the components below
		setEnabled(false);
		return;
	}
	// re-enable all controls
	setEnabled(true);

	m_current = component;

	update();

}

void SVNetworkComponentEditWidget::update()
{

	// now update the GUI controls

	NANDRAD::HydraulicNetworkComponent::ModelType nandradModelType =
		VICUS::NetworkComponent::nandradNetworkComponentModelType(m_current->m_modelType);

	// enable schedules tool buttons (based on required schedules)
	std::vector<std::string> reqScheduleNames = NANDRAD::HydraulicNetworkComponent::requiredScheduleNames(nandradModelType);
	m_ui->groupBoxSchedules->setVisible(!reqScheduleNames.empty());
	m_ui->toolButtonSchedule1->setVisible(reqScheduleNames.size()==1 || reqScheduleNames.size()==2);
	m_ui->toolButtonSchedule2->setVisible(reqScheduleNames.size()==2);

	// update schedule labels
	m_ui->labelSchedule1->clear();
	m_ui->labelSchedule2->clear();
	if (reqScheduleNames.size()>0)
		m_ui->labelSchedule1->setText(VICUS::camelCase2ReadableString(reqScheduleNames[0]));
	if (reqScheduleNames.size()>1)
		m_ui->labelSchedule2->setText(VICUS::camelCase2ReadableString(reqScheduleNames[1]));

	// update Schedule names (based on existing schedules)
	if (m_current->m_scheduleIds.size()>0){
		m_ui->lineEditSchedule1->setVisible(true);
		if (m_db.m_schedules[m_current->m_scheduleIds[0]] == nullptr)
			m_ui->lineEditSchedule1->setText(tr("Invalid Schedule"));
		else
			m_ui->lineEditSchedule1->setText(QtExt::MultiLangString2QString(
				m_db.m_schedules[m_current->m_scheduleIds[0]]->m_displayName));
	}
	if (m_current->m_scheduleIds.size()>1){
		m_ui->lineEditSchedule2->setVisible(true);
		if (m_db.m_schedules[m_current->m_scheduleIds[1]] == nullptr)
			m_ui->lineEditSchedule2->setText(tr("Invalid Schedule"));
		else
			m_ui->lineEditSchedule2->setText(QtExt::MultiLangString2QString(
				m_db.m_schedules[m_current->m_scheduleIds[1]]->m_displayName));
	}

	// update pipe properties
	m_ui->lineEditPipeProperties->clear();
	m_ui->groupBoxPipeProperties->setVisible(false);
	if (VICUS::NetworkComponent::hasPipeProperties(m_current->m_modelType)){
		m_ui->groupBoxPipeProperties->setVisible(true);
		const VICUS::NetworkPipe *pipe = m_db.m_pipes[m_current->m_pipePropertiesId];
		if(pipe != nullptr)
			m_ui->lineEditPipeProperties->setText(QtExt::MultiLangString2QString(pipe->m_displayName));
	}

	// update controller properties
	std::vector<NANDRAD::HydraulicNetworkControlElement::ControlledProperty> availableCtrProps;
	availableCtrProps = NANDRAD::HydraulicNetworkControlElement::availableControlledProperties(nandradModelType);
	if(availableCtrProps.size() > 0){
		m_ui->groupBoxController->setVisible(true);
	}

	if(m_current->m_networkController.m_controlledProperty != VICUS::NetworkController::NUM_CP){
		m_ui->lineEditController->setText(QString::fromLatin1(VICUS::KeywordListQt::Keyword("NetworkController::ControlledProperty", m_current->m_networkController.m_controlledProperty)));
		m_ui->toolButtonControllerRemove->setEnabled(true);
	} else {
		m_ui->lineEditController->clear();
		m_ui->toolButtonControllerRemove->setEnabled(false);
	}

	// update table widgets and plot
	m_ui->plotTab1->setVisible(true);
	m_ui->widgetPlot1->setVisible(true);
	m_ui->plotTab2->setVisible(true);
	m_ui->widgetPlot2->setVisible(true);

	updateParameterTableWidget();
	updatePolynomCoeffTableWidget();
	updatePolynomPlot();


	// look up all available HeatExchange Modeltypes for this component
	std::vector<VICUS::NetworkHeatExchange::ModelType> availableHeatExchangeModelTypes = VICUS::NetworkComponent::availableHeatExchangeTypes(m_current->m_modelType);

	// if no HE Modeltype except NUM_T available, disable Heat Exchange tab
	if(availableHeatExchangeModelTypes.size() == 1 && availableHeatExchangeModelTypes[0] == VICUS::NetworkHeatExchange::NUM_T){
		m_ui->tabWidget->setTabEnabled(1, false);
	} else {
		m_ui->tabWidget->setTabEnabled(1, true);
	}

	// clear combobox from previous entries
	m_ui->comboBoxHeatExchange->clear();
	// insert all available HE modeltypes into the HE combobox, adds "None" last
	for(VICUS::NetworkHeatExchange::ModelType heatExchangeMT : availableHeatExchangeModelTypes){
		if(heatExchangeMT == VICUS::NetworkHeatExchange::NUM_T || heatExchangeMT == VICUS::NetworkHeatExchange::T_TemperatureZone || heatExchangeMT == VICUS::NetworkHeatExchange::T_TemperatureConstructionLayer) {
			continue;
		}
		m_ui->comboBoxHeatExchange->addItem(VICUS::KeywordListQt::Keyword("NetworkHeatExchange::ModelType", static_cast<int>(heatExchangeMT)), heatExchangeMT);
	}
	m_ui->comboBoxHeatExchange->addItem("None", static_cast<int>(VICUS::NetworkHeatExchange::NUM_T));

	// clear vector that temporarily saves all changes made to a heat exchange
	m_vectorTempHeatExchange.clear();
	// fill vector with all available Heat Exchange modeltypes, adds "None"/NUM_T modeltype last
	for(VICUS::NetworkHeatExchange::ModelType heatExchangeMT: availableHeatExchangeModelTypes){
		if(heatExchangeMT == VICUS::NetworkHeatExchange::NUM_T) {
			continue;
		}
		VICUS::NetworkHeatExchange newHeatExchange;
		newHeatExchange.m_modelType = heatExchangeMT;
		newHeatExchange.setDefaultValues(heatExchangeMT);
		m_vectorTempHeatExchange.push_back(newHeatExchange);
	}
	m_vectorTempHeatExchange.push_back(VICUS::NetworkHeatExchange());

	// set the comboBox and stackedWidget to the HE modeltype of the current component
	for(int index = 0; index < m_ui->comboBoxHeatExchange->count(); index++){
		if(m_current->m_heatExchange.m_modelType == static_cast<VICUS::NetworkHeatExchange::ModelType>(m_ui->comboBoxHeatExchange->itemData(index).toInt())){
			on_comboBoxHeatExchange_activated(index);
			m_ui->stackedWidgetHeatExchange->setCurrentIndex(static_cast<int>(m_current->m_heatExchange.m_modelType));
		}
	}
}

void SVNetworkComponentEditWidget::updatePageHeatLossConstant()
{
	// set label and lineEdit in pageHeatLossConstant invisible
	if(m_current->m_heatExchange.m_individualHeatFlux == true){
		m_ui->radioButtonHeatLossConstantUser->setChecked(true);
		on_radioButtonHeatLossConstantUser_clicked();
	} else {
		m_ui->radioButtonHeatLossConstantPredef->setChecked(true);
		on_radioButtonHeatLossConstantPredef_clicked();
	}
}

void SVNetworkComponentEditWidget::updatePageHeatLossSpline()
{
	handleTsv();

	// set widgets in pageHeatLossSpline to appropriate values
	m_ui->checkBoxHeatLossSplineIndividual->setChecked(m_current->m_heatExchange.m_individualHeatFlux);
	on_checkBoxHeatLossSplineIndividual_clicked(m_current->m_heatExchange.m_individualHeatFlux);
}

void SVNetworkComponentEditWidget::updateParameterTableWidget() const{
	FUNCID(SVNetworkComponentEditWidget::updateParameterTableWidget);

	NANDRAD::HydraulicNetworkComponent::ModelType nandradModelType =
			VICUS::NetworkComponent::nandradNetworkComponentModelType(m_current->m_modelType);

	// populate table widget with properties
	m_ui->tableWidgetParameters->clearContents();

	// get required parameters of the current component
	std::vector<unsigned int> paraVecStd = NANDRAD::HydraulicNetworkComponent::requiredParameter(nandradModelType, 1);
	std::vector<unsigned int> paraVecAdd = m_current->additionalRequiredParameter(m_current->m_modelType);
	std::vector<unsigned int> paraVec;
	for (unsigned int i: paraVecStd)
		paraVec.push_back(i);
	for (unsigned int i: paraVecAdd)
		paraVec.push_back(i);

	// get integer parameters
	std::vector<unsigned int> paraVecInt = m_current->requiredIntParameter(m_current->m_modelType);

	// get optional parameters
	std::vector<unsigned int> paraVecOpt = m_current->optionalParameter(m_current->m_modelType);

	int rowCount = paraVec.size() + paraVecInt.size() + paraVecOpt.size();
	// populate table widget with parameters
	m_ui->tableWidgetParameters->setRowCount(rowCount);
	if (paraVec.empty() && paraVecInt.empty() && paraVecOpt.empty())
		m_ui->groupBoxModelParameters->setVisible(false);
	else
		m_ui->groupBoxModelParameters->setVisible(true);

	if(SVSettings::instance().m_theme == SVSettings::TT_Dark)
		m_ui->tableWidgetParameters->setMaximumHeight(rowCount * m_ui->tableWidgetParameters->rowHeight(0)+6);
	else
		m_ui->tableWidgetParameters->setMaximumHeight(rowCount * m_ui->tableWidgetParameters->rowHeight(0)+2);
	m_ui->tableWidgetParameters->blockSignals(true);

	int rowCounter = 0;
	for (unsigned int para: paraVec) {
		QTableWidgetItem * item = new QTableWidgetItem(VICUS::KeywordListQt::Keyword("NetworkComponent::para_t", (int)para));
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		m_ui->tableWidgetParameters->setItem(rowCounter, 0, item);
		try {
			IBK::Unit ioUnit(VICUS::KeywordListQt::Unit("NetworkComponent::para_t", (int)para));
			item = new QTableWidgetItem(QString::fromStdString(ioUnit.name()));
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			m_ui->tableWidgetParameters->setItem(rowCounter, 2, item);

			if (m_current->m_para[para].name.empty())
				item = new QTableWidgetItem(); // TODO : Hauke, set some meaningful initial value?
			else
				item = new QTableWidgetItem(QString("%L1").arg(m_current->m_para[para].get_value(ioUnit)));
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
			if ((unsigned int)rowCounter < paraVecStd.size())
				item->setData(Qt::UserRole, DT_DoubleStd);
			else
				item->setData(Qt::UserRole, DT_DoubleAdditional);
			item->setData(Qt::UserRole+1, para);
			m_ui->tableWidgetParameters->setItem(rowCounter, 1, item);

			++rowCounter;
		}
		catch (IBK::Exception & ex) {
			IBK::IBK_Message(ex.what(), IBK::MSG_ERROR, FUNC_ID);
		}
	}


	// populate table widget with integer parameters

	for (unsigned int paraInt: paraVecInt) {
		// parameter name
		QTableWidgetItem * item = new QTableWidgetItem(VICUS::KeywordListQt::Keyword("NetworkComponent::intPara_t", (int)paraInt));
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		m_ui->tableWidgetParameters->setItem(rowCounter, 0, item);
		try {
			// parameter unit
			item = new QTableWidgetItem("-");
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			m_ui->tableWidgetParameters->setItem(rowCounter, 2, item);
			// parameter value
			if (m_current->m_intPara[paraInt].name.empty())
				item = new QTableWidgetItem(); // TODO : Hauke, set some meaningful initial value?
			else
				item = new QTableWidgetItem(QString("%L1").arg(m_current->m_intPara[paraInt].value));
			item->setData(Qt::UserRole, DT_Integer);
			item->setData(Qt::UserRole+1, paraInt);
			m_ui->tableWidgetParameters->setItem(rowCounter, 1, item);

			++rowCounter;
		}
		catch (IBK::Exception & ex) {
			IBK::IBK_Message(ex.what(), IBK::MSG_ERROR, FUNC_ID);
		}
	}


	// populate table widget with optional parameters

	QFont fnt;
	fnt.setItalic(true);
	for (unsigned int paraOpt: paraVecOpt) {
		// parameter name
		QTableWidgetItem * item = new QTableWidgetItem(VICUS::KeywordListQt::Keyword("NetworkComponent::para_t", (int)paraOpt));
		item->setFont(fnt);
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		m_ui->tableWidgetParameters->setItem(rowCounter, 0, item);
		try {
			// parameter unit
			IBK::Unit ioUnit(VICUS::KeywordListQt::Unit("NetworkComponent::para_t", (int)paraOpt));
			item = new QTableWidgetItem(QString::fromStdString(ioUnit.name()));
			item->setFont(fnt);
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			m_ui->tableWidgetParameters->setItem(rowCounter, 2, item);
			// parameter value
			if (m_current->m_para[paraOpt].name.empty())
				item = new QTableWidgetItem(); // TODO : Hauke, set some meaningful initial value?
			else
				item = new QTableWidgetItem(QString("%L1").arg(m_current->m_para[paraOpt].get_value(ioUnit)));
			item->setFont(fnt);
			item->setData(Qt::UserRole, DT_DoubleOptional);
			item->setData(Qt::UserRole+1, paraOpt);
			m_ui->tableWidgetParameters->setItem(rowCounter, 1, item);

			++rowCounter;
		}
		catch (IBK::Exception & ex) {
			IBK::IBK_Message(ex.what(), IBK::MSG_ERROR, FUNC_ID);
		}
	}

	m_ui->tableWidgetParameters->blockSignals(false);
	m_ui->tableWidgetParameters->resizeColumnsToContents();
}


void SVNetworkComponentEditWidget::updatePolynomCoeffTableWidget() const {

	m_ui->tableWidgetPolynomCoefficients->blockSignals(true);
	m_ui->tableWidgetPolynomCoefficients->clearContents();
	m_ui->tableWidgetPolynomCoefficients->setRowCount(0);
	m_ui->tableWidgetPolynomCoefficients->setColumnCount(0);

	unsigned int rowCount=0;
	unsigned int columnCount=0;
	bool isOptional = false;
	std::vector<std::string> header;
	switch (m_current->m_modelType ) {
		case VICUS::NetworkComponent::MT_HeatPumpOnOffSourceSide: {
			header = {"QdotCondensator", "ElectricalPower"};
			columnCount = 6;
			isOptional = false;
		} break;
		case VICUS::NetworkComponent::MT_HeatPumpVariableSourceSide: {
			header = {"COP"};
			columnCount = 6;
			isOptional = false;
		} break;
		case VICUS::NetworkComponent::MT_ConstantPressurePump:
		case VICUS::NetworkComponent::MT_ControlledPump:
		case VICUS::NetworkComponent::MT_VariablePressurePump: {
			header = {"MaximumElectricalPower", "MaximumPressureHead"};
			columnCount = 3;
			isOptional = true;
		} break;
		default: {
			m_ui->tableWidgetPolynomCoefficients->blockSignals(false);
			return;
		}
	}

	// set header, row and column count
	m_ui->tableWidgetPolynomCoefficients->verticalHeader()->setVisible(true);
	rowCount = header.size();
	m_ui->tableWidgetPolynomCoefficients->setRowCount((int)rowCount);
	m_ui->tableWidgetPolynomCoefficients->setColumnCount((int)columnCount);

	if (columnCount > 0 || rowCount > 0) {
		m_ui->groupBoxPolynom->setVisible(true);
	}

	// better to read reference
	const std::map<std::string, std::vector<double> > &values = m_current->m_polynomCoefficients.m_values;

	QFont font;
	font.setItalic(isOptional);

	// in case the value map is empty we write zeros into the table, otherwise we use the according values
	for (unsigned int row=0; row<rowCount; ++row) {
		// set header
		QTableWidgetItem *headItem = new QTableWidgetItem( QString::fromStdString(header[row]));
		headItem->setFont(font);
		m_ui->tableWidgetPolynomCoefficients->setVerticalHeaderItem((int)row, headItem);
		// populate values
		for (unsigned int col=0; col<columnCount; ++col) {
			double val = 0; // default value
			// if we have a value in the map, use that
			if (values.find(header[row]) != values.end() && col < values.at(header[row]).size() )
				val = values.at(header[row])[col];
			QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(val));
			item->setFont(font);
			m_ui->tableWidgetPolynomCoefficients->setItem((int)row, (int)col, item);
		}
	}

	m_ui->tableWidgetPolynomCoefficients->resizeRowsToContents();

	int tableWidgetHeight = rowCount * m_ui->tableWidgetPolynomCoefficients->rowHeight(0);
	tableWidgetHeight += m_ui->tableWidgetPolynomCoefficients->horizontalScrollBar()->height();
	m_ui->tableWidgetPolynomCoefficients->setMinimumHeight(tableWidgetHeight);
	m_ui->tableWidgetPolynomCoefficients->setMaximumHeight(tableWidgetHeight);
	m_ui->tableWidgetPolynomCoefficients->blockSignals(false);
}


void SVNetworkComponentEditWidget::updatePolynomPlot() {

	m_ui->widgetPlot1->detachItems( QwtPlotItem::Rtti_PlotCurve );
	m_ui->widgetPlot1->detachItems( QwtPlotItem::Rtti_PlotMarker );
	m_ui->widgetPlot1->setAxisTitle(QwtPlot::xBottom, "");
	m_ui->widgetPlot1->setAxisTitle(QwtPlot::yLeft, "");
	m_ui->widgetPlot1->replot();

#if QT_VERSION >= QT_VERSION_CHECK(5,15,0)
	m_ui->tabWidgetPlots->setTabVisible(0, false);
#else
	m_ui->plotTab1->setEnabled(false);
	m_ui->widgetPlot1->setVisible(false);
#endif

	m_ui->widgetPlot2->detachItems( QwtPlotItem::Rtti_PlotCurve );
	m_ui->widgetPlot2->detachItems( QwtPlotItem::Rtti_PlotMarker );
	m_ui->widgetPlot2->setAxisTitle(QwtPlot::xBottom, "");
	m_ui->widgetPlot2->setAxisTitle(QwtPlot::yLeft, "");
	m_ui->widgetPlot2->replot();

#if QT_VERSION >= QT_VERSION_CHECK(5,15,0)
	m_ui->tabWidgetPlots->setTabVisible(1, false);
#else
	m_ui->plotTab2->setEnabled(false);
	m_ui->widgetPlot2->setVisible(false);
#endif

	QString xLabel;
	QString yLabel1, yLabel2;
	std::vector<QString> curveLabels1, curveLabels2;
	switch (m_current->m_modelType ) {
		case VICUS::NetworkComponent::MT_HeatPumpVariableSourceSide: {

			// if invalid polynom, do nothing
			if (m_current->m_polynomCoefficients.m_values.find("COP") == m_current->m_polynomCoefficients.m_values.end())
				return;
			const std::vector<double> &coeffs = m_current->m_polynomCoefficients.m_values.at("COP");
			if (coeffs.size() != 6)
				return;

			// create x data (evaporator temperature)
			m_xData.clear();
			double T=-5;
			while (T<15){
				m_xData.push_back(T);
				T += 0.1;
			}

			// create y data (COP)
			m_yData1.clear();
			std::vector<double> TcVec = {35, 45, 55};
			for (double &Tc: TcVec) {
				m_yData1.push_back(std::vector<double>());
				curveLabels1.push_back(QString("%1 °C").arg(Tc));
				for (double &Te: m_xData)
					m_yData1.back().push_back(coeffs[0] + coeffs[1] * (Te+273.15) + coeffs[2] * (Tc+273.15) + coeffs[3] * (Te+273.15) * (Tc+273.15) +
									coeffs[4] * (Te+273.15) * (Te+273.15) + coeffs[5] * (Tc+273.15) * (Tc+273.15));
			}
			xLabel = "Evaporator Temperature [C]";
			yLabel1 = "COP [-]";
			m_ui->tabWidgetPlots->setTabText(0, "COP");
			m_yData2.clear();

		} break;

		case VICUS::NetworkComponent::MT_ConstantPressurePump:
		case VICUS::NetworkComponent::MT_ControlledPump:
		case VICUS::NetworkComponent::MT_VariablePressurePump: {

			// check if we have a polynom
			bool havePolynom = false;
			if (m_current->m_polynomCoefficients.m_values.find("MaximumPressureHead") != m_current->m_polynomCoefficients.m_values.end())
				havePolynom = true;
			// if so check size
			std::vector<double> coeffs1;
			std::vector<double> coeffs2;
			if (havePolynom) {
				coeffs1 = m_current->m_polynomCoefficients.m_values.at("MaximumPressureHead");
				coeffs2 = m_current->m_polynomCoefficients.m_values.at("MaximumElectricalPower");
				if (coeffs1.size() != 3)
					return;
			}

			// parameter readability
			double &maxDpPara = m_current->m_para[VICUS::NetworkComponent::P_MaximumPressureHead].value;
			double &maxPelPara = m_current->m_para[VICUS::NetworkComponent::P_PumpMaximumElectricalPower].value;
			double &maxEtaPara = m_current->m_para[VICUS::NetworkComponent::P_PumpMaximumEfficiency].value;

			// find maximum Vdot
			double VdotMax=0; // in m3/s
			double dpMax;
			while (VdotMax<1) {
				VdotMax += 1e-3;
				if (havePolynom) // polynom model
					dpMax = coeffs1[0] * VdotMax * VdotMax + coeffs1[1] * VdotMax + coeffs1[2];
				else // simple model
					dpMax = maxDpPara * (1 - maxDpPara / (4 * maxPelPara * maxEtaPara) * VdotMax);
				if (dpMax<=0)
					break;
			}

			// create x data
			m_xData.clear();
			double Vdot=0;
			while (Vdot<VdotMax){
				m_xData.push_back(Vdot*3600);
				Vdot += VdotMax/100;
			}
			// create y data1
			m_yData1.clear();
			m_yData1.push_back(std::vector<double>());
			double dp;
			for (double &Vdot: m_xData) {
				if (havePolynom)
					dp = coeffs1[0] * (Vdot/3600) * (Vdot/3600) + coeffs1[1] * (Vdot/3600) + coeffs1[2];
				else
					dp = maxDpPara * (1 - maxDpPara / (4 * maxPelPara * maxEtaPara) * Vdot/3600);
				m_yData1.back().push_back(dp/1e5);
			}
			xLabel = "Volume flow rate [m³/h]";
			yLabel1 = "Max. Pressure Head [bar]";
			curveLabels1.push_back(QString("max. dp"));
			m_ui->tabWidgetPlots->setTabText(0, "Max. Pressure Head");

			// create y data2
			m_yData2.clear();
			m_yData2.push_back(std::vector<double>());
			for (double &Vdot: m_xData) {
				double Pel;
				if (havePolynom)
					Pel = coeffs2[0] * (Vdot/3600) * (Vdot/3600) + coeffs2[1] * (Vdot/3600) + coeffs2[2];
				else
					Pel = maxPelPara;
				m_yData2.back().push_back(Pel);
			}
			xLabel = "Volume flow rate [m³/h]";
			yLabel2 = "Max. Electrical Power [W]";
			curveLabels2.push_back(QString("Pel"));
			m_ui->tabWidgetPlots->setTabText(1, "Max. El. Power");
		} break;

		default:
			return;
	}

	std::vector<QColor> colors = {"#db2b39", "#29335c", "#f3a712"};
	// now do all the plotting
#if QT_VERSION >= QT_VERSION_CHECK(5,15,0)
	m_ui->tabWidgetPlots->setTabVisible(0, true);
#else
	m_ui->plotTab1->setEnabled(true);
	m_ui->widgetPlot1->setVisible(true);
#endif
	m_curves1.clear();
	Q_ASSERT(curveLabels1.size()==m_yData1.size());
	for (unsigned int i=0; i<m_yData1.size(); ++i) {
		m_curves1.push_back(addConfiguredCurve(m_ui->widgetPlot1));
		// adjust styling based on current theme's settings
		configureCurveTheme(m_curves1.back());
		m_curves1.back()->setPen(colors[i]);
		// set data
		m_curves1.back()->setRawSamples(m_xData.data(), m_yData1[i].data(), (int)m_xData.size());
		m_curves1.back()->setTitle(curveLabels1[i]);
	}
	QFont ft;
	ft.setPointSize(10);
	QwtText xl(xLabel);
	xl.setFont(ft);
	m_ui->widgetPlot1->setAxisTitle(QwtPlot::xBottom, xl);
	QwtText yl(yLabel1);
	yl.setFont(ft);
	m_ui->widgetPlot1->setAxisTitle(QwtPlot::yLeft, yl);
	if (curveLabels1.size()>1) {
		QwtLegend* legend = new QwtLegend;
		m_ui->widgetPlot1->insertLegend(legend, QwtPlot::RightLegend);
	}
	m_ui->widgetPlot1->replot();


	if (!m_yData2.empty()) {
#if QT_VERSION >= QT_VERSION_CHECK(5,15,0)
		m_ui->tabWidgetPlots->setTabVisible(1, true);
#else
		m_ui->plotTab2->setEnabled(false);
		m_ui->widgetPlot2->setVisible(true);
#endif
		m_curves2.clear();
		Q_ASSERT(curveLabels2.size()==m_yData2.size());
		for (unsigned int i=0; i<m_yData2.size(); ++i) {
			m_curves2.push_back(addConfiguredCurve(m_ui->widgetPlot2));
			// adjust styling based on current theme's settings
			configureCurveTheme(m_curves2.back());
			m_curves2.back()->setPen(colors[i]);
			// set data
			m_curves2.back()->setRawSamples(m_xData.data(), m_yData2[i].data(), (int)m_xData.size());
			m_curves2.back()->setTitle(curveLabels2[i]);
		}
		QFont ft;
		ft.setPointSize(10);
		QwtText xl(xLabel);
		xl.setFont(ft);
		m_ui->widgetPlot2->setAxisTitle(QwtPlot::xBottom, xl);
		QwtText yl2(yLabel2);
		yl2.setFont(ft);
		m_ui->widgetPlot2->setAxisTitle(QwtPlot::yLeft, yl2);
		if (curveLabels2.size()>1) {
			QwtLegend* legend2 = new QwtLegend;
			m_ui->widgetPlot2->insertLegend(legend2, QwtPlot::RightLegend);
		}
		m_ui->widgetPlot2->replot();
	}


}

void SVNetworkComponentEditWidget::handleTsv()
{
	qDebug() << "Loading TSV";
	QString directory = ":/demandProfiles/Residential_HeatingLoad.tsv";
	QTemporaryFile tempFile;
	if (tempFile.open()) {
		// Copy the resource to the temporary file
		QFile resourceFile(directory);
		if (resourceFile.open(QIODevice::ReadOnly)) {
			tempFile.write(resourceFile.readAll());

			// Important: Flush the data to ensure all data is written to disk
			tempFile.flush();

			// Use tempFile.fileName() as the absolute path to the temporary file
			directory = tempFile.fileName();
		}
	}

	IBK::Path ibkDirectory(directory.toStdString());
	IBK::CSVReader reader;
	try {
		reader.read(ibkDirectory);
	}
	catch (...) {
		qDebug() << "Could not load TSV successfully";
	}

	qDebug() << "TSV succesfully loaded";
	for(auto column : reader.m_captions){
		qDebug() << "Column: " << QString::fromStdString(column);
	}
	qDebug() << "values: " << reader.m_values[4][1];
	m_heatLossSplineXData = reader.colData(0);

	for(int i = 1; i < reader.m_nColumns; i++){
		const std::vector<double>& colData = reader.colData(i);
		double maxValue = *(std::max_element(colData.begin(), colData.end()));
		m_heatLossSplineMaxYValues.push_back(maxValue);
		m_mapHeatLossSplineYData[maxValue] = reader.colData(i);
	}

	m_heatLossSplineXPlotData = m_heatLossSplineXData;
	calculateNewHeatLossSplineYData(1, m_heatLossSplineYPlotData);

	m_ui->widgetPlotHeatLossSpline->setAxisTitle(QwtPlot::xBottom, "Time [h]");
	m_ui->widgetPlotHeatLossSpline->setAxisTitle(QwtPlot::yLeft, "Heating Demand [W]");
	if(m_heatLossSplineCurve != nullptr) delete m_heatLossSplineCurve;
	m_heatLossSplineCurve = new QwtPlotCurve("Data");
	m_heatLossSplineCurve->setSamples(m_heatLossSplineXPlotData.data(), m_heatLossSplineYPlotData.data(), m_heatLossSplineXPlotData.size());
	m_heatLossSplineCurve->attach(m_ui->widgetPlotHeatLossSpline);
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, m_heatLossSplineXPlotData.size());

	if(m_heatLossSplineZoomer != nullptr) delete m_heatLossSplineZoomer;
	m_heatLossSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotHeatLossSpline->canvas() );
	m_heatLossSplineZoomer->setZoomBase();
	m_heatLossSplineCurve->plot()->replot();
}

double SVNetworkComponentEditWidget::calculateHeatingEnergyDemand()
{
	double heatingEnergyDemand = 0;
	for(unsigned int i = 0; i < m_heatLossSplineYPlotData.size(); i++){
		heatingEnergyDemand += m_heatLossSplineYPlotData[i];
	}
	return heatingEnergyDemand;
}

void SVNetworkComponentEditWidget::calculateNewHeatLossSplineYData(double k, std::vector<double> & vectorToSaveNewValues)
{
	double maxValueUser = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;
	double maxValue = maxYValueForMap();
	if (maxValueUser == 0.0) maxValueUser = maxValue;
	double ratio =  maxValueUser / maxValue;

	auto scaling = [k, maxValueUser, ratio](double y){
		double relativeValue = y * ratio;
		relativeValue = relativeValue / maxValueUser;
		double adjustedRelativeValue = std::pow(relativeValue,k);
		double adjustedAbsoluteValue = maxValueUser * adjustedRelativeValue;
		return adjustedAbsoluteValue;
	};

	vectorToSaveNewValues.resize(m_heatLossSplineXData.size());
	std::vector<double>& valuesToBeTransformed = m_mapHeatLossSplineYData[maxValue];
	std::transform(valuesToBeTransformed.begin(), valuesToBeTransformed.end(), vectorToSaveNewValues.begin(), scaling );
}


void SVNetworkComponentEditWidget::on_toolButtonSchedule1_clicked()
{
	Q_ASSERT(m_current != nullptr);

	// open schedule edit dialog in selection mode
	unsigned int id = 0;
	if (m_current->m_scheduleIds.size()>0)
		id = m_current->m_scheduleIds[0];

	unsigned int newId = SVMainWindow::instance().dbScheduleEditDialog()->select(id);

	// if dialog was canceled do nothing
	if (newId == VICUS::INVALID_ID)
		return;

	// else if we have a new id set it
	if (id != newId) {
		if (m_current->m_scheduleIds.size()>0)
			m_current->m_scheduleIds[0] = newId;
		else
			m_current->m_scheduleIds.push_back(newId);
	}
	update();
}


void SVNetworkComponentEditWidget::on_toolButtonSchedule2_clicked()
{
	Q_ASSERT(m_current != nullptr);

	// open schedule edit dialog in selection mode
	unsigned int id = 0;
	if (m_current->m_scheduleIds.size()==2)
		id = m_current->m_scheduleIds[1];

	unsigned int newId = SVMainWindow::instance().dbScheduleEditDialog()->select(id);

	// if dialog was canceled do nothing
	if (newId == VICUS::INVALID_ID)
		return;

	if (id != newId) {
		if (m_current->m_scheduleIds.size()==2)
			m_current->m_scheduleIds[1] = newId;
		else
			m_current->m_scheduleIds.push_back(newId);
	}
	update();
}


void SVNetworkComponentEditWidget::on_tableWidgetParameters_cellChanged(int row, int column) {

	Q_ASSERT(column==1); // only values can be edited

	QString errMsg("");

	// get pointer to item and its content
	QTableWidgetItem * item = m_ui->tableWidgetParameters->item(row, 1);
	QString text = item->text();

	bool ok = false;

	// Double parameters

	if (item->data(Qt::UserRole) == DT_DoubleStd ||
		item->data(Qt::UserRole) == DT_DoubleAdditional ||
		item->data(Qt::UserRole) == DT_DoubleOptional ) {

		VICUS::NetworkComponent::para_t paraNum = VICUS::NetworkComponent::para_t(
												item->data(Qt::UserRole + 1).toUInt());
		// empty parameters are allowed
		if (text.isEmpty()){
			m_current->m_para[paraNum] = IBK::Parameter();
			return;
		}

		// check number
		double val = QtExt::Locale().toDouble(text, &ok);
		if (!ok)
			val = text.toDouble(&ok);
		if (!ok)
			errMsg = "Only numbers allowed!";

		// now do parameter specific checks
		if (ok) {
			IBK::Parameter parameter(VICUS::KeywordListQt::Keyword("NetworkComponent::para_t", paraNum), val,
									 VICUS::KeywordListQt::Unit("NetworkComponent::para_t", paraNum));
			try {
				if (item->data(Qt::UserRole) == DT_DoubleStd ||
					item->data(Qt::UserRole) == DT_DoubleOptional)
					NANDRAD::HydraulicNetworkComponent::checkModelParameter(parameter, paraNum);
				else
					VICUS::NetworkComponent::checkAdditionalParameter(parameter, paraNum);
			} catch (IBK::Exception &ex) {
				errMsg = ex.what();
				ok = false;
			}
			// finally set value
			VICUS::KeywordList::setParameter(m_current->m_para, "NetworkComponent::para_t", paraNum, val);
		}
		else {
			m_ui->tableWidgetParameters->blockSignals(true);
			if (m_current->m_para[paraNum].empty())
				item->setText("");
			else
				item->setText(QString("%1").arg(m_current->m_para[paraNum].value));
			m_ui->tableWidgetParameters->blockSignals(false);
		}

	}


	// Integer parameters

	else if (item->data(Qt::UserRole) == DT_Integer)  {

		VICUS::NetworkComponent::intPara_t paraNum = VICUS::NetworkComponent::intPara_t(
												item->data(Qt::UserRole + 1).toUInt());
		// empty parameters are allowed
		if (text.isEmpty()){
			m_current->m_intPara[paraNum] = IBK::IntPara();
			return;
		}

		// check if is integer and if it is double then cast it to integer
		int val = QtExt::Locale().toInt(text, &ok);
		if (!ok){
			val = (int)QtExt::Locale().toDouble(text, &ok);
		}
		if (!ok)
			errMsg = "Only numbers allowed!";

		// now do parameter specific checks
		std::string paraName = VICUS::KeywordListQt::Keyword("NetworkComponent::intPara_t", paraNum);
		if (ok) {
			IBK::IntPara parameter(paraName, val);
			try {
				VICUS::NetworkComponent::checkIntParameter(parameter, paraNum);
			} catch (IBK::Exception &ex) {
				errMsg = ex.what();
				ok = false;
			}
			// finally set value
			m_current->m_intPara[paraNum] = IBK::IntPara(paraName, val);
		}
		else {
			m_ui->tableWidgetParameters->blockSignals(true);
			if (m_current->m_para[paraNum].empty())
				item->setText("");
			else
				item->setText(QString("%1").arg(m_current->m_intPara[paraNum].value));
			m_ui->tableWidgetParameters->blockSignals(false);
		}
	}

	if (!ok){
		QMessageBox msgBox(QMessageBox::Critical, "Invalid Value", errMsg, QMessageBox::Ok, this);
		msgBox.exec();
	}
}


void SVNetworkComponentEditWidget::on_toolButtonPipeProperties_clicked()
{
	Q_ASSERT(m_current != nullptr);

	// open schedule edit dialog in selection mode
	unsigned int id = 0;
	if (m_current->m_pipePropertiesId != VICUS::INVALID_ID)
		id = m_current->m_pipePropertiesId;

	unsigned int newId = SVMainWindow::instance().dbPipeEditDialog()->select(id);

	// if dialog was canceled do nothing
	if (newId == VICUS::INVALID_ID)
		return;

	// else if we have a new id set it
	if (id != newId) {
		m_current->m_pipePropertiesId = newId;
	}
	update();
}


void SVNetworkComponentEditWidget::on_tableWidgetPolynomCoefficients_cellChanged(int row, int /*column*/) {

	std::string header = m_ui->tableWidgetPolynomCoefficients->verticalHeaderItem(row)->text().toStdString();

	m_current->m_polynomCoefficients.m_values[header].clear();
	bool allZero = true;
	for (int col=0; col<m_ui->tableWidgetPolynomCoefficients->columnCount(); ++col) {

		// check number
		QString text = m_ui->tableWidgetPolynomCoefficients->item(row, col)->text();
		bool ok = false;
		double val=0;
		if (!text.isEmpty()) {
			val = QtExt::Locale().toDouble(text, &ok);
			if (!ok)
				val = text.toDouble(&ok);
		}
		// set value back
		if (ok)
			m_current->m_polynomCoefficients.m_values[header].push_back(val);
		else
			m_current->m_polynomCoefficients.m_values[header].push_back(0);

		if (m_current->m_polynomCoefficients.m_values[header][(unsigned int)col]>0 ||
			m_current->m_polynomCoefficients.m_values[header][(unsigned int)col]<0)
			allZero = false;
	}
	// if all values are zero we remove this entry (so if it is optional it would still be considered valid)
	if (allZero)
		m_current->m_polynomCoefficients.m_values.erase(header);

	update();
}


void SVNetworkComponentEditWidget::on_toolButtonControllerSet_clicked()
{
	VICUS::NetworkController controller;
	controller.m_modelType = VICUS::NetworkController::MT_Constant;
	controller.m_controlledProperty = VICUS::NetworkController::CP_TemperatureDifference;
	m_current->m_networkController = controller;

	if(m_controllerEditDialog == nullptr){
		m_controllerEditDialog = new SVNetworkControllerEditDialog(this);
	}

	VICUS::NetworkController tmpController = m_current->m_networkController;
	m_controllerEditDialog->setup(tmpController, m_current->m_modelType);
	m_controllerEditDialog->exec();

	if (m_controllerEditDialog->result() == QDialog::Accepted){
		m_current->m_networkController = m_controllerEditDialog->controller();
		QString controllerName = VICUS::KeywordListQt::Keyword("NetworkController::ControlledProperty", static_cast<int>(m_current->m_networkController.m_controlledProperty));
		m_ui->lineEditController->setText(controllerName);
		m_ui->toolButtonControllerRemove->setEnabled(true);
		emit controllerChanged(controllerName);
	}

}


void SVNetworkComponentEditWidget::on_toolButtonControllerRemove_clicked()
{
	m_current->m_networkController = VICUS::NetworkController();
	m_ui->lineEditController->clear();
	emit controllerChanged("");
}


void SVNetworkComponentEditWidget::on_comboBoxHeatExchange_activated(int index)
{
	VICUS::NetworkHeatExchange::ModelType modelType = static_cast<VICUS::NetworkHeatExchange::ModelType>(m_ui->comboBoxHeatExchange->currentData().toInt());

	//store old heatExchange
	for(VICUS::NetworkHeatExchange& heatExchange : m_vectorTempHeatExchange){
		if(heatExchange.m_modelType == m_current->m_heatExchange.m_modelType){
			heatExchange = m_current->m_heatExchange;
		}
	}

	//take newly selected Heat Exchanger from vector
	m_current->m_heatExchange = m_vectorTempHeatExchange[index];

	switch(m_current->m_heatExchange.m_modelType){
		case VICUS::NetworkHeatExchange::T_HeatingDemandSpaceHeating:
			updatePageHeatingDemandSpaceHeating();
			break;
		case VICUS::NetworkHeatExchange::T_HeatLossConstant:
			updatePageHeatLossConstant();
			break;
		case VICUS::NetworkHeatExchange::T_HeatLossSplineCondenser:
		case VICUS::NetworkHeatExchange::T_HeatLossSpline:
			updatePageHeatLossSpline();
			break;
		default: break;
	}

	// change stackedWidget to the appropriate page
	m_ui->stackedWidgetHeatExchange->setCurrentIndex(static_cast<int>(modelType));
}


void SVNetworkComponentEditWidget::on_radioButtonHeatLossConstantPredef_clicked()
{
	m_ui->lineEditHeatLossConstantUser->clear();
	m_current->m_heatExchange.m_individualHeatFlux = false;
	m_ui->labelHeatLossConstantUserHeatFlux->setVisible(false);
	m_ui->labelHeatLossConstantUserUnit->setVisible(false);
	m_ui->lineEditHeatLossConstantUser->setVisible(false);
}


void SVNetworkComponentEditWidget::on_radioButtonHeatLossConstantUser_clicked()
{
	m_current->m_heatExchange.m_individualHeatFlux = true;
	m_ui->labelHeatLossConstantUserHeatFlux->setVisible(true);
	m_ui->labelHeatLossConstantUserUnit->setVisible(true);
	m_ui->lineEditHeatLossConstantUser->setVisible(true);
	m_ui->lineEditHeatLossConstantUser->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatLoss].get_value());
}


void SVNetworkComponentEditWidget::on_lineEditHeatLossConstantUser_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatLoss, m_ui->lineEditHeatLossConstantUser->value());
}


void SVNetworkComponentEditWidget::on_lineEditTemperatureConstantHeatTransferCoefficient_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient, m_ui->lineEditTemperatureConstantHeatTransferCoefficient->value());
}


void SVNetworkComponentEditWidget::on_lineEditTemperatureConstantTemperature_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_Temperature, m_ui->lineEditTemperatureConstantTemperature->value());
}


void SVNetworkComponentEditWidget::on_checkBoxHeatLossSplineIndividual_clicked(bool checked)
{
	m_current->m_heatExchange.m_individualHeatFlux = checked;
	if(m_current->m_heatExchange.m_individualHeatFlux){
		m_ui->widgetDefineHeatExchangeSpline->setEnabled(false);
	} else {
		m_ui->widgetDefineHeatExchangeSpline->setEnabled(true);
		on_comboBoxHeatLossSplineUserBuildingType_activated(static_cast<int>(m_current->m_heatExchange.m_buildingType));
		if(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value == 0.0) {
			m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setValue(10);
		}
		else {
			m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].get_value());
		}
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value());
		m_ui->lineEditHeatLossSplineFloorArea->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value());
	}
}


void SVNetworkComponentEditWidget::on_comboBoxHeatLossSplineUserBuildingType_activated(int index)
{
	// if the index is NUM_BT or invalid, set to SingleFamilyHouse
	if(index >= VICUS::NetworkHeatExchange::NUM_BT) index = 0;
	m_ui->comboBoxHeatLossSplineUserBuildingType->setCurrentIndex(index);
	m_current->m_heatExchange.m_buildingType = static_cast<VICUS::NetworkHeatExchange::BuildingType>(index);
	qDebug() << "building Type set: " << VICUS::KeywordListQt::Keyword("NetworkHeatExchange::BuildingType", index);
	if(m_current->m_heatExchange.m_buildingType != VICUS::NetworkHeatExchange::BT_UserDefineBuilding && m_current->m_heatExchange.m_buildingType != VICUS::NetworkHeatExchange::NUM_BT){
		m_ui->stackedWidgetHeatLossSpline->setCurrentIndex(0);
	} else {
		m_ui->stackedWidgetHeatLossSpline->setCurrentIndex(1);
	}
}

void SVNetworkComponentEditWidget::on_checkBoxHeatLossSplineDemandCurveUserAreaRelatedValues_stateChanged(int arg1)
{
	m_current->m_heatExchange.m_areaRelatedValues = static_cast<bool>(arg1);
}


void SVNetworkComponentEditWidget::on_checkBoxHeatLossSplineDemandCurveUserWithCoolingDemand_stateChanged(int arg1)
{
	m_current->m_heatExchange.m_withCoolingDemand = static_cast<bool>(arg1);
}


void SVNetworkComponentEditWidget::on_lineEditHeatLossSplineFloorArea_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_FloorArea, m_ui->lineEditHeatLossSplineFloorArea->value());
}

void SVNetworkComponentEditWidget::on_horizontalSliderHeatLossSplinePlot_sliderMoved(int position)
{
	double k = position < 100 ? (position / 100.0d) : std::pow(position / 100.0d, 4);
	m_k = k;
	calculateNewHeatLossSplineYData(k, m_heatLossSplineYPlotData);
	m_heatLossSplineCurve->setSamples(m_heatLossSplineXPlotData.data(), m_heatLossSplineYPlotData.data(), m_heatLossSplineXPlotData.size());
	m_heatLossSplineCurve->plot()->replot();
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(calculateHeatingEnergyDemand() / 1000);
}


void SVNetworkComponentEditWidget::on_lineEditHeatLossSplineMaximumHeatingLoad_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumHeatingLoad, m_ui->lineEditHeatLossSplineMaximumHeatingLoad->value());
	calculateNewHeatLossSplineYData(m_k, m_heatLossSplineYPlotData);
	m_heatLossSplineCurve->setSamples(m_heatLossSplineXPlotData.data(), m_heatLossSplineYPlotData.data(), m_heatLossSplineXPlotData.size());
	m_heatLossSplineCurve->plot()->replot();
	double newHeatingEnergyDemand = calculateHeatingEnergyDemand() / 1000;
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(newHeatingEnergyDemand);
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, newHeatingEnergyDemand);
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumHeatingLoad, m_ui->lineEditHeatLossSplineMaximumHeatingLoad->value());

}

double SVNetworkComponentEditWidget::maxYValueForMap()
{
	double currentMaxValue = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;
	for(int i = 0; i < m_heatLossSplineMaxYValues.size(); i++){
		if(currentMaxValue < m_heatLossSplineMaxYValues[i]) return m_heatLossSplineMaxYValues[i];
	}
	return m_heatLossSplineMaxYValues.back();
}


void SVNetworkComponentEditWidget::on_lineEditHeatLossSplineHeatingEnergyDemand_editingFinishedSuccessfully()
{
	if(m_isHeatingEnergyDemandDialogAlreadyOpen) return;
	m_isHeatingEnergyDemandDialogAlreadyOpen = true;
	QDialog dialog(this);
	dialog.setWindowTitle("Choose how to adjust the graph");

	QVBoxLayout layout(&dialog);

	// Buttons
	QPushButton button1("Adjust Maximum Heating Load", &dialog);
	QPushButton button2("Adjust Graph", &dialog);
	QPushButton button3("Cancel", &dialog);

	layout.addWidget(&button1);
	layout.addWidget(&button2);
	layout.addWidget(&button3);

	// Setting unique result values for buttons
	QObject::connect(&button1, &QPushButton::clicked, [&]() { dialog.done(1); });
	QObject::connect(&button2, &QPushButton::clicked, [&]() { dialog.done(2); });
	QObject::connect(&button3, &QPushButton::clicked, [&]() { dialog.done(3); });

	int result = dialog.exec();

	double newHeatingEnergyDemand = m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value();
	m_isHeatingEnergyDemandDialogAlreadyOpen = false;

	if(result == 3) return;
	if(result == 1) {
		double previousHeatingDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value();
		double ratio = newHeatingEnergyDemand / previousHeatingDemand;
		double previousMaximumHeatingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].get_value();
		double newMaximumHeatingLoad = previousMaximumHeatingLoad * ratio;
		m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setValue(newMaximumHeatingLoad);
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->clearFocus();

		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, newHeatingEnergyDemand);

		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumHeatingLoad, newMaximumHeatingLoad);
		calculateNewHeatLossSplineYData(m_k, m_heatLossSplineYPlotData);
		m_heatLossSplineCurve->setSamples(m_heatLossSplineXPlotData.data(), m_heatLossSplineYPlotData.data(), m_heatLossSplineXPlotData.size());
		m_heatLossSplineCurve->plot()->replot();
	}
}

