#ifndef InstanceDataH
#define InstanceDataH

#include <vector>

#include <IBK_Path.h>
#include <IBK_FormatString.h>

#include "NandradModelFMU.h"

#include "fmi2common/fmi2FunctionTypes.h"
#include "fmi2common/InstanceDataCommon.h"

/*! This class wraps all data needed for a single instance of the Therakles model as FMU. */
class InstanceData : public InstanceDataCommon {
public:
	/*! Constructor. */
	InstanceData();

	/*! Destructor, waits for spin-down of OpenMP threads. */
	~InstanceData();

	/*! Initializes InstanceData */
	void init();

	/*! Called from fmi2DoStep(). */
	virtual void integrateTo(double tCommunicationIntervalEnd);

	/*! Called from either doStep() or terminate() in CoSimulation mode whenever
		a communication interval has been completed and all related buffers can be cleared/output files can be
		written.
	*/
	virtual void clearBuffers();

	// Functions for getting/setting the state

	/*! This function computes the size needed for full serizalization of
		the FMU and stores the size in m_fmuStateSize.
		\note The size includes the leading 8byte for the 64bit integer size
		of the memory array (for testing purposes).
	*/
	virtual void computeFMUStateSize();

	/*! Copies the internal state of the FMU to the memory array pointed to by FMUstate.
		Memory array always has size m_fmuStateSize.
	*/
	virtual void serializeFMUstate(void * FMUstate);

	/*! Copies the content of the memory array pointed to by FMUstate to the internal state of the FMU.
		Memory array always has size m_fmuStateSize.
	*/
	virtual void deserializeFMUstate(void * FMUstate);


	/*! The actual model that contains all the physics. */
	NandradModelFMU		m_model;

	/*! Holds the start time from the co-sim master in setupExperiment(). */
	double				m_tStart;

}; // class InstanceData

#endif // InstanceDataH
