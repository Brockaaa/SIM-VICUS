#include "SVUndoAddDrawingOSM.h"
#include "SVProjectHandler.h"
#include "SVSettings.h"

SVUndoAddDrawingOSM::SVUndoAddDrawingOSM(const QString & label, const VICUS::DrawingOSM & addedDrawing) :
	m_addedDrawing(addedDrawing)
{
	setText( label );
}


void SVUndoAddDrawingOSM::undo() {
	// remove drawing
	Q_ASSERT(!theProject().m_drawingsOSM.empty());

	theProject().m_drawingsOSM.pop_back();
	theProject().updatePointers();

	SVProjectHandler::instance().setModified( SVProjectHandler::DrawingOSMModified);
}


void SVUndoAddDrawingOSM::redo() {
	// append drawing
	theProject().m_drawingsOSM.push_back(m_addedDrawing);
	theProject().updatePointers();

	SVProjectHandler::instance().setModified( SVProjectHandler::DrawingOSMModified);
}

