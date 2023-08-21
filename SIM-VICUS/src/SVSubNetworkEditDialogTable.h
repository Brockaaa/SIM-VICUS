#ifndef SVSUBNETWORKEDITDIALOGTABLE_H
#define SVSUBNETWORKEDITDIALOGTABLE_H

#include <QWidget>
#include <QTableWidget>

#include <VICUS_BMGlobals.h>
#include "VICUS_NetworkComponent.h"

class SVBMZoomMeshGraphicsView;

namespace Ui {
class SVSubNetworkEditDialogTable;
}

namespace VICUS{
class NetworkController;
}

class SVSubNetworkEditDialogTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit SVSubNetworkEditDialogTable(QWidget *parent = nullptr);
    ~SVSubNetworkEditDialogTable();
    int rowSize() const;
    void addElement(VICUS::NetworkComponent::ModelType type);
    void addElement(VICUS::NetworkComponent &controller);
    void clear();
    std::vector<QString> m_elementList;

private:
    Ui::SVSubNetworkEditDialogTable *ui;

    int m_rowSize = 0;
    int m_defaultRowHeight = VICUS::BLOCK_HEIGHT;

    void startDrag(Qt::DropActions supportedActions) override;
    void focusOutEvent(QFocusEvent *event) override;

    bool dragging = false;
    QPoint dragStartPosition;

    SVBMZoomMeshGraphicsView *                      BM_GraphicsView = nullptr;


};

#endif // SVSUBNETWORKEDITDIALOGTABLE_H
