#ifndef SVSUBNETWORKEDITDIALOG_H
#define SVSUBNETWORKEDITDIALOG_H

#include <QDialog>
#include <QGraphicsScene>

namespace Ui {
class SVSubNetworkEditDialog;
}

class SVBMSceneManager;
class SVBMZoomMeshGraphicsView;

class SVSubNetworkEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SVSubNetworkEditDialog(QWidget *parent = nullptr);
    ~SVSubNetworkEditDialog();
    SVBMZoomMeshGraphicsView *zoomMeshGraphicsView();

protected:
    void blockSelectedEvent();

    void selectionClearedEvent();
private slots:

    void on_removeBlockButton_clicked();

    void on_saveButton_clicked();

    void on_openButton_clicked();

private:
    Ui::SVSubNetworkEditDialog *ui;
    void createToolBox();
    SVBMSceneManager        *m_sceneManager = nullptr;
};

#endif // SVSUBNETWORKEDITDIALOG_H
