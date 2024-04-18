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
	Q_ASSERT(VICUS::NetworkHeatExchange::NUM_T == 9);

	configureChart(m_ui->widgetPlotHeatLossSpline);

	//sets up validating line edit appropriately
	m_ui->lineEditTemperatureConstantHeatTransferCoefficient->setMinimum(0, false);
	m_ui->lineEditTemperatureSplineHeatTransferCoefficient->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineFloorArea->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineFloorArea->setMinimum(0, false);
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setFormat('f', 0);

	// set comboBox in pageHeatLossSpline
	for(int i = 0; i < VICUS::NetworkHeatExchange::NUM_BT; i++){
		m_ui->comboBoxHeatLossSplineUserBuildingType->addItem(VICUS::KeywordListQt::Description("NetworkHeatExchange::BuildingType", i));
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
			m_ui->comboBoxHeatExchange->setCurrentIndex(index);
			on_comboBoxHeatExchange_activated(index);
			return;
		}
	}
	m_ui->comboBoxHeatExchange->setCurrentIndex(m_ui->comboBoxHeatExchange->count()-1);
	on_comboBoxHeatExchange_activated(m_ui->comboBoxHeatExchange->count()-1);
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageHeatLossConstant()
{
	m_ui->checkBoxHeatLossConstantIndividual->setChecked(m_current->m_heatExchange.m_individualHeatFlux);
	on_checkBoxHeatLossConstantIndividual_stateChanged(static_cast<int>(m_current->m_heatExchange.m_individualHeatFlux));
}

void SVNetworkComponentHeatExchangeEditWidget::updatePageHeatLossSpline()
{
	m_vectorTempHeatExchangeBuildingType.clear();
	m_ui->filepathDataFile->setFilename("");

	for(int i = 0; i < VICUS::NetworkHeatExchange::NUM_BT; i++){
		VICUS::NetworkHeatExchange::BuildingType buildingType = static_cast<VICUS::NetworkHeatExchange::BuildingType>(i);
		VICUS::NetworkHeatExchange newHeatExchange;
		newHeatExchange.m_buildingType = buildingType;
		newHeatExchange.setDefaultValues(VICUS::NetworkHeatExchange::T_HeatLossSpline);
		m_vectorTempHeatExchangeBuildingType.push_back(newHeatExchange);
	}

	if(m_heatLossSplineXData.size() == 0) handleTsv();

	// set widgets in pageHeatLossSpline to appropriate values
	m_ui->checkBoxHeatLossSplineIndividual->setChecked(m_current->m_heatExchange.m_individualHeatFlux);
	on_checkBoxHeatLossSplineIndividual_clicked(m_current->m_heatExchange.m_individualHeatFlux);
}

void SVNetworkComponentHeatExchangeEditWidget::updatePageTemperatureConstant()
{
	m_ui->lineEditTemperatureConstantHeatTransferCoefficient->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient].get_value());
	m_ui->lineEditTemperatureConstantTemperature->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_Temperature].get_value());
}

