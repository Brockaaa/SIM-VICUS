/*	The SIM-VICUS data model library.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Dirk Weiss  <dirk.weiss -[at]- tu-dresden.de>
	  Stephan Hirth  <stephan.hirth -[at]- tu-dresden.de>
	  Hauke Hirsch  <hauke.hirsch -[at]- tu-dresden.de>

	  ... all the others from the SIM-VICUS team ... :-)

	This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This library is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#include "VICUS_NetworkHeatExchange.h"

#include "VICUS_KeywordList.h"
#include "VICUS_Schedule.h"

#include <IBK_CSVReader.h>

#include <QFile>
#include <QTextStream>

namespace VICUS {


void NetworkHeatExchange::setDefaultValues(NetworkHeatExchange::ModelType modelType)
{
	m_modelType = modelType;
	switch(modelType){
		case T_HeatLossSpline:
		case T_HeatLossSplineCondenser: {
			if (m_buildingType == NUM_BT){
				m_buildingType = BT_ResidentialBuildingSingleFamily;
			}
			if (m_buildingType == BT_ResidentialBuildingSingleFamily) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 10);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 7500);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 1875);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 5);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 1200);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingSupplyTemperature, 35);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterSupplyTemperature, 50);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 150);
				m_withCoolingDemand = false;
				m_withDomesticHotWaterDemand = true;
			} else if (m_buildingType == BT_ResidentialBuildingMultiFamily) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 100);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 50000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 12500);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 25);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 25000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingSupplyTemperature, 35);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterSupplyTemperature, 50);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 1000);
				m_withCoolingDemand = false;
				m_withDomesticHotWaterDemand = true;
			} else if (m_buildingType == BT_ResidentialBuildingLarge) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 100);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 50000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 12500);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 25);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 25000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingSupplyTemperature, 35);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterSupplyTemperature, 50);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 1000);
				m_withCoolingDemand = false;
				m_withDomesticHotWaterDemand = true;
			} else if (m_buildingType == BT_OfficeBuilding) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 100);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 50000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 6250);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 25);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 25000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingSupplyTemperature, 35);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterSupplyTemperature, 50);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 1000);
				m_withCoolingDemand = true;
				m_withDomesticHotWaterDemand = false;
			}
			break;
		}
		case T_HeatLossConstant:
		case T_HeatLossConstantCondenser: {
			KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatLoss, 5000);
			KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingSupplyTemperature, 35);
			break;
		}
		case T_TemperatureSpline:
		case T_TemperatureSplineEvaporator: {
			KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_ExternalHeatTransferCoefficient, 25);
			m_ambientTemperatureType = VICUS::NetworkHeatExchange::AT_UndisturbedSoilTemperature;
			break;
		}
		case T_TemperatureConstant: {
			KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_ExternalHeatTransferCoefficient, 25);
			KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_Temperature, 20);
			break;
		}
		case T_TemperatureConstructionLayer:
		case T_TemperatureZone:
		case T_HeatingDemandSpaceHeating:
		case NUM_T:
		break;
	}
}


void NetworkHeatExchange::readPredefinedTSVFiles() const{

	if (m_modelType == T_HeatLossSpline ||
		m_modelType == T_HeatLossSplineCondenser) {

		QString fileHeatingDemand, fileCoolingDemand, fileDHWDemand;
		bool readHeatingCoolingFiles = true;
		switch (m_buildingType) {
			case BT_ResidentialBuildingSingleFamily: {
				fileHeatingDemand = ":/predefinedSplines/heatFluxes/Residential_SingleFamily_HeatingLoad.tsv";
				fileCoolingDemand = ":/predefinedSplines/heatFluxes/Residential_SingleFamily_CoolingLoad.tsv";
			}
			break;
			case BT_ResidentialBuildingMultiFamily: {
				fileHeatingDemand = ":/predefinedSplines/heatFluxes/Residential_MultiFamily_HeatingLoad.tsv";
				fileCoolingDemand = ":/predefinedSplines/heatFluxes/Residential_MultiFamily_CoolingLoad.tsv";
			} break;
			case BT_ResidentialBuildingLarge: {
				fileHeatingDemand = ":/predefinedSplines/heatFluxes/Residential_Large_HeatingLoad.tsv";
				fileCoolingDemand = ":/predefinedSplines/heatFluxes/Residential_Large_CoolingLoad.tsv";
			} break;
			case BT_OfficeBuilding: {
				fileHeatingDemand = ":/predefinedSplines/heatFluxes/Office_HeatingLoad.tsv";
				fileCoolingDemand = ":/predefinedSplines/heatFluxes/Office_CoolingLoad.tsv";
			} break;
			case BT_UserDefineBuilding:
			case NUM_BT:
				readHeatingCoolingFiles = false;
			break;
		}

		if (readHeatingCoolingFiles) {
			readSingleTSVFile(fileHeatingDemand, m_heatingDemandSplineOrig);
			readSingleTSVFile(fileCoolingDemand, m_coolingDemandSplineOrig);
		}

	}
	else if (m_modelType == T_TemperatureSpline ||
			 m_modelType == T_TemperatureSplineEvaporator) {

		QString fileTemperature;
		bool readFile = true;
		switch (m_ambientTemperatureType) {
			case AT_UndisturbedSoilTemperature:
				fileTemperature = ":/predefinedSplines/temperatures/UndisturbedSoilTemperature.tsv";
			break;
			case AT_BoreholeHeatExchangerTemperature:
				fileTemperature = ":/predefinedSplines/temperatures/BoreholeHeatExchangerTemperature.tsv";
			break;
			case AT_UserDefined:
			case NUM_AT:
				readFile = false;
			break;
		}

		if (readFile) {
			readSingleTSVFile(fileTemperature, m_temperatureSplineY);
		}
	}
	else
		Q_ASSERT(false);
}


void NetworkHeatExchange::readSingleTSVFile(QString filename, std::vector<double> & yData) const{
	FUNCID(NetworkHeatExchange::readSingleTSVFile);

	IBK::CSVReader reader;
	try {
		// We need to read the file within Qt in order to resolve the resources,
		// then we just pass the string to CSV reader
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			throw IBK::Exception(IBK::FormatString("Could not open or access file."), FUNC_ID);
		QTextStream in(&file);
		QString qStr;
		while (!in.atEnd()) {
			qStr += in.readLine() + '\n';
		}
		file.close();
		// Convert to std::string
		std::string content = qStr.toStdString();
		// parse csv
		reader.parse(content);
		if (reader.m_nColumns != 2)
			throw IBK::Exception(IBK::FormatString("Tsv file must have exactly 2 columns."), FUNC_ID);
		if (reader.m_nRows != 8760)
			throw IBK::Exception(IBK::FormatString("Tsv file must have exactly 8760 rows."), FUNC_ID);
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception(ex, IBK::FormatString("Error reading tsv file '%1'.").arg(filename.toStdString()), FUNC_ID);
	}
	yData = reader.colData(1);
}


void NetworkHeatExchange::calculateHeatLossSplineFromKValue(double k, const std::vector<double> & original, std::vector<double> & result,
															double maxValueRequired, double maxValueExisting) const {

	// copy the original function and set time points with DHW preparation to 0
	std::vector<double> originalWithDHWOperation = original;
	for (unsigned int i: m_timePointsDHWPreparation)
		originalWithDHWOperation[i] = 0;

	maxValueExisting = *std::max_element(originalWithDHWOperation.begin(), originalWithDHWOperation.end());
	double ratio =  maxValueRequired / maxValueExisting;

	auto scaling = [k, maxValueRequired, ratio](double y){
		double relativeValue = y * ratio;
		relativeValue = relativeValue / maxValueRequired;
		double adjustedRelativeValue = std::pow(relativeValue,k);
		double adjustedAbsoluteValue = maxValueRequired * adjustedRelativeValue;
		return adjustedAbsoluteValue;
	};

	result.resize(originalWithDHWOperation.size());
	std::transform(originalWithDHWOperation.begin(), originalWithDHWOperation.end(), result.begin(), scaling);
}


bool NetworkHeatExchange::calculateNewKValue(const std::vector<double> & original, double integralRequired, double maxValueRequired,
											 double & integralResult, double & KResult) const {
	/* Caution:
	 'integralRequired' should be in [Wh], all other quantities in Si Units [W]
	 */

	Q_ASSERT(!original.empty());

	// copy the original function and set time points with DHW preparation to 0
	std::vector<double> originalWithDHWOperation = original;
	for (unsigned int i: m_timePointsDHWPreparation)
		originalWithDHWOperation[i] = 0;

	double maxValueExisting = *std::max_element(originalWithDHWOperation.begin(), originalWithDHWOperation.end());

	// if maxValueRequired is too large, scale both maxValueRequired and integral down to avoid double imprecision //
	int power = 0;
	while( maxValueRequired > 1000000/* 5mW */ ){
		maxValueRequired /= 10;
		integralRequired /= 10;
		power++;
	}

	std::vector<double> newlyCalculatedYPlotValues;

	// constants
	int maxLoopIterations = 50;
	double lowerBound = 0;
	double upperBound = 1024;

	IBK::NearEqual<double> nearEqual(0.5);

	KResult = 1;
	for (int i = 0 ; i < maxLoopIterations; i++){
		calculateHeatLossSplineFromKValue(KResult, originalWithDHWOperation, newlyCalculatedYPlotValues, maxValueRequired, maxValueExisting);
		integralResult = std::accumulate(newlyCalculatedYPlotValues.begin(), newlyCalculatedYPlotValues.end(), 0.0);
		if (nearEqual(integralRequired, integralResult)){
			integralResult = integralResult * pow(10, power);
			return true;
		}
		else if (integralResult < integralRequired){
			double difference = KResult - lowerBound;
			upperBound = KResult;
			KResult -= difference / 2;
		} else {
			double difference = upperBound - KResult;
			lowerBound = KResult;
			KResult += difference / 2;
		}
	}

	integralResult = integralResult * pow(10, power);
	return false;
}


