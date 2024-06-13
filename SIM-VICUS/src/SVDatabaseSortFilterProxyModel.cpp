#include "SVDatabaseSortFilterProxyModel.h"

#include "SVConstants.h"

SVDatabaseSortFilterProxyModel::SVDatabaseSortFilterProxyModel(QObject * parent) :
	QSortFilterProxyModel(parent)
{

}


void SVDatabaseSortFilterProxyModel::setFilterText(const QString & filterText, const int filterColumn) {
	beginResetModel();
	m_filterText = filterText;
	m_filterColumn = filterColumn;
	endResetModel();
}

void SVDatabaseSortFilterProxyModel::setPersistentFilter(const QString & persistentFilterText, const int persistentFilterColumn)
{
	beginResetModel();
	m_persistentFilterText = persistentFilterText;
	m_persistentFilterColumn = persistentFilterColumn;
	endResetModel();
}


bool SVDatabaseSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const {
	if (filterRegExp().isEmpty() && m_persistentFilterColumn == -1 && m_filterText == "")
		return true; // no filter, always accepted

	// first apply persistent filter and return false if condition not satisfied
	if(m_persistentFilterColumn != -1){
		QModelIndex index = sourceModel()->index(source_row, m_persistentFilterColumn, source_parent);
		if(index.data().toString() != m_persistentFilterText) return false;
	}

	// then apply persistent filter and return false if condition not satisfied
	if(m_filterColumn != -1){
		QModelIndex index = sourceModel()->index(source_row, m_filterColumn, source_parent);
		if(!index.data().toString().contains(m_filterText)) return false;
	}

	// then hand over to default implementation to filter for whatever the user has set in the UI
	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}


bool SVDatabaseSortFilterProxyModel::lessThan(const QModelIndex & source_left, const QModelIndex & source_right) const {
	// different comparison operations
	return source_left.data().toString() < source_right.data().toString();
}