void SVNetworkComponentHeatExchangeEditWidget::on_comboBoxHeatExchange_activated(int index)
{
	//store old heatExchange
	for(VICUS::NetworkHeatExchange& heatExchange : m_vectorTempHeatExchange){
		if(heatExchange.m_modelType == m_current->m_heatExchange.m_modelType){
			heatExchange = m_current->m_heatExchange;
		}
	}

	//take newly selected Heat Exchanger from vector
	m_current->m_heatExchange = m_vectorTempHeatExchange[index];

	// change stackedWidget to the appropriate page
	m_ui->stackedWidgetHeatExchange->setCurrentIndex(static_cast<int>(m_current->m_heatExchange.m_modelType));

	switch(m_current->m_heatExchange.m_modelType){
		case VICUS::NetworkHeatExchange::T_TemperatureConstant:
			updatePageTemperatureConstant();
			break;
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

}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossConstantIndividual_stateChanged(int arg1)
{
	bool checked = static_cast<bool>(arg1);
	m_current->m_heatExchange.m_individualHeatFlux = checked;
	m_ui->labelHeatLossConstantUserHeatFlux->setEnabled(checked);
	m_ui->labelHeatLossConstantUserUnit->setEnabled(checked);
	m_ui->lineEditHeatLossConstantUser->setEnabled(checked);
	m_ui->lineEditHeatLossConstantUser->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatLoss].get_value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossConstantUser_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatLoss, m_ui->lineEditHeatLossConstantUser->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditTemperatureConstantHeatTransferCoefficient_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient, m_ui->lineEditTemperatureConstantHeatTransferCoefficient->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditTemperatureConstantTemperature_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_Temperature, m_ui->lineEditTemperatureConstantTemperature->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossSplineIndividual_clicked(bool checked)
{
	m_current->m_heatExchange.m_individualHeatFlux = checked;
	// if checked, disable everything
	if(m_current->m_heatExchange.m_individualHeatFlux){
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
	if(index >= VICUS::NetworkHeatExchange::NUM_BT) index = 0;
	m_ui->comboBoxHeatLossSplineUserBuildingType->setCurrentIndex(index);

	// store old heatExchange
	for(unsigned int i = 0; i < m_vectorTempHeatExchangeBuildingType.size(); i++) {
		if(m_vectorTempHeatExchangeBuildingType[i].m_buildingType == m_current->m_heatExchange.m_buildingType) {
			m_vectorTempHeatExchangeBuildingType[i] = m_current->m_heatExchange;
		}
	}

	// get new heatExchange from vector
	m_current->m_heatExchange = m_vectorTempHeatExchangeBuildingType[index];

	if(m_current->m_heatExchange.m_buildingType != VICUS::NetworkHeatExchange::BT_UserDefineBuilding){
		m_ui->stackedWidgetHeatLossSpline->setCurrentIndex(0);
		m_ui->checkBoxHeatLossSplineAreaRelatedValues->setChecked(static_cast<int>(m_current->m_heatExchange.m_areaRelatedValues));
		m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].get_value());
		m_ui->groupBoxHeatLossSplineCooling->setChecked(m_current->m_heatExchange.m_withCoolingDemand);
		m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setValue(m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].get_value());
		initializeHeatLossSplineAreaRelatedValues();

		// enable or disable floorArea related widgets depending if areaRelatedValues is set in heatExchange
		m_ui->labelHeatLossSplineFloorArea->setEnabled(m_current->m_heatExchange.m_areaRelatedValues);
		m_ui->labelHeatLossSplineFloorAreaUnit->setEnabled(m_current->m_heatExchange.m_areaRelatedValues);
		m_ui->lineEditHeatLossSplineFloorArea->setEnabled(m_current->m_heatExchange.m_areaRelatedValues);

		updatePlotDataPredef();
	} else {
		m_ui->stackedWidgetHeatLossSpline->setCurrentIndex(1);
		m_ui->filepathDataFile->setFilename(QString::fromStdString(m_current->m_heatExchange.m_userDefinedTsvFile.str()));
		on_filepathDataFile_editingFinished();
	}
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineFloorArea_editingFinishedSuccessfully()
{
	// get newly set FloorArea and calculate what energyDemand results from that
	double newFloorArea = m_ui->lineEditHeatLossSplineFloorArea->value();
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
		m_heatLossSplineCoolingCurve->setSamples(m_heatLossSplineXData.data(), m_heatLossSplineCoolingYPlotData.data(), m_heatLossSplineXData.size());
	}

	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(oldEnergyDemandHeating);
	m_ui->lineEditHeatLossSplineFloorArea->setValue(newFloorArea);
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_FloorArea, newFloorArea);
	m_heatLossSplineHeatingCurve->setSamples(m_heatLossSplineXData.data(), m_heatLossSplineHeatingYPlotData.data(), m_heatLossSplineXData.size());
	m_heatLossSplineHeatingCurve->plot()->replot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineMaximumHeatingLoad_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumHeatingLoad, m_ui->lineEditHeatLossSplineMaximumHeatingLoad->value());
	calculateNewHeatLossSplineYData(m_kHeating, m_heatLossSplineHeatingYPlotData);
	double maximumHeatingLoad, maximumCoolingLoad;
	maximumHeatingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;
	maximumCoolingLoad = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value;
	m_heatLossSplineHeatingCurve->setSamples(m_heatLossSplineXData.data(), m_heatLossSplineHeatingYPlotData.data(), m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad : maximumCoolingLoad);
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
	if(areaRelatedValues){
		if(m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value() == m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific].get_value()) return;
	} else {
		if(m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value() == m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value()) return;
	}

	double previousHeatingDemand;
	if(areaRelatedValues){
		previousHeatingDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific].get_value();
	} else {
		previousHeatingDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value();
	}

	double floorArea = 1;
	if(areaRelatedValues) {
		floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
	}

	double newHeatingEnergyDemand = m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value() * floorArea;

	if(calculateNewK(newHeatingEnergyDemand)){
		if(areaRelatedValues){
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific, newHeatingEnergyDemand / floorArea);
			m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(newHeatingEnergyDemand / floorArea);
		} else {
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, newHeatingEnergyDemand);
		}
	} else {
		// calculate if the requested energyDemand is too big or too small, then present the calculated energyDemand to the user and ask him if he accepts the new value
		double newIntegralCalculated = m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value() / floorArea;


		HeatLossSplineEnergyDemandDialog heatLossSplineEnergyDemandDialog(this, previousHeatingDemand, newIntegralCalculated, true, true);

		//heatLossSplineEnergyDemandDialog.exec();
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(newIntegralCalculated);
		if(areaRelatedValues){
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific, newIntegralCalculated);
		} else {
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, newIntegralCalculated);
		}
	}
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->clearFocus();
	m_heatLossSplineHeatingCurve->setSamples(m_heatLossSplineXData.data(), m_heatLossSplineHeatingYPlotData.data(), m_heatLossSplineXData.size());
	m_heatLossSplineHeatingCurve->plot()->replot();
}

