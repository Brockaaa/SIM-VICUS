#include "SVNetworkComponentHeatExchangeEditWidget.h"
#include "ui_SVNetworkComponentHeatExchangeEditWidget.h"

#include "SVSettings.h"
#include "SVChartUtils.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_plot_zoomer.h>

#include <VICUS_NetworkComponent.h>
#include <VICUS_NetworkHeatExchange.h>
#include <VICUS_KeywordListQt.h>
#include <VICUS_utilities.h>

#include <IBK_Parameter.h>
#include <IBK_FileUtils.h>
#include <IBK_CSVReader.h>
#include <IBK_math.h>

#include <QPushButton>

#include <QtExt_Directories.h>

SVNetworkComponentHeatExchangeEditWidget::SVNetworkComponentHeatExchangeEditWidget(QWidget *parent)
	: QWidget(parent)
	, m_ui(new Ui::SVNetworkComponentHeatExchangeEditWidget)
{
	m_ui->setupUi(this);

	// checks if VICUS::NetworkHeatExchange was changed. stackedWidgetHeatExchange must be adjusted accordingly
	Q_ASSERT(VICUS::NetworkHeatExchange::NUM_T == 10);

	configureChart(m_ui->widgetPlotHeatLossSpline);

	//sets up validating line edit appropriately
	m_ui->lineEditHeatTransferCoefficientConstant->setMinimum(0, false);
	m_ui->lineEditHeatTransferCoefficientSpline->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setMinimum(0, false);
	m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineFloorArea->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineFloorArea->setMinimum(0, false);
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setMinimum(0, false);
	m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setFormat('f', 0);

	// set comboBox in pageHeatLossSpline
	for(int i = 0; i < VICUS::NetworkHeatExchange::NUM_BT; i++){
		m_ui->comboBoxHeatLossSplineUserBuildingType->addItem(VICUS::KeywordListQt::Description("NetworkHeatExchange::BuildingType", i));
	}

	// set comboBox in pageTemperatureSpline
	for(int i = 0; i < VICUS::NetworkHeatExchange::NUM_AT; i++){
		m_ui->comboBoxTemperatureSpline->addItem(VICUS::KeywordListQt::Description("NetworkHeatExchange::AmbientTemperatureType", i));
	}

	m_ui->filepathDataFile->setup("", true, true, tr("Time-series data files (*.tsv *.csv);;All files (*.*)"),
								  SVSettings::instance().m_dontUseNativeDialogs);
}

SVNetworkComponentHeatExchangeEditWidget::~SVNetworkComponentHeatExchangeEditWidget()
{
	delete m_ui;
}

void SVNetworkComponentHeatExchangeEditWidget::updateInput(VICUS::NetworkComponent * component)
{
	m_current = component;


	// look up all available HeatExchange Modeltypes for this component
	std::vector<VICUS::NetworkHeatExchange::ModelType> availableHeatExchangeModelTypes = VICUS::NetworkComponent::availableHeatExchangeTypes(m_current->m_modelType);

	// if no HE Modeltype except NUM_T available, disable Heat Exchange tab
	if(availableHeatExchangeModelTypes.size() == 1 && availableHeatExchangeModelTypes[0] == VICUS::NetworkHeatExchange::NUM_T){
		this->setEnabled(false);
	} else {
		this->setEnabled(true);
	}

	// clear combobox from previous entries
	m_ui->comboBoxHeatExchange->clear();
	// insert all available HE modeltypes into the HE combobox, adds "None" last
	for(VICUS::NetworkHeatExchange::ModelType heatExchangeMT : availableHeatExchangeModelTypes){
		if (heatExchangeMT == VICUS::NetworkHeatExchange::NUM_T )
			m_ui->comboBoxHeatExchange->addItem(tr("Adiabatic"), VICUS::NetworkHeatExchange::NUM_T);
		else
			m_ui->comboBoxHeatExchange->addItem(VICUS::KeywordListQt::Description("NetworkHeatExchange::ModelType", heatExchangeMT), heatExchangeMT);
	}


	// clear vector that temporarily saves all changes made to a heat exchange
	m_vectorTempHeatExchange.clear();
	// fill vector with all available Heat Exchange modeltypes, adds "None"/NUM_T modeltype last
	for(VICUS::NetworkHeatExchange::ModelType heatExchangeMT: availableHeatExchangeModelTypes){
		if(heatExchangeMT == VICUS::NetworkHeatExchange::NUM_T) {
			m_vectorTempHeatExchange.push_back(VICUS::NetworkHeatExchange());
		}
		else {
			VICUS::NetworkHeatExchange newHeatExchange;
			newHeatExchange.m_modelType = heatExchangeMT;
			newHeatExchange.setDefaultValues(heatExchangeMT);
			m_vectorTempHeatExchange.push_back(newHeatExchange);
		}
	}

	// set the comboBox and stackedWidget to the hx modeltype of the current component
	int idx = m_ui->comboBoxHeatExchange->findData(m_current->m_heatExchange.m_modelType);
	if (idx < 0) // in case there was an hx modeltype set which is not available, set the first one
		idx = 0;
	m_ui->comboBoxHeatExchange->setCurrentIndex(idx);
	on_comboBoxHeatExchange_activated(idx);
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageHeatLossConstant()
{
	m_ui->checkBoxHeatLossConstantIndividual->setChecked(m_current->m_heatExchange.m_individualHeatExchange);
	on_checkBoxHeatLossConstantIndividual_stateChanged(static_cast<int>(m_current->m_heatExchange.m_individualHeatExchange));
}

void SVNetworkComponentHeatExchangeEditWidget::updatePageHeatLossSpline(VICUS::NetworkHeatExchange::ModelType hxModelType)
{
	// hxModelType must be one of both!
	Q_ASSERT(	hxModelType == VICUS::NetworkHeatExchange::T_HeatLossSpline
			 || hxModelType == VICUS::NetworkHeatExchange::T_HeatLossSplineCondenser );

	m_vectorTempHeatExchangeBuildingType.clear();
	m_ui->filepathDataFile->setFilename("");

	for(int i = 0; i < VICUS::NetworkHeatExchange::NUM_BT; i++){
		VICUS::NetworkHeatExchange::BuildingType buildingType = static_cast<VICUS::NetworkHeatExchange::BuildingType>(i);
		VICUS::NetworkHeatExchange newHeatExchange;
		newHeatExchange.m_buildingType = buildingType;
		newHeatExchange.setDefaultValues(hxModelType);
		m_vectorTempHeatExchangeBuildingType.push_back(newHeatExchange);
	}

	if(m_heatLossSplineXData.size() == 0) {
		readTsvHeatLossSpline();
		readTsvDomesticHotWaterDemand();
	}

	// set widgets in pageHeatLossSpline to appropriate values
	m_ui->checkBoxHeatLossSplineIndividual->setChecked(m_current->m_heatExchange.m_individualHeatExchange);
	on_checkBoxHeatLossSplineIndividual_clicked(m_current->m_heatExchange.m_individualHeatExchange);
}

void SVNetworkComponentHeatExchangeEditWidget::updatePageTemperatureConstant()
{
	m_ui->lineEditHeatTransferCoefficientConstant->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient].value);
	m_ui->lineEditTemperatureConstantTemperature->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_Temperature].value);
}

void SVNetworkComponentHeatExchangeEditWidget::updatePageTemperatureSpline()
{
	m_ui->lineEditHeatTransferCoefficientSpline->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient].value);
	m_ui->widgetTemperatureSplineFilePathDataFile->setFilename("");
	m_ui->comboBoxTemperatureSpline->setCurrentIndex((int)m_current->m_heatExchange.m_ambientTemperatureType);
	on_comboBoxTemperatureSpline_activated((int)m_current->m_heatExchange.m_ambientTemperatureType);
}

