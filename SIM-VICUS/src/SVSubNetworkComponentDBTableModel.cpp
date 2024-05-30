#include "SVSubNetworkComponentDBTableModel.h"

SVSubNetworkComponentDBTableModel::SVSubNetworkComponentDBTableModel(QObject *parent, SVDatabase & db)
	: SVAbstractDatabaseTableModel(parent),
	m_db(&db)
{
	Q_ASSERT(m_db != nullptr);
}

int SVSubNetworkComponentDBTableModel::rowCount(const QModelIndex & parent) const
{
	return 0;
}

int SVSubNetworkComponentDBTableModel::columnCount(const QModelIndex & parent) const
{
	return 0;
}

QVariant SVSubNetworkComponentDBTableModel::data(const QModelIndex & index, int role) const
{
	return QVariant();
}

int SVSubNetworkComponentDBTableModel::columnIndexId() const
{
	return 0;
}

void SVSubNetworkComponentDBTableModel::resetModel()
{

}

QModelIndex SVSubNetworkComponentDBTableModel::addNewItem()
{
	return QModelIndex();
}

QModelIndex SVSubNetworkComponentDBTableModel::copyItem(const QModelIndex & index)
{
	return QModelIndex();
}

void SVSubNetworkComponentDBTableModel::deleteItem(const QModelIndex & index)
{

}

void SVSubNetworkComponentDBTableModel::setItemLocal(const QModelIndex & index, bool local)
{

}

void SVSubNetworkComponentDBTableModel::setColumnResizeModes(QTableView * tableView)
{

}