void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossSplineAreaRelatedValues_stateChanged(int arg1)
{
	bool areaRelated = m_current->m_heatExchange.m_areaRelatedValues = static_cast<bool>(arg1);

	double heatingEnergyDemand, coolingEnergyDemand, domesticHotWaterDemand, floorArea = 0;

	floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
	if(areaRelated){
		heatingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value() / floorArea;
		coolingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value() / floorArea;
		domesticHotWaterDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand].get_value() / floorArea;
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific, heatingEnergyDemand);
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific, coolingEnergyDemand);
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_DomesticHotWaterDemandAreaSpecific, domesticHotWaterDemand);
		m_ui->labelHeatLossSplineHeatingEnergyDemandUnit->setText("kWh/m²");
		m_ui->labelHeatLossSplineCoolingEnergyDemandUnit->setText("kWh/m²");
		m_ui->labelHeatLossSplineDomesticHotWaterDemandUnit->setText("kWh/m²");
		m_ui->labelHeatLossSplineFloorArea->setEnabled(true);
		m_ui->labelHeatLossSplineFloorAreaUnit->setEnabled(true);
		m_ui->lineEditHeatLossSplineFloorArea->setEnabled(true);
	} else {
		heatingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific].get_value() * floorArea;
		coolingEnergyDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value() * floorArea;
		domesticHotWaterDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemandAreaSpecific].get_value() * floorArea;
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, heatingEnergyDemand);
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand, coolingEnergyDemand);
		VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand, domesticHotWaterDemand);
		m_ui->labelHeatLossSplineHeatingEnergyDemandUnit->setText("kWh");
		m_ui->labelHeatLossSplineCoolingEnergyDemandUnit->setText("kWh");
		m_ui->labelHeatLossSplineDomesticHotWaterDemandUnit->setText("kWh");
		m_ui->labelHeatLossSplineFloorArea->setEnabled(false);
		m_ui->labelHeatLossSplineFloorAreaUnit->setEnabled(false);
		m_ui->lineEditHeatLossSplineFloorArea->setEnabled(false);
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
	if(areaRelatedValues){
		if(m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() == m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value()) return;
	} else {
		if(m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() == m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value()) return;
	}

	double previousCoolingDemand;
	if(areaRelatedValues){
		previousCoolingDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific].get_value();
	} else {
		previousCoolingDemand = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value();
	}

	double floorArea = 1;
	if(areaRelatedValues) {
		floorArea = m_current->m_heatExchange.m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value();
	}

	double newCoolingEnergyDemand = m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() * floorArea;

	if(calculateNewK(newCoolingEnergyDemand, VICUS::NetworkHeatExchange::P_MaximumCoolingLoad)){
		if(areaRelatedValues){
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific, newCoolingEnergyDemand / floorArea);
			m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(newCoolingEnergyDemand / floorArea);
		} else {
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand, newCoolingEnergyDemand);
		}
	} else {
		double newIntegralCalculated = m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() / floorArea;
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(newIntegralCalculated);
		if(areaRelatedValues){
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific, newIntegralCalculated);
		} else {
			VICUS::KeywordList::setParameter(m_current->m_heatExchange.m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand, newIntegralCalculated);
		}
	}
	m_ui->lineEditHeatLossSplineCoolingEnergyDemand->clearFocus();
	m_heatLossSplineCoolingCurve->setSamples(m_heatLossSplineXData.data(), m_heatLossSplineCoolingYPlotData.data(), m_heatLossSplineXData.size());
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
	m_heatLossSplineCoolingCurve->setSamples(m_heatLossSplineXData.data(), m_heatLossSplineCoolingYPlotData.data(), m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad : maximumCoolingLoad);
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


