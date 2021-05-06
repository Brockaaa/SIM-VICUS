/*	NANDRAD Solver Framework and Model Implementation.

	Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Anne Paepcke     <anne.paepcke -[at]- tu-dresden.de>

	This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
*/

#ifndef NM_ThermalNetworkStatesModelH
#define NM_ThermalNetworkStatesModelH

#include "NM_AbstractModel.h"


namespace NANDRAD {
	class HydraulicNetwork;
	class HydraulicNetworkComponent;
	class SimulationParameter;
}


namespace NANDRAD_MODEL {


class HydraulicNetworkModel;
class ThermalNetworkModelImpl;

/*!	A model that computes all temperature states of hydraulic network given the internal energy density

	The following results are provided:

	ModelReferenceType = MRT_NETWORKELEMENT
	id = (id of flow element)
	Quantity = FluidTemperature  (in [K])
*/
class ThermalNetworkStatesModel : public AbstractModel {
public:

	/*! Constructor. */
	ThermalNetworkStatesModel(unsigned int id, const std::string &displayName) :
		m_id(id), m_displayName(displayName), m_n(0)
	{
	}

	/*! D'tor, released pimpl object. */
	~ThermalNetworkStatesModel() override;

	/*! Initializes model. */
	void setup(const NANDRAD::HydraulicNetwork & nw,
			   const HydraulicNetworkModel &networkModel,
			   const NANDRAD::SimulationParameter &simPara);

	// *** Re-implemented from AbstractModel

	/*! Network model is referenced via Network and ID. */
	virtual NANDRAD::ModelInputReference::referenceType_t referenceType() const override {
		return NANDRAD::ModelInputReference::MRT_NETWORK;
	}

	/*! Return unique class ID name of implemented model. */
	virtual const char * ModelIDName() const override { return "ThermalNetworkStatesModel"; }

	/*! Returns unique ID of this model instance. */
	virtual unsigned int id() const override { return m_id; }

	/*! Returns display name of this model instance. */
	virtual const char * displayName() const override { return m_displayName.c_str(); }

	/*! Populates the vector resDesc with descriptions of all results provided by this model. */
	virtual void resultDescriptions(std::vector<QuantityDescription> & resDesc) const override;

	/*! Retrieves reference pointer to a value with given quantity ID name.
		\note Quantity name of "y" returns pointer to start of local y data vector.
		\return Returns pointer to memory location with this quantity, otherwise nullptr if parameter ID was not found.
	*/
	virtual const double * resultValueRef(const InputReference & quantity) const override;

	// *** Other public member functions

	/*! Returns number of conserved variables (i.e. length of y vector passed to yInitial() and update() ). */
	unsigned int nPrimaryStateResults() const { return m_n; }

	/*! Returns a vector of dependencies of all result quantities from y input quantities). */
	void stateDependencies(std::vector< std::pair<const double *, const double *> > & resultInputValueReferences) const;

	/*! Sets initial states in y vector.
		This function is called after setup(), so that parameters needed for
		computing the initial condition are already present.

		\param Pointer to the memory array holding all initial states for this network model (to be written into).
	*/
	void yInitial(double * y);

	/*! Passes states to flow element models and computes mean fluid temperature.
		This function is called directly from NandradModel as first step in the model evaluation.

		\param Pointer to the memory array holding all states for this room model.
			   The vector has either size 1 for thermal calculations or size 2 for hygrothermal calculations.
	*/
	int update(const double * y);

private:

	/*! Network ID. */
	unsigned int									m_id;
	/*! Display name (for error messages). */
	std::string										m_displayName;

	/*! Total number of unknowns. */
	unsigned int									m_n;
	/*! Cached input data vector (size m_n == nPrimaryStateResults()). */
	std::vector<double>								m_y;

	/*! Storage of all network element ids, used for vector output. */
	std::vector<unsigned int>						m_elementIds;

	/*! Vector with references to mean fluid temperatures (size = m_elementIds.size()).
		Result quantity of current model, published as 'FluidTemperature' result for each flow element. */
	std::vector<const double*>						m_meanTemperatureRefs;

	/*! Pointer to NANDRAD network structure*/
	const NANDRAD::HydraulicNetwork					*m_network=nullptr;

	/*! Private implementation (Pimpl) of the network solver. */
	ThermalNetworkModelImpl							*m_p = nullptr;


	friend class ThermalNetworkBalanceModel;
};

} // namespace NANDRAD_MODEL

#endif // NM_ThermalNetworkStatesModelH