void SVNetworkComponentHeatExchangeEditWidget::on_comboBoxHeatExchange_activated(int index)
{
	// store old heat exchange to vector
	for(VICUS::NetworkHeatExchange& heatExchange : m_vectorTempHeatExchange){
		if(heatExchange.m_modelType == m_current->m_heatExchange.m_modelType){
			heatExchange = m_current->m_heatExchange;
		}
	}

	// take newly selected heat exchange from vector
	m_current->m_heatExchange = m_vectorTempHeatExchange[(unsigned int)index];

	// set according page and update content
	switch (m_current->m_heatExchange.m_modelType){
		case VICUS::NetworkHeatExchange::T_TemperatureConstant:
			m_ui->stackedWidgetHeatExchange->setCurrentIndex(0);
			updatePageTemperatureConstant();
			break;
		case VICUS::NetworkHeatExchange::T_TemperatureSpline:
		case VICUS::NetworkHeatExchange::T_TemperatureSplineEvaporator:
			m_ui->stackedWidgetHeatExchange->setCurrentIndex(1);
			updatePageTemperatureSpline();
			break;
		case VICUS::NetworkHeatExchange::T_HeatLossConstant:
		case VICUS::NetworkHeatExchange::T_HeatLossConstantCondenser:
			m_ui->stackedWidgetHeatExchange->setCurrentIndex(2);
			updatePageHeatLossConstant();
			break;
		case VICUS::NetworkHeatExchange::T_HeatLossSplineCondenser:
		case VICUS::NetworkHeatExchange::T_HeatLossSpline:
			m_ui->stackedWidgetHeatExchange->setCurrentIndex(3);
			updatePageHeatLossSpline(m_current->m_heatExchange.m_modelType);
			break;
		case VICUS::NetworkHeatExchange::T_TemperatureZone:
		case VICUS::NetworkHeatExchange::T_TemperatureConstructionLayer:
		case VICUS::NetworkHeatExchange::T_HeatingDemandSpaceHeating:
		case VICUS::NetworkHeatExchange::NUM_T:
			m_ui->stackedWidgetHeatExchange->setCurrentIndex(4);
			break;
	}
}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossConstantIndividual_stateChanged(int arg1)
{
	bool checked = static_cast<bool>(arg1);
	m_current->m_heatExchange.m_individualHeatExchange = checked;
	m_ui->labelHeatLossConstantUserHeatFlux->setEnabled(!checked);
	m_ui->labelHeatLossConstantUserUnit->setEnabled(!checked);
	m_ui->lineEditHeatLossConstantUser->setEnabled(!checked);
	m_ui->toolButtonSetDefaultValues->setEnabled(!checked);
	m_ui->lineEditHeatLossConstantUser->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatLoss].get_value("kW"));
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossConstantUser_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatLoss, m_ui->lineEditHeatLossConstantUser->value()*1000);
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditTemperatureConstantTemperature_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_Temperature, m_ui->lineEditTemperatureConstantTemperature->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatTransferCoefficientConstant_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient, m_ui->lineEditHeatTransferCoefficientConstant->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatTransferCoefficientSpline_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient, m_ui->lineEditHeatTransferCoefficientSpline->value());
}

void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossSplineIndividual_clicked(bool checked)
{
	m_current->m_heatExchange.m_individualHeatExchange = checked;
	// if checked, disable everything
	if(m_current->m_heatExchange.m_individualHeatExchange){
		if(m_heatLossSplineCoolingCurve != nullptr){
			m_heatLossSplineCoolingCurve->detach();
		}
		if(m_heatLossSplineHeatingCurve != nullptr){
			m_heatLossSplineHeatingCurve->detach();
		}
		m_ui->widgetPlotHeatLossSpline->setEnabled(false);
		m_ui->widgetPlotHeatLossSpline->replot();
		m_ui->widgetDefineHeatExchangeSpline->setEnabled(false);
	}
	/* if unchecked, enable everything and set all line edits that do not depend on other checkboxes to the appropriate value
	 * afterwards trigger all checkboxes to fill in all lineEdits that depend on those checkboxes */
	else {
		m_ui->widgetPlotHeatLossSpline->setEnabled(true);
		// set comboBox to the building type
		m_ui->widgetDefineHeatExchangeSpline->setEnabled(true);
		on_comboBoxHeatLossSplineUserBuildingType_activated(static_cast<int>(m_current->m_heatExchange.m_buildingType));
		// if user defined building type, do not fill out the rest
		if(m_current->m_heatExchange.m_buildingType == VICUS::NetworkHeatExchange::BT_UserDefineBuilding) return;
		// if Maximum Heating Load is set, fill out the line Edit
		if(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value == 0.0) {
			m_ui->lineEditHeatLossSplineMaximumHeatingLoad->clear();
		}
		else {
			m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].get_value());
		}
		// if Floor Area is set, fill out the line Edit
		if(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].value == 0.0) {
			m_ui->lineEditHeatLossSplineFloorArea->clear();
		}
		else {
			m_ui->lineEditHeatLossSplineFloorArea->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value());
		}

		// set checkbox AreaRelatedValues which will fill in the lineEdits that depend on it
		m_ui->checkBoxHeatLossSplineAreaRelatedValues->setChecked(m_current->m_heatExchange.m_areaRelatedValues);
		initializeHeatLossSplineAreaRelatedValues();
	}
}


