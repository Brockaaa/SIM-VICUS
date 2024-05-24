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
	m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineFloorArea->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineFloorArea->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setMinimum(0, false);

	m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setFormat('f', 0);
	m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setMinimum(0, false);

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
	m_temperatureSplineCurve = new QwtPlotCurve();
	m_temperatureSplineCurve->setPen(QColor("#d90429"));

	if (m_heatLossSplineZoomer == nullptr)
		m_heatLossSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotHeatLossSpline->canvas() );
	m_heatLossSplineZoomer->setZoomBase();

	if(m_temperatureSplineZoomer == nullptr)
		m_temperatureSplineZoomer = new QwtPlotZoomer(m_ui->widgetPlotTemperatureSpline->canvas() );
	m_temperatureSplineZoomer->setZoomBase();
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

	// update of relevant page
	on_comboBoxHeatExchange_activated(idx);
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageHeatLossConstant()
{
	m_ui->checkBoxHeatLossConstantIndividual->setChecked(m_hx->m_individualHeatExchange);
	m_ui->lineEditHeatLossConstantUser->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatLoss].get_value("kW"));
	on_checkBoxHeatLossConstantIndividual_stateChanged(static_cast<int>(m_hx->m_individualHeatExchange));
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageHeatLossSpline(VICUS::NetworkHeatExchange::ModelType hxModelType) {

	// hxModelType must be one of both!
	Q_ASSERT(hxModelType == VICUS::NetworkHeatExchange::T_HeatLossSpline ||
			 hxModelType == VICUS::NetworkHeatExchange::T_HeatLossSplineCondenser );

	m_ui->filepathDataFile->setFilename("");

	// set default building type
	on_comboBoxHeatLossSplineBuildingType_activated(m_hx->m_buildingType);

	m_ui->checkBoxHeatLossSplineIndividual->setChecked(m_hx->m_individualHeatExchange);
	on_checkBoxHeatLossSplineIndividual_clicked(m_hx->m_individualHeatExchange);
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageTemperatureConstant()
{
	m_ui->lineEditHeatTransferCoefficientConstant->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient].get_value());
	m_ui->lineEditTemperatureConstantTemperature->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_Temperature].get_value());
}


void SVNetworkComponentHeatExchangeEditWidget::updatePageTemperatureSpline()
{
	m_ui->lineEditHeatTransferCoefficientSpline->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient].get_value());
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


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossConstantIndividual_stateChanged(int arg1)
{
	bool checked = static_cast<bool>(arg1);
	m_hx->m_individualHeatExchange = arg1;
	m_ui->labelHeatLossConstantUserHeatFlux->setEnabled(!checked);
	m_ui->labelHeatLossConstantUserUnit->setEnabled(!checked);
	m_ui->lineEditHeatLossConstantUser->setEnabled(!checked);
	m_ui->toolButtonSetDefaultValues->setEnabled(!checked);
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossConstantUser_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatLoss, m_ui->lineEditHeatLossConstantUser->value()*1000);
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditTemperatureConstantTemperature_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_Temperature, m_ui->lineEditTemperatureConstantTemperature->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatTransferCoefficientConstant_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient, m_ui->lineEditHeatTransferCoefficientConstant->value());
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatTransferCoefficientSpline_editingFinishedSuccessfully()
{
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_ExternalHeatTransferCoefficient, m_ui->lineEditHeatTransferCoefficientSpline->value());
}


void SVNetworkComponentHeatExchangeEditWidget::updateHeatLossSplinePageForBuildingType()
{
	// if user defined building type, do not fill out the rest
	if (m_hx->m_buildingType == VICUS::NetworkHeatExchange::BT_UserDefineBuilding)
		return;

	m_ui->lineEditHeatLossSplineMaximumHeatingLoad->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].get_value());
	m_ui->lineEditHeatLossSplineFloorArea->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_FloorArea].get_value());
	m_ui->lineEditHeatLossSplineMaximumCoolingLoad->setValue(m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].get_value());
	m_ui->groupBoxHeatLossSplineCooling->setChecked(m_hx->m_withCoolingDemand);
	m_ui->groupBoxDomesticHotWaterDemand->setChecked(m_hx->m_withDomesticHotWaterDemand);

	// update area related values
	updateEnergyDemandValuesAreaSpecific();
}


