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
	Q_ASSERT(VICUS::NetworkHeatExchange::NUM_T == 11);

	configureChart(m_ui->widgetPlotHeatLossSpline);

	//sets up validating line edit appropriately
	m_ui->lineEditTemperatureConstantHeatTransferCoefficient->setMinimum(0, false);
	m_ui->lineEditTemperatureSplineHeatTransferCoefficient->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineFloorArea->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineFloorArea->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineDomesticHotWaterShare->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineDomesticHotWaterShare->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineDHWSupplyTemperature->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineDHWSupplyTemperature->setMinimum(15, false);

	m_ui->lineEditHeatLossSplineHeatingSupplyTemperature->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineHeatingSupplyTemperature->setMinimum(15, false);

	// set comboBox in pageHeatLossSpline
	for(int i = 0; i < VICUS::NetworkHeatExchange::NUM_BT; i++){
		m_ui->comboBoxHeatLossSplineBuildingType->addItem(VICUS::KeywordListQt::Description("NetworkHeatExchange::BuildingType", i));
	}

	// set comboBox in pageTemperatureSpline
	for(int i = 0; i < VICUS::NetworkHeatExchange::NUM_AT; i++){
		m_ui->comboBoxTemperatureSpline->addItem(VICUS::KeywordListQt::Description("NetworkHeatExchange::AmbientTemperatureType", i));
	}

	m_ui->filepathDataFile->setup("", true, true, tr("Time-series data files (*.tsv *.csv);;All files (*.*)"),
								  SVSettings::instance().m_dontUseNativeDialogs);

	// *** Init plots

	// axis labels
	QFont ft;
	ft.setPointSize(10);
	QwtText xl(tr("Time [h]"));
	xl.setFont(ft);
	QwtText yl(tr("Heat flux [kW]"));
	yl.setFont(ft);
	m_ui->widgetPlotHeatLossSpline->setAxisTitle(QwtPlot::xBottom, xl);
	m_ui->widgetPlotHeatLossSpline->setAxisTitle(QwtPlot::yLeft, yl);

	yl = tr("Temperature [C]");
	m_ui->widgetPlotTemperatureSpline->setAxisTitle(QwtPlot::xBottom, xl);
	m_ui->widgetPlotTemperatureSpline->setAxisTitle(QwtPlot::yLeft, yl);

	//creating curve for heating / cooling
	m_heatLossSplineHeatingCurve = new QwtPlotCurve(tr("Heating"));
	m_heatLossSplineHeatingCurve->setPen(QColor("#d90429"));
	m_heatLossSplineCoolingCurve = new QwtPlotCurve(tr("Cooling"));
	m_heatLossSplineCoolingCurve->setPen(QColor("#1e6091"));
	m_heatLossSplineDHWCurve = new QwtPlotCurve(tr("DHW"));
	m_heatLossSplineDHWCurve->setPen(QColor("#653780"));
	m_temperatureSplineCurve = new QwtPlotCurve();
	m_temperatureSplineCurve->setPen(QColor("#d90429"));

	if (m_heatLossSplineZoomer == nullptr)
		m_heatLossSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotHeatLossSpline->canvas() );
	m_heatLossSplineZoomer->setZoomBase();

	if(m_temperatureSplineZoomer == nullptr)
		m_temperatureSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotTemperatureSpline->canvas() );
	m_temperatureSplineZoomer->setZoomBase();

	m_ui->radioButtonShowYear->setChecked(true);
}


SVNetworkComponentHeatExchangeEditWidget::~SVNetworkComponentHeatExchangeEditWidget()
{
	delete m_ui;
}