void SVNetworkComponentHeatExchangeEditWidget::on_comboBoxHeatLossSplineUserBuildingType_activated(int index)
{
	// if the index is NUM_BT or invalid, set to Residentialbuilding
	if (index >= VICUS::NetworkHeatExchange::NUM_BT)
		index = 0;
	m_ui->comboBoxHeatLossSplineUserBuildingType->setCurrentIndex(index);

	// store old heatExchange
	for (unsigned int i = 0; i < m_vectorTempHeatExchangeBuildingType.size(); i++) {
		if (m_vectorTempHeatExchangeBuildingType[i].m_buildingType == m_current->m_heatExchange.m_buildingType) {
			m_vectorTempHeatExchangeBuildingType[i] = m_current->m_heatExchange;
		}
	}

	// get new heatExchange from vector
	m_current->m_heatExchange = m_vectorTempHeatExchangeBuildingType[(unsigned int)index];

	if (m_current->m_heatExchange.m_buildingType != VICUS::NetworkHeatExchange::BT_UserDefineBuilding){
		m_heatLossSplineHwUserProfile = mappingHeatLossSplineHotWaterYData();
		if(m_heatLossSplineHwUserProfile == NUM_HW){
			m_ui->groupBoxDomesticHotWaterDemand->setEnabled(false);
			m_ui->groupBoxDomesticHotWaterDemand->setChecked(false);
			m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->clear();
		} else {
			m_ui->groupBoxDomesticHotWaterDemand->setEnabled(true);
			m_ui->groupBoxDomesticHotWaterDemand->setChecked(m_current->m_heatExchange.m_withDomesticHotWaterDemand);
		}

		m_ui->stackedWidgetHeatLossSpline->setCurrentIndex(0);
		m_ui->checkBoxHeatLossSplineAreaRelatedValues->setChecked(static_cast<int>(m_current->m_heatExchange.m_areaRelatedValues));
		m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].get_value());
		m_ui->groupBoxHeatLossSplineCooling->setChecked(m_current->m_heatExchange.m_withCoolingDemand);
		m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].get_value());
		initializeHeatLossSplineAreaRelatedValues();

		// enable or disable floorArea related widgets depending if areaRelatedValues is set in heatExchange
		m_ui->labelHeatLossSplineFloorArea->setEnabled(true);
		m_ui->labelHeatLossSplineFloorAreaUnit->setEnabled(true);
		m_ui->lineEditHeatLossSplineFloorArea->setEnabled(true);

		updateHeatLossSplinePlotDataPredef();
	} else {
		m_ui->stackedWidgetHeatLossSpline->setCurrentIndex(1);
		m_ui->filepathDataFile->setFilename(QString::fromStdString(m_current->m_heatExchange.m_userDefinedTsvFile.str()));
		on_filepathDataFile_editingFinished();
	}
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineFloorArea_editingFinishedSuccessfully()
{
	double newFloorArea = m_ui->lineEditHeatLossSplineFloorArea->value();

	if(!m_current->m_heatExchange.m_areaRelatedValues){
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_FloorArea, newFloorArea);
		return;
	}

	// get newly set FloorArea and calculate what energyDemand results from that

	double oldEnergyDemandHeating, oldEnergyDemandCooling;
	oldEnergyDemandHeating = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific].get_value();


	// check if new FloorArea is reachable
	bool successfulNewHeatingK = calculateNewK(oldEnergyDemandHeating * newFloorArea );
	bool successfulNewCoolingK = true;
	if(m_current->m_heatExchange.m_withCoolingDemand) {
		oldEnergyDemandCooling = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value();;
		successfulNewCoolingK = calculateNewK(oldEnergyDemandHeating * newFloorArea );
	}

	// if the desired floorArea is not reachable, calculate the closest possible value to the desired floorArea
	double newFloorAreaHeating, newFloorAreaCooling;
	if(!(successfulNewHeatingK)){
		double newEnergyDemandHeating = m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value();
		newFloorAreaHeating = newEnergyDemandHeating / oldEnergyDemandHeating;
		newFloorArea = (int)(newFloorAreaHeating + 0.5);
	}
	if(!(successfulNewCoolingK)){
		double newEnergyDemandCooling = m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value();
		newFloorAreaCooling = newEnergyDemandCooling / oldEnergyDemandCooling;
		newFloorArea = (int)(newFloorAreaCooling + 0.5);
	}
	if((!successfulNewHeatingK) && (!successfulNewCoolingK)){
		// if newFloorArea too small
		if((newFloorAreaHeating >= newFloorArea) && (newFloorAreaCooling >= newFloorArea)){
			newFloorArea = newFloorAreaHeating > newFloorAreaCooling ? newFloorAreaHeating : newFloorAreaCooling;
		}
		// if newFloorArea too big
		else if ((newFloorAreaHeating <= newFloorArea) && (newFloorAreaCooling <= newFloorArea)){
			newFloorArea = newFloorAreaHeating > newFloorAreaCooling ? newFloorAreaCooling : newFloorAreaHeating;
		} else {
			Q_ASSERT(false); // no new floorArea can be found
		}
		newFloorArea = (int)(newFloorArea + 0.5);
	}

	// set new values, reset the lineEdits to the original value and plot everything
	if(m_current->m_heatExchange.m_withCoolingDemand) {
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(oldEnergyDemandCooling);
		std::vector<double> coolingValuesToPlot;
		for(double value : m_heatLossSplineCoolingYPlotData)
			coolingValuesToPlot.push_back(value / 1000); // convert to kW
		m_heatLossSplineCoolingCurve->setSamples(m_heatLossSplineXData.data(), coolingValuesToPlot.data(), m_heatLossSplineXData.size());
	}

	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(oldEnergyDemandHeating);
	m_ui->lineEditHeatLossSplineFloorArea->setValue(newFloorArea);
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_FloorArea, newFloorArea);
	std::vector<double> heatingValuesToPlot;
	for(double value : m_heatLossSplineHeatingYPlotData)
		heatingValuesToPlot.push_back(value / 1000); // convert to kW
	m_heatLossSplineHeatingCurve->setSamples(m_heatLossSplineXData.data(), heatingValuesToPlot.data(), m_heatLossSplineXData.size());
	m_heatLossSplineHeatingCurve->plot()->replot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineMaximumHeatingLoad_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumHeatingLoad, m_ui->lineEditHeatLossSplineMaximumHeatingLoad->value());
	calculateNewHeatLossSplineYData(m_kHeating, m_heatLossSplineHeatingYPlotData);
	double maximumHeatingLoad, maximumCoolingLoad;
	maximumHeatingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;
	maximumCoolingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value;
	std::vector<double> heatingValuesToPlot;
	for(double value : m_heatLossSplineHeatingYPlotData)
		heatingValuesToPlot.push_back(value / 1000); // convert to kW
	m_heatLossSplineHeatingCurve->setSamples(m_heatLossSplineXData.data(), heatingValuesToPlot.data(), m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad / 1000 : maximumCoolingLoad / 1000);
	m_heatLossSplineHeatingCurve->plot()->replot();
	m_heatLossSplineZoomer->setZoomBase();
	double newHeatingEnergyDemand = calculateEnergyDemand() / 1000;
	if(m_current->m_heatExchange.m_areaRelatedValues) {
		double floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
		newHeatingEnergyDemand /= floorArea;
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific, newHeatingEnergyDemand);
	} else {
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, newHeatingEnergyDemand);
	}

	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(newHeatingEnergyDemand);
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumHeatingLoad, m_ui->lineEditHeatLossSplineMaximumHeatingLoad->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineHeatingEnergyDemand_editingFinishedSuccessfully()
{
	bool areaRelatedValues = m_current->m_heatExchange.m_areaRelatedValues;

	IBK::NearEqual<double> nearEqual(0.5);
	// check if requested EnergyDemand is equal to already set energyDemand, if yes, just return
	if(areaRelatedValues){
		if(nearEqual(m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value(), m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific].get_value())) return;
	} else {
		if(nearEqual(m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value(), m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value())) return;
	}

	// get previously set EnergyDemand
	double previousHeatingDemand;
	if(areaRelatedValues){
		previousHeatingDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific].get_value();
	} else {
		previousHeatingDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value();
	}

	// set floorArea only to a value != 1, if areaRelatedValues are set
	double floorArea = 1;
	if(areaRelatedValues) {
		floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
	}

	double newHeatingEnergyDemand = m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value() * floorArea;
	if(calculateNewK(newHeatingEnergyDemand) || nearEqual(m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value() / floorArea, previousHeatingDemand / floorArea)){
		if(areaRelatedValues){
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific, newHeatingEnergyDemand / floorArea);
			m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(newHeatingEnergyDemand / floorArea);
		} else {
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, newHeatingEnergyDemand);
		}
	} else {
		double newIntegralCalculated = m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value() / floorArea;
		QString requested = QString::number(newHeatingEnergyDemand,'f',  0);
		QString closest = QString::number(newIntegralCalculated, 'f', 0);
		QString previous = QString::number(previousHeatingDemand, 'f', 0);

		QMessageBox msgBox(this);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setWindowTitle(QString("Requested HeatingEnergyDemand not reachable"));
		msgBox.setText(QString("The requested HeatingEnergyDemand of %1 kWh is not reachable. The closest reachable value is %2. Take the closest value or revert to the previous value %3 kWh?")
						   .arg(requested, closest, previous));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

		msgBox.setButtonText(QMessageBox::Yes, QString("Take closest reachable Value %1").arg(closest));
		msgBox.setButtonText(QMessageBox::No, QString("Revert to previous Value %1").arg(previous));

		int result = msgBox.exec();

		if(result == QMessageBox::Yes){
			m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(newIntegralCalculated);
			if(areaRelatedValues){
				VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific, newIntegralCalculated / floorArea);
			} else {
				VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, newIntegralCalculated);
			}
		} else {
			Q_ASSERT(calculateNewK(previousHeatingDemand * floorArea));
			m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(previousHeatingDemand);
			if(areaRelatedValues){
				VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific, previousHeatingDemand);
			} else {
				VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, previousHeatingDemand);
			}
		}
	}
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->clearFocus();
	std::vector<double> heatingValuesToPlot;
	for(double value : m_heatLossSplineHeatingYPlotData)
		heatingValuesToPlot.push_back(value / 1000); // convert to kW
	m_heatLossSplineHeatingCurve->setSamples(m_heatLossSplineXData.data(), heatingValuesToPlot.data(), m_heatLossSplineXData.size());
	m_heatLossSplineHeatingCurve->plot()->replot();
}

