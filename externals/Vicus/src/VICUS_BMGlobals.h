/*	BSD 3-Clause License

	This file is part of the BlockMod Library.

	Copyright (c) 2019, Andreas Nicolai
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	   contributors may be used to endorse or promote products derived from
	   this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef BM_GlobalsH
#define BM_GlobalsH

#include <QString>

namespace VICUS{

class BMGlobals {
public:

	/*! Tests, if a given grid distance is approximately zero (with respect to grid spacing).
		Function accounts for rounding errors.
	*/
	static bool nearZero(double gridDistance);

	/*! Size of labels to draw on sockets. */
	static double LabelFontSize;

	/*! Constant to identify hidden block used during connection operation. */
	static const char * const InvisibleLabel;
};

const int BLOCK_WIDTH = 64;
const int BLOCK_HEIGHT = 64;

const int CONNECTORBLOCK_WIDTH = 13;
const int CONNECTORBLOCK_HEIGHT = 13;

const int ENTRANCEEXITBLOCK_WIDTH = 50;
const int ENTRANCEEXITBLOCK_HEIGHT = 50;

const int ENTRANCE_ID = 333333;
const int EXIT_ID = 666666;

const QString INLET_NAME = "inlet";
const QString OUTLET_NAME = "outlet";
const QString SUBNETWORK_INLET_NAME = "globalInlet";
const QString SUBNETWORK_OUTLET_NAME = "globalOutlet";
const QString CONNECTORBLOCK_NAME = "connectorBlock";
const QString CONNECTOR_NAME = "connector";

const QString INVALIDXMLREAD = "Invalid XML read";

enum BMBlockType{
	GlobalInlet,
	GlobalOutlet,
	NetworkComponentBlock,
	ConnectorBlock,
	InvisibleBlock
};

} // namespace VICUS


#endif // BM_GlobalsH
