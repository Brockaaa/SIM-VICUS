# -------------------------------------------------
# Project for Nandrad library
# -------------------------------------------------
TARGET = Nandrad
TEMPLATE = lib

# this pri must be sourced from all our libraries,
# it contains all functions defined for casual libraries
include( ../../../IBK/projects/Qt/IBK.pri )

unix|mac {
	VER_MAJ = 2
	VER_MIN = 0
	VER_PAT = 0
	VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}
}

LIBS += -lIBK -lTiCPP

INCLUDEPATH = \
	../../src \
	../../../IBK/src \
	../../../IBKMK/src \
	../../../TiCPP/src

DEPENDPATH = $${INCLUDEPATH}

HEADERS += \
	../../src/NANDRAD_ArgsParser.h \
	../../src/NANDRAD_CodeGenMacros.h \
	../../src/NANDRAD_Constants.h \
	../../src/NANDRAD_ConstructionInstance.h \
	../../src/NANDRAD_ConstructionType.h \
	../../src/NANDRAD_DailyCycle.h \
	../../src/NANDRAD_DataTable.h \
	../../src/NANDRAD_EmbeddedObject.h \
	../../src/NANDRAD_EmbeddedObjectWindow.h \
	../../src/NANDRAD_FMIDescription.h \
	../../src/NANDRAD_FMIVariableDefinition.h \
	../../src/NANDRAD_HVACControlModel.h \
	../../src/NANDRAD_HydraulicFluid.h \
	../../src/NANDRAD_HydraulicNetworkComponent.h \
	../../src/NANDRAD_HydraulicNetworkControlElement.h \
	../../src/NANDRAD_HydraulicNetworkElement.h \
	../../src/NANDRAD_HydraulicNetwork.h \
	../../src/NANDRAD_HydraulicNetworkHeatExchange.h \
	../../src/NANDRAD_HydraulicNetworkPipeProperties.h \
	../../src/NANDRAD_IdealHeatingCoolingModel.h \
	../../src/NANDRAD_IdealPipeRegisterModel.h \
	../../src/NANDRAD_IdealSurfaceHeatingModel.h \
	../../src/NANDRAD_IDGroup.h \
	../../src/NANDRAD_InterfaceAirFlow.h \
	../../src/NANDRAD_Interface.h \
	../../src/NANDRAD_InterfaceHeatConduction.h \
	../../src/NANDRAD_InterfaceLongWaveEmission.h \
	../../src/NANDRAD_InterfaceSolarAbsorption.h \
	../../src/NANDRAD_InterfaceVaporDiffusion.h \
	../../src/NANDRAD_InternalLoadsModel.h \
	../../src/NANDRAD_Interval.h \
	../../src/NANDRAD_KeywordList.h \
	../../src/NANDRAD_LinearSplineParameter.h \
	../../src/NANDRAD_Location.h \
	../../src/NANDRAD_Material.h \
	../../src/NANDRAD_MaterialLayer.h \
	../../src/NANDRAD_ModelInputReference.h \
	../../src/NANDRAD_Models.h \
	../../src/NANDRAD_NaturalVentilationModel.h \
	../../src/NANDRAD_ObjectList.h \
	../../src/NANDRAD_OutputDefinition.h \
	../../src/NANDRAD_OutputGrid.h \
	../../src/NANDRAD_Outputs.h \
	../../src/NANDRAD_Project.h \
	../../src/NANDRAD_ProjectInfo.h \
	../../src/NANDRAD_Schedule.h \
	../../src/NANDRAD_Schedules.h \
	../../src/NANDRAD_Sensor.h \
	../../src/NANDRAD_SerializationTest.h \
	../../src/NANDRAD_ShadingControlModel.h \
	../../src/NANDRAD_SimulationParameter.h \
	../../src/NANDRAD_SolarLoadsDistributionModel.h \
	../../src/NANDRAD_SolverParameter.h \
	../../src/NANDRAD_Thermostat.h \
	../../src/NANDRAD_Utilities.h \
	../../src/NANDRAD_WindowDivider.h \
	../../src/NANDRAD_WindowFrame.h \
	../../src/NANDRAD_WindowGlazingLayer.h \
	../../src/NANDRAD_WindowGlazingSystem.h \
	../../src/NANDRAD_WindowShading.h \
	../../src/NANDRAD_Zone.h