void SVNetworkComponentHeatExchangeEditWidget::updateInput(VICUS::NetworkComponent *component)
{
	FUNCID(SVNetworkComponentHeatExchangeEditWidget::updateInput);
	m_hx = &component->m_heatExchange;

	// before reading tsv files etc, disable everything
	this->setEnabled(false);

	// look up all available HeatExchange Modeltypes for this component
	std::vector<VICUS::NetworkHeatExchange::ModelType> availableHeatExchangeModelTypes = VICUS::NetworkComponent::availableHeatExchangeTypes(component->m_modelType);

	// if the only available hx Modeltype is NUM_T (adiabatic), return
	Q_ASSERT(availableHeatExchangeModelTypes.size() > 0);
	if (availableHeatExchangeModelTypes.size() == 1 && availableHeatExchangeModelTypes[0] == VICUS::NetworkHeatExchange::NUM_T){
		return;
	}
	else {
		if (!m_hasBeenInitialized) {
			// we store the default values for all building types, including splines from tsv here, these will be read only once
			for (unsigned int i = 0; i < VICUS::NetworkHeatExchange::NUM_BT; i++){
				m_vectorTempHeatExchangeBuildingType[i] = VICUS::NetworkHeatExchange();
				VICUS::NetworkHeatExchange::BuildingType buildingType = VICUS::NetworkHeatExchange::BuildingType(i);
				VICUS::NetworkHeatExchange newHeatExchange;
				newHeatExchange.m_buildingType = buildingType;
				newHeatExchange.setDefaultValues(VICUS::NetworkHeatExchange::T_HeatLossSpline);
				try {
					newHeatExchange.readPredefinedTSVFiles();
				}  catch (IBK::Exception &ex) {
					throw IBK::Exception(ex, tr("Could not read tsv file for updating pre-defined heating demands.").toStdString(), FUNC_ID);
				}
				m_vectorTempHeatExchangeBuildingType[i] = newHeatExchange;
			}

			// also read and store predefined temperature splines
			VICUS::NetworkHeatExchange tempHX;
			tempHX.m_modelType = VICUS::NetworkHeatExchange::T_TemperatureSpline;
			for (unsigned int i=0; i<VICUS::NetworkHeatExchange::AT_UserDefined; ++i) {
				tempHX.m_ambientTemperatureType = VICUS::NetworkHeatExchange::AmbientTemperatureType(i);
				tempHX.readPredefinedTSVFiles();
				m_predefinedTemperatureSpline[i] = tempHX.m_temperatureSplineY;
			}

			// initialization only once!
			m_hasBeenInitialized = true;
		}

		// if we have a new component with missing splines from tsv, we provide them
		if (m_hx->m_heatingDemandSplineOrig.empty()) {
			m_hx->m_heatingDemandSplineOrig = m_vectorTempHeatExchangeBuildingType[m_hx->m_buildingType].m_heatingDemandSplineOrig;
			m_hx->m_coolingDemandSplineOrig = m_vectorTempHeatExchangeBuildingType[m_hx->m_buildingType].m_coolingDemandSplineOrig;
		}
	}

	this->setEnabled(true);

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
			if (heatExchangeMT == VICUS::NetworkHeatExchange::T_HeatLossSpline ||
				heatExchangeMT == VICUS::NetworkHeatExchange::T_HeatLossSplineCondenser) {
				/* sets default values for all buildingType HeatExchangers */
				for (VICUS::NetworkHeatExchange& heatExchangeBT : m_vectorTempHeatExchangeBuildingType){
					heatExchangeBT.m_modelType = heatExchangeMT;
					heatExchangeBT.setDefaultValues(heatExchangeMT);
				}
				newHeatExchange = m_vectorTempHeatExchangeBuildingType[newHeatExchange.m_buildingType];
				newHeatExchange.m_modelType = heatExchangeMT;
			}
			m_vectorTempHeatExchange.push_back(newHeatExchange);
		}
	}

	// set the comboBox and stackedWidget to the hx modeltype of the current component
	int idx = m_ui->comboBoxHeatExchange->findData(m_hx->m_modelType);
	if (idx < 0) // in case there was an hx modeltype set which is not available, set the first one
		idx = 0;
	m_ui->comboBoxHeatExchange->setCurrentIndex(idx);

	// this also enables / disables the remaining widget. We still continue to update everything
	m_ui->checkBoxExternallyDefined->setChecked(m_hx->m_individualHeatExchange);

	// update of relevant page
	on_comboBoxHeatExchange_activated(idx);
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageHeatLossConstant() {

	m_ui->lineEditHeatLossConstantUser->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatLoss].get_value("kW"));

	bool showTemperatureEdit = false;
	if (m_hx->m_modelType == VICUS::NetworkHeatExchange::T_HeatLossConstantCondenser) {
		m_ui->lineEditHeatLossConstantSupplyTemperature->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingSupplyTemperature].get_value("C"));
		showTemperatureEdit = true;
	}
	m_ui->labelHeatLossConstantSupplyTemperature->setVisible(showTemperatureEdit);
	m_ui->labelHeatLossConstantSupplyTemperatureUnit->setVisible(showTemperatureEdit);
	m_ui->lineEditHeatLossConstantSupplyTemperature->setVisible(showTemperatureEdit);
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageHeatLossSpline(VICUS::NetworkHeatExchange::ModelType hxModelType) {

	// hxModelType must be one of both!
	Q_ASSERT(hxModelType == VICUS::NetworkHeatExchange::T_HeatLossSpline ||
			 hxModelType == VICUS::NetworkHeatExchange::T_HeatLossSplineCondenser );

	m_ui->filepathDataFile->setFilename("");

	on_comboBoxHeatLossSplineBuildingType_activated(m_hx->m_buildingType);

	// show temperature input only for heat pump
	bool modellingHeatPump= m_hx->m_modelType == VICUS::NetworkHeatExchange::T_HeatLossSplineCondenser;
	m_ui->lineEditHeatLossSplineHeatingSupplyTemperature->setVisible(modellingHeatPump);
	m_ui->labelHeatLossSplineHeatingSupplyTemp->setVisible(modellingHeatPump);
	m_ui->labelHeatLossSplineHeatingSupplyTempUnit->setVisible(modellingHeatPump);
	m_ui->lineEditHeatLossSplineDHWSupplyTemperature->setVisible(modellingHeatPump);
	m_ui->labelHeatLossSplineDHWSupplyTemp->setVisible(modellingHeatPump);
	m_ui->labelHeatLossSplineDHWSupplyTempUnit->setVisible(modellingHeatPump);
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageTemperatureConstant() {
	m_ui->checkBoxTemperatureConstantHeatTransferCoeff->setChecked(m_hx->m_useHeatTransferCoefficient);
	on_checkBoxTemperatureConstantHeatTransferCoeff_stateChanged(m_hx->m_useHeatTransferCoefficient);
	m_ui->lineEditTemperatureConstantHeatTransferCoefficient->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient].get_value());
	m_ui->lineEditTemperatureConstantTemperature->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_Temperature].get_value());
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageTemperatureSpline() {
	m_ui->checkBoxTemperatureSplineHeatTransferCoefficient->setChecked(m_hx->m_useHeatTransferCoefficient);
	m_ui->lineEditTemperatureSplineHeatTransferCoefficient->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient].get_value());
	m_ui->widgetTemperatureSplineFilePathDataFile->setFilename("");
	m_ui->comboBoxTemperatureSpline->setCurrentIndex((int)m_hx->m_ambientTemperatureType);
	on_comboBoxTemperatureSpline_activated((int)m_hx->m_ambientTemperatureType);
}


