#ifndef SVNETWORKCONTROLLEREDITDIALOG_H
#define SVNETWORKCONTROLLEREDITDIALOG_H

#include "SVAbstractDatabaseEditWidget.h"
#include <QDialog>

class SVDBNetworkControllerTableModel;

namespace VICUS {
	class NetworkController;
class BMBlock;
}

namespace Ui {
class SVDBNetworkControllerEditWidget;
}

class SVNetworkControllerEditDialog :  public QDialog {
	Q_OBJECT

public:

	explicit SVNetworkControllerEditDialog(QWidget *parent = nullptr, SVDatabase * db = nullptr);
	~SVNetworkControllerEditDialog() override;

	/*! Needs to be called once, before the widget is being used. */
	void setController(VICUS::NetworkController *controller);

	void setup(VICUS::BMBlock *block, VICUS::NetworkController controller, VICUS::NetworkComponent *networkComponent);

signals:
	void controllerAccepted(VICUS::BMBlock* block, VICUS::NetworkController controller);

private slots:

	void on_lineEditSetpoint_editingFinished();

	void on_lineEditKp_editingFinished();

	void on_lineEditKi_editingFinished();

	void on_radioButtonSchedule_clicked(bool checked);

	void on_radioButtonFixedSetPoint_clicked(bool checked);

	void on_toolButtonSchedule_clicked();

	void on_comboBoxProperty_activated(int index);

	void on_comboBoxControllerType_activated(int index);

	void on_lineEditMaxControllerResultValue_editingFinished();

	void on_toolButtonRemoveSchedule_clicked();

	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

private:
	Ui::SVDBNetworkControllerEditWidget *m_ui;

	SVDatabase              *m_db = nullptr;

	/*! Pointer to currently edited controller.
		The pointer is updated whenever updateInput() is called.
		A nullptr pointer means that there is no component to edit.
	*/
	VICUS::NetworkController			m_currentController;

	VICUS::BMBlock                      *m_currentBlock;
};

#endif // SVNETWORKCONTROLLEREDITDIALOG_H
