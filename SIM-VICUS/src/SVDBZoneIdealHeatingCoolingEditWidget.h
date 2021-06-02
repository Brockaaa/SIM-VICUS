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

#ifndef SVDBZoneIdealHeatingCoolingEditWidgetH
#define SVDBZoneIdealHeatingCoolingEditWidgetH

#include "SVAbstractDatabaseEditWidget.h"

namespace Ui {
	class SVDBZoneIdealHeatingCoolingEditWidget;
}

namespace VICUS {
	class ZoneIdealHeatingCooling;
}

class SVDBZoneIdealHeatingCoolingTableModel;
class SVDatabase;

class SVDBZoneIdealHeatingCoolingEditWidget : public SVAbstractDatabaseEditWidget {
	Q_OBJECT

public:
	explicit SVDBZoneIdealHeatingCoolingEditWidget(QWidget *parent = nullptr);
	~SVDBZoneIdealHeatingCoolingEditWidget() override;

	/*! Needs to be called once, before the widget is being used. */
	void setup(SVDatabase * db, SVAbstractDatabaseTableModel * dbModel) override;

	/*! Sets up the widget for a Schedule with a given ID. */
	void updateInput(int id) override;

private slots:
	void on_lineEditName_editingFinished();
	void on_pushButtonColor_colorChanged();

	void on_lineEditHeatingLimit_editingFinished();
	void on_lineEditCoolingLimit_editingFinished();

	void on_checkBoxHeatingLimit_toggled(bool checked);
	void on_checkBoxCoolingLimit_toggled(bool checked);

private:

	/*! Set up the modified variable of the model to true. */
	void modelModify();

	Ui::SVDBZoneIdealHeatingCoolingEditWidget			*m_ui;

	/*! Cached pointer to database object. */
	SVDatabase											*m_db;

	/*! Pointer to the database model, to modify items when data has changed in the widget. */
	SVDBZoneIdealHeatingCoolingTableModel				*m_dbModel;

	/*! Pointer to currently edited zone ideal heating cooling model.
		The pointer is updated whenever updateInput() is called.
		A nullptr pointer means that there is no model to edit.
	*/
	VICUS::ZoneIdealHeatingCooling						*m_current;
};

#endif // SVDBZoneIdealHeatingCoolingEditWidgetH