void SVNetworkComponentHeatExchangeEditWidget::on_comboBoxHeatExchange_activated(int index)
{
	// store old heat exchange to vector
	for (VICUS::NetworkHeatExchange& heatExchange : m_vectorTempHeatExchange){
		if(heatExchange.m_modelType == m_hx->m_modelType){
			heatExchange = *m_hx;
		}
	}

	// take newly selected heat exchange from vector
	*m_hx = m_vectorTempHeatExchange[(unsigned int)index];


	// set according page and update content
	switch (m_hx->m_modelType){
		case VICUS::NetworkHeatExchange::T_TemperatureConstant:
		case VICUS::NetworkHeatExchange::T_TemperatureConstantEvaporator:
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
			updatePageHeatLossSpline(m_hx->m_modelType);
			break;
		case VICUS::NetworkHeatExchange::T_TemperatureZone:
		case VICUS::NetworkHeatExchange::T_TemperatureConstructionLayer:
		case VICUS::NetworkHeatExchange::T_HeatingDemandSpaceHeating:
		case VICUS::NetworkHeatExchange::NUM_T:
			m_ui->stackedWidgetHeatExchange->setCurrentIndex(4);
			break;
	}

	emit heatExchangeChanged(m_hx->m_modelType);
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossConstantUser_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatLoss, m_ui->lineEditHeatLossConstantUser->value()*1000);
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditTemperatureConstantTemperature_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_Temperature, m_ui->lineEditTemperatureConstantTemperature->value());
}

void SVNetworkComponentHeatExchangeEditWidget::on_lineEditTemperatureSplineHeatTransferCoefficient_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient, m_ui->lineEditTemperatureSplineHeatTransferCoefficient->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditTemperatureConstantHeatTransferCoefficient_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient, m_ui->lineEditTemperatureConstantHeatTransferCoefficient->value());
}


void SVNetworkComponentHeatExchangeEditWidget::updateHeatLossSplinePageForBuildingType()
{
	// if user defined building type, do not fill out the rest
	if (m_hx->m_buildingType == VICUS::NetworkHeatExchange::BT_UserDefineBuilding)
		return;

	m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].get_value());
	m_ui->lineEditHeatLossSplineFloorArea->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value());
	m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].get_value());

	m_ui->lineEditHeatLossSplineHeatingSupplyTemperature->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingSupplyTemperature].get_value("C"));
	m_ui->lineEditHeatLossSplineDHWSupplyTemperature->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterSupplyTemperature].get_value("C"));

	m_ui->checkBoxCooling->setChecked(m_hx->m_withCoolingDemand);
	m_ui->widgetCooling->setEnabled(m_hx->m_withCoolingDemand);

	m_ui->checkBoxDHW->setChecked(m_hx->m_withDomesticHotWaterDemand);
	m_ui->widgetDHW->setEnabled(m_hx->m_withDomesticHotWaterDemand);

	// update area related values
	updateEnergyDemandValues();
}


void SVNetworkComponentHeatExchangeEditWidget::updateEnergyDemandValues() {
	bool areaRelated = m_hx->m_areaRelatedValues;
	m_ui->checkBoxHeatLossSplineAreaRelatedValues->setChecked(areaRelated);
	m_ui->labelHeatLossSplineFloorAreaUnit->setEnabled(areaRelated);
	m_ui->lineEditHeatLossSplineFloorArea->setEnabled(areaRelated);

	double shareDHW = m_hx->m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand].get_value() /
				(m_hx->m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand].get_value() + m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value());
	m_ui->lineEditHeatLossSplineDomesticHotWaterShare->setValue(shareDHW * 100);

	if (areaRelated) {
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value() /
																	m_hx->m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value());
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value() /
																	m_hx->m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value());
		m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand].get_value() /
																	m_hx->m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value());
		m_ui->labelHeatLossSplineHeatingEnergyDemandUnit->setText("kWh/m²");
		m_ui->labelHeatLossSplineCoolingEnergyDemandUnit->setText("kWh/m²");
		m_ui->labelHeatLossSplineDomesticHotWaterDemandUnit->setText("kWh/m²");
	}
	else {
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value());
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value());
		m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand].get_value());
		m_ui->labelHeatLossSplineHeatingEnergyDemandUnit->setText("kWh");
		m_ui->labelHeatLossSplineCoolingEnergyDemandUnit->setText("kWh");
		m_ui->labelHeatLossSplineDomesticHotWaterDemandUnit->setText("kWh");
	}
}