bool NetworkHeatExchange::generateHeatingDemandSpline(std::vector<double> & spline, double k) const{
	if (k<0) {
		double finalHeatingDemand;
		if ( !calculateNewKValue(m_heatingDemandSplineOrig, m_para[P_HeatingEnergyDemand].get_value("Wh"), m_para[P_MaximumHeatingLoad].value, finalHeatingDemand, k) )
			return false;
		// Note: final and requested demands should be identical here
	}
	calculateHeatLossSplineFromKValue(k, m_heatingDemandSplineOrig, spline, m_para[P_MaximumHeatingLoad].value);
	return true;
}


bool NetworkHeatExchange::generateCoolingDemandSpline(std::vector<double> & spline, double k) const{
	if (k<0) {
		double finalCoolingDemand;
		if (!calculateNewKValue(m_coolingDemandSplineOrig, m_para[P_CoolingEnergyDemand].get_value("Wh"), m_para[P_MaximumCoolingLoad].value, finalCoolingDemand, k))
			return false;
		// Note: final and requested demands should be identical here
	}
	calculateHeatLossSplineFromKValue(k, m_coolingDemandSplineOrig, spline, m_para[P_MaximumCoolingLoad].value);
	return true;
}


void NetworkHeatExchange::generateDHWDemandSpline(std::vector<double> & spline) const {

	m_timePointsDHWPreparation.clear();

	if (!m_withDomesticHotWaterDemand)
		return;

	double dhwDemandPerDay = m_para[VICUS::NetworkHeatExchange::P_DomesticHotWaterDemand].get_value("Wh") / 365.0;
	if (dhwDemandPerDay <= 0)
		return;
	double dhwMaxLoad = 0.7 * m_para[VICUS::NetworkHeatExchange::P_MaximumHeatingLoad].get_value("W");

	// hours for DHW preparation per day should be an integer
	unsigned int hoursPerDay = (unsigned int)std::ceil(dhwDemandPerDay / dhwMaxLoad);

	// it it would be less than one hour, reduce the max load
	if (hoursPerDay < 1) {
		dhwMaxLoad = dhwDemandPerDay;
		hoursPerDay = 1.0;
	}
	// it it would be more than 4 hours, increase the max load
	else if (hoursPerDay > 4) {
		hoursPerDay = 4;
		dhwMaxLoad = dhwDemandPerDay / hoursPerDay;
	// adapat max load to meet the correct demand
	} else {
		dhwMaxLoad = dhwDemandPerDay / hoursPerDay;
	}

	// set according time points in yearly profile to dhwMaxLoad
	std::vector<unsigned int> possibleHours = {2,3,15,16}; // must not be 0 or 24
	spline = std::vector<double>(8760, 0.0);
	for (unsigned int i=0; i<365; ++i) {
		for (unsigned int j=0; j<hoursPerDay; ++j )
			spline[i*24 + possibleHours[j]] = dhwMaxLoad;
	}

	// store time points where there is DHW preparation. At those time points (and 1 hour before, after) there must be not heating/cooling operation
	for (unsigned int i=0; i<spline.size(); ++i) {
		if (spline[i] > 0) {
			m_timePointsDHWPreparation.push_back(i-1);
			m_timePointsDHWPreparation.push_back(i);
			m_timePointsDHWPreparation.push_back(i+1);
		}
	}
}