void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossSplineAreaRelatedValues_stateChanged(int arg1)
{
	bool areaRelated = m_current->m_heatExchange.m_areaRelatedValues = static_cast<bool>(arg1);

	double heatingEnergyDemand, coolingEnergyDemand, domesticHotWaterDemand, floorArea = 0;

	floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
	if(areaRelated){
		heatingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value();
		if(heatingEnergyDemand == 0) heatingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific].get_value();
		else heatingEnergyDemand /= floorArea;
		coolingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value();
		if(coolingEnergyDemand == 0)m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value();
		else coolingEnergyDemand /= floorArea;
		domesticHotWaterDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand].get_value();
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific, heatingEnergyDemand);
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific, coolingEnergyDemand);
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_DomesticHotWaterDemandAreaSpecific, domesticHotWaterDemand);
		m_ui->labelHeatLossSplineHeatingEnergyDemandUnit->setText("kWh/m²");
		m_ui->labelHeatLossSplineCoolingEnergyDemandUnit->setText("kWh/m²");
		m_ui->labelHeatLossSplineDomesticHotWaterDemandUnit->setText("kWh/m²");
	} else {
		heatingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific].get_value() * floorArea;
		if(heatingEnergyDemand == 0) heatingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value();
		coolingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value() * floorArea;
		if(coolingEnergyDemand == 0) coolingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value();
		domesticHotWaterDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemandAreaSpecific].get_value() * floorArea;
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, heatingEnergyDemand);
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand, coolingEnergyDemand);
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand, domesticHotWaterDemand);
		m_ui->labelHeatLossSplineHeatingEnergyDemandUnit->setText("kWh");
		m_ui->labelHeatLossSplineCoolingEnergyDemandUnit->setText("kWh");
		m_ui->labelHeatLossSplineDomesticHotWaterDemandUnit->setText("kWh");
	}

	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_Temperature, m_ui->lineEditTemperatureConstantTemperature->value());
	if(heatingEnergyDemand == 0) {
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->clear();
	} else {
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(heatingEnergyDemand);
	}

	if(coolingEnergyDemand == 0) {
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->clear();
	} else {
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(coolingEnergyDemand);
	}


	m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setValue(domesticHotWaterDemand);

	if(floorArea == 0) {
		m_ui->lineEditHeatLossSplineFloorArea->clear();
	} else {
		m_ui->lineEditHeatLossSplineFloorArea->setValue(floorArea);
	}
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineDomesticHotWaterDemand_editingFinishedSuccessfully()
{
	if(m_current->m_heatExchange.m_areaRelatedValues){
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_DomesticHotWaterDemandAreaSpecific, m_ui->lineEditHeatLossSplineFloorArea->value());
	} else {
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand, m_ui->lineEditHeatLossSplineFloorArea->value());
	}
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineCoolingEnergyDemand_editingFinishedSuccessfully()
{
	bool areaRelatedValues = m_current->m_heatExchange.m_areaRelatedValues;

	IBK::NearEqual<double> nearEqual(1);
	// check if requested EnergyDemand is equal to already set energyDemand, if yes, just return
	if(areaRelatedValues){
		if(m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() == m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value()) return;
	} else {
		if(m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() == m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value()) return;
	}

	// get previously set EnergyDemand
	double previousCoolingDemand;
	if(areaRelatedValues){
		previousCoolingDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value();
	} else {
		previousCoolingDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value();
	}

	// set floorArea only to a value != 1, if areaRelatedValues are set
	double floorArea = 1;
	if(areaRelatedValues) {
		floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
	}

	double newCoolingEnergyDemand = m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() * floorArea;
	if(calculateNewK(newCoolingEnergyDemand, VICUS::NetworkHeatExchange::P_MaximumCoolingLoad) || nearEqual(m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() / floorArea, previousCoolingDemand / floorArea)){
		if(areaRelatedValues){
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific, newCoolingEnergyDemand / floorArea);
			m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(newCoolingEnergyDemand / floorArea);
		} else {
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand, newCoolingEnergyDemand);
		}
	} else {
		double newIntegralCalculated = m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() / floorArea;
		QString requested = QString::number(newCoolingEnergyDemand,'f',  0);
		QString closest = QString::number(newIntegralCalculated, 'f', 0);
		QString previous = QString::number(previousCoolingDemand, 'f', 0);


		QMessageBox msgBox(this);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setWindowTitle(QString("Requested CoolingEnergyDemand not reachable"));
		msgBox.setText(QString("The requested CoolingEnergyDemand of %1 kWh is not reachable. The closest reachable value is %2. Take the closest value or revert to the previous value %3 kWh?")
						   .arg(requested, closest, previous));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

		msgBox.setButtonText(QMessageBox::Yes, QString("Take closest reachable Value %1").arg(closest));
		msgBox.setButtonText(QMessageBox::No, QString("Revert to previous Value %1").arg(previous));

		int result = msgBox.exec();

		if(result == QMessageBox::Yes){
			m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(newIntegralCalculated);
			if(areaRelatedValues){
				VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific, newIntegralCalculated / floorArea);
			} else {
				VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand, newIntegralCalculated);
			}
		} else {
			Q_ASSERT(calculateNewK(previousCoolingDemand * floorArea));
			m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(previousCoolingDemand);
			if(areaRelatedValues){
				VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific, previousCoolingDemand);
			} else {
				VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand, previousCoolingDemand);
			}
		}
	}
	m_ui->lineEditHeatLossSplineCoolingEnergyDemand->clearFocus();
	std::vector<double> coolingValuesToPlot;
	for(double value : m_heatLossSplineCoolingYPlotData)
		coolingValuesToPlot.push_back(value / 1000); // convert to kW
	m_heatLossSplineCoolingCurve->setSamples(m_heatLossSplineXData.data(), coolingValuesToPlot.data(), m_heatLossSplineXData.size());
	m_heatLossSplineCoolingCurve->plot()->replot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_groupBoxHeatLossSplineCooling_clicked(bool checked)
{
	bool areaRelatedValues = m_current->m_heatExchange.m_areaRelatedValues;
	m_current->m_heatExchange.m_withCoolingDemand = checked;
	// if checked, fill in the lineEdits with values depending if areaRelatedValues is set
	if(checked){
		double maximumCoolingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].get_value();
		if(maximumCoolingLoad == 0){
			m_ui->lineEditHeatLossSplineMaximumCoolingLoad->clear();
		} else {
			m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setValue(maximumCoolingLoad);
		}

		// coolingEnergyDemand depends on areaRelatedValues
		double coolingEnergyDemand;
		if(areaRelatedValues) {
			coolingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value();
		} else {
			coolingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value();
		}

		if(coolingEnergyDemand == 0){
			m_ui->lineEditHeatLossSplineCoolingEnergyDemand->clear();
		} else {
			m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(coolingEnergyDemand);
		}
	}
	setCoolingCurve(checked);
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineMaximumCoolingLoad_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumCoolingLoad, m_ui->lineEditHeatLossSplineMaximumCoolingLoad->value());
	calculateNewHeatLossSplineYData(m_kCooling, m_heatLossSplineCoolingYPlotData, VICUS::NetworkHeatExchange::P_MaximumCoolingLoad);
	double maximumHeatingLoad, maximumCoolingLoad;
	maximumHeatingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;
	maximumCoolingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value;
	std::vector<double> coolingValuesToPlot;
	for(double value : m_heatLossSplineCoolingYPlotData)
		coolingValuesToPlot.push_back(value / 1000); // convert to kW
	m_heatLossSplineCoolingCurve->setSamples(m_heatLossSplineXData.data(), coolingValuesToPlot.data(), m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad / 1000 : maximumCoolingLoad / 1000);
	m_heatLossSplineCoolingCurve->plot()->replot();
	m_heatLossSplineZoomer->setZoomBase();

	double newCoolingEnergyDemand = calculateEnergyDemand(VICUS::NetworkHeatExchange::P_CoolingEnergyDemand) / 1000;
	if(m_current->m_heatExchange.m_areaRelatedValues) {
		double floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
		newCoolingEnergyDemand /= floorArea;
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific, newCoolingEnergyDemand);
	} else {
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand, newCoolingEnergyDemand);
	}
	m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(newCoolingEnergyDemand);
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumCoolingLoad, m_ui->lineEditHeatLossSplineMaximumCoolingLoad->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_filepathDataFile_editingFinished()
{

	// clear embedded spline data
	m_vectorHeatLossSplineUserYData.clear();
	m_vectorHeatLossSplineUserXData.clear();

	QString dataFilePath = m_ui->filepathDataFile->filename();
	if (dataFilePath.trimmed().isEmpty()) {
		m_current->m_heatExchange.m_userDefinedTsvFile.clear();
		if(m_heatLossSplineHeatingCurve != nullptr) {
			m_heatLossSplineHeatingCurve->detach();
		}
		if(m_heatLossSplineCoolingCurve != nullptr) {
			m_heatLossSplineCoolingCurve->detach();
		}
		m_ui->widgetPlotHeatLossSpline->replot();
		return;
	}

	updateHeatLossSplineSelectColumnList(); // if there are columns to be selected, the widget will be re-enabled here
}

void SVNetworkComponentHeatExchangeEditWidget::on_widgetTemperatureSplineFilePathDataFile_editingFinished(){
	updateTemperatureSplineSelectColumnList();
}

void SVNetworkComponentHeatExchangeEditWidget::on_listWidgetHeatLossSplineSelectColumn_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
	qDebug() << "HeatLossSpline List Widget Select Column ";
	if (current == nullptr)
		return; // do nothing

	// get column index
	int currentListItem = current->data(Qt::UserRole).toInt();
	if (currentListItem < 0) {
		// invalid unit in data column, cannot use this column
		return;
	}

	// add suffix to file name
	IBK::Path fname(IBK::Path(m_ui->filepathDataFile->filename().toStdString()));
	IBK::Path adjustedFileName;
	int number;
	IBK::extract_number_suffix(fname, adjustedFileName, number);
	QString extendedFilename = QString("%1?%2")
								   .arg(QString::fromStdString(adjustedFileName.str()))
								   .arg(currentListItem);
	m_ui->filepathDataFile->setFilename( extendedFilename );
	m_current->m_heatExchange.m_userDefinedTsvFile = IBK::Path(extendedFilename.toStdString());

	updateHeatLossSplinePlotDataUser();
}