SOURCES += \
	../../src/NANDRAD_ArgsParser.cpp \
	../../src/NANDRAD_Constants.cpp \
	../../src/NANDRAD_ConstructionInstance.cpp \
	../../src/NANDRAD_ConstructionType.cpp \
	../../src/NANDRAD_DailyCycle.cpp \
	../../src/NANDRAD_DataTable.cpp \
	../../src/NANDRAD_EmbeddedObject.cpp \
	../../src/NANDRAD_EmbeddedObjectWindow.cpp \
	../../src/NANDRAD_FMIDescription.cpp \
	../../src/NANDRAD_FMIVariableDefinition.cpp \
	../../src/NANDRAD_HVACControlModel.cpp \
	../../src/NANDRAD_HydraulicFluid.cpp \
	../../src/NANDRAD_HydraulicNetworkComponent.cpp \
	../../src/NANDRAD_HydraulicNetwork.cpp \
	../../src/NANDRAD_HydraulicNetworkControlElement.cpp \
	../../src/NANDRAD_HydraulicNetworkElement.cpp \
	../../src/NANDRAD_HydraulicNetworkHeatExchange.cpp \
	../../src/NANDRAD_HydraulicNetworkPipeProperties.cpp \
	../../src/NANDRAD_IdealHeatingCoolingModel.cpp \
	../../src/NANDRAD_IdealPipeRegisterModel.cpp \
	../../src/NANDRAD_IdealSurfaceHeatingModel.cpp \
	../../src/NANDRAD_IDGroup.cpp \
	../../src/NANDRAD_InterfaceAirFlow.cpp \
	../../src/NANDRAD_Interface.cpp \
	../../src/NANDRAD_InterfaceHeatConduction.cpp \
	../../src/NANDRAD_InterfaceLongWaveEmission.cpp \
	../../src/NANDRAD_InterfaceSolarAbsorption.cpp \
	../../src/NANDRAD_InterfaceVaporDiffusion.cpp \
	../../src/NANDRAD_InternalLoadsModel.cpp \
	../../src/NANDRAD_Interval.cpp \
	../../src/NANDRAD_KeywordList.cpp \
	../../src/NANDRAD_LinearSplineParameter.cpp \
	../../src/NANDRAD_Material.cpp \
	../../src/NANDRAD_Models.cpp \
	../../src/NANDRAD_NaturalVentilationModel.cpp \
	../../src/NANDRAD_ObjectList.cpp \
	../../src/NANDRAD_OutputDefinition.cpp \
	../../src/NANDRAD_OutputGrid.cpp \
	../../src/NANDRAD_Outputs.cpp \
	../../src/NANDRAD_Project.cpp \
	../../src/NANDRAD_Schedule.cpp \
	../../src/NANDRAD_Schedules.cpp \
	../../src/NANDRAD_Sensor.cpp \
	../../src/NANDRAD_ShadingControlModel.cpp \
	../../src/NANDRAD_SimulationParameter.cpp \
	../../src/NANDRAD_SolarLoadsDistributionModel.cpp \
	../../src/NANDRAD_SolverParameter.cpp \
	../../src/NANDRAD_Thermostat.cpp \
	../../src/NANDRAD_Utilities.cpp \
	../../src/NANDRAD_WindowGlazingSystem.cpp \
	../../src/NANDRAD_WindowShading.cpp \
	../../src/ncg/ncg_NANDRAD_ConstructionInstance.cpp \
	../../src/ncg/ncg_NANDRAD_ConstructionType.cpp \
	../../src/ncg/ncg_NANDRAD_DailyCycle.cpp \
	../../src/ncg/ncg_NANDRAD_EmbeddedObject.cpp \
	../../src/ncg/ncg_NANDRAD_EmbeddedObjectWindow.cpp \
	../../src/ncg/ncg_NANDRAD_FMIDescription.cpp \
	../../src/ncg/ncg_NANDRAD_FMIVariableDefinition.cpp \
	../../src/ncg/ncg_NANDRAD_HVACControlModel.cpp \
	../../src/ncg/ncg_NANDRAD_HydraulicFluid.cpp \
	../../src/ncg/ncg_NANDRAD_HydraulicNetworkComponent.cpp \
	../../src/ncg/ncg_NANDRAD_HydraulicNetwork.cpp \
	../../src/ncg/ncg_NANDRAD_HydraulicNetworkControlElement.cpp \
	../../src/ncg/ncg_NANDRAD_HydraulicNetworkElement.cpp \
	../../src/ncg/ncg_NANDRAD_HydraulicNetworkHeatExchange.cpp \
	../../src/ncg/ncg_NANDRAD_HydraulicNetworkPipeProperties.cpp \
	../../src/ncg/ncg_NANDRAD_IdealHeatingCoolingModel.cpp \
	../../src/ncg/ncg_NANDRAD_IdealPipeRegisterModel.cpp \
	../../src/ncg/ncg_NANDRAD_IdealSurfaceHeatingModel.cpp \
	../../src/ncg/ncg_NANDRAD_InterfaceAirFlow.cpp \
	../../src/ncg/ncg_NANDRAD_Interface.cpp \
	../../src/ncg/ncg_NANDRAD_InterfaceHeatConduction.cpp \
	../../src/ncg/ncg_NANDRAD_InterfaceLongWaveEmission.cpp \
	../../src/ncg/ncg_NANDRAD_InterfaceSolarAbsorption.cpp \
	../../src/ncg/ncg_NANDRAD_InterfaceVaporDiffusion.cpp \
	../../src/ncg/ncg_NANDRAD_InternalLoadsModel.cpp \
	../../src/ncg/ncg_NANDRAD_Interval.cpp \
	../../src/ncg/ncg_NANDRAD_Location.cpp \
	../../src/ncg/ncg_NANDRAD_Material.cpp \
	../../src/ncg/ncg_NANDRAD_MaterialLayer.cpp \
	../../src/ncg/ncg_NANDRAD_Models.cpp \
	../../src/ncg/ncg_NANDRAD_NaturalVentilationModel.cpp \
	../../src/ncg/ncg_NANDRAD_ObjectList.cpp \
	../../src/ncg/ncg_NANDRAD_OutputDefinition.cpp \
	../../src/ncg/ncg_NANDRAD_OutputGrid.cpp \
	../../src/ncg/ncg_NANDRAD_Outputs.cpp \
	../../src/ncg/ncg_NANDRAD_Project.cpp \
	../../src/ncg/ncg_NANDRAD_ProjectInfo.cpp \
	../../src/ncg/ncg_NANDRAD_Schedule.cpp \
	../../src/ncg/ncg_NANDRAD_Sensor.cpp \
	../../src/ncg/ncg_NANDRAD_SerializationTest.cpp \
	../../src/ncg/ncg_NANDRAD_ShadingControlModel.cpp \
	../../src/ncg/ncg_NANDRAD_SimulationParameter.cpp \
	../../src/ncg/ncg_NANDRAD_SolarLoadsDistributionModel.cpp \
	../../src/ncg/ncg_NANDRAD_SolverParameter.cpp \
	../../src/ncg/ncg_NANDRAD_Thermostat.cpp \
	../../src/ncg/ncg_NANDRAD_WindowDivider.cpp \
	../../src/ncg/ncg_NANDRAD_WindowFrame.cpp \
	../../src/ncg/ncg_NANDRAD_WindowGlazingLayer.cpp \
	../../src/ncg/ncg_NANDRAD_WindowGlazingSystem.cpp \
	../../src/ncg/ncg_NANDRAD_WindowShading.cpp \
	../../src/ncg/ncg_NANDRAD_Zone.cpp