void NetworkHeatExchange::checkAndInitializeSpline() const {
	FUNCID(NetworkHeatExchange::checkAndInitializeSpline);

	try {

		m_exportSpline = NANDRAD::LinearSplineParameter();

		if (m_modelType == T_TemperatureSpline || m_modelType == T_TemperatureSplineEvaporator) {

			Q_ASSERT(m_ambientTemperatureType != NUM_AT);
			if (m_ambientTemperatureType == AT_UserDefined) {
				m_exportSpline.m_tsvFile = m_userDefinedTsvFile;
			}
			else {

				readPredefinedTSVFiles();

				std::vector<double> time(m_temperatureSplineY.size());
				for (unsigned int i=0; i<m_temperatureSplineY.size(); ++i)
					time[i] = i; // we assume spline in hourly values

				NANDRAD::LinearSplineParameter spl;
				m_exportSpline.m_name = "Temperature"; // this name is checked for in NANDRAD
				m_exportSpline.m_xUnit = IBK::Unit("h");
				m_exportSpline.m_yUnit = IBK::Unit("C");
				m_exportSpline.m_interpolationMethod = NANDRAD::LinearSplineParameter::I_LINEAR;
				m_exportSpline.m_wrapMethod = NANDRAD::LinearSplineParameter::C_CYCLIC;
				m_exportSpline.m_values.setValues(time, m_temperatureSplineY);
			}

		}
		else if (m_modelType == T_HeatLossSpline || m_modelType == T_HeatLossSplineCondenser) {

			Q_ASSERT(m_buildingType != NUM_BT);
			if (m_buildingType == BT_UserDefineBuilding) {
				m_exportSpline.m_tsvFile = m_userDefinedTsvFile;
			}
			else {

				readPredefinedTSVFiles();

				// first generate DHW spline, this changes the original functions for heating/cooling!
				std::vector<double> DHWSpline;
				if (m_withDomesticHotWaterDemand) {
					generateDHWDemandSpline(DHWSpline);
				}

				// generate heating spline
				std::vector<double> heatingSpline;
				bool success = generateHeatingDemandSpline(heatingSpline);
				if (!success)
					throw IBK::Exception("Could not generate heating demand spline from given parameters.", FUNC_ID);

				// generate cooling spline
				std::vector<double> coolingSpline;
				if (m_withCoolingDemand) {
					success = generateCoolingDemandSpline(coolingSpline);
					if (!success)
						throw IBK::Exception("Could not generate cooling demand spline from given parameters.", FUNC_ID);
					Q_ASSERT(heatingSpline.size() == coolingSpline.size());
				}

				// merge to one vector
				std::vector<double> time(heatingSpline.size());
				std::vector<double> heatFlux(heatingSpline.size());
				for (unsigned int i=0; i<heatingSpline.size(); ++i) {
					time[i] = i; // we assume spline in hourly values
					if (DHWSpline[i] > 0)
						heatFlux[i] = DHWSpline[i];
					else if (heatingSpline[i] > 0)
						heatFlux[i] = heatingSpline[i];
					else if (coolingSpline.size() > 0 && coolingSpline[i] > 0)
						heatFlux[i] = -coolingSpline[i];
				}

				m_exportSpline.m_name = "HeatLoss"; // this name is checked for in NANDRAD
				m_exportSpline.m_xUnit = IBK::Unit("h");
				m_exportSpline.m_yUnit = IBK::Unit("W");
				m_exportSpline.m_interpolationMethod = NANDRAD::LinearSplineParameter::I_LINEAR;
				m_exportSpline.m_wrapMethod = NANDRAD::LinearSplineParameter::C_CYCLIC;
				m_exportSpline.m_values.setValues(time, heatFlux);
			}
		}
	}  catch (IBK::Exception &ex) {
		throw IBK::Exception(ex, "Error generating heat exchange spline for project export.", FUNC_ID);
	}

}