void SVNetworkComponentHeatExchangeEditWidget::on_listWidgetTemperatureSplineSelectColumn_currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous)
{
	qDebug() << "TemperatureSpline List Widget Select Column ";
	if (current == nullptr)
		return; // do nothing

	// get column index
	int currentListItem = current->data(Qt::UserRole).toInt();
	if (currentListItem < 0) {
		// invalid unit in data column, cannot use this column
		return;
	}

	// add suffix to file name
	IBK::Path fname(IBK::Path(m_ui->widgetTemperatureSplineFilePathDataFile->filename().toStdString()));
	IBK::Path adjustedFileName;
	int number;
	IBK::extract_number_suffix(fname, adjustedFileName, number);
	QString extendedFilename = QString("%1?%2")
								   .arg(QString::fromStdString(adjustedFileName.str()))
								   .arg(currentListItem);
	m_ui->widgetTemperatureSplineFilePathDataFile->setFilename( extendedFilename );
	m_current->m_heatExchange.m_userDefinedTsvFile = IBK::Path(extendedFilename.toStdString());

	NANDRAD::LinearSplineParameter spl;
	spl.m_tsvFile = IBK::Path(extendedFilename.toStdString());

	try {
		spl.readTsv();
	}
	catch (IBK::Exception & ex) {
		ex.writeMsgStackToError();
		return;
	}

	m_temperatureSplineXPlotData = spl.m_values.x();
	m_temperatureSplineYPlotData = spl.m_values.y();

	updateTemperatureSplinePlotData();
}


void SVNetworkComponentHeatExchangeEditWidget::updateHeatLossSplineSelectColumnList()
{
	// clear list widget
	m_ui->listWidgetHeatLossSplineSelectColumn->selectionModel()->blockSignals(true);
	m_ui->listWidgetHeatLossSplineSelectColumn->clear();
	m_ui->listWidgetHeatLossSplineSelectColumn->selectionModel()->blockSignals(false);

	QString dataFilePath = m_ui->filepathDataFile->filename();
	if(dataFilePath == QString("")) return;
	// parse tsv-file and if several data columns are in file, show the column selection list widget
	IBK::Path filePath(dataFilePath.toStdString()); // this is always an absolute path
	// check if we have a  csv/tsv file
	IBK::Path adjustedFileName;
	int selectedColumn = 1;
	IBK::extract_number_suffix(filePath, adjustedFileName, selectedColumn);
	std::string extension = IBK::tolower_string(adjustedFileName.extension());
	// read first line of file
	IBK::CSVReader reader;
	try {
		// read only header
		reader.read(adjustedFileName, true, true);
	}
	catch (...) {
		//m_ui->widgetTimeSeriesPreview->setErrorMessage(tr("Error reading data file.")); //TODO
		return;
	}

	if(selectedColumn != -1){
		auto item = m_ui->listWidgetHeatLossSplineSelectColumn->item(selectedColumn);
		m_ui->listWidgetHeatLossSplineSelectColumn->setCurrentItem(item);
	}


	m_ui->listWidgetHeatLossSplineSelectColumn->setEnabled(true);
	m_ui->listWidgetHeatLossSplineSelectColumn->selectionModel()->blockSignals(true);

	// process all columns past the first
	for (unsigned int i=1; i<reader.m_captions.size(); ++i) {

		// try to extract unit
		QListWidgetItem * item = nullptr;
		std::string ustr = reader.m_units[i];
		if (ustr.empty())
			ustr = "-";
		item = new QListWidgetItem(QString("%1 [%2]").arg(QString::fromStdString(reader.m_captions[i]),
														  QString::fromStdString(ustr)) );
		try {
			IBK::Unit u(ustr); // will throw in case of unknown unit

			item->setData(Qt::UserRole, i);
			item->setData(Qt::UserRole+1, QString::fromStdString(ustr));
			item->setData(Qt::UserRole+2, QString::fromStdString(reader.m_captions[i]));
			item->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		}
		catch (...) {
			item->setData(Qt::UserRole, -2); // unrecognized unit
			item->setForeground(Qt::gray);
		}
		m_ui->listWidgetHeatLossSplineSelectColumn->addItem(item);
	}
	selectedColumn = qMin(selectedColumn, (int)reader.m_captions.size());

	m_ui->listWidgetHeatLossSplineSelectColumn->setCurrentRow(selectedColumn-1);
	m_ui->listWidgetHeatLossSplineSelectColumn->selectionModel()->blockSignals(false);

	// we now have a column selected, trigger update of diagram
	on_listWidgetHeatLossSplineSelectColumn_currentItemChanged(m_ui->listWidgetHeatLossSplineSelectColumn->currentItem(), nullptr);
}

void SVNetworkComponentHeatExchangeEditWidget::updateTemperatureSplineSelectColumnList()
{
	qDebug() << "updateTemperatureSplineSelectColumnList";
	// clear list widget
	m_ui->listWidgetTemperatureSplineSelectColumn->selectionModel()->blockSignals(true);
	m_ui->listWidgetTemperatureSplineSelectColumn->clear();
	m_ui->listWidgetTemperatureSplineSelectColumn->selectionModel()->blockSignals(false);

	QString dataFilePath = m_ui->widgetTemperatureSplineFilePathDataFile->filename();
	if(dataFilePath == QString("")) {
		return;
	}
	// parse tsv-file and if several data columns are in file, show the column selection list widget
	IBK::Path filePath(dataFilePath.toStdString()); // this is always an absolute path
	// check if we have a  csv/tsv file
	IBK::Path adjustedFileName;
	int selectedColumn = 1;
	IBK::extract_number_suffix(filePath, adjustedFileName, selectedColumn);
	std::string extension = IBK::tolower_string(adjustedFileName.extension());
	// read first line of file
	IBK::CSVReader reader;
	try {
		// read only header
		reader.read(adjustedFileName, true, true);
	}
	catch (...) {
		//m_ui->widgetTimeSeriesPreview->setErrorMessage(tr("Error reading data file.")); //TODO
		return;
	}

	if(selectedColumn != -1){
		auto item = m_ui->listWidgetTemperatureSplineSelectColumn->item(selectedColumn);
		m_ui->listWidgetTemperatureSplineSelectColumn->setCurrentItem(item);
	}

	m_ui->widgetTemperatureSplineSelectColumn->setEnabled(true);
	m_ui->listWidgetTemperatureSplineSelectColumn->selectionModel()->blockSignals(true);


	// process all columns past the first
	for (unsigned int i=1; i<reader.m_captions.size(); ++i) {

		// try to extract unit
		QListWidgetItem * item = nullptr;
		std::string ustr = reader.m_units[i];
		if (ustr.empty())
			ustr = "-";
		item = new QListWidgetItem(QString("%1 [%2]").arg(QString::fromStdString(reader.m_captions[i]),
														  QString::fromStdString(ustr)) );
		try {
			IBK::Unit u(ustr); // will throw in case of unknown unit

			item->setData(Qt::UserRole, i);
			item->setData(Qt::UserRole+1, QString::fromStdString(ustr));
			item->setData(Qt::UserRole+2, QString::fromStdString(reader.m_captions[i]));
			item->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		}
		catch (...) {
			item->setData(Qt::UserRole, -2); // unrecognized unit
			item->setForeground(Qt::gray);
		}
		m_ui->listWidgetTemperatureSplineSelectColumn->addItem(item);
	}
	selectedColumn = qMin(selectedColumn, (int)reader.m_captions.size());

	m_ui->listWidgetTemperatureSplineSelectColumn->setCurrentRow(selectedColumn-1);
	m_ui->listWidgetTemperatureSplineSelectColumn->selectionModel()->blockSignals(false);

	// we now have a column selected, trigger update of diagram
	on_listWidgetTemperatureSplineSelectColumn_currentItemChanged(m_ui->listWidgetTemperatureSplineSelectColumn->currentItem(), nullptr);
}


void SVNetworkComponentHeatExchangeEditWidget::readTsvHeatLossSpline()
{
	std::vector<QString> directories;
	directories.push_back(QString("/demandProfiles/Residential_HeatingLoad.tsv"));
	directories.push_back(QString("/demandProfiles/Residential_CoolingLoad.tsv"));
	directories.push_back(QString("/demandProfiles/Office_HeatingLoad.tsv"));
	directories.push_back(QString("/demandProfiles/Office_CoolingLoad.tsv"));

	for(unsigned int i = 0; i < directories.size(); i++){
		bool heating = directories[i].contains("Heating");
		IBK::CSVReader reader;

		directories[i] = QtExt::Directories::resourcesRootDir().append(directories[i]);

		IBK::Path ibkDirectory(directories[i].toStdString());
		try {
			reader.read(ibkDirectory);
		}
		catch (...) {
			qDebug() << "Could not load HeatLossSplineTSV successfully";
		}

		if(i == 0){
			m_heatLossSplineXData = reader.colData(0);
		}
		for(unsigned int j = 1; j < reader.m_nColumns; j++){
			if(heating){
				m_vectorHeatLossSplineHeatingYData.push_back(reader.colData(j));
			}
			else{
				m_vectorHeatLossSplineCoolingYData.push_back(reader.colData(j));
			}
		}
	}
}


