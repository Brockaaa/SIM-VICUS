#include "VICUS_NetworkElement.h"

namespace VICUS {

NetworkElement::NetworkElement()
{

}

bool NetworkElement::operator!=(const NetworkElement &other) const
{
	// check ids
	if (m_id != other.m_id ||
		m_inletNodeId != other.m_inletNodeId ||
		m_outletNodeId != other.m_outletNodeId ||
		m_componentId != other.m_componentId ||
		m_controlElementId != other.m_controlElementId)

		return true;
	else
		return false;
}


} // namespace VICUS