NANDRAD::HydraulicNetworkHeatExchange NetworkHeatExchange::toNandradHeatExchange() const {

	NANDRAD::HydraulicNetworkHeatExchange hx = NANDRAD::HydraulicNetworkHeatExchange();
	hx.m_modelType = NANDRAD::HydraulicNetworkHeatExchange::ModelType(m_modelType);
	switch(m_modelType){
		case T_TemperatureConstant:
		case T_TemperatureConstantEvaporator: {
			hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_Temperature] = m_para[P_Temperature];
			if (m_useHeatTransferCoefficient)
				hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_ExternalHeatTransferCoefficient] = m_para[P_ExternalHeatTransferCoefficient];
			else
				hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_ExternalHeatTransferCoefficient].set(1e10, IBK::Unit("W/m2K"));
			break;
		}
		case T_TemperatureSpline:
		case T_TemperatureSplineEvaporator: {
			checkAndInitializeSpline(); // we need to execute initialization to generate spline!
			hx.m_splPara[NANDRAD::HydraulicNetworkHeatExchange::SPL_Temperature] = m_exportSpline;
			if (m_useHeatTransferCoefficient)
				hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_ExternalHeatTransferCoefficient] = m_para[P_ExternalHeatTransferCoefficient];
			else
				hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_ExternalHeatTransferCoefficient].set(1e10, IBK::Unit("W/m2K"));
			break;
		}
		case T_HeatLossConstant:
		case T_HeatLossConstantCondenser: {
			hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_HeatLoss] = m_para[P_HeatLoss];
			break;
		}
		case T_HeatLossSpline:
		case T_HeatLossSplineCondenser: {
			checkAndInitializeSpline(); // we need to execute initialization to generate spline!
			hx.m_splPara[NANDRAD::HydraulicNetworkHeatExchange::SPL_Temperature] = m_exportSpline;
			break;
		}
		case T_TemperatureConstructionLayer:
		case T_TemperatureZone:
		case T_HeatingDemandSpaceHeating:
		case NUM_T:
		break;
	}
	return hx;
}

