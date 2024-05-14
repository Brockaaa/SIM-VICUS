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

#include <IBK_CSVReader.h>


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
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 0);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 5);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 1200);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 150);
			} else if (m_buildingType == BT_ResidentialBuildingMultiFamily) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 100);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 50000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 0);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 25);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 25000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 1000);
			} else if (m_buildingType == BT_ResidentialBuildingLarge) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 100);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 50000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 0);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 25);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 25000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 1000);
			} else if (m_buildingType == BT_OfficeBuilding) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 100);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 50000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 0);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 25);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 25000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 1000);
			}
			break;
		}
		case T_HeatLossConstant:
		case T_HeatLossConstantCondenser: {
			KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatLoss, 5000);
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


void NetworkHeatExchange::readTSVFiles(QString ressourcesDir, BuildingType buildingType) {

	QString fileHeatingDemand, fileCoolingDemand, fileDHWDemand;
	bool readHeatingCoolingFiles = true;
	switch (buildingType) {
		case BT_ResidentialBuildingSingleFamily: {
			fileHeatingDemand = ("/demandProfiles/Residential_SingleFamily_HeatingLoad.tsv");
			fileCoolingDemand = ("/demandProfiles/Residential_SingleFamily_CoolingLoad.tsv");
//			fileDHWDemand = ("/demandProfiles/Residential_CoolingLoad.tsv");
		}
		break;
		case BT_ResidentialBuildingMultiFamily: {
			fileHeatingDemand = ("/demandProfiles/Residential_MultiFamily_HeatingLoad.tsv");
			fileCoolingDemand = ("/demandProfiles/Residential_MultiFamily_CoolingLoad.tsv");
		} break;
		case BT_ResidentialBuildingLarge: {
			fileHeatingDemand = ("/demandProfiles/Residential_Large_HeatingLoad.tsv");
			fileCoolingDemand = ("/demandProfiles/Residential_Large_CoolingLoad.tsv");
		} break;
		case BT_OfficeBuilding: {
			fileHeatingDemand = ("/demandProfiles/Office_HeatingLoad.tsv");
			fileCoolingDemand = ("/demandProfiles/Office_CoolingLoad.tsv");
		} break;
		case BT_UserDefineBuilding:
		case NUM_BT:
			readHeatingCoolingFiles = false;
		break;
	}

	if (readHeatingCoolingFiles) {
		QString fileHeatingDemandFull = ressourcesDir + fileHeatingDemand;
		readSingleTSVFile(fileHeatingDemandFull, m_heatingDemandTimeData, m_heatingDemandSplineOrig);

		std::vector<double> dummy;
		QString fileCoolingDemandFull = ressourcesDir + fileCoolingDemand;
		readSingleTSVFile(fileCoolingDemandFull, dummy, m_coolingDemandSplineOrig);
	}
}


void NetworkHeatExchange::readSingleTSVFile(QString filename, std::vector<double> & xData, std::vector<double> & yData) {
	FUNCID(NetworkHeatExchange::readSingleTSVFile);

	IBK::CSVReader reader;
	IBK::Path ibkDirectory(filename.toStdString());
	try {
		reader.read(ibkDirectory);
		if (reader.m_nColumns != 2)
			throw IBK::Exception(IBK::FormatString("Tsv file must have exactly 2 columns."), FUNC_ID);
		if (reader.m_nRows != 8760)
			throw IBK::Exception(IBK::FormatString("Tsv file must have exactly 8760 rows."), FUNC_ID);
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception(ex, IBK::FormatString("Error reading tsv file '%1'.").arg(filename.toStdString()), FUNC_ID);
	}
	xData = reader.colData(0);
	yData = reader.colData(1);
}



void NetworkHeatExchange::calculateHeatLossSplineFromKValue(double k, const std::vector<double> & original, std::vector<double> & result,
															double maxValueRequired, double maxValueExisting) {

	if (maxValueExisting < 0)
		maxValueExisting = *std::max_element(original.begin(), original.end());

	double ratio =  maxValueRequired / maxValueExisting;

	auto scaling = [k, maxValueRequired, ratio](double y){
		double relativeValue = y * ratio;
		relativeValue = relativeValue / maxValueRequired;
		double adjustedRelativeValue = std::pow(relativeValue,k);
		double adjustedAbsoluteValue = maxValueRequired * adjustedRelativeValue;
		return adjustedAbsoluteValue;
	};

	result.resize(original.size());
	std::transform(original.begin(), original.end(), result.begin(), scaling);
}


