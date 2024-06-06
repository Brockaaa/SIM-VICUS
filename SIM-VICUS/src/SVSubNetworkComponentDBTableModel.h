#ifndef SVSUBNETWORKCOMPONENTDBTABLEMODEL_H
#define SVSUBNETWORKCOMPONENTDBTABLEMODEL_H

#include "SVAbstractDatabaseEditWidget.h"
#include <QObject>

class SVSubNetworkComponentDBTableModel : public SVAbstractDatabaseTableModel
{
	Q_OBJECT
public:
	/*! Columns shown in the table view. */
	enum Columns {
		ColId,
		ColName,
		ColType,
		NumColumns
	};

	explicit SVSubNetworkComponentDBTableModel(QObject *parent, SVDatabase & db);


	// QAbstractItemModel interface
public:
	int rowCount(const QModelIndex & parent) const;
	int columnCount(const QModelIndex & parent) const;
	QVariant data(const QModelIndex & index, int role) const;
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const ;

	// SVAbstractDatabaseTableModel interface
public:
	int columnIndexId() const;
	SVDatabase::DatabaseTypes databaseType() const { return SVDatabase::DT_NetworkComponents; }
	void resetModel();
	QModelIndex addNewItem(){return QModelIndex();}
	QModelIndex copyItem(const QModelIndex & index){return QModelIndex();}
	void deleteItem(const QModelIndex & index);
	void setItemLocal(const QModelIndex & index, bool local){}
	void setColumnResizeModes(QTableView * tableView);

private:
	SVDatabase	*m_db;
};

#endif // SVSUBNETWORKCOMPONENTDBTABLEMODEL_H