void SVNetworkComponentHeatExchangeEditWidget::on_comboBoxHeatLossSplineBuildingType_activated(int index) {
	// if the index is NUM_BT or invalid, set to Residentialbuilding
	if (index >= VICUS::NetworkHeatExchange::NUM_BT)
		index = 0;
	m_ui->comboBoxHeatLossSplineBuildingType->setCurrentIndex(index);

	// store old heatExchange
	m_vectorTempHeatExchangeBuildingType[m_hx->m_buildingType] = *m_hx;

	// get new heatExchange from vector
	*m_hx = m_vectorTempHeatExchangeBuildingType[(unsigned int)index];

	if (m_hx->m_buildingType != VICUS::NetworkHeatExchange::BT_UserDefineBuilding){
		m_ui->stackedWidgetHeatLossSpline->setCurrentIndex(0);
		updateHeatLossSplinePageForBuildingType();
	} else {
		m_ui->stackedWidgetHeatLossSpline->setCurrentIndex(1);
		m_ui->filepathDataFile->setFilename(QString::fromStdString(m_hx->m_userDefinedTsvFile.str()));
		on_filepathDataFile_editingFinished();
	}
	if (m_hx->m_buildingType < VICUS::NetworkHeatExchange::BT_UserDefineBuilding)
		updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineFloorArea_editingFinishedSuccessfully() {

	Q_ASSERT(m_hx->m_areaRelatedValues);

	double previousFloorArea = m_hx->m_para[VICUS::NetworkHeatExchange::P_FloorArea].value;
	double newFloorArea = m_ui->lineEditHeatLossSplineFloorArea->value();

	//  *** For heating
	// check if we can find a new k with that area
	double requestedHeatingDemand, finalHeatingDemand;
	requestedHeatingDemand = m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value("Wh") / previousFloorArea * newFloorArea;
	bool successfulNewHeatingK = m_hx->calculateNewKValue(m_hx->m_heatingDemandSplineOrig, requestedHeatingDemand,
														  m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value,
															finalHeatingDemand, m_kHeating);
	// if not, calculate the closest possible area
	double fallbackFloorAreaHeating = newFloorArea;
	if (!successfulNewHeatingK) {
		double previousAreaSpecHeatingDemand =  m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value("Wh") / previousFloorArea;
		fallbackFloorAreaHeating = finalHeatingDemand / previousAreaSpecHeatingDemand;
		newFloorArea = std::ceil(fallbackFloorAreaHeating);
	}

	// *** For cooling
	// check if we can find a new k with that area
	bool successfulNewCoolingK = true;
	double fallbackFloorAreaCooling = newFloorArea;
	double finalCoolingDemand = m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].value;
	if (m_hx->m_withCoolingDemand) {
		double requestedCoolingDemand;
		requestedCoolingDemand = m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value("Wh") / previousFloorArea * newFloorArea;
		bool successfulNewCoolingK = m_hx->calculateNewKValue(m_hx->m_coolingDemandSplineOrig, requestedCoolingDemand,
															  m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value,
																finalCoolingDemand, m_kCooling);
		// if not, calculate the closest possible area
		if (!successfulNewCoolingK) {
			double previousAreaSpecCoolingDemand =  m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value("Wh") / previousFloorArea;
			fallbackFloorAreaCooling = finalCoolingDemand / previousAreaSpecCoolingDemand;
			newFloorArea = std::ceil(fallbackFloorAreaCooling);
		}
	}


	if (!successfulNewHeatingK && !successfulNewCoolingK){
		// if newFloorArea too small
		if ((fallbackFloorAreaHeating >= newFloorArea) && (fallbackFloorAreaCooling >= newFloorArea)){
			newFloorArea = fallbackFloorAreaHeating > fallbackFloorAreaCooling ? fallbackFloorAreaHeating : fallbackFloorAreaCooling;
		}
		// if newFloorArea too big
		else if ((fallbackFloorAreaHeating <= newFloorArea) && (fallbackFloorAreaCooling <= newFloorArea)){
			newFloorArea = fallbackFloorAreaHeating > fallbackFloorAreaCooling ? fallbackFloorAreaCooling : fallbackFloorAreaHeating;
		} else {
			Q_ASSERT(false); // no new floorArea can be found
		}
		newFloorArea = std::ceil(newFloorArea);
	}

	// finally set value back to line edit (might have changed) and store it
	m_ui->lineEditHeatLossSplineFloorArea->setValue(newFloorArea);
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_FloorArea, newFloorArea);
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand, finalHeatingDemand / 1000);
	if (m_hx->m_withCoolingDemand) {
		VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand, finalCoolingDemand / 1000);
	}

	// plot
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineMaximumHeatingLoad_editingFinishedSuccessfully() {
	// set new max value
	double newMaximumHeatingLoad = m_ui->lineEditHeatLossSplineMaximumHeatingLoad->value();
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumHeatingLoad,
									 newMaximumHeatingLoad);
	std::vector<double> heatingSpline;
	bool success = m_hx->generateHeatingDemandSpline(heatingSpline, m_kHeating);
	Q_ASSERT(success); //  we only scale the curve, should never give any problems

	// also calculate new energy demand value
	double newHeatingDemand = std::accumulate(heatingSpline.begin(), heatingSpline.end(), 0.0);
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand,
									   newHeatingDemand / 1000);
	// and update values
	updateEnergyDemandValues();
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::modifyEnergyDemandValue(bool heating) {

	VICUS::NetworkHeatExchange::para_t para;
	double requestedDemand, maxLoad; 	// newly requested value
	if (heating) {
		para = VICUS::NetworkHeatExchange::P_HeatingEnergyDemand;
		maxLoad = m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;
		requestedDemand = m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value() * 1000; // to Wh
	}
	else {
		para = VICUS::NetworkHeatExchange::P_CoolingEnergyDemand;
		maxLoad = m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value;
		requestedDemand = m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() * 1000; // to Wh
	}

	bool areaRelatedValues = m_hx->m_areaRelatedValues;
	double previousDemand = m_hx->m_para[para].get_value("Wh");
	if (areaRelatedValues)
		requestedDemand *= m_hx->m_para[VICUS::NetworkHeatExchange::P_FloorArea].value;
	// if not so different return
	IBK::NearEqual<double> nearEqual(0.5);
	if (nearEqual(requestedDemand, previousDemand))
		return;

	// try calculating new k
	double timeFullHours = requestedDemand / maxLoad;
	if (heating && timeFullHours > 3300) {
		double reachableDemand = 3200 * maxLoad;
		// ask user how to proceed:
		QMessageBox msgBox(this);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setWindowTitle(tr("Requested energy demand not reachable"));
		msgBox.setText(tr("The requested energy demand of %1 kWh is not reachable. The closest reachable value is %2. Take the closest value or revert to the previous value %3 kWh?")
						   .arg(requestedDemand/1000, 0, 'f', 0).arg(reachableDemand/1000, 0, 'f', 0).arg(previousDemand/1000, 0, 'f', 0));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setButtonText(QMessageBox::Yes, tr("Take closest reachable value %1").arg(reachableDemand/1000,0,'f',0));
		msgBox.setButtonText(QMessageBox::No, tr("Revert to previous value %1").arg(previousDemand/1000,0,'f',0));
		int result = msgBox.exec();
		if(result == QMessageBox::Yes)
			requestedDemand =  reachableDemand;
		else
			requestedDemand = previousDemand;
	}

	double finalDemand;
	if (heating) {
		m_hx->calculateNewKValue(m_hx->m_heatingDemandSplineOrig, requestedDemand, maxLoad,
													finalDemand, m_kHeating);
	}
	else {
		m_hx->calculateNewKValue(m_hx->m_coolingDemandSplineOrig, requestedDemand, maxLoad,
													finalDemand, m_kCooling);
	}

	// finally store value
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", para, finalDemand/1000);  // set in kWh

	updateEnergyDemandValues();
	updateHeatLossSplinePredefPlot();

	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->clearFocus();
	m_ui->lineEditHeatLossSplineCoolingEnergyDemand->clearFocus();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineHeatingEnergyDemand_editingFinishedSuccessfully() {
	modifyEnergyDemandValue(true);
}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossSplineAreaRelatedValues_stateChanged(int arg1) {
	m_hx->m_areaRelatedValues = arg1;
	updateEnergyDemandValues();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineDomesticHotWaterDemand_editingFinishedSuccessfully()
{
	double requestedDHWDemand = m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->value();
	if (m_hx->m_areaRelatedValues)
		requestedDHWDemand *= m_hx->m_para[VICUS::NetworkHeatExchange::P_FloorArea].value;

	double previousDHWDemand = m_hx->m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand].get_value("kWh");

	// generates DHW spline and store according DHW time points (which can not be used for heating/cooling anymore)
	std::vector<double> splineDHW;
	m_hx->generateDHWDemandSpline(splineDHW);
	bool allSuccessful = true;

	// now trigger again calculation of k values for heating and cooling, even demands have not changed
	// but original splines have (taking into account restricted time points for DHW)
	double heatingDemand = m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value("Wh");
	double heatingDemandResult;
	m_kHeating = -1.0;
	bool successfulNewKHeating = m_hx->calculateNewKValue(m_hx->m_heatingDemandSplineOrig, heatingDemand,
													m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value, heatingDemandResult, m_kHeating);
	// if this was not possible, set previous DHW demand and re-calculate DHW and heating curves
	if (!successfulNewKHeating) {
		QMessageBox::critical(this,"", tr("Combination of given DHW demand and heating demand is not achievable. Reset to previous values."));
		VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand,
										 previousDHWDemand);
		m_hx->generateDHWDemandSpline(splineDHW);
		m_hx->calculateNewKValue(m_hx->m_heatingDemandSplineOrig, heatingDemand,
														m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value, heatingDemandResult, m_kHeating);
		allSuccessful = false;
	}

	if (allSuccessful && m_hx->m_withCoolingDemand) {
		double coolingDemand = m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value("Wh");
		m_kCooling = -1.0;
		bool successfulNewKCooling = m_hx->calculateNewKValue(m_hx->m_coolingDemandSplineOrig, coolingDemand,
														m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value, coolingDemand, m_kCooling);
		// if this was not possible, set previous DHW demand and re-calculate DHW and heating + cooling curves
		if (!successfulNewKCooling) {
			QMessageBox::critical(this,"", tr("Combination of given DHW demand and cooling demand is not achievable. Reset to previous values."));
			VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand,
											 previousDHWDemand);
			m_hx->generateDHWDemandSpline(splineDHW);
			m_hx->calculateNewKValue(m_hx->m_heatingDemandSplineOrig, heatingDemand,
															m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value, heatingDemandResult, m_kHeating);
			double coolingDemandResult;
			m_hx->calculateNewKValue(m_hx->m_coolingDemandSplineOrig, coolingDemand,
															m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value, coolingDemandResult, m_kHeating);
			allSuccessful = false;
		}
	}

	// if all worked, we can stoe the new DHW demand
	if (allSuccessful)
		VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t",
									 VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand, requestedDHWDemand);

	updateEnergyDemandValues();
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineCoolingEnergyDemand_editingFinishedSuccessfully() {
	modifyEnergyDemandValue(false);
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineMaximumCoolingLoad_editingFinishedSuccessfully() {

	// set new max value
	double newMaximumCoolingLoad = m_ui->lineEditHeatLossSplineMaximumCoolingLoad->value();
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumCoolingLoad,
									 newMaximumCoolingLoad);
	std::vector<double> coolingSpline;
	bool success = m_hx->generateCoolingDemandSpline(coolingSpline, m_kCooling);
	Q_ASSERT(success); //  we only scale the curve, should never give any problems

	// also calculate new energy demand value
	double newCoolingDemand = std::accumulate(coolingSpline.begin(), coolingSpline.end(), 0.0);
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand,
									   newCoolingDemand / 1000);
	// and update values
	updateEnergyDemandValues();
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_filepathDataFile_editingFinished() {
	QString dataFilePath = m_ui->filepathDataFile->filename();
	if (dataFilePath.trimmed().isEmpty()) {
		m_hx->m_userDefinedTsvFile.clear();
		if(m_heatLossSplineHeatingCurve != nullptr) {
			m_heatLossSplineHeatingCurve->detach();
		}
		if(m_heatLossSplineCoolingCurve != nullptr) {
			m_heatLossSplineCoolingCurve->detach();
		}
		m_ui->widgetPlotHeatLossSpline->replot();
		return;
	}

	updateSplineSelectColumnList(VICUS::NetworkHeatExchange::T_HeatLossSpline); // if there are columns to be selected, the widget will be re-enabled here
}


