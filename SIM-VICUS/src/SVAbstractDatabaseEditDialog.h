#ifndef SVABSTRACTDATABASEEDITDIALOG_H
#define SVABSTRACTDATABASEEDITDIALOG_H

#include <QDialog>

namespace Ui {
class SVAbstractDatabaseEditDialog;
}

class SVAbstractDatabaseTableModel;
class SVAbstractDatabaseEditWidget;
//class SVInternalLoadsTableModel;
class QModelIndex;
class QGroupBox;
class SVDatabaseSortFilterProxyModel;

#include <VICUS_Constants.h>

class SVAbstractDatabaseEditDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SVAbstractDatabaseEditDialog(QWidget *parent, SVAbstractDatabaseTableModel * tableModel,
										  SVAbstractDatabaseEditWidget * editWidget,
										  const QString & title, const QString & editWidgetTitle,
										  bool horizontalLayout);
	~SVAbstractDatabaseEditDialog();

	/*! Starts the dialog in "edit" mode. */
	void edit(unsigned int initialId = VICUS::INVALID_ID);

	/*! Starts the dialog in "select mode".
		\param initialId The item indicated by this ID is initially selected.
		\return If an item was selected and double-clicked/or the "Select" button was
				pressed, the function returns the ID of the selected item. Otherwise, if the
				dialog was aborted, the function returns VICUS::INVALID_ID.
	*/
	unsigned int select(unsigned int initialId, bool resetModel = true, QString filterText = "", int filterColumn = -1);

	SVAbstractDatabaseTableModel * dbModel() const;

private slots:
	void on_pushButtonSelect_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonClose_clicked();

	/*! Connected to the respective signal in the table view.
		Enables/disables the remove button.
	*/
	void onCurrentIndexChanged(const QModelIndex &current, const QModelIndex &/*previous*/);

	void onStyleChanged();

	void on_toolButtonApplyFilter_clicked();

	void on_comboBoxColumn_currentIndexChanged(int /*index*/);

	void on_lineEditFilter_returnPressed();

	void onScreenChanged(const QScreen * screen);

private:
	/*! If table contains an element with matching ID, this row is made current.
		Signals are blocked in this function.
	*/
	void selectItemById(unsigned int id);

	/*! Adjusts size of dialog and share that is occupied by table view */
	void resizeDBDialog(double maxShareTableView=0.6);

	Ui::SVAbstractDatabaseEditDialog *m_ui;

	/*! The sort filter model (owned). */
	SVDatabaseSortFilterProxyModel	*m_proxyModel	= nullptr;
	/*! The table model (owned). */
	SVAbstractDatabaseTableModel	*m_dbModel		= nullptr;
	/*! The edit widget (owned). */
	SVAbstractDatabaseEditWidget	*m_editWidget	= nullptr;
	QWidget							*m_editWidgetContainerWidget = nullptr;

	QString							m_currentFilter = "";

	QSize							m_screenSize;
};

#endif // SVABSTRACTDATABASEEDITDIALOG_H
