#include "VicOSM_Constants.h"

namespace VicOSM {

const char * const VERSION			= "1.0";
const char * const LONG_VERSION		= "2.0.0";

unsigned int INVALID_ID = 0xFFFFFFFF;

const char * XML_READ_ERROR = "Error in XML file, line %1: %2";
const char * XML_READ_UNKNOWN_ATTRIBUTE = "Unknown/unsupported attribute '%1' in line %2.";
const char * XML_READ_UNKNOWN_ELEMENT = "Unknown/unsupported tag '%1' in line %2.";
const char * XML_READ_UNKNOWN_NAME = "Name '%1' for tag '%2' in line %3 is invalid/unknown.";

} // namespace VicOSM