void SVNetworkComponentHeatExchangeEditWidget::on_widgetTemperatureSplineFilePathDataFile_editingFinished(){
	updateSplineSelectColumnList(VICUS::NetworkHeatExchange::T_TemperatureSpline);
}


void SVNetworkComponentHeatExchangeEditWidget::on_listWidgetHeatLossSplineSelectColumn_currentItemChanged(QListWidgetItem *current,
																										  QListWidgetItem */*previous*/) {
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
	m_hx->m_userDefinedTsvFile = IBK::Path(extendedFilename.toStdString());

	updateHeatLossSplineUserPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_listWidgetTemperatureSplineSelectColumn_currentItemChanged(QListWidgetItem * current,
																											 QListWidgetItem * /*previous*/)
{

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
	m_hx->m_userDefinedTsvFile = IBK::Path(extendedFilename.toStdString());

	updateUserTemperatureSplinePlotData();
}


void SVNetworkComponentHeatExchangeEditWidget::updateSplineSelectColumnList(VICUS::NetworkHeatExchange::ModelType modelType){
	QListWidget* listWidget;
	QtExt::BrowseFilenameWidget* filePathWidget;

	switch(modelType){
		case VICUS::NetworkHeatExchange::T_TemperatureSpline:
		{
			listWidget = m_ui->listWidgetTemperatureSplineSelectColumn;
			filePathWidget = m_ui->widgetTemperatureSplineFilePathDataFile;
			break;
		}

		case VICUS::NetworkHeatExchange::T_HeatLossSpline:
		{
			listWidget = m_ui->listWidgetHeatLossSplineSelectColumn;
			filePathWidget = m_ui->filepathDataFile;
			break;
		}
		default:
			return;
	}

	// Clear list widget
	listWidget->selectionModel()->blockSignals(true);
	listWidget->clear();
	listWidget->selectionModel()->blockSignals(false);

	// Get the file path from the UI
	QString dataFilePath = filePathWidget->filename();
	if(dataFilePath.isEmpty()) {
		listWidget->clear();
		listWidget->setEnabled(false);
		return;
	}
	listWidget->setEnabled(true);

	// Check and parse the data file
	IBK::Path filePath(dataFilePath.toStdString());
	IBK::Path adjustedFileName;
	int selectedColumn = 1;
	IBK::extract_number_suffix(filePath, adjustedFileName, selectedColumn);
	std::string extension = IBK::tolower_string(adjustedFileName.extension());

	// Read only the header of the file to extract column names and units
	IBK::CSVReader reader;
	try {
		reader.read(adjustedFileName, true, true);
	}
	catch (...) {
		return;
	}

	if(selectedColumn != -1){
		auto item = listWidget->item(selectedColumn);
		listWidget->setCurrentItem(item);
	}

	// Populate the list widget with column names and units
	for (unsigned int i = 1; i < reader.m_captions.size(); ++i) {
		std::string ustr = reader.m_units[i];
		if (ustr.empty())
			ustr = "-";
		QListWidgetItem *item = new QListWidgetItem(QString("%1 [%2]").arg(
			QString::fromStdString(reader.m_captions[i]), QString::fromStdString(ustr)));

		try {
			IBK::Unit u(ustr);
			item->setData(Qt::UserRole, i);
			item->setData(Qt::UserRole+1, QString::fromStdString(ustr));
			item->setData(Qt::UserRole+2, QString::fromStdString(reader.m_captions[i]));
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		}
		catch (...) {
			item->setData(Qt::UserRole, -2);
			item->setForeground(Qt::gray);
		}
		listWidget->addItem(item);
	}
	selectedColumn = qMin(selectedColumn, (int)reader.m_captions.size() - 1);

	// Update the list widget selection and enable it
	listWidget->setCurrentRow(selectedColumn-1);
	listWidget->selectionModel()->blockSignals(false);

	// Trigger an update based on the new selection
	if(modelType == VICUS::NetworkHeatExchange::T_TemperatureSpline)
		on_listWidgetTemperatureSplineSelectColumn_currentItemChanged(listWidget->currentItem(), nullptr);
	else
		on_listWidgetHeatLossSplineSelectColumn_currentItemChanged(listWidget->currentItem(), nullptr);
}


void SVNetworkComponentHeatExchangeEditWidget::updateHeatLossSplinePredefPlot() {
	Q_ASSERT(m_hx->m_buildingType < VICUS::NetworkHeatExchange::BT_UserDefineBuilding);

	std::vector<double> splineDHWDetail;
	if (m_hx->m_withDomesticHotWaterDemand) {
		m_hx->generateDHWDemandSpline(splineDHWDetail);
	}

	// calculates new 'k' only if needed
	if (m_kHeating<0){
		double finalHeatingDemand;
		if (!m_hx->calculateNewKValue(m_hx->m_heatingDemandSplineOrig, m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value("Wh"),
									  m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value, finalHeatingDemand, m_kHeating) )
			return;
	}

	std::vector<double> heatingSpline, coolingSpline;
	m_hx->calculateHeatLossSplineFromKValue(m_kHeating, m_hx->m_heatingDemandSplineOrig, heatingSpline,
											m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value);

	if (m_hx->m_withCoolingDemand) {
		// calculates new 'k' only if needed
		if(m_kCooling<0){
			double finalCoolingDemand;
			if (!m_hx->calculateNewKValue(m_hx->m_coolingDemandSplineOrig, m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value("Wh"),
										  m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value, finalCoolingDemand, m_kCooling) )
				return;
		}
		m_hx->calculateHeatLossSplineFromKValue(m_kCooling, m_hx->m_coolingDemandSplineOrig, coolingSpline,
												m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value);
	}


	// time expected in hours
	std::vector<double> time(heatingSpline.size());
	for (unsigned int i=0; i<heatingSpline.size(); ++i)
		time[i] = i;

	double maxYValue = m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;

	//creating curve for heating
	std::vector<double> heatingValuesToPlot;
	for (double value : heatingSpline)
		heatingValuesToPlot.push_back(value / 1000); // convert to kW
	m_heatLossSplineHeatingCurve->setSamples(time.data(), heatingValuesToPlot.data(), time.size());
	m_heatLossSplineHeatingCurve->attach(m_ui->widgetPlotHeatLossSpline);

	//creating curve for cooling
	if (m_hx->m_withCoolingDemand) {
		std::vector<double> coolingValuesToPlot;
		for(double value : coolingSpline)
			coolingValuesToPlot.push_back(value / 1000); // convert to kW
		m_heatLossSplineCoolingCurve->setSamples(time.data(), coolingValuesToPlot.data(), time.size());
		m_heatLossSplineCoolingCurve->attach(m_ui->widgetPlotHeatLossSpline);
		if (m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value > maxYValue)
			maxYValue = m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value;
	} else {
		m_heatLossSplineCoolingCurve->detach();
	}

	//creating curve for DHW
	if (m_hx->m_withDomesticHotWaterDemand) {
		if (m_ui->radioButtonShowDay->isChecked()) {
			// real curve
			std::vector<double> dhwValuesToPlot;
			for(double value : splineDHWDetail)
				dhwValuesToPlot.push_back(value / 1000); // convert to kW
			m_heatLossSplineDHWCurve->setSamples(time.data(), dhwValuesToPlot.data(), time.size());
			m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 72, 72+2*24);
			double maxDHWLoad = *std::max_element(splineDHWDetail.begin(), splineDHWDetail.end());
			if (maxDHWLoad> maxYValue)
				maxYValue = maxDHWLoad;
		}
		else {
			// average curve
			double dhwHeatLoadAvg = std::accumulate(splineDHWDetail.begin(), splineDHWDetail.end(), 0) / 8760. / 1000.;
			std::vector<double> tAvg = {0, 8759};
			std::vector<double> yAvg = {dhwHeatLoadAvg, dhwHeatLoadAvg};
			m_heatLossSplineDHWCurve->setSamples(tAvg.data(), yAvg.data(), 2);
			m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, time.back());
		}
		m_heatLossSplineDHWCurve->attach(m_ui->widgetPlotHeatLossSpline);
	} else {
		m_heatLossSplineDHWCurve->detach();
		m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, time.back());
	}

	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maxYValue / 1000);
	m_ui->widgetPlotHeatLossSpline->replot();
	m_heatLossSplineZoomer->setZoomBase();
}


