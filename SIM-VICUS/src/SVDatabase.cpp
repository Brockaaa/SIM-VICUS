﻿/*	SIM-VICUS - Building and District Energy Simulation Tool.

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

#include "SVDatabase.h"

#include <IBK_messages.h>
#include <IBK_FormatString.h>

#include <VICUS_KeywordList.h>

#include <QtExt_Directories.h>

#include "SVProjectHandler.h"

const unsigned int USER_ID_SPACE_START = 10000;


SVDatabase::SVDatabase() :
	m_materials(USER_ID_SPACE_START),
	m_constructions(2*USER_ID_SPACE_START),
	m_windows(3*USER_ID_SPACE_START),
	m_windowGlazingSystems(30*USER_ID_SPACE_START),
	m_boundaryConditions(4*USER_ID_SPACE_START),
	m_components(5*USER_ID_SPACE_START),
	m_subSurfaceComponents(16*USER_ID_SPACE_START),
	m_surfaceHeatings(35*USER_ID_SPACE_START),
	m_pipes(USER_ID_SPACE_START*100),
	m_fluids(USER_ID_SPACE_START*1001),
	m_networkComponents(USER_ID_SPACE_START*1002),
	m_networkControllers(USER_ID_SPACE_START*1003),
	m_subNetworks(USER_ID_SPACE_START*1004),
//	m_EPDElements(USER_ID_SPACE_START),
	m_schedules(6*USER_ID_SPACE_START),
	m_internalLoads(7*USER_ID_SPACE_START),
	m_zoneControlThermostat(11*USER_ID_SPACE_START),
	m_zoneControlShading(13*USER_ID_SPACE_START),
	m_zoneControlVentilationNatural(12*USER_ID_SPACE_START),
	m_zoneIdealHeatingCooling(20*USER_ID_SPACE_START),
	m_ventilationNatural(15*USER_ID_SPACE_START),
	m_infiltration(14*USER_ID_SPACE_START),
	m_zoneTemplates(8*USER_ID_SPACE_START)
{
}


void SVDatabase::readDatabases(DatabaseTypes t) {
	// built-in databases

	// built-in dbs are only read when no filter is applied (i.e. general initialization)
	if (t == NUM_DT) {
		IBK::Path dbDir(QtExt::Directories::databasesDir().toStdString());

		m_materials.readXML(				dbDir / "db_materials.xml", "Materials", "Material", true);
		m_constructions.readXML(			dbDir / "db_constructions.xml", "Constructions", "Construction", true);
		m_windows.readXML(					dbDir / "db_windows.xml", "Windows", "Window", true);
		m_windowGlazingSystems.readXML(		dbDir / "db_windowGlazingSystems.xml", "WindowGlazingSystems", "WindowGlazingSystem", true);
		m_boundaryConditions.readXML(		dbDir / "db_boundaryConditions.xml", "BoundaryConditions", "BoundaryCondition", true);
		m_components.readXML(				dbDir / "db_components.xml", "Components", "Component", true);
		m_subSurfaceComponents.readXML(		dbDir / "db_subSurfaceComponents.xml", "SubSurfaceComponents", "SubSurfaceComponent", true);
		m_surfaceHeatings.readXML(			dbDir / "db_surfaceHeatings.xml", "SurfaceHeatings", "SurfaceHeating", true);
		m_pipes.readXML(					dbDir / "db_pipes.xml", "NetworkPipes", "NetworkPipe", true);
		m_fluids.readXML(					dbDir / "db_fluids.xml", "NetworkFluids", "NetworkFluid", true);
		m_networkComponents.readXML(		dbDir / "db_networkComponents.xml", "NetworkComponents", "NetworkComponent", true);
		m_networkControllers.readXML(		dbDir / "db_networkControllers.xml", "NetworkControllers", "NetworkController", true);
		m_subNetworks.readXML		(		dbDir / "db_subNetworks.xml", "SubNetworks", "SubNetwork", true);
		m_schedules.readXML(				dbDir / "db_schedules.xml", "Schedules", "Schedule", true);
		m_internalLoads.readXML(			dbDir / "db_internalLoads.xml", "InternalLoads", "InternalLoad", true);
		m_zoneControlThermostat.readXML(	dbDir / "db_zoneControlThermostat.xml", "ZoneControlThermostats", "ZoneControlThermostat", true);
		m_zoneControlShading.readXML(		dbDir / "db_zoneControlShading.xml", "ZoneControlShadings", "ZoneControlShading", true);
		m_zoneControlVentilationNatural.readXML(	dbDir / "db_zoneControlVentilationNatural.xml", "ZoneControlVentilationNaturals", "ZoneControlVentilationNatural", true);
		m_zoneIdealHeatingCooling.readXML(	dbDir / "db_zoneIdealHeatingCooling.xml", "ZoneIdealHeatingCoolings", "ZoneIdealHeatingCooling", true);
		m_ventilationNatural.readXML(		dbDir / "db_ventilationNatural.xml", "VentilationNaturals", "VentilationNatural", true);
		m_infiltration.readXML(				dbDir / "db_infiltration.xml", "Infiltrations", "Infiltration", true);
		m_zoneTemplates.readXML(			dbDir / "db_zoneTemplates.xml", "ZoneTemplates", "ZoneTemplate", true);

	}

	// user databases

	IBK::Path userDbDir(QtExt::Directories::userDataDir().toStdString());

	// now read user databases - for dialogs which request reloading of an individual user DB, the parameter
	// t indicates which database to read. By default t is NUM_DT (at program start), which means: read all user DB files.
	if (t == NUM_DT || t == DT_Materials)
		m_materials.readXML(				userDbDir / "db_materials.xml", "Materials", "Material", false);
	if (t == NUM_DT || t == DT_Constructions)
		m_constructions.readXML(			userDbDir / "db_constructions.xml", "Constructions", "Construction", false);
	if (t == NUM_DT || t == DT_Windows)
		m_windows.readXML(					userDbDir / "db_windows.xml", "Windows", "Window", false);
	if (t == NUM_DT || t == DT_WindowGlazingSystems)
		m_windowGlazingSystems.readXML(		userDbDir / "db_windowGlazingSystems.xml", "WindowGlazingSystems", "WindowGlazingSystem", false);
	if (t == NUM_DT || t == DT_BoundaryConditions)
		m_boundaryConditions.readXML(		userDbDir / "db_boundaryConditions.xml", "BoundaryConditions", "BoundaryCondition", false);
	if (t == NUM_DT || t == DT_Components)
		m_components.readXML(				userDbDir / "db_components.xml", "Components", "Component", false);
	if (t == NUM_DT || t == DT_SubSurfaceComponents)
		m_subSurfaceComponents.readXML(		userDbDir / "db_subSurfaceComponents.xml", "SubSurfaceComponents", "SubSurfaceComponent", false);
	if (t == NUM_DT || t == DT_SurfaceHeating)
		m_surfaceHeatings.readXML(			userDbDir / "db_surfaceHeatings.xml", "SurfaceHeatings", "SurfaceHeating", false);
	if (t == NUM_DT || t == DT_Pipes)
		m_pipes.readXML(					userDbDir / "db_pipes.xml", "NetworkPipes", "NetworkPipe", false);
	if (t == NUM_DT || t == DT_Fluids)
		m_fluids.readXML(					userDbDir / "db_fluids.xml", "NetworkFluids", "NetworkFluid", false);
	if (t == NUM_DT || t == DT_NetworkComponents)
		m_networkComponents.readXML(		userDbDir / "db_networkComponents.xml", "NetworkComponents", "NetworkComponent", false);
	if (t == NUM_DT || t == DT_NetworkControllers)
		m_networkControllers.readXML(		userDbDir / "db_networkControllers.xml", "NetworkControllers", "NetworkController", false);
	if (t == NUM_DT || t == DT_SubNetworks)
		m_subNetworks.readXML(				userDbDir / "db_subNetworks.xml", "SubNetworks", "SubNetwork", false);
	if (t == NUM_DT || t == DT_Schedules)
		m_schedules.readXML(				userDbDir / "db_schedules.xml", "Schedules", "Schedule", false);
	if (t == NUM_DT || t == DT_InternalLoads)
		m_internalLoads.readXML(			userDbDir / "db_internalLoads.xml", "InternalLoads", "InternalLoad", false);
	if (t == NUM_DT || t == DT_ZoneControlThermostat)
		m_zoneControlThermostat.readXML(	userDbDir / "db_zoneControlThermostat.xml", "ZoneControlThermostats", "ZoneControlThermostat", false);
	if (t == NUM_DT || t == DT_ZoneControlShading)
		m_zoneControlShading.readXML(		userDbDir / "db_zoneControlShading.xml", "ZoneControlShadings", "ZoneControlShading", false);
	if (t == NUM_DT || t == DT_ZoneControlNaturalVentilation)
		m_zoneControlVentilationNatural.readXML(	userDbDir / "db_zoneControlVentilationNatural.xml", "ZoneControlVentilationNaturals", "ZoneControlVentilationNatural", false);
	if (t == NUM_DT || t == DT_ZoneIdealHeatingCooling)
		m_zoneIdealHeatingCooling.readXML(	userDbDir / "db_zoneIdealHeatingCooling.xml", "ZoneIdealHeatingCoolings", "ZoneIdealHeatingCooling", false);
	if (t == NUM_DT || t == DT_VentilationNatural)
		m_ventilationNatural.readXML(		userDbDir / "db_ventilationNatural.xml", "VentilationNaturals", "VentilationNatural", false);
	if (t == NUM_DT || t == DT_Infiltration)
		m_infiltration.readXML(				userDbDir / "db_infiltration.xml", "Infiltrations", "Infiltration", false);
	if (t == NUM_DT || t == DT_ZoneTemplates)
		m_zoneTemplates.readXML(			userDbDir / "db_zoneTemplates.xml", "ZoneTemplates", "ZoneTemplate", false);
}


void SVDatabase::writeDatabases() const {
	// we only write user databases

	IBK::Path userDbDir(QtExt::Directories::userDataDir().toStdString());

	m_materials.writeXML(			userDbDir / "db_materials.xml", "Materials");
	m_constructions.writeXML(		userDbDir / "db_constructions.xml", "Constructions");
	m_windows.writeXML(				userDbDir / "db_windows.xml", "Windows");
	m_windowGlazingSystems.writeXML(userDbDir / "db_windowGlazingSystems.xml", "WindowGlazingSystems");
	m_boundaryConditions.writeXML(	userDbDir / "db_boundaryConditions.xml", "BoundaryConditions");
	m_components.writeXML(			userDbDir / "db_components.xml", "Components");
	m_subSurfaceComponents.writeXML(userDbDir / "db_subSurfaceComponents.xml", "SubSurfaceComponents");
	m_surfaceHeatings.writeXML(		userDbDir / "db_surfaceHeatings.xml", "SurfaceHeatings");
	m_pipes.writeXML(				userDbDir / "db_pipes.xml", "NetworkPipes");
	m_fluids.writeXML(				userDbDir / "db_fluids.xml", "NetworkFluids");
	m_networkComponents.writeXML(	userDbDir / "db_networkComponents.xml", "NetworkComponents");
	m_networkControllers.writeXML(	userDbDir / "db_networkControllers.xml", "NetworkControllers");
	m_subNetworks.writeXML		(	userDbDir / "db_subNetworks.xml", "SubNetworks");
	m_schedules.writeXML(			userDbDir / "db_schedules.xml", "Schedules");
	m_internalLoads.writeXML(		userDbDir / "db_internalLoads.xml", "InternalLoads");
	m_zoneControlThermostat.writeXML(userDbDir / "db_zoneControlThermostat.xml", "ZoneControlThermostats");
	m_zoneControlShading.writeXML(	userDbDir / "db_zoneControlShading.xml", "ZoneControlShadings");
	m_zoneControlVentilationNatural.writeXML(userDbDir / "db_zoneControlVentilationNatural.xml", "ZoneControlVentilationNaturals");
	m_zoneIdealHeatingCooling.writeXML(	userDbDir / "db_zoneIdealHeatingCooling.xml", "ZoneIdealHeatingCoolings");
	m_ventilationNatural.writeXML(	userDbDir / "db_ventilationNatural.xml", "VentilationNaturals");
	m_infiltration.writeXML(		userDbDir / "db_infiltration.xml", "Infiltrations");
	m_zoneTemplates.writeXML(		userDbDir / "db_zoneTemplates.xml", "ZoneTemplates");
}

// Local sort operator, so sort AbstractDBElement vectors by m_id member
struct SortByID : public std::binary_function<VICUS::AbstractDBElement, VICUS::AbstractDBElement, bool> {
	bool operator()(VICUS::AbstractDBElement & x, VICUS::AbstractDBElement & y) const {
		return x.m_id < y.m_id;
	}

};


// Local utility function used to convert a set of items to a vector sorted by id
template <typename T>
void storeVector(std::vector<T> & vec, const std::set<const T*> & container) {
	// clear target vector
	vec.clear();
	// store objects but skip nullptr
	for (const T * c : container)
		if (c != nullptr) vec.push_back(*c);
	std::sort(vec.begin(), vec.end(), SortByID());
}


void SVDatabase::updateEmbeddedDatabase(VICUS::Project & p) {

	// create sets for objects that are referenced from other objects
	std::set<const VICUS::Material *>					referencedMaterials;
	std::set<const VICUS::Construction *>				referencedConstructions;
	std::set<const VICUS::Window *>						referencedWindows;
	std::set<const VICUS::WindowGlazingSystem *>		referencedGlazingSystems;
	std::set<const VICUS::BoundaryCondition *>			referencedBC;
	std::set<const VICUS::Component *>					referencedComponents;
	std::set<const VICUS::SubSurfaceComponent *>		referencedSubSurfaceComponents;
	std::set<const VICUS::SurfaceHeating *>				referencedSurfaceHeatings;

	std::set<const VICUS::NetworkPipe*>					referencedNetworkPipes;
	std::set<const VICUS::NetworkFluid *>				referencedNetworkFluids;
	std::set<const VICUS::NetworkComponent *>			referencedNetworkComponents;
	std::set<const VICUS::NetworkController *>			referencedNetworkControllers;
	std::set<const VICUS::SubNetwork *>					referencedSubNetworks;

	std::set<const VICUS::Schedule *>					referencedSchedule;
	std::set<const VICUS::InternalLoad *>				referencedInternalLoads;
	std::set<const VICUS::ZoneControlThermostat *>		referencedThermostats;
	std::set<const VICUS::ZoneControlShading *>			referencedControlShading;
	std::set<const VICUS::VentilationNatural *>			referencedVentilation;
	std::set<const VICUS::ZoneIdealHeatingCooling *> 	referencedIdealHeatingCooling;
	std::set<const VICUS::ZoneControlNaturalVentilation *>	referencedControlNaturalVentilation;
	std::set<const VICUS::Infiltration *>				referencedInfiltration;
	std::set<const VICUS::ZoneTemplate *>				referencedZoneTemplates;


	// we first collect all objects that are not referenced themselves
	// then, we collect objects that are referenced from an already collected object
	// this is continued until we have collected all objects that are used somewhere in the
	// project

	// Note: we lookup database elements by ID. If ID is INVALID_ID or if the database element
	//       is missing, the lookup call returns a nullptr. This may hence appear also in
	//       the referencedXXX vector. When later a referenced element is processed, we need
	//       to check for nullptr before de-referencing it.


	// *** ComponentInstance and Component ***
	for (const VICUS::ComponentInstance & ci : p.m_componentInstances) {
		const VICUS::Component * c = m_components[ci.m_idComponent];
		referencedSurfaceHeatings.insert(m_surfaceHeatings[ci.m_idSurfaceHeating]);
		if (c == nullptr) continue;

		referencedComponents.insert(c);
		referencedConstructions.insert(m_constructions[c->m_idConstruction]);
		referencedBC.insert(m_boundaryConditions[c->m_idSideABoundaryCondition]);
		referencedBC.insert(m_boundaryConditions[c->m_idSideBBoundaryCondition]);
	}

	// *** SubSurfaceComponentInstance, SubSurfaceComponent, Window and WindowGlazingSystems ***
	for (VICUS::SubSurfaceComponentInstance & ci : p.m_subSurfaceComponentInstances) {
		const VICUS::SubSurfaceComponent * c = m_subSurfaceComponents[ci.m_idSubSurfaceComponent];
		referencedSubSurfaceComponents.insert(c);
		if (c == nullptr) continue;

		referencedBC.insert(m_boundaryConditions[c->m_idSideABoundaryCondition]);
		referencedBC.insert(m_boundaryConditions[c->m_idSideBBoundaryCondition]);

		// collect referenced windows
		const VICUS::Window * w = m_windows[c->m_idWindow];
		if (w == nullptr) continue;

		referencedWindows.insert(w);
		referencedGlazingSystems.insert(m_windowGlazingSystems[w->m_idGlazingSystem]);
	}

	// *** SurfaceHeating and Pipes ***
	for (const VICUS::SurfaceHeating * sh : referencedSurfaceHeatings) {
		if (sh == nullptr) continue;
		referencedNetworkPipes.insert(m_pipes[sh->m_idPipe]);
	}

	// *** ZoneTemplate ***
	for (const VICUS::Building & b : p.m_buildings)
		for (const VICUS::BuildingLevel & bl : b.m_buildingLevels)
			for (const VICUS::Room &  r : bl.m_rooms)
				referencedZoneTemplates.insert(m_zoneTemplates[r.m_idZoneTemplate]);


	// *** Materials ***
	//
	// referenced from constructions and window (frame+divider)

	for (const VICUS::Construction * c : referencedConstructions) {
		if (c == nullptr) continue;
		for (const VICUS::MaterialLayer & ml : c->m_materialLayers)
			referencedMaterials.insert(m_materials[ml.m_idMaterial]);
	}
	for (const VICUS::Window * c : referencedWindows) {
		if (c == nullptr) continue;
		referencedMaterials.insert(m_materials[c->m_frame.m_idMaterial]);
		referencedMaterials.insert(m_materials[c->m_divider.m_idMaterial]);
	}


	// *** everything that is referenced from zone templates

	for (const VICUS::ZoneTemplate * zt : referencedZoneTemplates) {
		if(zt == nullptr)
			continue;
		for (unsigned int i=0; i<VICUS::ZoneTemplate::NUM_ST; ++i) {
			IDType idType = zt->m_idReferences[i];
			const VICUS::InternalLoad *intLoad = m_internalLoads[idType];
			const VICUS::ZoneControlThermostat * thermo = m_zoneControlThermostat[idType];
			const VICUS::ZoneIdealHeatingCooling * idealHeatCool = m_zoneIdealHeatingCooling[idType];
			const VICUS::Infiltration *inf = m_infiltration[idType];
			const VICUS::VentilationNatural *ventiNat = m_ventilationNatural[idType];
			if (intLoad	!= nullptr) {
				referencedInternalLoads.insert(intLoad);
				VICUS::ZoneTemplate::SubTemplateType tempType = (VICUS::ZoneTemplate::SubTemplateType)i;
				switch (tempType) {
					case VICUS::ZoneTemplate::ST_IntLoadPerson:
						referencedSchedule.insert(m_schedules[intLoad->m_idActivitySchedule]);
						referencedSchedule.insert(m_schedules[intLoad->m_idOccupancySchedule]);
					break;

					case VICUS::ZoneTemplate::ST_IntLoadEquipment:
					case VICUS::ZoneTemplate::ST_IntLoadLighting:
					case VICUS::ZoneTemplate::ST_IntLoadOther:
						referencedSchedule.insert(m_schedules[intLoad->m_idPowerManagementSchedule]);
					break;

					case VICUS::ZoneTemplate::ST_ControlThermostat:
					case VICUS::ZoneTemplate::ST_ControlNaturalVentilation:
					case VICUS::ZoneTemplate::ST_Infiltration:
					case VICUS::ZoneTemplate::ST_VentilationNatural:
					case VICUS::ZoneTemplate::ST_IdealHeatingCooling:
					case VICUS::ZoneTemplate::NUM_ST:
					break;
				}
			}
			else if(thermo != nullptr) {
				referencedThermostats.insert(thermo);

				referencedSchedule.insert(m_schedules[thermo->m_idHeatingSetpointSchedule]);
				referencedSchedule.insert(m_schedules[thermo->m_idCoolingSetpointSchedule]);
			}
			else if (inf != nullptr) {
				referencedInfiltration.insert(inf);
			}
			else if (ventiNat != nullptr) {
				referencedVentilation.insert(ventiNat);
				referencedSchedule.insert(m_schedules[ventiNat->m_idSchedule]);
			}
			else if(idealHeatCool != nullptr)
				referencedIdealHeatingCooling.insert(idealHeatCool);
		}
	}


	// iterate through networks
	for (const VICUS::Network &net: p.m_geometricNetworks){

		// fluids
		referencedNetworkFluids.insert(m_fluids[net.m_idFluid]);

		// pipes
		for (const VICUS::NetworkEdge &edge: net.m_edges)
			referencedNetworkPipes.insert(m_pipes[edge.m_idPipe]);

		// sub networks
		for (const VICUS::NetworkNode &node: net.m_nodes)
			referencedSubNetworks.insert(m_subNetworks[node.m_idSubNetwork]);
	}

	// iterate through collected sub networks
	for (const VICUS::SubNetwork *sub: referencedSubNetworks) {
		if (sub == nullptr) continue;

		// components and controllers referenced from elements
		for (const NANDRAD::HydraulicNetworkElement &el: sub->m_elements) {
			referencedNetworkComponents.insert(m_networkComponents[el.m_componentId]);
			referencedNetworkControllers.insert(m_networkControllers[el.m_controlElementId]);
		}
	}

	// iterate through components
	for (const VICUS::NetworkComponent *comp: referencedNetworkComponents) {
		if (comp == nullptr) continue;

		// schedules
		for (unsigned int i: comp->m_scheduleIds)
			referencedSchedule.insert(m_schedules[i]);
	}


	// *** transfer collected objects to project's embedded database ***

	storeVector(p.m_embeddedDB.m_materials, referencedMaterials);
	storeVector(p.m_embeddedDB.m_constructions, referencedConstructions);
	storeVector(p.m_embeddedDB.m_windows, referencedWindows);
	storeVector(p.m_embeddedDB.m_windowGlazingSystems, referencedGlazingSystems);
	storeVector(p.m_embeddedDB.m_boundaryConditions, referencedBC);
	storeVector(p.m_embeddedDB.m_components, referencedComponents);
	storeVector(p.m_embeddedDB.m_subSurfaceComponents, referencedSubSurfaceComponents);
	storeVector(p.m_embeddedDB.m_surfaceHeatings, referencedSurfaceHeatings);

	storeVector(p.m_embeddedDB.m_pipes, referencedNetworkPipes);
	storeVector(p.m_embeddedDB.m_fluids, referencedNetworkFluids);
	storeVector(p.m_embeddedDB.m_networkComponents, referencedNetworkComponents);
	storeVector(p.m_embeddedDB.m_networkControllers, referencedNetworkControllers);
	storeVector(p.m_embeddedDB.m_subNetworks, referencedSubNetworks);

	storeVector(p.m_embeddedDB.m_schedules, referencedSchedule);
	storeVector(p.m_embeddedDB.m_internalLoads, referencedInternalLoads);
	storeVector(p.m_embeddedDB.m_zoneControlThermostats, referencedThermostats);
	storeVector(p.m_embeddedDB.m_zoneControlShading, referencedControlShading);
	storeVector(p.m_embeddedDB.m_zoneControlVentilationNatural, referencedControlNaturalVentilation);
	storeVector(p.m_embeddedDB.m_zoneIdealHeatingCooling, referencedIdealHeatingCooling);
	storeVector(p.m_embeddedDB.m_ventilationNatural, referencedVentilation);
	storeVector(p.m_embeddedDB.m_infiltration, referencedInfiltration);
	storeVector(p.m_embeddedDB.m_zoneTemplates, referencedZoneTemplates);
}

// local search function to identify duplicates in DBs
template <typename T>
void findDublicates(const VICUS::Database<T> & db, std::vector<SVDatabase::DuplicateInfo> & dupInfos) {
	std::set<unsigned int> duplicateIDs; // stores all IDs of all already found duplicates
	// process all database elements
	for (typename std::map<unsigned int, T>::const_iterator it = db.begin(); it != db.end(); ++it) {
		// skip elements already marked as duplicates
		if (duplicateIDs.find(it->first) != duplicateIDs.end() ) continue;

		// process all other elements
		for (typename std::map<unsigned int, T>::const_iterator it2 = db.begin(); it2 != db.end(); ++it2) {
			// skip ourselves
			if (it->first == it2->first) continue;
			// skip elements already marked as duplicates
			if (duplicateIDs.find(it2->first) != duplicateIDs.end() ) continue;

			// are we sufficiently similar
			VICUS::AbstractDBElement::ComparisonResult compRes = it->second.equal(&it2->second);
			if (compRes != VICUS::AbstractDBElement::Different) {
				SVDatabase::DuplicateInfo info;
				info.m_idFirst = it->first;
				info.m_idSecond = it2->first;
				info.m_identical = (compRes == VICUS::AbstractDBElement::Equal);
				dupInfos.push_back(info);
				duplicateIDs.insert(it->first);
				duplicateIDs.insert(it2->first);
				break;
			}
		}
	}
}



void SVDatabase::determineDuplicates(std::vector<std::vector<SVDatabase::DuplicateInfo> > & duplicatePairs) const {

	// process all databases and search for duplicates
	findDublicates(m_materials, duplicatePairs[DT_Materials]);
	findDublicates(m_constructions, duplicatePairs[DT_Constructions]);
	findDublicates(m_windows, duplicatePairs[DT_Windows]);
	findDublicates(m_windowGlazingSystems, duplicatePairs[DT_WindowGlazingSystems]);
	findDublicates(m_boundaryConditions, duplicatePairs[DT_BoundaryConditions]);
	findDublicates(m_components, duplicatePairs[DT_Components]);
	findDublicates(m_subSurfaceComponents, duplicatePairs[DT_SubSurfaceComponents]);
	findDublicates(m_surfaceHeatings, duplicatePairs[DT_SurfaceHeating]);
	findDublicates(m_pipes, duplicatePairs[DT_Pipes]);
	findDublicates(m_fluids, duplicatePairs[DT_Fluids]);
	findDublicates(m_networkComponents, duplicatePairs[DT_NetworkComponents]);
	findDublicates(m_networkControllers, duplicatePairs[DT_NetworkControllers]);
	findDublicates(m_subNetworks, duplicatePairs[DT_SubNetworks]);
	findDublicates(m_schedules, duplicatePairs[DT_Schedules]);
	findDublicates(m_internalLoads, duplicatePairs[DT_InternalLoads]);
	findDublicates(m_zoneControlThermostat, duplicatePairs[DT_ZoneControlThermostat]);
	findDublicates(m_zoneControlShading, duplicatePairs[DT_ZoneControlShading]);
	findDublicates(m_zoneControlVentilationNatural, duplicatePairs[DT_ZoneControlNaturalVentilation]);
	findDublicates(m_zoneIdealHeatingCooling, duplicatePairs[DT_ZoneIdealHeatingCooling]);
	findDublicates(m_ventilationNatural, duplicatePairs[DT_VentilationNatural]);
	findDublicates(m_infiltration, duplicatePairs[DT_Infiltration]);
	findDublicates(m_zoneTemplates, duplicatePairs[DT_Materials]);
}


// local convenience function to substitute IDs and mark the respective DB as modified
template <typename T>
void replaceID(unsigned int oldID, unsigned int newId, unsigned int & idVar, T & db) {
	if (idVar == oldID) {
		idVar = newId;
		db.m_modified = true;
	}
}

void SVDatabase::removeDBElement(SVDatabase::DatabaseTypes dbType, unsigned int elementID, unsigned int replacementElementID) {
	// depending on database type, we need to replace references to the element on other dbs as well
	// Note: if we have a project, also replace directly referenced DB elements in project
	//       - Components
	//       - SubSurfaceComponents
	//       - ZoneTemplate
	//       - NetworkPipes
	//       - NetworkFluid
	//       - NetworkComponent
	//       - SubNetwork

	switch (dbType) {

		case DT_Materials : {
			// materials are used in construction layers, window frame and divider
			// replace mat ID everywhere
			for (const auto & p : m_constructions) {
				VICUS::Construction & con = const_cast<VICUS::Construction &>(p.second); // const-cast is ok here
				for (VICUS::MaterialLayer & ml : con.m_materialLayers)
					replaceID(elementID, replacementElementID, ml.m_idMaterial, m_constructions);
			}
			for (const auto & p : m_windows) {
				VICUS::Window & w = const_cast<VICUS::Window&>(p.second); // const-cast is ok here
				replaceID(elementID, replacementElementID, w.m_frame.m_idMaterial, m_windows);
				replaceID(elementID, replacementElementID, w.m_divider.m_idMaterial, m_windows);
			}
			// finally remove material
			m_materials.remove(elementID);
			m_materials.m_modified = true;
		} break;

		case DT_Constructions : {
			for (const auto & p : m_components) {
				VICUS::Component & c = const_cast<VICUS::Component &>(p.second); // const-cast is ok here
				replaceID(elementID, replacementElementID, c.m_idConstruction, m_components);
			}
			for (const auto & p : m_subSurfaceComponents) {
				VICUS::SubSurfaceComponent & c = const_cast<VICUS::SubSurfaceComponent &>(p.second); // const-cast is ok here
				replaceID(elementID, replacementElementID, c.m_idConstruction, m_subSurfaceComponents);
			}
			m_constructions.remove(elementID);
			m_constructions.m_modified = true;
		} break;

		case SVDatabase::DT_Windows:
			for (const auto & p : m_subSurfaceComponents) {
				VICUS::SubSurfaceComponent & c = const_cast<VICUS::SubSurfaceComponent &>(p.second); // const-cast is ok here
				replaceID(elementID, replacementElementID, c.m_idWindow, m_subSurfaceComponents);
			}
			m_windows.remove(elementID);
			m_windows.m_modified = true;
		break;

		case SVDatabase::DT_WindowGlazingSystems:
			for (const auto & p : m_windows) {
				VICUS::Window & c = const_cast<VICUS::Window &>(p.second); // const-cast is ok here
				replaceID(elementID, replacementElementID, c.m_idGlazingSystem, m_windows);
			}
			m_windowGlazingSystems.remove(elementID);
			m_windowGlazingSystems.m_modified = true;
		break;

		case SVDatabase::DT_BoundaryConditions:
			for (const auto & p : m_components) {
				VICUS::Component & c = const_cast<VICUS::Component &>(p.second); // const-cast is ok here
				replaceID(elementID, replacementElementID, c.m_idSideABoundaryCondition, m_components);
				replaceID(elementID, replacementElementID, c.m_idSideBBoundaryCondition, m_components);
			}
			for (const auto & p : m_subSurfaceComponents) {
				VICUS::SubSurfaceComponent & c = const_cast<VICUS::SubSurfaceComponent &>(p.second); // const-cast is ok here
				replaceID(elementID, replacementElementID, c.m_idSideABoundaryCondition, m_subSurfaceComponents);
				replaceID(elementID, replacementElementID, c.m_idSideBBoundaryCondition, m_subSurfaceComponents);
			}
			m_boundaryConditions.remove(elementID);
			m_boundaryConditions.m_modified = true;
		break;

		case SVDatabase::DT_Components:
			// components are referenced from project
			if (SVProjectHandler::instance().isValid()) {
				for (const auto & p : project().m_componentInstances) {
					VICUS::ComponentInstance & c = const_cast<VICUS::ComponentInstance &>(p); // const-cast is ok here
					if (c.m_idComponent == elementID)
						c.m_idComponent = replacementElementID;
				}
			}
			m_components.remove(elementID);
			m_components.m_modified = true;
		break;

		case SVDatabase::DT_SubSurfaceComponents:
			// components are referenced from project
			if (SVProjectHandler::instance().isValid()) {
				for (const auto & p : project().m_subSurfaceComponentInstances) {
					VICUS::SubSurfaceComponentInstance & c = const_cast<VICUS::SubSurfaceComponentInstance &>(p); // const-cast is ok here
					if (c.m_idSubSurfaceComponent == elementID)
						c.m_idSubSurfaceComponent = replacementElementID;
				}
			}
			m_subSurfaceComponents.remove(elementID);
			m_subSurfaceComponents.m_modified = true;
		break;

		case SVDatabase::DT_SurfaceHeating:
		break;
		case SVDatabase::DT_Pipes:
		break;
		case SVDatabase::DT_Fluids:
		break;
		case SVDatabase::DT_NetworkComponents:
		break;
		case SVDatabase::DT_NetworkControllers:
		break;
		case SVDatabase::DT_SubNetworks:
		break;
		case SVDatabase::DT_Schedules:
		break;
		case SVDatabase::DT_InternalLoads:
		break;
		case SVDatabase::DT_ZoneControlThermostat:
		break;
		case SVDatabase::DT_ZoneControlShading:
		break;
		case SVDatabase::DT_ZoneControlNaturalVentilation:
		break;
		case SVDatabase::DT_ZoneIdealHeatingCooling:
		break;
		case SVDatabase::DT_VentilationNatural:
		break;
		case SVDatabase::DT_Infiltration:
		break;
		case SVDatabase::DT_ZoneTemplates:
		break;
		case SVDatabase::NUM_DT: ; // just to make compiler happy
	}

}


