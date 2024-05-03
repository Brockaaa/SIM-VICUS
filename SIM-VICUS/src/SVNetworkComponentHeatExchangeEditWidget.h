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

#ifndef SVNETWORKCOMPONENTHEATEXCHANGEEDITWIDGET_H
#define SVNETWORKCOMPONENTHEATEXCHANGEEDITWIDGET_H

#include <QWidget>

#include <QDialog>

#include <VICUS_NetworkHeatExchange.h>

class QListWidgetItem;

namespace Ui {
	class SVNetworkComponentHeatExchangeEditWidget;
}

namespace VICUS {
	class NetworkComponent;
}

class QwtPlot;
class QwtPlotCurve;
class QwtPlotZoomer;

class SVNetworkComponentHeatExchangeEditWidget : public QWidget
{
	Q_OBJECT

public:

	explicit SVNetworkComponentHeatExchangeEditWidget(QWidget *parent = nullptr);
	~SVNetworkComponentHeatExchangeEditWidget();

	/*! updates the Widget and sets current Component with this. */
	void updateInput(VICUS::NetworkComponent *component);

	/*! updates pages */
	void updatePageHeatLossConstant();
	void updatePageHeatLossSpline();
	void updatePageTemperatureConstant();
	void updatePageTemperatureSpline();
	void updatePageTemperatureSplineEvaporator(){}
	void updatePageHeatingDemandSpaceHeating(){}

private slots:

	void on_comboBoxHeatExchange_activated(int index);

	void on_checkBoxHeatLossConstantIndividual_stateChanged(int arg1);

	void on_lineEditHeatLossConstantUser_editingFinishedSuccessfully();

	void on_lineEditTemperatureConstantTemperature_editingFinishedSuccessfully();

	void on_checkBoxHeatLossSplineIndividual_clicked(bool checked);

	void on_comboBoxHeatLossSplineUserBuildingType_activated(int index);

	void on_lineEditHeatLossSplineFloorArea_editingFinishedSuccessfully();

	void on_lineEditHeatLossSplineMaximumHeatingLoad_editingFinishedSuccessfully();

	void on_lineEditHeatLossSplineHeatingEnergyDemand_editingFinishedSuccessfully();

	void on_checkBoxHeatLossSplineAreaRelatedValues_stateChanged(int arg1);

	void on_lineEditHeatLossSplineDomesticHotWaterDemand_editingFinishedSuccessfully();

	void on_lineEditHeatLossSplineCoolingEnergyDemand_editingFinishedSuccessfully();

	void on_groupBoxHeatLossSplineCooling_clicked(bool checked);

	void on_lineEditHeatLossSplineMaximumCoolingLoad_editingFinishedSuccessfully();

	void on_filepathDataFile_editingFinished();

	void on_widgetTemperatureSplineFilePathDataFile_editingFinished();

	void on_listWidgetHeatLossSplineSelectColumn_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

	void on_listWidgetTemperatureSplineSelectColumn_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

	void on_comboBoxTemperatureSpline_activated(int index);

	void on_toolButtonSetDefaultValues_clicked();

	void on_groupBoxDomesticHotWaterDemand_clicked(bool checked);

private:

	void updateHeatLossSplineSelectColumnList();

	void updateTemperatureSplineSelectColumnList();

	void readTsvHeatLossSpline();

	void readTsvDomesticHotWaterDemand();

	int indexHeatLossSplineHotWaterYData();

	void updateHeatLossSplinePlotDataPredef();

	void updateHeatLossSplinePlotDataUser();

	void updateTemperatureSplinePlotData();

	void updateTemperatureSplinePlotDataUser();

	void initializeHeatLossSplineAreaRelatedValues();

	double calculateEnergyDemand(VICUS::NetworkHeatExchange::para_t parameter = VICUS::NetworkHeatExchange::P_HeatingEnergyDemand);

	double calculateEnergyDemand(const std::vector<double>& vectorWithValues);

	void calculateNewHeatLossSplineYData(double k, std::vector<double>& vectorToSaveNewValues, VICUS::NetworkHeatExchange::para_t parameter = VICUS::NetworkHeatExchange::P_MaximumHeatingLoad);

	void calculateNewHeatLossSplineHotWaterYData(double floorArea);

	bool calculateNewK(double valueToReach, VICUS::NetworkHeatExchange::para_t parameter = VICUS::NetworkHeatExchange::P_MaximumHeatingLoad);

	void setCoolingCurve(bool set);

	void setHotWaterCurve(bool set);

	Ui::SVNetworkComponentHeatExchangeEditWidget *m_ui;

	/*! Pointer to currently edited component.
		The pointer is updated whenever updateInput() is called.
		A nullptr pointer means that there is no component to edit.
	*/
	VICUS::NetworkComponent					*m_current = nullptr;

	/*! The data vectors needed for plotting HeatLossSpline. */
	std::vector<double>						m_xData;
	std::vector<std::vector<double>>		m_yData1;
	std::vector<std::vector<double>>		m_yData2;

	/*! Vector to temporarily hold all NetworkHeatExchange that were modified after a Block was selected in the scene */
	std::vector<VICUS::NetworkHeatExchange>	m_vectorTempHeatExchange;
	/*! Vector to temporarily store a NetworkHeatExchange to be saved when the building type was changed */
	std::vector<VICUS::NetworkHeatExchange> m_vectorTempHeatExchangeBuildingType;

	/*! Curve visible in HeatLossSpline plot */
	QwtPlotCurve							*m_heatLossSplineHeatingCurve = nullptr;
	QwtPlotCurve							*m_heatLossSplineCoolingCurve = nullptr;
	QwtPlotCurve							*m_heatLossSplineHotWaterCurve = nullptr;
	QwtPlotZoomer							*m_heatLossSplineZoomer = nullptr;

	/* data vector to be displayed in TemperatureSplinePlot */
	std::vector<double>						m_temperatureSplineYPlotData;
	std::vector<double>						m_temperatureSplineXPlotData;

	/*! Curve visible in TemperatureSpline plot */
	QwtPlotCurve							*m_temperatureSplineCurve = nullptr;
	QwtPlotZoomer							*m_temperatureSplineZoomer = nullptr;

	/*! Data vectors to store the original values of the tsv file */
	std::vector<std::vector<double>>		m_vectorHeatLossSplineHeatingYData;
	std::vector<std::vector<double>>		m_vectorHeatLossSplineCoolingYData;
	std::vector<std::vector<double>>		m_vectorHeatLossSplineHotWaterYData;
	std::vector<double>						m_vectorHeatLossSplineHeatingMaxValues;
	std::vector<double>						m_vectorHeatLossSplineCoolingMaxValues;
	std::vector<double>						m_heatLossSplineXData;

	/*! Data vectors to store data values from tsv specified by user */
	std::vector<double>						m_vectorHeatLossSplineUserYData;
	std::vector<double>						m_vectorHeatLossSplineUserXData;

	/*! Parameter to adjust curves to reach desired Energydemand */
	double									m_kHeating = 1;
	double									m_kCooling = 1;

	/*! Data vectors to store values to be displayed in HeatLossSpline Plot */
	std::vector<double>						m_heatLossSplineHeatingYPlotData;
	std::vector<double>						m_heatLossSplineCoolingYPlotData;
	std::vector<double>						m_heatLossSplineHotWaterYPlotData;

};

#endif // SVNETWORKCOMPONENTHEATEXCHANGEEDITWIDGET_H
