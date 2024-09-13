#ifndef SVUNDOADDDRAWINGOSMH
#define SVUNDOADDDRAWINGOSMH

#include "SVUndoCommandBase.h"

#include <VICUS_DrawingOSM.h>


class SVUndoAddDrawingOSM: public SVUndoCommandBase {
	Q_DECLARE_TR_FUNCTIONS(SVUndoAddNetwork)

public:
	SVUndoAddDrawingOSM(const QString & label, const VICUS::DrawingOSM & addedDrawing);

	virtual void undo();
	virtual void redo();

private:

	VICUS::DrawingOSM		m_addedDrawing;

	double				m_farDistance;
	double				m_gridWidth;
	double				m_gridSpacing;
};



#endif // SVUNDOADDDRAWINGOSMH