void SVNetworkComponentHeatExchangeEditWidget::updateHeatLossSplineUserPlot()
{
	IBK::Path fname(m_hx->m_userDefinedTsvFile);
	if (!fname.isValid()) {
		m_heatLossSplineHeatingCurve->detach();
		m_heatLossSplineCoolingCurve->detach();
		m_ui->widgetPlotHeatLossSpline->replot();
		return;
	}

	NANDRAD::LinearSplineParameter spl;
	spl.m_tsvFile = fname;
	spl.m_name = "HeatFlux";

	try {
		spl.checkAndInitialize("", IBK::Unit("h"), IBK::Unit("W"), IBK::Unit("W"), std::numeric_limits<double>::lowest(), false, std::numeric_limits<double>::max(), false, nullptr, true);
	}
	catch (IBK::Exception & ex) {
		QMessageBox::critical(this, QString(), tr("Could not read file. It might not fit tsv format.\n%1").arg(ex.what()));
		m_heatLossSplineHeatingCurve->detach();
		m_heatLossSplineCoolingCurve->detach();
		m_ui->widgetPlotHeatLossSpline->replot();
		return;
	}

	std::vector<double> heatLossSpline = spl.m_values.y();

	// time expected in hours
	std::vector<double> time(heatLossSpline.size());
	for (unsigned int i=0; i<heatLossSpline.size(); ++i)
		time[i] = i;

	bool containsNegativeValues = false;
	double maximumHeatingLoad = 0;
	double maximumCoolingLoad = 0;
	for(double value : heatLossSpline){
		if(value < 0){
			containsNegativeValues = true;
			break;
		}
	}

	// filter negative values and plot cooling curve
	std::vector<double> negativeHeatfluxes;
	if (containsNegativeValues) {
		for(unsigned int i = 0; i < time.size(); i++){
			if(heatLossSpline[i] < 0){
				negativeHeatfluxes.push_back(-heatLossSpline[i] / 1000);
				heatLossSpline[i] = 0;
				if (maximumCoolingLoad < negativeHeatfluxes.back())
					maximumCoolingLoad = negativeHeatfluxes.back();
			}
			else {
				negativeHeatfluxes.push_back(0);
			}
		}
		m_heatLossSplineCoolingCurve->setSamples(time.data(), negativeHeatfluxes.data(), time.size());
		m_heatLossSplineCoolingCurve->attach(m_ui->widgetPlotHeatLossSpline);
	}
	else {
		m_heatLossSplineCoolingCurve->detach();
	}

	// plot heating curve
	std::vector<double> heatingValuesToPlot;
	for (double value : heatLossSpline){
		heatingValuesToPlot.push_back(value / 1000); // convert to kW
		if(maximumHeatingLoad < heatingValuesToPlot.back())
			maximumHeatingLoad = heatingValuesToPlot.back();
	}

	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, time.back());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad  : maximumCoolingLoad );
	m_heatLossSplineHeatingCurve->setSamples(time.data(), heatingValuesToPlot.data(), time.size());
	m_heatLossSplineHeatingCurve->attach(m_ui->widgetPlotHeatLossSpline);
	m_ui->widgetPlotHeatLossSpline->replot();

	m_heatLossSplineZoomer->setZoomBase();
}


