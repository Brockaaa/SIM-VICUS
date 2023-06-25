#ifndef SVSUBNETWORKEDITDIALOGTABLE_H
#define SVSUBNETWORKEDITDIALOGTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QListWidget>

#include <VICUS_BMConstants.h>

#include "VICUS_NetworkComponent.h"

class SVBMZoomMeshGraphicsView;

namespace Ui {
class SVSubNetworkEditDialogTable;
}

class SVSubNetworkEditDialogTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit SVSubNetworkEditDialogTable(QWidget *parent = nullptr);
    ~SVSubNetworkEditDialogTable();
    int rowSize() const;
    void addElement(VICUS::NetworkComponent::ModelType type);

private:
    Ui::SVSubNetworkEditDialogTable *ui;

    std::vector<VICUS::NetworkComponent::ModelType> elementList = std::vector<VICUS::NetworkComponent::ModelType>();

    int m_rowSize = 0;
    int m_defaultRowHeight = BLOCK_HEIGHT;

    SVBMZoomMeshGraphicsView *BM_GraphicsView = nullptr;

    void startDrag(Qt::DropActions supportedActions) override;

    bool dragging = false;
    QPoint dragStartPosition;

};

#endif // SVSUBNETWORKEDITDIALOGTABLE_H
