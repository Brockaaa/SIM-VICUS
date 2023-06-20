#include "SVSubNetworkEditDialog.h"
#include "ui_SVSubNetworkEditDialog.h"

#include "QHBoxLayout"
#include "QPushButton"
#include <QRandomGenerator>
#include <QTextEdit>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QList>
#include <QString>
#include <QFileDialog>

#include <BM_Network.h>
#include <BM_ZoomMeshGraphicsView.h>
#include <BM_SceneManager.h>
#include <BM_Block.h>
#include <BM_Globals.h>
#include "SVSubNetworkEditDialogTable.h"

#include "SVSettings.h"

#include <VICUS_NetworkComponent.h>


SVSubNetworkEditDialog::SVSubNetworkEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SVSubNetworkEditDialog)
{
    ui->setupUi(this);
    SVSubNetworkEditDialog::createToolBox();
    QList<int> ratio;
    ratio << 300 << 1000;
    ui->splitter->setSizes(ratio);
    ui->splitter->setStretchFactor(1,1);
    ui->viewWidget->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->viewWidget->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->viewWidget->setResolution(1);
    m_sceneManager = qobject_cast<BLOCKMOD::SceneManager*>(ui->viewWidget->scene());
    connect(m_sceneManager, &BLOCKMOD::SceneManager::newBlockSelected,
            this, &SVSubNetworkEditDialog::blockSelectedEvent);
    connect(m_sceneManager, &BLOCKMOD::SceneManager::selectionCleared,
            this, &SVSubNetworkEditDialog::selectionClearedEvent);
    ui->stackedWidget->setCurrentIndex(0);
    for(QObject* const widget : ui->stackedWidget->children())
        qDebug() << widget->objectName();
}

SVSubNetworkEditDialog::~SVSubNetworkEditDialog()
{
    delete ui;
}

void SVSubNetworkEditDialog::createToolBox(){

    ui->tbox->m_mode = true;
    ui->tbox->layout()->setMargin(0);
    ui->tbox->blockSignals(true);


    SVSubNetworkEditDialogTable * pipes = new SVSubNetworkEditDialogTable(this);
    SVSubNetworkEditDialogTable * pumps = new SVSubNetworkEditDialogTable(this);
    SVSubNetworkEditDialogTable * heatpumps = new SVSubNetworkEditDialogTable(this);
    SVSubNetworkEditDialogTable * other = new SVSubNetworkEditDialogTable(this);

    for(const auto& pair : VICUS::ModelTypeAttributes){
        switch(pair.second.category){
        case VICUS::Pipes:
            pipes->addElement(pair.first);
            break;
        case VICUS::Pumps:
            pumps->addElement(pair.first);
            break;
        case VICUS::Heatpumps:
            heatpumps->addElement(pair.first);
            break;
        case VICUS::Other:
            other->addElement(pair.first);
            break;
        default:
            qDebug() << "no entry for VICUS::NetworkComponent::ModelType " << pair.first;
        }
    }

    ui->tbox->addPage(tr("Pipes"), pipes);
    ui->tbox->addPage(tr("Pumps"), pumps);
    ui->tbox->addPage(tr("Heatpumps"), heatpumps);
    ui->tbox->addPage(tr("Other"), other);
    ui->tbox->blockSignals(false);

    ui->tbox->setCurrentIndex(0);

}

BLOCKMOD::ZoomMeshGraphicsView *SVSubNetworkEditDialog::ZoomMeshGraphicsView(){
    return ui->viewWidget;
}

void SVSubNetworkEditDialog::blockSelectedEvent()
{
    bool ok = false;
    BLOCKMOD::Block const  *blockToDisplay = nullptr;
    QList<const BLOCKMOD::Block*> blocks = m_sceneManager->selectedBlocks();
    if(blocks.size() == 1){
        blockToDisplay = blocks.first();
        blockToDisplay->m_name.toInt(&ok);
    }
    if(blockToDisplay && ok)
        ui->stackedWidget->setCurrentIndex(1);
    else
        ui->stackedWidget->setCurrentIndex(0);

}

void SVSubNetworkEditDialog::selectionClearedEvent(){
    qDebug() << "selectionClearedEvent";
    ui->stackedWidget->setCurrentIndex(0);
}

void SVSubNetworkEditDialog::on_removeBlockButton_clicked()
{
    ui->viewWidget->removeBlock();
}

void SVSubNetworkEditDialog::on_saveButton_clicked()
{
    QString fname = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("BM File (*.bm);;All Files(*.*)"), nullptr, SVSettings::instance().m_dontUseNativeDialogs ? QFileDialog::DontUseNativeDialog : QFileDialog::Options());

    qDebug() << "Save to: " << fname;
    ZoomMeshGraphicsView()->saveNetwork(fname);
}


void SVSubNetworkEditDialog::on_openButton_clicked()
{
    QString fname = QFileDialog::getOpenFileName(
        this,
        tr("Select BlockMod file"),
        QString(),
        tr("BlockMod files (*.bm)"), nullptr,
        SVSettings::instance().m_dontUseNativeDialogs ? QFileDialog::DontUseNativeDialog : QFileDialog::Options()
        );

    if (fname.isEmpty())
        return;

    qDebug() << fname;
    static_cast<BLOCKMOD::ZoomMeshGraphicsView*>(ZoomMeshGraphicsView())->openNetwork(fname);
}
