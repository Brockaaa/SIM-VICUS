#ifndef VICUS_NETWORKCONTROLLER_H
#define VICUS_NETWORKCONTROLLER_H

#include "VICUS_AbstractDBElement.h"
#include "VICUS_CodeGenMacros.h"
#include "VICUS_Constants.h"
#include "VICUS_Database.h"
#include "VICUS_Schedule.h"

#include <NANDRAD_HydraulicNetworkControlElement.h>

#include <QColor>


namespace VICUS {

/*! This class is a copy of NANDRAD::HydraulicNetworkControlElement with some added members, methods
 * to make it usable as a class for the VICUS Database.
 * NOTE: Other options like deriving it from the base class doesnt really bring a benefit since we need
 * all the declarations for the code generator anyway.
 * Also making a child element of type NANDRAD::HydraulicNetworkControlElement does not work, since we want to have
 * uniform member names like 'm_id' and 'm_displayName' for the DB read/write process with template functions
 * This this should be the best solution ...
 */

class NetworkController: public AbstractDBElement {

public:
	NetworkController();

	/*! Defines variability options for set point values. */
	enum ModelType {
		MT_Constant,					// Keyword: Constant				'Set points are given as constant parameters'
		/*! Generates 'TemperatureDifferenceSetpointSchedule' or 'MassFluxSetpointSchedule' depending on
			controlled property for each network element that uses this controller.
			InputRef-Typ: NetworkElement, id = id of network element that uses the component with this controller
		*/
		MT_Scheduled,					// Keyword: Scheduled				'Scheduled set point values'
		NUM_MT
	};

	/*! Controlled property used as signal input for the controller. */
	enum ControlledProperty {
		/*! Temperature difference is computed from pre-defined heat loss and compared against target temperature difference. */
		CP_TemperatureDifference,						// Keyword: TemperatureDifference						'Control temperature difference of this element '
		/*! Temperature difference of the following flow element is computed from outlet temperature of this element and outlet temperature of the following element.
			This temperature difference is compared against target temperature difference. */
		CP_TemperatureDifferenceOfFollowingElement,		// Keyword: TemperatureDifferenceOfFollowingElement		'Control temperature difference of the following element'
		/*! Thermostat heating/cooling control values determine whether valve is open or closed. */
		CP_ThermostatValue,								// Keyword: ThermostatValue								'Control zone thermostat values'
		/*! Try to achieve target mass flow in current element. */
		CP_MassFlux,									// Keyword: MassFlux									'Control mass flux'
		NUM_CP
	};

	/*! Different model variants. */
	enum ControllerType {
		CT_PController,			// Keyword: PController				'PController'
		CT_PIController,		// Keyword: PIController			'PIController'
		NUM_CT
	};

	/*! Model parameters. */
	enum para_t {
		P_Kp,								// Keyword: Kp								[---]	'Kp-parameter'
		P_Ki,								// Keyword: Ki								[---]	'Ki-parameter'
		P_Kd,								// Keyword: Kd								[---]	'Kd-parameter'
		P_TemperatureDifferenceSetpoint,	// Keyword: TemperatureDifferenceSetpoint	[K]		'Target temperature difference'
		P_MassFluxSetpoint,					// Keyword: MassFluxSetpoint				[kg/s]	'Target mass flux'
		NUM_P
	};

	/*! Integer/whole number parameters. */
	enum References {
		/*! Id of zone whose thermostat is used for control: only for controlled property 'ThermostatValue'. */
		ID_ThermostatZoneId,				// Keyword: ThermostatZoneId				[-]		'ID of zone containing thermostat'
		NUM_ID
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE
	VICUS_COMP(NetworkController)

	/*! Checks if all parameters are valid. */
	bool isValid(const Database<Schedule> &scheduleDB) const;

	/*! Comparison operator */
	ComparisonResult equal(const AbstractDBElement *other) const override;

	/*! A copy of NANDRAD::HydraulicNetworkControlElement::checkParameters */
	void checkParameters() const;


	// *** PUBLIC MEMBER VARIABLES added for VICUS ***

	/*! Display name. */
	IBK::MultiLanguageString			m_displayName;									// XML:A

	/*! False color. */
	QColor								m_color;										// XML:A

	/*! reference to schedule */
	unsigned int						m_scheduleId = INVALID_ID;						// XML:A


	// *** PUBLIC MEMBER VARIABLES from NANDRAD::HydraulicNetworkControlElement ***

	IDType							m_id = NANDRAD::INVALID_ID;						// XML:A:required

	/*! Determines variability of setpoint parameters. */
	ModelType						m_modelType = NUM_MT;							// XML:A:required

	/*! Controller type (P, PI, ...) */
	ControllerType					m_controllerType = NUM_CT;						// XML:A

	/*! property which shall be controlled (temperature difference, ...) */
	ControlledProperty				m_controlledProperty = NUM_CP;					// XML:A:required

	/*! Integer/ID reference parameters. */
	IDType							m_idReferences[NUM_ID];							// XML:E

	/*! Used to cut the system input, if this is zero, it will not be considered	*/
	double							m_maximumControllerResultValue = 0;				// XML:E

	/*! Controller parameters. */
	IBK::Parameter					m_para[NUM_P];									// XML:E


};



} // namespace VICUS

#endif // VICUS_NETWORKCONTROLLER_H
