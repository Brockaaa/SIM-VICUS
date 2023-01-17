/*	SIM-VICUS - Building and District Energy Simulation Tool.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Dirk Weiss  <dirk.weiss -[at]- tu-dresden.de>
	  Stephan Hirth  <stephan.hirth -[at]- tu-dresden.de>
	  Hauke Hirsch  <hauke.hirsch -[at]- tu-dresden.de>

	  ... all the others from the SIM-VICUS team ... :-)

	This program is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#include "SVDBLCAPeriodTableModel.h"

#include <QIcon>
#include <QFont>
#include <QTableView>
#include <QHeaderView>

#include <VICUS_LCAPeriod.h>
#include <VICUS_Database.h>
#include <VICUS_KeywordListQt.h>

#include <NANDRAD_KeywordList.h>

#include <SVConversions.h>

#include "SVConstants.h"
#include "SVStyle.h"

SVDBLCAPeriodTableModel::SVDBLCAPeriodTableModel(QObject *parent, SVDatabase &db) :
	SVAbstractDatabaseTableModel(parent),
	m_db(&db)
{
	Q_ASSERT(m_db != nullptr);
}


QVariant SVDBLCAPeriodTableModel::data ( const QModelIndex & index, int role) const {
	if (!index.isValid())
		return QVariant();

	// readability improvement
	const VICUS::Database<VICUS::LCAPeriod> & lcaDB = m_db->m_lcaPeriods;

	int row = index.row();
	if (row >= (int)lcaDB.size())
		return QVariant();

	std::map<unsigned int, VICUS::LCAPeriod>::const_iterator it = lcaDB.begin();
	std::advance(it, row);

	switch (role) {
		case Qt::DisplayRole : {
			switch (index.column()) {
				case ColKg					: return it->first;
				case ColCode				: return it->first;
				case ColName				: return QtExt::MultiLangString2QString(it->second.m_displayName);
				case ColPeriod				: return it->first;
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


int SVDBLCAPeriodTableModel::rowCount ( const QModelIndex & ) const {
	return (int)m_db->m_lcaPeriods.size();
}


QVariant SVDBLCAPeriodTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation == Qt::Vertical)
		return QVariant();
	switch (role) {
		case Qt::DisplayRole: {
			switch ( section ) {
				case ColKg					: return tr("Group");
				case ColCode				: return tr("Code");
				case ColName				: return tr("Description");
				case ColPeriod				: return tr("Lifetime");
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


void SVDBLCAPeriodTableModel::resetModel() {
	beginResetModel();
	endResetModel();
}


QModelIndex SVDBLCAPeriodTableModel::addNewItem() {
	VICUS::LCAPeriod bc;
	bc.m_displayName.setEncodedString("en:<new boundary condition>");
	bc.m_color = SVStyle::randomColor();

	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	unsigned int id = m_db->m_lcaPeriods.add( bc );
	endInsertRows();
	QModelIndex idx = indexById(id);
	return idx;
}


QModelIndex SVDBLCAPeriodTableModel::copyItem(const QModelIndex & existingItemIndex) {
	// lookup existing item
	const VICUS::Database<VICUS::LCAPeriod> & db = m_db->m_lcaPeriods;
	Q_ASSERT(existingItemIndex.isValid() && existingItemIndex.row() < (int)db.size());
	std::map<unsigned int, VICUS::LCAPeriod>::const_iterator it = db.begin();
	std::advance(it, existingItemIndex.row());
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	// create new item and insert into DB
	VICUS::LCAPeriod newItem(it->second);
	newItem.m_color = SVStyle::randomColor();
	unsigned int id = m_db->m_lcaPeriods.add( newItem );
	endInsertRows();
	QModelIndex idx = indexById(id);
	return idx;
}


void SVDBLCAPeriodTableModel::deleteItem(const QModelIndex & index) {
	if (!index.isValid())
		return;
	unsigned int id = data(index, Role_Id).toUInt();
	beginRemoveRows(QModelIndex(), index.row(), index.row());
	m_db->m_lcaPeriods.remove(id);
	endRemoveRows();
}


void SVDBLCAPeriodTableModel::setColumnResizeModes(QTableView * tableView) {
	tableView->horizontalHeader()->setSectionResizeMode(SVDBLCAPeriodTableModel::ColKg, QHeaderView::Fixed);
	tableView->horizontalHeader()->setSectionResizeMode(SVDBLCAPeriodTableModel::ColCode, QHeaderView::Fixed);
	tableView->horizontalHeader()->setSectionResizeMode(SVDBLCAPeriodTableModel::ColName, QHeaderView::Fixed);
	tableView->horizontalHeader()->setSectionResizeMode(SVDBLCAPeriodTableModel::ColPeriod, QHeaderView::Stretch);
}


void SVDBLCAPeriodTableModel::setItemLocal(const QModelIndex &index, bool local) {
	if (!index.isValid())
		return;
	unsigned int id = data(index, Role_Id).toUInt();
	m_db->m_lcaPeriods[id]->m_local = local;
	m_db->m_lcaPeriods.m_modified = true;
	setItemModified(id);
}


void SVDBLCAPeriodTableModel::setItemModified(unsigned int id) {
	QModelIndex idx = indexById(id);
	QModelIndex left = index(idx.row(), 0);
	QModelIndex right = index(idx.row(), NumColumns-1);
	emit dataChanged(left, right);
}


QModelIndex SVDBLCAPeriodTableModel::indexById(unsigned int id) const {
	for (int i=0; i<rowCount(); ++i) {
		QModelIndex idx = index(i, 0);
		if (data(idx, Role_Id).toUInt() == id)
			return idx;
	}
	return QModelIndex();
}