void SVNetworkComponentHeatExchangeEditWidget::updatePredefinedTemperatureSplinePlotData() {
	Q_ASSERT(m_hx->m_ambientTemperatureType < VICUS::NetworkHeatExchange::AT_UserDefined);

	m_ui->widgetPlotTemperatureSpline->setEnabled(true);
	double minYValue, maxYValue;

	std::vector<double> &temperatureSpline = m_predefinedTemperatureSpline[m_hx->m_ambientTemperatureType];

	minYValue = *(std::min_element(temperatureSpline.begin(), temperatureSpline.end()));
	maxYValue = *(std::max_element(temperatureSpline.begin(), temperatureSpline.end()));
	double scaleYMin = minYValue < 0 ? minYValue * 1.1 : minYValue * 0.9;
	double scaleYMax = maxYValue < 0 ? maxYValue * 0.9 : maxYValue * 1.1;

	// time expected in hours
	std::vector<double> time(temperatureSpline.size());
	for (unsigned int i=0; i<temperatureSpline.size(); ++i)
		time[i] = i;

	m_ui->widgetPlotTemperatureSpline->setAxisScale(QwtPlot::xBottom, 0, time.back());
	m_ui->widgetPlotTemperatureSpline->setAxisScale(QwtPlot::yLeft, scaleYMin, scaleYMax);

	m_temperatureSplineCurve->setSamples(time.data(), temperatureSpline.data(), temperatureSpline.size());
	m_temperatureSplineCurve->attach(m_ui->widgetPlotTemperatureSpline);

	m_ui->widgetPlotTemperatureSpline->replot();

	m_temperatureSplineZoomer->setZoomBase();
}


