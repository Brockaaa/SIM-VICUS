# Qt Session file for shadow builds

TEMPLATE = subdirs

#EXTRA_LIBS += dxfrw

SUBDIRS = \
		CO2ComfortVentilation \
		SIM-VICUS \
		QuaZIP \
		qwt \
		QtExt \
		Vicus \
		CCM \
		Shading \
		DataIO \
		IBK \
		IBKMK \
		IntegratorFramework \
		Nandrad \
		NandradSolver \
		NandradModel \
		SuiteSparse \
		sundials \
		TiCPP \
		Zeppelin \
		IDFReader \
		RoomClipper \
		clipper \
		NandradCodeGenerator \
		NandradFMUGenerator \
		NandradSolverFMI

# where to find the sub projects
SIM-VICUS.file = SIM-VICUS/projects/Qt/SIM-VICUS.pro
NandradSolver.file = NandradSolver/projects/Qt/NandradSolver.pro
NandradSolverFMI.file = NandradSolverFMI/projects/Qt/NandradSolverFMI.pro
NandradCodeGenerator.file = NandradCodeGenerator/projects/Qt/NandradCodeGenerator.pro
NandradFMUGenerator.file = NandradFMUGenerator/projects/Qt/NandradFMUGenerator.pro

CCM.file = externals/CCM/projects/Qt/CCM.pro
Shading.file = externals/Shading/projects/Qt/Shading.pro
DataIO.file = externals/DataIO/projects/Qt/DataIO.pro
IBK.file = externals/IBK/projects/Qt/IBK.pro
IBKMK.file = externals/IBKMK/projects/Qt/IBKMK.pro
IntegratorFramework.file = externals/IntegratorFramework/projects/Qt/IntegratorFramework.pro
Nandrad.file = externals/Nandrad/projects/Qt/Nandrad.pro
SuiteSparse.file = externals/SuiteSparse/projects/Qt/SuiteSparse.pro
sundials.file = externals/sundials/projects/Qt/sundials.pro
TiCPP.file = externals/TiCPP/projects/Qt/TiCPP.pro
Zeppelin.file = externals/Zeppelin/projects/Qt/Zeppelin.pro
QuaZIP.file = externals/QuaZIP/projects/Qt/QuaZIP.pro
qwt.file = externals/qwt/projects/Qt/qwt.pro
Vicus.file = externals/Vicus/projects/Qt/Vicus.pro
QtExt.file = externals/QtExt/projects/Qt/QtExt.pro
IDFReader.file = externals/IDFReader/projects/Qt/IDFReader.pro
NandradModel.file = NandradSolver/projects/Qt/NandradModel.pro
clipper.file = externals/clipper/projects/Qt/clipper.pro
RoomClipper.file = externals/RoomClipper/projects/Qt/RoomClipper.pro

DummyDatabasePlugin.file = plugins/DummyDatabasePlugin/DummyDatabasePlugin.pro
DummyImportPlugin.file = plugins/DummyImportPlugin/DummyImportPlugin.pro

CO2ComfortVentilation.file = FMUs/CO2ComfortVentilation/projects/Qt/CO2ComfortVentilation.pro

# application and shared lib dependencies
NandradSolver.depends = NandradModel DataIO CCM TiCPP IBK IntegratorFramework Nandrad IBKMK
NandradSolverFMI.depends = NandradModel DataIO CCM TiCPP IBK IntegratorFramework Nandrad IBKMK
NandradCodeGenerator.depends = IBK Nandrad QtExt TiCPP
SIM-VICUS.depends = QuaZIP qwt Vicus Nandrad IBK TiCPP CCM QtExt Zeppelin IDFReader Shading DataIO clipper RoomClipper
NandradFMUGenerator.depends = IBK Nandrad QtExt QuaZIP TiCPP


# library dependencies
CCM.depends = IBK TiCPP
Shading.depends = IBK TiCPP CCM IBKMK DataIO RoomClipper
DataIO.depends = IBK
IBKMK.depends = IBK sundials
TiCPP.depends = IBK
QtExt.depends = IBK
IDFReader.depends = IBK IBKMK
IntegratorFramework.depends = IBK IBKMK sundials SuiteSparse
sundials.depends = SuiteSparse
Nandrad.depends = IBK TiCPP IBKMK
Zeppelin.depends = IBK
Vicus.depends = IBK TiCPP Nandrad IBKMK CCM DataIO
NandradModel.depends = DataIO CCM TiCPP IBK IntegratorFramework Nandrad IBKMK
RoomClipper.depends = IBK Nandrad IBKMK TiCPP CCM clipper Vicus

DummyDatabasePlugin.depends = Vicus
DummyImportPlugin.depends = Vicus

# only build dxfrw if enabled

contains(EXTRA_LIBS,dxfrw) {
	SUBDIRS += dxfrw

	dxfrw.file = externals/dxfrw/projects/Qt/dxfrw.pro

	Vicus.depends += dxfrw
}
