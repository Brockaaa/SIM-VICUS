#include "SVSubNetworkComponentDBTableModel.h"

#include <QIcon>
#include <QTableView>
#include <QHeaderView>

#include "SVConversions.h"
#include "SVConstants.h"

SVSubNetworkComponentDBTableModel::SVSubNetworkComponentDBTableModel(QObject *parent, SVDatabase & db)
	: SVAbstractDatabaseTableModel(parent),
	m_db(&db)
{
	Q_ASSERT(m_db != nullptr);
}

int SVSubNetworkComponentDBTableModel::rowCount(const QModelIndex & parent) const
{
	return (int)m_db->m_networkComponents.size();
}

int SVSubNetworkComponentDBTableModel::columnCount(const QModelIndex & parent) const
{
	return NumColumns;
}

QVariant SVSubNetworkComponentDBTableModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	// readability improvement
	const VICUS::Database<VICUS::NetworkComponent> & ctrl = m_db->m_networkComponents;

	int row = index.row();
	if (row >= (int)ctrl.size())
		return QVariant();

	std::map<unsigned int, VICUS::NetworkComponent>::const_iterator it = ctrl.begin();
	std::advance(it, row);

	switch (role) {
		case Qt::DisplayRole : {

			switch (index.column()) {
				case ColId					: return it->first;
				case ColName				: return QtExt::MultiLangString2QString(it->second.m_displayName);
					// Note: description is too long here for "Type"
				case ColType				: return VICUS::KeywordList::Keyword("NetworkComponent::ModelType",
													   it->second.m_modelType);
			}
		} break;

		case Role_Id :
			return it->first;

		case Role_BuiltIn :
			return it->second.m_builtIn;

		case Role_Local :
			return it->second.m_local;

		case Role_Referenced:
			return it->second.m_isReferenced;
	}

	return QVariant();
}

QVariant SVSubNetworkComponentDBTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Vertical)
		return QVariant();
	switch (role) {
		case Qt::DisplayRole: {
			switch ( section ) {
				case ColId					: return tr("Id");
				case ColName				: return tr("Name");
				case ColType				: return tr("Type");
				default: ;
			}
		} break;

		case Qt::FontRole : {
			QFont f;
			f.setBold(true);
			f.setPointSizeF(f.pointSizeF()*0.8);
			return f;
		}
	} // switch
	return QVariant();
}

int SVSubNetworkComponentDBTableModel::columnIndexId() const
{
	return ColId;
}

void SVSubNetworkComponentDBTableModel::resetModel()
{
	beginResetModel();
	endResetModel();
}


void SVSubNetworkComponentDBTableModel::deleteItem(const QModelIndex & index)
{
	if (!index.isValid())
		return;
	unsigned int id = data(index, Role_Id).toUInt();
	beginRemoveRows(QModelIndex(), index.row(), index.row());
	m_db->m_networkComponents.remove(id);
	endRemoveRows();
}


void SVSubNetworkComponentDBTableModel::setColumnResizeModes(QTableView * tableView)
{
	tableView->horizontalHeader()->setSectionResizeMode(SVSubNetworkComponentDBTableModel::ColName, QHeaderView::Stretch);
}