void SVNetworkComponentHeatExchangeEditWidget::readTsvDomesticHotWaterDemand()
{
	std::map<HotWaterPredefUserProfile, QString> directories;
	directories[HW_Residential] = QString("/demandProfiles/Residential_HotWaterDemand.tsv");

	for(auto &directory : directories){
		IBK::CSVReader reader;

		directories[directory.first] = QtExt::Directories::resourcesRootDir().append(directories[directory.first]);

		IBK::Path ibkDirectory(directories[directory.first].toStdString());
		try {
			reader.read(ibkDirectory);
		}
		catch (...) {
			qDebug() << "Could not load successfully";
		}

		m_mapHeatLossSplineHotWaterYData[directory.first] = reader.colData(1);
	}
}

SVNetworkComponentHeatExchangeEditWidget::HotWaterPredefUserProfile SVNetworkComponentHeatExchangeEditWidget::mappingHeatLossSplineHotWaterYData()
{
	// TODO when new tsvs and buildingTypes
	switch(m_current->m_heatExchange.m_buildingType){
		case VICUS::NetworkHeatExchange::BT_ResidentialBuildingSingleFamily:
		case VICUS::NetworkHeatExchange::BT_ResidentialBuildingMultiFamily:
		case VICUS::NetworkHeatExchange::BT_ResidentialBuildingLarge:
			return HW_Residential;
		default:
			return NUM_HW;
	}
}

void SVNetworkComponentHeatExchangeEditWidget::updateHeatLossSplinePlotDataPredef()
{
	for(unsigned int i = 0; i < m_vectorHeatLossSplineHeatingYData.size(); i++){
		double maxValue = *(std::max_element(m_vectorHeatLossSplineHeatingYData[i].begin(), m_vectorHeatLossSplineHeatingYData[i].end()));
		m_vectorHeatLossSplineHeatingMaxValues.push_back(maxValue);
	}

	for(unsigned int i = 0; i < m_vectorHeatLossSplineCoolingYData.size(); i++){
		double maxValue = *(std::max_element(m_vectorHeatLossSplineCoolingYData[i].begin(), m_vectorHeatLossSplineCoolingYData[i].end()));
		m_vectorHeatLossSplineCoolingMaxValues.push_back(maxValue);
	}


	VICUS::NetworkHeatExchange::para_t parameterHeating, parameterCooling;
	double floorArea = 1;

	if(m_current->m_heatExchange.m_areaRelatedValues){
		parameterHeating = VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific;
		parameterCooling = VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific;
		floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
	} else {
		parameterHeating = VICUS::NetworkHeatExchange::P_HeatingEnergyDemand;
		parameterCooling = VICUS::NetworkHeatExchange::P_CoolingEnergyDemand;

	}

	if(m_current->m_heatExchange.m_para[parameterHeating].get_value() == 0){
		m_kHeating = 1;
		calculateNewHeatLossSplineYData(m_kHeating, m_heatLossSplineHeatingYPlotData);
	} else {
		/* if assertion fails, the provided HeatingEnergyLoad is not reachable with the provided MaximumHeatingValue and the graph */
		Q_ASSERT(calculateNewK(m_current->m_heatExchange.m_para[parameterHeating].get_value() * floorArea));
		calculateNewHeatLossSplineYData(m_kHeating, m_heatLossSplineHeatingYPlotData);
	}

	if(m_current->m_heatExchange.m_para[parameterCooling].get_value() == 0){
		m_kCooling = 1;
		calculateNewHeatLossSplineYData(m_kCooling, m_heatLossSplineCoolingYPlotData, VICUS::NetworkHeatExchange::P_MaximumCoolingLoad);
	} else {
		Q_ASSERT(calculateNewK(m_current->m_heatExchange.m_para[parameterCooling].get_value() * floorArea, VICUS::NetworkHeatExchange::P_MaximumCoolingLoad));
		calculateNewHeatLossSplineYData(m_kCooling, m_heatLossSplineCoolingYPlotData, VICUS::NetworkHeatExchange::P_MaximumCoolingLoad);
	}

	double maximumHeatingLoad, maximumCoolingLoad;
	maximumHeatingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;
	maximumCoolingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value;
	m_ui->widgetPlotHeatLossSpline->setAxisTitle(QwtPlot::xBottom, "Time [h]");
	m_ui->widgetPlotHeatLossSpline->setAxisTitle(QwtPlot::yLeft, "[kW]");
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad / 1000 : maximumCoolingLoad / 1000);

	//creating curve for heating
	if(m_heatLossSplineHeatingCurve == nullptr) {
		m_heatLossSplineHeatingCurve = new QwtPlotCurve("Heating");
		m_heatLossSplineHeatingCurve->setPen(Qt::red);
	}
	std::vector<double> heatingValuesToPlot;
	for(double value : m_heatLossSplineHeatingYPlotData)
		heatingValuesToPlot.push_back(value / 1000); // convert to kW
	m_heatLossSplineHeatingCurve->setSamples(m_heatLossSplineXData.data(), heatingValuesToPlot.data(), m_heatLossSplineXData.size());
	m_heatLossSplineHeatingCurve->attach(m_ui->widgetPlotHeatLossSpline);

	//creating curve for cooling
	setCoolingCurve(m_current->m_heatExchange.m_withCoolingDemand);

	if(m_heatLossSplineZoomer == nullptr) m_heatLossSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotHeatLossSpline->canvas() );
	m_heatLossSplineZoomer->setZoomBase();

}

void SVNetworkComponentHeatExchangeEditWidget::updateHeatLossSplinePlotDataUser()
{
	if(m_heatLossSplineCoolingCurve == nullptr){
		m_heatLossSplineCoolingCurve = new QwtPlotCurve("Cooling");
		m_heatLossSplineCoolingCurve->setPen(Qt::blue);
	}

	IBK::Path fname(m_ui->filepathDataFile->filename().toStdString());
	NANDRAD::LinearSplineParameter spl;
	spl.m_tsvFile = fname;

	try {
		spl.readTsv();
	}
	catch (IBK::Exception & ex) {
		ex.writeMsgStackToError();
		return;
	}

	m_vectorHeatLossSplineUserXData = spl.m_values.x();
	m_vectorHeatLossSplineUserYData = spl.m_values.y();

	bool containsNegativeValues = false;
	double maximumHeatingLoad = 0;
	double maximumCoolingLoad = 0;
	for(double value : m_vectorHeatLossSplineUserYData){
		if(value < 0){
			containsNegativeValues = true;
			break;
		}
	}

	std::vector<double> vectorContainingCoolingValues;
	if(containsNegativeValues) {
		for(unsigned int i = 0; i < m_vectorHeatLossSplineUserXData.size(); i++){
			if(m_vectorHeatLossSplineUserYData[i] < 0){
				vectorContainingCoolingValues.push_back(-m_vectorHeatLossSplineUserYData[i]);
				m_vectorHeatLossSplineUserYData[i] = 0;
				if (maximumCoolingLoad < *vectorContainingCoolingValues.end()) maximumCoolingLoad = *vectorContainingCoolingValues.end();
			} else {
				vectorContainingCoolingValues.push_back(0);
			}
		}

		if(m_heatLossSplineCoolingCurve == nullptr) {
			m_heatLossSplineCoolingCurve = new QwtPlotCurve("Cooling");
			m_heatLossSplineCoolingCurve->setPen(Qt::blue);
		}
		std::vector<double> coolingValuesToPlot;
		for(double value : m_heatLossSplineCoolingYPlotData)
			coolingValuesToPlot.push_back(value / 1000); // convert to kW
		m_heatLossSplineCoolingCurve->setSamples(m_vectorHeatLossSplineUserXData.data(), coolingValuesToPlot.data(), m_vectorHeatLossSplineUserXData.size());
		m_heatLossSplineCoolingCurve->attach(m_ui->widgetPlotHeatLossSpline);
	} else {
		if (m_heatLossSplineCoolingCurve != nullptr)
			m_heatLossSplineCoolingCurve->detach();
	}

	maximumHeatingLoad = *(std::max_element(m_vectorHeatLossSplineUserYData.begin(), m_vectorHeatLossSplineUserYData.end()));

	if(m_heatLossSplineHeatingCurve == nullptr) {
		m_heatLossSplineHeatingCurve = new QwtPlotCurve("Heating");
		m_heatLossSplineHeatingCurve->setPen(Qt::red);
	}
	std::vector<double> heatingValuesToPlot;
	for(double value : m_heatLossSplineHeatingYPlotData)
		heatingValuesToPlot.push_back(value / 1000); // convert to kW
	m_heatLossSplineHeatingCurve->setSamples(m_vectorHeatLossSplineUserXData.data(), heatingValuesToPlot.data(), m_heatLossSplineXData.size());
	m_heatLossSplineHeatingCurve->attach(m_ui->widgetPlotHeatLossSpline);
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad / 1000 : maximumCoolingLoad / 1000);
	m_ui->widgetPlotHeatLossSpline->replot();

	if(m_heatLossSplineZoomer == nullptr) m_heatLossSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotHeatLossSpline->canvas() );
	m_heatLossSplineZoomer->setZoomBase();

}