void SVNetworkComponentHeatExchangeEditWidget::updateUserTemperatureSplinePlotData()
{
	IBK::Path fname(m_ui->widgetTemperatureSplineFilePathDataFile->filename().toStdString());
	m_ui->widgetPlotTemperatureSpline->setEnabled(fname.isValid());
	NANDRAD::LinearSplineParameter spl;
	spl.m_tsvFile = fname;
	spl.m_name = "Temperature";

	try {
		spl.checkAndInitialize("", IBK::Unit("s"), IBK::Unit("K"), IBK::Unit("K"), std::numeric_limits<double>::lowest(), false, std::numeric_limits<double>::max(), false, nullptr);
	}
	catch (IBK::Exception & ex) {
		QMessageBox::critical(this, QString(), tr("Could not read file. It might not fit tsv format.\n%1").arg(ex.what()));
		m_temperatureSplineCurve->detach();
		m_ui->widgetPlotTemperatureSpline->replot();
		return;
	}


	std::vector<double> temperatureSpline = spl.m_values.y();
	// values converting from K to C
	for(unsigned int i = 0; i < temperatureSpline.size(); i++){
		temperatureSpline[i] -= 273.15;
	}

	std::vector<double> time(temperatureSpline.size());
	for (unsigned int i=0; i<temperatureSpline.size(); ++i)
		time[i] = i;


	// plot heating curve
	double maximumTemperature = *std::max_element(temperatureSpline.begin(), temperatureSpline.end());
	double minimumTemperature = *std::min_element(temperatureSpline.begin(), temperatureSpline.end());
	m_temperatureSplineCurve->setSamples(time.data(), temperatureSpline.data(), time.size());
	m_temperatureSplineCurve->attach(m_ui->widgetPlotTemperatureSpline);
	m_ui->widgetPlotTemperatureSpline->setAxisScale(QwtPlot::xBottom, 0, time.back());
	m_ui->widgetPlotTemperatureSpline->setAxisScale(QwtPlot::yLeft, minimumTemperature, maximumTemperature);
	m_ui->widgetPlotTemperatureSpline->replot();

	m_temperatureSplineZoomer->setZoomBase();

}


void SVNetworkComponentHeatExchangeEditWidget::on_comboBoxTemperatureSpline_activated(int index)
{
	m_hx->m_ambientTemperatureType = VICUS::NetworkHeatExchange::AmbientTemperatureType(index);
	bool isUserDefined = m_hx->m_ambientTemperatureType == VICUS::NetworkHeatExchange::AT_UserDefined;

	m_ui->listWidgetTemperatureSplineSelectColumn->setVisible(isUserDefined);
	m_ui->labelTemperatureSplineHeatFilePath->setVisible(isUserDefined);
	m_ui->labelTemperatureSplineSelectColumn->setVisible(isUserDefined);
	m_ui->listWidgetTemperatureSplineSelectColumn->setVisible(isUserDefined);
	m_ui->widgetTemperatureSplineFilePathDataFile->setVisible(isUserDefined);

	if (!isUserDefined){
		m_hx->m_userDefinedTsvFile.clear();
		updatePredefinedTemperatureSplinePlotData();
	} else {
		m_ui->widgetTemperatureSplineFilePathDataFile->setFilename(QString::fromStdString(m_hx->m_userDefinedTsvFile.str()));
		bool validFileName = m_hx->m_userDefinedTsvFile.isValid();
		m_ui->widgetPlotTemperatureSpline->setEnabled(m_hx->m_userDefinedTsvFile.isValid());
		if(!validFileName){
			m_temperatureSplineCurve->detach();
			m_ui->widgetPlotTemperatureSpline->replot();
		}
		updateSplineSelectColumnList(VICUS::NetworkHeatExchange::T_TemperatureSpline);
	}
}


void SVNetworkComponentHeatExchangeEditWidget::on_toolButtonSetDefaultValues_clicked() {
	if (m_hx->m_buildingType == VICUS::NetworkHeatExchange::BT_UserDefineBuilding)
		return;
	m_hx->setDefaultValues(m_hx->m_modelType);

	// re-set k values
	m_kHeating = -1;
	if (m_hx->m_withCoolingDemand) {
		m_kCooling = -1;
	}
	if (m_hx->m_withDomesticHotWaterDemand)

	updateEnergyDemandValues();
	updateHeatLossSplinePageForBuildingType();
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxDHW_stateChanged(int arg1) {
	m_hx->m_withDomesticHotWaterDemand = arg1;
	m_ui->widgetDHW->setEnabled(arg1);
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxCooling_stateChanged(int arg1) {
	m_hx->m_withCoolingDemand = arg1;
	m_ui->widgetCooling->setEnabled(arg1);
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_radioButtonShowYear_clicked() {
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_radioButtonShowDay_clicked() {
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossConstantSupplyTemperature_editingFinishedSuccessfully() {
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingSupplyTemperature,
									 m_ui->lineEditHeatLossConstantSupplyTemperature->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxTemperatureConstantHeatTransferCoeff_stateChanged(int arg1) {
	m_ui->lineEditTemperatureConstantHeatTransferCoefficient->setEnabled(arg1);
	m_ui->labelTemperatureConstantHeatTransferCoefficientUnit->setEnabled(arg1);
}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxTemperatureSplineHeatTransferCoefficient_stateChanged(int arg1) {
	m_ui->lineEditTemperatureSplineHeatTransferCoefficient->setEnabled(arg1);
	m_ui->labelTemperatureSplineHeatTransferCoefficientUnit->setEnabled(arg1);
}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxExternallyDefined_stateChanged(int arg1) {

	emit externallyDefinedStateChanged(arg1);

	// enable / disable widgets
	m_ui->stackedWidgetHeatExchange->setEnabled(!arg1);
	m_ui->comboBoxHeatExchange->setEnabled(!arg1);
}