SVNetworkComponentHeatExchangeEditWidget::HeatLossSplineEnergyDemandDialog::HeatLossSplineEnergyDemandDialog(QWidget * parent, double previousEnergyDemand, double calculatedEnergyDemand, bool requestTooBig, bool heatingDemand) : QDialog(parent)
{
	setWindowTitle("Choose how to adjust the graph");

	QString typeOfEnergyDemand;
	if(heatingDemand)
		typeOfEnergyDemand = QString("HeatingEnergyDemand");
	else
		typeOfEnergyDemand = QString("CoolingEnergyDemand");

	QString reqTooBig;
	QString maximum;
	if(requestTooBig){
		reqTooBig = QString("big");
		maximum = QString("maximum");
	}
	else {
		reqTooBig = QString("small");
		maximum = QString("minimum");
	}

	QString errorMessage = QString("The requested %1 is too %2. The previous %1 is %4, the %5 reachable %1 is %7")
							   .arg(typeOfEnergyDemand).arg(reqTooBig).arg(previousEnergyDemand).arg(maximum).arg(calculatedEnergyDemand);
//qmessagebox question
	QVBoxLayout *layout1 = new QVBoxLayout(this);
	QWidget widgetToHoldHLayout(this);
	QHBoxLayout *layout2 = new QHBoxLayout(&widgetToHoldHLayout);
	QLabel *label = new QLabel(errorMessage);

	QPushButton *button1 = new QPushButton("Take New Value", this);
	QPushButton *button2 = new QPushButton("Leave previous Value", this);

	layout2->addWidget(button1);
	layout2->addWidget(button2);

	layout1->addWidget(label);
	layout1->addWidget(&widgetToHoldHLayout);

	connect(button1, &QPushButton::clicked, this, [this]() { this->done(1); });
	connect(button2, &QPushButton::clicked, this, [this]() { this->done(2); });
}

void SVNetworkComponentHeatExchangeEditWidget::on_lineEditTemperatureSplineHeatTransferCoefficient_editingFinishedSuccessfully()
{

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

void SVNetworkComponentHeatExchangeEditWidget::on_listWidgetHeatLossSplineSelectColumn_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (current == nullptr)
		return; // do nothing

	// get column index
	int currentListItem = current->data(Qt::UserRole).toInt();
	if (currentListItem < 0) {
		// invalid unit in data column, cannot use this column
		return;
	}
	QString unitName = current->data(Qt::UserRole+1).toString();

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

	updatePlotDataUser();
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
		QModelIndex currentIndex = m_ui->listWidgetHeatLossSplineSelectColumn->currentIndex();
		auto item = m_ui->listWidgetHeatLossSplineSelectColumn->item(selectedColumn);
		m_ui->listWidgetHeatLossSplineSelectColumn->setCurrentItem(item);
	}


	m_ui->widgetHeatLossSplineSelectColumn->setEnabled(true);
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


