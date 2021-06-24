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

#ifndef SVSimulationShadingOptionsH
#define SVSimulationShadingOptionsH

#include <QDialog>
#include <QProgressDialog>
#include <QElapsedTimer>

#include <NANDRAD_SimulationParameter.h>
#include <VICUS_Project.h>

namespace Ui {
	class SVSimulationShadingOptions;
}

namespace SH {
	class StructuralShading;
}

/*! The widget holds all data needed for pre calculated shading factors. */
class SVSimulationShadingOptions : public QDialog {
	Q_OBJECT

public:
	explicit SVSimulationShadingOptions(QWidget *parent,
										NANDRAD::SimulationParameter & solverParams, NANDRAD::Location & location);
	~SVSimulationShadingOptions();

	/*! Defines the specific output type */
	enum OutputType {
		TsvFile,		///< write output to tsv file
		D6oFile,		///< write output to d6o file
		D6bFile			///< write output to d6b file
	};

	/*! Defines the detail type */
	enum DetailType {
		Fast,			///< fast calculation parameters
		Detailed,		///< detailed calculation paramtesers
		Manual,			///< manually defined parameters
		NUM_DT
	};

	/*! Defines whether to use "all geometry" or "only selected geometry". */
	bool m_useOnlySelectedSurfaces = false;

private slots:
	void on_pushButtonCalculate_clicked();

	void on_radioButtonFast_toggled(bool checked);

	void on_radioButtonManual_toggled(bool checked);

	void on_radioButtonDetailed_toggled(bool checked);

private:
	/*! Function that calculates the shading factors for selected outside surfaces
		Returns false if some error occurred during creation of the NANDRAD project.
	*/
	void calculateShadingFactors();

	/*! Sets the simulation parameters grid size and cone deg */
	void setSimulationParameters(const DetailType &dt);


	Ui::SVSimulationShadingOptions		*m_ui;								///< pointer to UI

	// Data storage locations, synchronized with user interface.
	const NANDRAD::SimulationParameter	*m_simParams = nullptr;
	const NANDRAD::Location				*m_location = nullptr;

	std::vector<const VICUS::Surface*>	m_selSurfaces;						///< vector with selected surfaces
	std::vector<const VICUS::Surface*>	m_selObstacles;						///< vector with selected dump geometry (obstacles)

	SH::StructuralShading				*m_shading = nullptr;				///< Owned, managed as pointer-to-object to hide SH namespace
};

#endif // SVShadingCalculationDialogH
