#ifndef SVSUBNETWORKCOMPONENTDBTABLEMODEL_H
#define SVSUBNETWORKCOMPONENTDBTABLEMODEL_H

#include "SVAbstractDatabaseEditWidget.h"
#include <QObject>

class SVSubNetworkComponentDBTableModel : public SVAbstractDatabaseTableModel
{
	Q_OBJECT
public:
	explicit SVSubNetworkComponentDBTableModel(QObject *parent, SVDatabase & db);

signals:


private:
	SVDatabase	*m_db;

	// QAbstractItemModel interface
public:
	int rowCount(const QModelIndex & parent) const;
	int columnCount(const QModelIndex & parent) const;
	QVariant data(const QModelIndex & index, int role) const;

	// SVAbstractDatabaseTableModel interface
public:
	int columnIndexId() const;
	SVDatabase::DatabaseTypes databaseType() const { return SVDatabase::DT_NetworkComponents; }
	void resetModel();
	QModelIndex addNewItem();
	QModelIndex copyItem(const QModelIndex & index);
	void deleteItem(const QModelIndex & index);
	void setItemLocal(const QModelIndex & index, bool local);
	void setColumnResizeModes(QTableView * tableView);
};

#endif // SVSUBNETWORKCOMPONENTDBTABLEMODEL_H