void SVNetworkComponentHeatExchangeEditWidget::updateTemperatureSplinePlotData()
{
	m_ui->widgetPlotTemperatureSpline->setEnabled(true);
	double minYValue, maxYValue;

	minYValue = *(std::min_element(m_temperatureSplineYPlotData.begin(), m_temperatureSplineYPlotData.end()));
	maxYValue = *(std::max_element(m_temperatureSplineYPlotData.begin(), m_temperatureSplineYPlotData.end()));
	double scaleYMin = minYValue < 0 ? minYValue * 1.1 : minYValue * 0.9;
	double scaleYMax = maxYValue < 0 ? maxYValue * 0.9 : maxYValue * 1.1;

	m_ui->widgetPlotTemperatureSpline->setAxisTitle(QwtPlot::xBottom, "Time [d]");
	m_ui->widgetPlotTemperatureSpline->setAxisTitle(QwtPlot::yLeft, "SupplyTemperatureSchedule [C]");
	m_ui->widgetPlotTemperatureSpline->setAxisScale(QwtPlot::xBottom, 0, m_temperatureSplineYPlotData.size());
	m_ui->widgetPlotTemperatureSpline->setAxisScale(QwtPlot::yLeft, scaleYMin, scaleYMax);

	if(m_temperatureSplineCurve == nullptr) {
		m_temperatureSplineCurve = new QwtPlotCurve("Temperature");
		m_temperatureSplineCurve->setPen(Qt::red);
	}
	m_temperatureSplineCurve->setSamples(m_temperatureSplineXPlotData.data(), m_temperatureSplineYPlotData.data(), m_temperatureSplineYPlotData.size());
	m_temperatureSplineCurve->attach(m_ui->widgetPlotTemperatureSpline);
	m_ui->widgetPlotTemperatureSpline->replot();

	if(m_temperatureSplineZoomer == nullptr) m_temperatureSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotTemperatureSpline->canvas() );
	m_temperatureSplineZoomer->setZoomBase();
}

void SVNetworkComponentHeatExchangeEditWidget::updateTemperatureSplinePlotDataUser()
{
	//if(m_heatLossSplineCoolingCurve == nullptr){
	//	m_heatLossSplineCoolingCurve = new QwtPlotCurve("Cooling");
	//	m_heatLossSplineCoolingCurve->setPen(Qt::blue);
	//}

	IBK::Path fname(m_ui->widgetTemperatureSplineFilePathDataFile->filename().toStdString());
	NANDRAD::LinearSplineParameter spl;
	spl.m_tsvFile = fname;

	try {
		spl.readTsv();
	}
	catch (IBK::Exception & ex) {
		ex.writeMsgStackToError();
		return;
	}

	//m_vectorHeatLossSplineUserXData = spl.m_values.x();
	//m_vectorHeatLossSplineUserYData = spl.m_values.y();

	bool containsNegativeValues = false;
	double maximumHeatingLoad = 0;
	double maximumCoolingLoad = 0;
	//for(double value : m_vectorHeatLossSplineUserYData){
	//	if(value < 0){
	//		containsNegativeValues = true;
	//		break;
	//	}
	//}


}

void SVNetworkComponentHeatExchangeEditWidget::initializeHeatLossSplineAreaRelatedValues()
{
	bool areaRelated = m_current->m_heatExchange.m_areaRelatedValues;
	double heatingEnergyDemand, coolingEnergyDemand, domesticHotWaterDemand = 0;
	double floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
	if(areaRelated){
		heatingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific].get_value();
		coolingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value();
		domesticHotWaterDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemandAreaSpecific].get_value();
		m_ui->labelHeatLossSplineHeatingEnergyDemandUnit->setText("kWh/m²");
		m_ui->labelHeatLossSplineCoolingEnergyDemandUnit->setText("kWh/m²");
		m_ui->labelHeatLossSplineDomesticHotWaterDemandUnit->setText("kWh/m²");
	} else {
		heatingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value();
		coolingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value();
		domesticHotWaterDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand].get_value();
		m_ui->labelHeatLossSplineHeatingEnergyDemandUnit->setText("kWh");
		m_ui->labelHeatLossSplineCoolingEnergyDemandUnit->setText("kWh");
		m_ui->labelHeatLossSplineDomesticHotWaterDemandUnit->setText("kWh");
	}

	if(heatingEnergyDemand == 0) {
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->clear();
	} else {
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(heatingEnergyDemand);
	}

	if(coolingEnergyDemand == 0) {
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->clear();
	} else {
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(coolingEnergyDemand);
	}

	if(domesticHotWaterDemand == 0){
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->clear();
	} else {
		m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setValue(domesticHotWaterDemand);
	}


	if(floorArea == 0) {
		m_ui->lineEditHeatLossSplineFloorArea->clear();
	} else {
		m_ui->lineEditHeatLossSplineFloorArea->setValue(floorArea);
	}
}

double SVNetworkComponentHeatExchangeEditWidget::calculateEnergyDemand(VICUS::NetworkHeatExchange::para_t parameter)
{
	std::vector<double>& plotData = parameter == VICUS::NetworkHeatExchange::P_HeatingEnergyDemand ? m_heatLossSplineHeatingYPlotData : m_heatLossSplineCoolingYPlotData;
	double energyDemand = 0;
	for(unsigned int i = 0; i < plotData.size(); i++){
		energyDemand += plotData[i];
	}
	return energyDemand;
}

double SVNetworkComponentHeatExchangeEditWidget::calculateEnergyDemand(const std::vector<double> & vectorWithValues)
{
	double energyDemand = 0;
	for(unsigned int i = 0; i < vectorWithValues.size(); i++){
		energyDemand += vectorWithValues[i];
	}
	return energyDemand;
}

void SVNetworkComponentHeatExchangeEditWidget::calculateNewHeatLossSplineYData(double k, std::vector<double> & vectorToSaveNewValues, VICUS::NetworkHeatExchange::para_t parameter)
{
	double maxValueUser = m_current->m_heatExchange.m_para[parameter].value;
	double maxValue;
	if( parameter == VICUS::NetworkHeatExchange::P_MaximumHeatingLoad)
		maxValue = m_vectorHeatLossSplineHeatingMaxValues[m_current->m_heatExchange.m_buildingType];
	else
		maxValue = m_vectorHeatLossSplineCoolingMaxValues[m_current->m_heatExchange.m_buildingType];

	if (maxValueUser == 0.0) maxValueUser = maxValue;
	double ratio =  maxValueUser / maxValue;

	auto scaling = [k, maxValueUser, ratio](double y){
		double relativeValue = y * ratio;
		relativeValue = relativeValue / maxValueUser;
		double adjustedRelativeValue = std::pow(relativeValue,k);
		double adjustedAbsoluteValue = maxValueUser * adjustedRelativeValue;
		return adjustedAbsoluteValue;
	};

	if( parameter == VICUS::NetworkHeatExchange::P_MaximumHeatingLoad){
		std::vector<double>& valuesToBeTransformed = m_vectorHeatLossSplineHeatingYData[m_current->m_heatExchange.m_buildingType];
		vectorToSaveNewValues.resize(valuesToBeTransformed.size());
		std::transform(valuesToBeTransformed.begin(), valuesToBeTransformed.end(), vectorToSaveNewValues.begin(), scaling );
	} else {
		std::vector<double>& valuesToBeTransformed = m_vectorHeatLossSplineCoolingYData[m_current->m_heatExchange.m_buildingType];
		vectorToSaveNewValues.resize(valuesToBeTransformed.size());
		std::transform(valuesToBeTransformed.begin(), valuesToBeTransformed.end(), vectorToSaveNewValues.begin(), scaling );
	}
}

void SVNetworkComponentHeatExchangeEditWidget::calculateNewHeatLossSplineHotWaterYData(double floorArea)
{
	Q_ASSERT(m_heatLossSplineHwUserProfile != NUM_HW);
	m_heatLossSplineHotWaterYPlotData = m_mapHeatLossSplineHotWaterYData[m_heatLossSplineHwUserProfile];
	return;
}