bool NetworkHeatExchange::calculateNewKValue(const std::vector<double> & original, double integralRequired, double maxValueRequired,
											 double & integralResult, double & KResult) {
	/* Caution:
	 'integralRequired' should be in [Wh], all other quantities in Si Units [W]
	 */

	Q_ASSERT(!original.empty());

	double maxValueExisting = *std::max_element(original.begin(), original.end());

	std::vector<double> newlyCalculatedYPlotValues;

	// constants
	int maxLoopIterations = 50;
	double lowerBound = 0;
	double upperBound = 1024;

	IBK::NearEqual<double> nearEqual(0.5);

	KResult = 1;
	for (int i = 0 ; i < maxLoopIterations; i++){
		calculateHeatLossSplineFromKValue(KResult, original, newlyCalculatedYPlotValues, maxValueRequired, maxValueExisting);
		integralResult = std::accumulate(newlyCalculatedYPlotValues.begin(), newlyCalculatedYPlotValues.end(), 0);
		if (nearEqual(integralRequired, integralResult)){
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

	return false;
}


void NetworkHeatExchange::updateSplines(QString ressourcesDir) {

	// read tsv files
	readTSVFiles(ressourcesDir, m_buildingType);

	std::vector<double> heatingSpline;
	heatingDemandSpline(heatingSpline);

	if (m_withCoolingDemand) {
		std::vector<double> coolingSpline;
		heatingDemandSpline(coolingSpline);
	}

	// TODO Hauke

}


bool NetworkHeatExchange::heatingDemandSpline(std::vector<double> & spline, double k) {
	if (k<0) {
		double finalHeatingDemand;
		if ( !calculateNewKValue(m_heatingDemandSplineOrig, m_para[P_HeatingEnergyDemand].get_value("Wh"), m_para[P_MaximumHeatingLoad].value, finalHeatingDemand, k) )
			return false;
		// Note: final and requested demands should be identical here
	}
	calculateHeatLossSplineFromKValue(k, m_heatingDemandSplineOrig, spline, m_para[P_MaximumHeatingLoad].value);
	return true;
}


bool NetworkHeatExchange::coolingDemandSpline(std::vector<double> & spline, double k) {
	if (k<0) {
		double finalCoolingDemand;
		if (!calculateNewKValue(m_coolingDemandSplineOrig, m_para[P_CoolingEnergyDemand].get_value("Wh"), m_para[P_MaximumCoolingLoad].value, finalCoolingDemand, k))
			return false;
		// Note: final and requested demands should be identical here
	}
	calculateHeatLossSplineFromKValue(k, m_coolingDemandSplineOrig, spline, m_para[P_MaximumCoolingLoad].value);
	return true;
}


NANDRAD::HydraulicNetworkHeatExchange NetworkHeatExchange::toNandradHeatExchange() const {

	NANDRAD::HydraulicNetworkHeatExchange hx = NANDRAD::HydraulicNetworkHeatExchange(NANDRAD::HydraulicNetworkHeatExchange::ModelType(m_modelType));
	switch(m_modelType){
		case T_TemperatureConstant: {
			hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_Temperature] = m_para[P_Temperature];
			hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_ExternalHeatTransferCoefficient] = m_para[P_ExternalHeatTransferCoefficient];
			break;
		}
		case T_TemperatureSpline:
		case T_TemperatureSplineEvaporator: {
			hx.m_splPara[NANDRAD::HydraulicNetworkHeatExchange::SPL_Temperature] = m_splPara[SPL_Temperature];
			hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_ExternalHeatTransferCoefficient] = m_para[P_ExternalHeatTransferCoefficient];
			break;
		}
		case T_HeatLossConstant:
		case T_HeatLossConstantCondenser: {
			hx.m_para[NANDRAD::HydraulicNetworkHeatExchange::P_HeatLoss] = m_para[P_HeatLoss];
			break;
		}
		case T_HeatLossSpline:
		case T_HeatLossSplineCondenser: {
			hx.m_splPara[NANDRAD::HydraulicNetworkHeatExchange::SPL_HeatLoss] = m_splPara[SPL_HeatLoss];
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

} //namespace VICUS