QString NetworkHeatExchange::iconFileFromModelType(ModelType modelType)
{
	switch(modelType) {
		case VICUS::NetworkHeatExchange::ModelType::T_HeatLossConstantCondenser:
		case VICUS::NetworkHeatExchange::ModelType::T_HeatLossConstant:
			return ":/icons/light/png/network_icons/heatflux_const.png";
		case VICUS::NetworkHeatExchange::ModelType::T_HeatLossSplineCondenser:
		case VICUS::NetworkHeatExchange::ModelType::T_HeatLossSpline:
			return ":/icons/light/png/network_icons/heatflux_spline.png";
		case VICUS::NetworkHeatExchange::ModelType::T_TemperatureConstant:
			return ":/icons/light/png/network_icons/temperature_const.png";
		case VICUS::NetworkHeatExchange::ModelType::T_TemperatureSpline:
			return ":/icons/light/png/network_icons/temperature_spline.png";
		default:
			return "";
	}

}


Schedule NetworkHeatExchange::condenserTemperatureSchedule() const{

	VICUS::Schedule sched;
	sched.m_haveAnnualSchedule = true;
	std::vector<double> x, y;

	if (m_modelType == VICUS::NetworkHeatExchange::T_HeatLossSplineCondenser) {
		Q_ASSERT(!m_timePointsDHWPreparation.empty());
		// time vec
		x.resize(8760);
		for (unsigned int i=0; i<8760; ++i)
			x[i] = i;
		// temperature vec
		y = std::vector<double>(8760, m_para[P_HeatingSupplyTemperature].get_value("C"));
		for (unsigned int i: m_timePointsDHWPreparation)
			y[i] = m_para[P_DomesticHotWaterSupplyTemperature].get_value("C");

	}
	else if (m_modelType == VICUS::NetworkHeatExchange::T_HeatLossConstantCondenser) {
		x = {0, 8759};
		y = std::vector<double>(2, m_para[P_HeatingSupplyTemperature].get_value("C"));
	}
	else {
		Q_ASSERT(false);
	}

	sched.m_annualSchedule = NANDRAD::LinearSplineParameter("CondenserMeanTemperatureSchedule",
															NANDRAD::LinearSplineParameter::I_CONSTANT, x, y,
															IBK::Unit("h"), IBK::Unit("C"));
	return sched;
}

} //namespace VICUS