bool SVNetworkComponentHeatExchangeEditWidget::calculateNewK(double energyDemandToReach, VICUS::NetworkHeatExchange::para_t parameter)
{
	/* check if demanded energyDemandToReach is 2500* bigger than maximumEnergyLoad. If yes,
	 * set energyDemandToReach to maximum allowed energy demand, calculate new k and return false */
	double maximumEnergyLoad = parameter == VICUS::NetworkHeatExchange::P_MaximumHeatingLoad ? m_current->m_heatExchange.m_para[parameter].get_value()
																							 : m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].get_value();

	if((energyDemandToReach / maximumEnergyLoad) > 2501) {
		energyDemandToReach = maximumEnergyLoad * 2500;
		calculateNewK(energyDemandToReach, parameter);
		return false;
	}

	double lowerBound = 0;
	double upperBound = 1024;
	double currentK = 1;
	int maximumLoopDepth = 50;

	IBK::NearEqual<double> nearEqual(0.5);

	qDebug() << "calculateNewK Goal: " << energyDemandToReach;
	std::vector<double> newlyCalculatedYPlotValues;
	double newlyCalculatedIntegral;
	for(int i = 0 ; i < maximumLoopDepth; i++){
		calculateNewHeatLossSplineYData(currentK, newlyCalculatedYPlotValues, parameter);
		newlyCalculatedIntegral = calculateEnergyDemand(newlyCalculatedYPlotValues);
		newlyCalculatedIntegral /= 1000;
		if(nearEqual(energyDemandToReach, newlyCalculatedIntegral)){
			if(parameter == VICUS::NetworkHeatExchange::P_MaximumHeatingLoad) {
				m_kHeating = currentK;
				m_heatLossSplineHeatingYPlotData = newlyCalculatedYPlotValues;
				m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(newlyCalculatedIntegral);
			}
			else {
				m_kCooling = currentK;
				m_heatLossSplineCoolingYPlotData = newlyCalculatedYPlotValues;
				m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(newlyCalculatedIntegral);
			}
			qDebug() << "Success: new k: " << currentK << " New Integral: " << newlyCalculatedIntegral;
			return true;
		}
		else if(newlyCalculatedIntegral < energyDemandToReach){
			double difference = currentK - lowerBound;
			upperBound = currentK;
			currentK -= difference / 2;
		} else {
			double difference = upperBound - currentK;
			lowerBound = currentK;
			currentK += difference / 2;
		}
	}

	qDebug() << "Unsuccessful k calculation";
	qDebug() << "calculated integral set in lineEdit";
	/* if energyDemandToReach was not reachable, set the last reached energyDemand in the lineEdit and return false */
	if(parameter == VICUS::NetworkHeatExchange::P_MaximumHeatingLoad) {
		m_kHeating = currentK;
		m_heatLossSplineHeatingYPlotData = newlyCalculatedYPlotValues;
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(newlyCalculatedIntegral);
	}
	else {
		m_kCooling = currentK;
		m_heatLossSplineCoolingYPlotData = newlyCalculatedYPlotValues;
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(newlyCalculatedIntegral);
	}
	return false;
}

void SVNetworkComponentHeatExchangeEditWidget::setCoolingCurve(bool set)
{
	if(m_heatLossSplineCoolingCurve == nullptr){
		m_heatLossSplineCoolingCurve = new QwtPlotCurve("Cooling");
		m_heatLossSplineCoolingCurve->setPen(Qt::blue);
	}

	if(set){
		std::vector<double> coolingValuesToPlot;
		for(double value : m_heatLossSplineCoolingYPlotData)
			coolingValuesToPlot.push_back(value / 1000); // convert to kW
		m_heatLossSplineCoolingCurve->setSamples(m_heatLossSplineXData.data(), coolingValuesToPlot.data(), m_heatLossSplineXData.size());
		m_heatLossSplineCoolingCurve->attach(m_ui->widgetPlotHeatLossSpline);
	} else {
		m_heatLossSplineCoolingCurve->detach();
	}
	m_ui->widgetPlotHeatLossSpline->replot();
}

void SVNetworkComponentHeatExchangeEditWidget::setHotWaterCurve(bool set)
{
	if(m_heatLossSplineHotWaterCurve == nullptr){
		m_heatLossSplineCoolingCurve = new QwtPlotCurve("Hot Water");
		m_heatLossSplineCoolingCurve->setPen(Qt::magenta);
	}

	if(set){
		std::vector<double> hotWaterValuesToPlot;
		for(double value : m_heatLossSplineHotWaterYPlotData)
			hotWaterValuesToPlot.push_back(value / 1000); // convert to kW
		m_heatLossSplineHotWaterCurve->setSamples(m_heatLossSplineXData.data(), hotWaterValuesToPlot.data(), m_heatLossSplineXData.size());
	} else {
		m_heatLossSplineHotWaterCurve->detach();
	}
}

void SVNetworkComponentHeatExchangeEditWidget::on_comboBoxTemperatureSpline_activated(int index)
{
	m_current->m_heatExchange.m_ambientTemperatureType = static_cast<VICUS::NetworkHeatExchange::AmbientTemperatureType>(index);
	bool isUserDefined = m_current->m_heatExchange.m_ambientTemperatureType == VICUS::NetworkHeatExchange::AT_UserDefined;
	m_ui->listWidgetTemperatureSplineSelectColumn->setVisible(isUserDefined);
	m_ui->labelTemperatureSplineHeatFilePath->setVisible(isUserDefined);
	m_ui->labelTemperatureSplineSelectColumn->setVisible(isUserDefined);
	m_ui->listWidgetTemperatureSplineSelectColumn->setVisible(isUserDefined);
	m_ui->widgetTemperatureSplineFilePathDataFile->setVisible(isUserDefined);

	if(!isUserDefined){
		m_current->m_heatExchange.m_userDefinedTsvFile.clear();
		QString directory;
		switch(m_current->m_heatExchange.m_ambientTemperatureType){
			case VICUS::NetworkHeatExchange::AT_BoreholeHeatExchangerTemperature:
				directory = QString("/demandProfiles/BoreholeHeatExchange.tsv");
				break;
			case VICUS::NetworkHeatExchange::AT_UndisturbedSoilTemperature:
				directory  = QString("/demandProfiles/SoilTemperature.tsv");
				break;
			default:
				directory = QString("/demandProfiles/BoreholeHeatExchange.tsv"); // compiler happy
		}
		directory = QtExt::Directories::resourcesRootDir().append(directory);
		IBK::Path ibkDirectory(directory.toStdString());
		IBK::CSVReader reader;

		qDebug() << "TemperatureTSV directory" << directory;

		try {
			reader.read(ibkDirectory);
		}
		catch (...) {
			qDebug() << "Could not load TemperatureSplineTSV successfully";
		}

		m_temperatureSplineXPlotData = reader.colData(0);
		m_temperatureSplineYPlotData = reader.colData(1);
		updateTemperatureSplinePlotData();
	} else {
		if(!m_current->m_heatExchange.m_userDefinedTsvFile.isValid()){
			m_ui->widgetTemperatureSplineFilePathDataFile->setFilename("");
			m_temperatureSplineCurve->detach();
			m_ui->widgetPlotTemperatureSpline->setEnabled(false);
		} else {
			m_ui->widgetTemperatureSplineFilePathDataFile->setFilename(QString::fromStdString(m_current->m_heatExchange.m_userDefinedTsvFile.str()));
		}

		updateTemperatureSplineSelectColumnList();
	}
}

void SVNetworkComponentHeatExchangeEditWidget::on_toolButtonSetDefaultValues_clicked()
{
	bool userDefinedValues = m_current->m_heatExchange.m_modelType == VICUS::NetworkHeatExchange::BT_UserDefineBuilding;
	if(!userDefinedValues){
		m_current->m_heatExchange.setDefaultValues(m_current->m_heatExchange.m_modelType);
		m_current->m_heatExchange.m_withCoolingDemand = true;
		m_current->m_heatExchange.m_areaRelatedValues = false;
		m_ui->lineEditHeatLossSplineFloorArea->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value());
		on_comboBoxHeatLossSplineUserBuildingType_activated((int)m_current->m_heatExchange.m_buildingType);
	}
}


void SVNetworkComponentHeatExchangeEditWidget::on_groupBoxDomesticHotWaterDemand_clicked(bool checked)
{

	qDebug() << "Domestic Hot Water Demand clicked. ";
	m_current->m_heatExchange.m_withDomesticHotWaterDemand = checked;
}