void SVNetworkComponentHeatExchangeEditWidget::handleTsv()
{
	qDebug() << "Loading TSV";
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
			qDebug() << "Reading " << directories[i];
			reader.read(ibkDirectory);
		}
		catch (...) {
			qDebug() << "Could not load TSV successfully";
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

void SVNetworkComponentHeatExchangeEditWidget::updatePlotDataPredef()
{
	for(int i = 0; i < m_vectorHeatLossSplineHeatingYData.size(); i++){
		double maxValue = *(std::max_element(m_vectorHeatLossSplineHeatingYData[i].begin(), m_vectorHeatLossSplineHeatingYData[i].end()));
		m_vectorHeatLossSplineHeatingMaxValues.push_back(maxValue);
	}

	for(int i = 0; i < m_vectorHeatLossSplineCoolingYData.size(); i++){
		double maxValue = *(std::max_element(m_vectorHeatLossSplineCoolingYData[i].begin(), m_vectorHeatLossSplineCoolingYData[i].end()));
		m_vectorHeatLossSplineHeatingMaxValues.push_back(maxValue);
	}


	VICUS::NetworkHeatExchange::para_t parameterHeating, parameterCooling;
	double floorArea = 1;
	parameterHeating = m_current->m_heatExchange.m_areaRelatedValues ? VICUS::NetworkHeatExchange::P_HeatingEnergyDemandAreaSpecific
																	 : VICUS::NetworkHeatExchange::P_HeatingEnergyDemand;
	parameterCooling = m_current->m_heatExchange.m_areaRelatedValues ? VICUS::NetworkHeatExchange::P_CoolingEnergyDemandAreaSpecific
																	 : VICUS::NetworkHeatExchange::P_CoolingEnergyDemand;

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
	m_ui->widgetPlotHeatLossSpline->setAxisTitle(QwtPlot::yLeft, "[W]");
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad : maximumCoolingLoad);

	//creating curve for heating
	if(m_heatLossSplineHeatingCurve == nullptr) {
		m_heatLossSplineHeatingCurve = new QwtPlotCurve("Heating");
		m_heatLossSplineHeatingCurve->setPen(Qt::red);
	}
	m_heatLossSplineHeatingCurve->setSamples(m_heatLossSplineXData.data(), m_heatLossSplineHeatingYPlotData.data(), m_heatLossSplineXData.size());
	m_heatLossSplineHeatingCurve->attach(m_ui->widgetPlotHeatLossSpline);

	//creating curve for cooling
	setCoolingCurve(m_current->m_heatExchange.m_withCoolingDemand);

	if(m_heatLossSplineZoomer == nullptr) m_heatLossSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotHeatLossSpline->canvas() );
	m_heatLossSplineZoomer->setZoomBase();

}

void SVNetworkComponentHeatExchangeEditWidget::updatePlotDataUser()
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
		for(int i = 0; i < m_vectorHeatLossSplineUserXData.size(); i++){
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
		m_heatLossSplineCoolingCurve->setSamples(m_vectorHeatLossSplineUserXData.data(), vectorContainingCoolingValues.data(), m_vectorHeatLossSplineUserXData.size());
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
	m_heatLossSplineHeatingCurve->setSamples(m_vectorHeatLossSplineUserXData.data(), m_vectorHeatLossSplineUserYData.data(), m_heatLossSplineXData.size());
	m_heatLossSplineHeatingCurve->attach(m_ui->widgetPlotHeatLossSpline);
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, m_heatLossSplineXData.size());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad : maximumCoolingLoad);
	m_ui->widgetPlotHeatLossSpline->replot();

	if(m_heatLossSplineZoomer == nullptr) m_heatLossSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotHeatLossSpline->canvas() );
	m_heatLossSplineZoomer->setZoomBase();

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

	m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setValue(domesticHotWaterDemand);

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

	IBK::NearEqual<double> nearEqual(1);

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
		m_heatLossSplineCoolingCurve->setSamples(m_heatLossSplineXData.data(), m_heatLossSplineCoolingYPlotData.data(), m_heatLossSplineXData.size());
		m_heatLossSplineCoolingCurve->attach(m_ui->widgetPlotHeatLossSpline);
	} else {
		m_heatLossSplineCoolingCurve->detach();
	}
	m_ui->widgetPlotHeatLossSpline->replot();
}
