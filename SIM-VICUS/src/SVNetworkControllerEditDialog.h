#ifndef SVNETWORKCONTROLLEREDITDIALOG_H
#define SVNETWORKCONTROLLEREDITDIALOG_H

#include "SVDatabase.h"

#include <QDialog>
#include <VICUS_NetworkComponent.h>
#include <VICUS_NetworkController.h>

namespace Ui {
class SVNetworkControllerEditDialog;
}

class SVNetworkControllerEditDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SVNetworkControllerEditDialog(QWidget *parent = nullptr);
	~SVNetworkControllerEditDialog();

	void setup(VICUS::NetworkController &controller, VICUS::NetworkComponent::ModelType modelType);

	void update();

	VICUS::NetworkController controller();

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

	void on_lineEditName_editingFinished();

private:
	Ui::SVNetworkControllerEditDialog *m_ui;

	SVDatabase              m_db;
	/* currently edited controller */
	VICUS::NetworkController			m_currentController;
};

#endif // SVNETWORKCONTROLLEREDITDIALOG_H