void SVNetworkComponentHeatExchangeEditWidget::updateEnergyDemandValuesAreaSpecific() {
	bool areaRelated = m_hx->m_areaRelatedValues;
	m_ui->checkBoxHeatLossSplineAreaRelatedValues->setChecked(areaRelated);
	m_ui->labelHeatLossSplineFloorAreaUnit->setEnabled(areaRelated);
	m_ui->lineEditHeatLossSplineFloorArea->setEnabled(areaRelated);
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


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossSplineIndividual_clicked(bool checked) {

	m_hx->m_individualHeatExchange = checked;

	// enable / disable widgets
	m_ui->widgetDefineHeatExchangeSpline->setEnabled(!checked);
	m_ui->widgetPlotHeatLossSpline->setEnabled(!checked);
	if (checked){
		if (m_heatLossSplineCoolingCurve != nullptr){
			m_heatLossSplineCoolingCurve->detach();
		}
		if(m_heatLossSplineHeatingCurve != nullptr){
			m_heatLossSplineHeatingCurve->detach();
		}
		m_ui->widgetPlotHeatLossSpline->replot();
	}
	// if unchecked: re-plot
	else {
		if (m_hx->m_buildingType == VICUS::NetworkHeatExchange::BT_UserDefineBuilding)
			updateHeatLossSplineUserPlot();
		else
			updateHeatLossSplinePredefPlot();
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
	double finalCoolingDemand;
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
	// get old and new max Value and adjust HeatingEnergyDemand
	double oldMaximumHeatingLoad =  m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;
	double newMaximumHeatingLoad = m_ui->lineEditHeatLossSplineMaximumHeatingLoad->value();
	double oldHeatingEnergyDemand = m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].value;
	double newHeatingEnergyDemand = oldHeatingEnergyDemand * (newMaximumHeatingLoad * 1000) / oldMaximumHeatingLoad;

	m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].value = newHeatingEnergyDemand;
	m_ui->lineEditHeatLossSplineHeatingEnergyDemand->setValue((int)newHeatingEnergyDemand / 1000);

	// set new max value
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumHeatingLoad,
									 newMaximumHeatingLoad);
	m_hx->calculateHeatLossSplineFromKValue(m_kHeating, m_hx->m_heatingDemandSplineOrig, m_heatLossSplineHeatingY, m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value);

	// also calculate new energy demand value
	double newHeatingDemand = std::accumulate(m_heatLossSplineHeatingY.begin(), m_heatLossSplineHeatingY.end(), 0.0);
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_HeatingEnergyDemand,
									   newHeatingDemand / 1000);
	// and update values
	updateEnergyDemandValuesAreaSpecific();
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::modifyEnergyDemandValue(bool heating) {

	VICUS::NetworkHeatExchange::para_t para;
	double requestedDemand; 	// newly requested value
	if (heating) {
		para = VICUS::NetworkHeatExchange::P_HeatingEnergyDemand;
		requestedDemand = m_ui->lineEditHeatLossSplineHeatingEnergyDemand->value() * 1000; // to Wh
		m_ui->lineEditHeatLossSplineHeatingEnergyDemand->clearFocus();
	}
	else {
		para = VICUS::NetworkHeatExchange::P_CoolingEnergyDemand;
		requestedDemand = m_ui->lineEditHeatLossSplineCoolingEnergyDemand->value() * 1000; // to Wh
		m_ui->lineEditHeatLossSplineCoolingEnergyDemand->clearFocus();
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
	double finalDemand;
	bool successfulNewK;
	if (heating) {
		successfulNewK = m_hx->calculateNewKValue(m_hx->m_heatingDemandSplineOrig, requestedDemand,
													m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value,
													finalDemand, m_kHeating);
	}
	else {
		successfulNewK = m_hx->calculateNewKValue(m_hx->m_coolingDemandSplineOrig, requestedDemand,
													m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value,
													finalDemand, m_kCooling);
	}

	// if all good, store value
	if (successfulNewK) {
		VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", para, finalDemand/1000);  // set in kWh
	}
	else {
		// if not, ask user how to proceed:
		QMessageBox msgBox(this);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setWindowTitle(QString("Requested energy demand not reachable"));
		msgBox.setText(QString("The requested energy demand of %1 kWh is not reachable. The closest reachable value is %2. Take the closest value or revert to the previous value %3 kWh?")
						   .arg(requestedDemand/1000, 0, 'f', 0).arg(finalDemand/1000, 0, 'f', 0).arg(previousDemand/1000, 0, 'f', 0));
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setButtonText(QMessageBox::Yes, QString("Take closest reachable value %1").arg(finalDemand/1000,0,'f',0));
		msgBox.setButtonText(QMessageBox::No, QString("Revert to previous value %1").arg(previousDemand/1000,0,'f',0));
		int result = msgBox.exec();

		if(result == QMessageBox::Yes)
			VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", para, finalDemand/1000);
		else
			VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", para, previousDemand/1000);
	}

	updateEnergyDemandValuesAreaSpecific();
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineHeatingEnergyDemand_editingFinishedSuccessfully() {
	modifyEnergyDemandValue(true);
}


void SVNetworkComponentHeatExchangeEditWidget::on_checkBoxHeatLossSplineAreaRelatedValues_stateChanged(int arg1) {
	m_hx->m_areaRelatedValues = arg1;
	updateEnergyDemandValuesAreaSpecific();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineDomesticHotWaterDemand_editingFinishedSuccessfully()
{
	double requestedDemand = m_ui->lineEditHeatLossSplineDomesticHotWaterDemand->value();
	if (m_hx->m_areaRelatedValues)
		requestedDemand *= m_hx->m_para[VICUS::NetworkHeatExchange::P_FloorArea].value;
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand, requestedDemand);
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineCoolingEnergyDemand_editingFinishedSuccessfully() {
	modifyEnergyDemandValue(false);
}


void SVNetworkComponentHeatExchangeEditWidget::on_groupBoxHeatLossSplineCooling_clicked(bool checked) {
	m_hx->m_withCoolingDemand = checked;
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_lineEditHeatLossSplineMaximumCoolingLoad_editingFinishedSuccessfully() {
	// get old and new max Value and adjust HeatingEnergyDemand
	double oldMaximumCoolingLoad =  m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value;
	double newMaximumCoolingLoad = m_ui->lineEditHeatLossSplineMaximumCoolingLoad->value();
	double oldCoolingEnergyDemand = m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].value;
	double newCoolingEnergyDemand = oldCoolingEnergyDemand * (newMaximumCoolingLoad * 1000) / oldMaximumCoolingLoad;

	m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].value = newCoolingEnergyDemand;

	// set new max value
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_MaximumCoolingLoad,
									 newMaximumCoolingLoad);
	bool success = m_hx->generateCoolingDemandSpline(m_heatLossSplineCoolingY, m_kCooling);
	Q_ASSERT(success); //  we only scale the curve, should never give any problems

	// also calculate new energy demand value
	double newCoolingDemand = std::accumulate(m_heatLossSplineCoolingY.begin(), m_heatLossSplineCoolingY.end(), 0.0);
	VICUS::KeywordList::setParameter(m_hx->m_para, "NetworkHeatExchange::para_t", VICUS::NetworkHeatExchange::P_CoolingEnergyDemand,
									   newCoolingDemand / 1000);
	// and update values
	updateEnergyDemandValuesAreaSpecific();
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


void SVNetworkComponentHeatExchangeEditWidget::on_listWidgetHeatLossSplineSelectColumn_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
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


void SVNetworkComponentHeatExchangeEditWidget::on_listWidgetTemperatureSplineSelectColumn_currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous)
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
		return;
	}

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

	// calculates new 'k' only if needed
	if (m_kHeating<0){
		double finalHeatingDemand;
		if (!m_hx->calculateNewKValue(m_hx->m_heatingDemandSplineOrig, m_hx->m_para[VICUS::NetworkHeatExchange::P_HeatingEnergyDemand].get_value("Wh"), m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value, finalHeatingDemand, m_kHeating) )
			return;
	}
	m_hx->calculateHeatLossSplineFromKValue(m_kHeating, m_hx->m_heatingDemandSplineOrig, m_heatLossSplineHeatingY, m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value);

	if (m_hx->m_withCoolingDemand)
	{
		if(m_kCooling<0){
			double finalCoolingDemand;
			if (!m_hx->calculateNewKValue(m_hx->m_coolingDemandSplineOrig, m_hx->m_para[VICUS::NetworkHeatExchange::P_CoolingEnergyDemand].get_value("Wh"), m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value, finalCoolingDemand, m_kCooling) )
				return;
		}
		m_hx->calculateHeatLossSplineFromKValue(m_kCooling, m_hx->m_coolingDemandSplineOrig, m_heatLossSplineCoolingY, m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value);
	}



	// time expected in hours
	std::vector<double> time(m_heatLossSplineHeatingY.size());
	for (unsigned int i=0; i<m_heatLossSplineHeatingY.size(); ++i)
		time[i] = i;

	double maximumHeatingLoad, maximumCoolingLoad;
	maximumHeatingLoad = m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].value;
	maximumCoolingLoad = m_hx->m_para[VICUS::NetworkHeatExchange::P_MaximumCoolingLoad].value;
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, time.back());
	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::yLeft, 0, maximumHeatingLoad > maximumCoolingLoad ? maximumHeatingLoad / 1000 : maximumCoolingLoad / 1000);

	//creating curve for heating
	std::vector<double> heatingValuesToPlot;
	for (double value : m_heatLossSplineHeatingY)
		heatingValuesToPlot.push_back(value / 1000); // convert to kW
	m_heatLossSplineHeatingCurve->setSamples(time.data(), heatingValuesToPlot.data(), time.size());
	m_heatLossSplineHeatingCurve->attach(m_ui->widgetPlotHeatLossSpline);

	//creating curve for cooling
	if (m_hx->m_withCoolingDemand) {
		std::vector<double> coolingValuesToPlot;
		for(double value : m_heatLossSplineCoolingY)
			coolingValuesToPlot.push_back(value / 1000); // convert to kW
		m_heatLossSplineCoolingCurve->setSamples(time.data(), coolingValuesToPlot.data(), time.size());
		m_heatLossSplineCoolingCurve->attach(m_ui->widgetPlotHeatLossSpline);
	} else {
		m_heatLossSplineCoolingCurve->detach();
	}
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
	std::vector<double> time(m_heatLossSplineHeatingY.size());
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

	m_ui->widgetPlotHeatLossSpline->setAxisScale(QwtPlot::xBottom, 0, time.size());
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
	for(int i = 0; i < temperatureSpline.size(); i++){
		temperatureSpline[i] -= 274.15;
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


//void SVNetworkComponentHeatExchangeEditWidget::calculateNewHeatLossSplineHotWaterYData(double floorArea)
//{
//	Q_ASSERT(m_heatLossSplineHwUserProfile != NUM_HW);
//	m_heatLossSplineHotWaterYPlotData = m_mapHeatLossSplineHotWaterYData[m_heatLossSplineHwUserProfile];
//	return;
//}


void SVNetworkComponentHeatExchangeEditWidget::setHotWaterCurve(bool set)
{

//	if(set){
//		std::vector<double> hotWaterValuesToPlot;
//		for(double value : m_heatLossSplineHotWaterYPlotData)
//			hotWaterValuesToPlot.push_back(value / 1000); // convert to kW
//		m_heatLossSplineHotWaterCurve->setSamples(m_heatLossSplineTime.data(), hotWaterValuesToPlot.data(), m_heatLossSplineTime.size());
//	} else {
//		m_heatLossSplineHotWaterCurve->detach();
//	}
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

	updateEnergyDemandValuesAreaSpecific();
	updateHeatLossSplinePageForBuildingType();
	updateHeatLossSplinePredefPlot();
}


void SVNetworkComponentHeatExchangeEditWidget::on_groupBoxDomesticHotWaterDemand_clicked(bool checked)
{
	qDebug() << "Domestic Hot Water Demand clicked. ";
	m_hx->m_withDomesticHotWaterDemand = checked;
}

