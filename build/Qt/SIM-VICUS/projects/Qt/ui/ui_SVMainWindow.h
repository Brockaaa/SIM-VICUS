/********************************************************************************
** Form generated from reading UI file 'SVMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVMAINWINDOW_H
#define UI_SVMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVMainWindow
{
public:
    QAction *actionFileNew;
    QAction *actionFileOpen;
    QAction *actionFileSave;
    QAction *actionFileSaveAs;
    QAction *actionFileExportProjectPackage;
    QAction *actionFileClose;
    QAction *actionFileQuit;
    QAction *actionFileRecentProjects;
    QAction *actionFileImportEneryPlusIDF;
    QAction *actionFileReload;
    QAction *actionFileOpenProjectDir;
    QAction *actionEditTextEditProject;
    QAction *actionEditPreferences;
    QAction *actionEditCleanProject;
    QAction *actionToolsCCMeditor;
    QAction *actionDBMaterials;
    QAction *actionDBConstructions;
    QAction *actionDBWindows;
    QAction *actionDBComponents;
    QAction *actionDBBoundaryConditions;
    QAction *actionDBNetworkPipes;
    QAction *actionDBHydraulicComponents;
    QAction *actionHelpKeyboardAndMouseControls;
    QAction *actionHelpOnlineManual;
    QAction *actionHelpAboutQt;
    QAction *actionHelpAbout;
    QAction *actionHelpCheckForUpdates;
    QAction *actionHelpBugReport;
    QAction *actionHelpVisitDiscussionForum;
    QAction *actionBuildingFloorManager;
    QAction *actionViewShowSurfaceNormals;
    QAction *actionDBSchedules;
    QAction *actionDBInternalLoadsPerson;
    QAction *actionDBInternalLoadsElectricEquipment;
    QAction *actionDBInternalLoadsLights;
    QAction *actionDBFluids;
    QAction *actionViewResetView;
    QAction *actionDBInfiltration;
    QAction *actionDBVentilationNatural;
    QAction *actionDBZoneControlThermostat;
    QAction *actionDBZoneControlShading;
    QAction *actionDBZoneControlVentilationNatural;
    QAction *actionDBInternalLoadsOther;
    QAction *actionDBWindowGlazingSystems;
    QAction *actionDBSubSurfaceComponents;
    QAction *actionDBZoneIdealHeatingCooling;
    QAction *actionDBZoneTemplates;
    QAction *actionDBControllers;
    QAction *actionDBSubNetworks;
    QAction *actionDBSurfaceHeatingSystems;
    QAction *actionBuildingSurfaceHeatings;
    QAction *actionDBRemoveDuplicates;
    QAction *actionViewShowGrid;
    QAction *actionHelpLinuxDesktopIntegration;
    QAction *actionViewFromSouth;
    QAction *actionViewFromWest;
    QAction *actionViewFromNorth;
    QAction *actionViewFromEast;
    QAction *actionViewFromAbove;
    QAction *actionViewFindSelectedGeometry;
    QAction *actionSimulationCO2Balance;
    QAction *actionDBSupplySystems;
    QAction *actionEditApplicationLog;
    QAction *actionFileImportNetworkGISData;
    QAction *actionEditProjectNotes;
    QAction *actionViewBirdsEyeViewSouthEast;
    QAction *actionViewBirdsEyeViewSouthWest;
    QAction *actionViewBirdsEyeViewNorthEast;
    QAction *actionViewBirdsEyeViewNorthWest;
    QAction *actionPluginsManager;
    QAction *actionExportNetworkAsGeoJSON;
    QAction *actionGeometryView;
    QAction *actionSimulationSettings;
    QAction *actionOpenPostProcessing;
    QAction *actionEPDElements;
    QAction *actionDWD_Weather_Data_Converter;
    QAction *actionExternal_Post_Processor;
    QAction *actionDBAcousticBoundaryConditions;
    QAction *actionDBAcousticSoundAbsorptions;
    QAction *actionNetwork_GIS_data;
    QAction *actionEneryPlus_IDF;
    QAction *actionExport_plugins;
    QAction *actionTest;
    QAction *actionPlugins;
    QAction *actionTest_2;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuExport;
    QMenu *menuExport_Plugins;
    QMenu *menuImport_2;
    QMenu *menuEdit;
    QMenu *menuLanguage;
    QMenu *menuHelp;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuDatabases;
    QMenu *menuInternal_Loads;
    QMenu *menuVentilationInfiltration;
    QMenu *menuZoneControl;
    QMenu *menuPlugins;
    QMenu *menuImport;
    QToolBar *toolBar;

    void setupUi(QMainWindow *SVMainWindow)
    {
        if (SVMainWindow->objectName().isEmpty())
            SVMainWindow->setObjectName(QString::fromUtf8("SVMainWindow"));
        SVMainWindow->resize(1112, 707);
        actionFileNew = new QAction(SVMainWindow);
        actionFileNew->setObjectName(QString::fromUtf8("actionFileNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/icons8/icons8-new-file-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileNew->setIcon(icon);
        actionFileOpen = new QAction(SVMainWindow);
        actionFileOpen->setObjectName(QString::fromUtf8("actionFileOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/icons8/icons8-ordner-oeffnen-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileOpen->setIcon(icon1);
        actionFileSave = new QAction(SVMainWindow);
        actionFileSave->setObjectName(QString::fromUtf8("actionFileSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/icons8/icons8-save-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileSave->setIcon(icon2);
        actionFileSaveAs = new QAction(SVMainWindow);
        actionFileSaveAs->setObjectName(QString::fromUtf8("actionFileSaveAs"));
        actionFileExportProjectPackage = new QAction(SVMainWindow);
        actionFileExportProjectPackage->setObjectName(QString::fromUtf8("actionFileExportProjectPackage"));
        actionFileClose = new QAction(SVMainWindow);
        actionFileClose->setObjectName(QString::fromUtf8("actionFileClose"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/dark/index.theme"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileClose->setIcon(icon3);
        actionFileQuit = new QAction(SVMainWindow);
        actionFileQuit->setObjectName(QString::fromUtf8("actionFileQuit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/gfx/icons8/icons8-close-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileQuit->setIcon(icon4);
        actionFileQuit->setMenuRole(QAction::QuitRole);
        actionFileRecentProjects = new QAction(SVMainWindow);
        actionFileRecentProjects->setObjectName(QString::fromUtf8("actionFileRecentProjects"));
        actionFileImportEneryPlusIDF = new QAction(SVMainWindow);
        actionFileImportEneryPlusIDF->setObjectName(QString::fromUtf8("actionFileImportEneryPlusIDF"));
        actionFileReload = new QAction(SVMainWindow);
        actionFileReload->setObjectName(QString::fromUtf8("actionFileReload"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/gfx/icons8/icons8-verfuegbare-updates-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFileReload->setIcon(icon5);
        actionFileOpenProjectDir = new QAction(SVMainWindow);
        actionFileOpenProjectDir->setObjectName(QString::fromUtf8("actionFileOpenProjectDir"));
        actionEditTextEditProject = new QAction(SVMainWindow);
        actionEditTextEditProject->setObjectName(QString::fromUtf8("actionEditTextEditProject"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/gfx/icons8/icons8-create-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditTextEditProject->setIcon(icon6);
        actionEditPreferences = new QAction(SVMainWindow);
        actionEditPreferences->setObjectName(QString::fromUtf8("actionEditPreferences"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/gfx/icons8/icons8-dienstleistungen-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditPreferences->setIcon(icon7);
        actionEditPreferences->setMenuRole(QAction::PreferencesRole);
        actionEditCleanProject = new QAction(SVMainWindow);
        actionEditCleanProject->setObjectName(QString::fromUtf8("actionEditCleanProject"));
        actionToolsCCMeditor = new QAction(SVMainWindow);
        actionToolsCCMeditor->setObjectName(QString::fromUtf8("actionToolsCCMeditor"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/gfx/icons8/icons8-rain-cloud-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolsCCMeditor->setIcon(icon8);
        actionDBMaterials = new QAction(SVMainWindow);
        actionDBMaterials->setObjectName(QString::fromUtf8("actionDBMaterials"));
        actionDBConstructions = new QAction(SVMainWindow);
        actionDBConstructions->setObjectName(QString::fromUtf8("actionDBConstructions"));
        actionDBWindows = new QAction(SVMainWindow);
        actionDBWindows->setObjectName(QString::fromUtf8("actionDBWindows"));
        actionDBComponents = new QAction(SVMainWindow);
        actionDBComponents->setObjectName(QString::fromUtf8("actionDBComponents"));
        actionDBBoundaryConditions = new QAction(SVMainWindow);
        actionDBBoundaryConditions->setObjectName(QString::fromUtf8("actionDBBoundaryConditions"));
        actionDBNetworkPipes = new QAction(SVMainWindow);
        actionDBNetworkPipes->setObjectName(QString::fromUtf8("actionDBNetworkPipes"));
        actionDBHydraulicComponents = new QAction(SVMainWindow);
        actionDBHydraulicComponents->setObjectName(QString::fromUtf8("actionDBHydraulicComponents"));
        actionHelpKeyboardAndMouseControls = new QAction(SVMainWindow);
        actionHelpKeyboardAndMouseControls->setObjectName(QString::fromUtf8("actionHelpKeyboardAndMouseControls"));
        actionHelpOnlineManual = new QAction(SVMainWindow);
        actionHelpOnlineManual->setObjectName(QString::fromUtf8("actionHelpOnlineManual"));
        actionHelpAboutQt = new QAction(SVMainWindow);
        actionHelpAboutQt->setObjectName(QString::fromUtf8("actionHelpAboutQt"));
        actionHelpAboutQt->setMenuRole(QAction::AboutQtRole);
        actionHelpAbout = new QAction(SVMainWindow);
        actionHelpAbout->setObjectName(QString::fromUtf8("actionHelpAbout"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/gfx/icons8/icons8-info-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelpAbout->setIcon(icon9);
        actionHelpAbout->setMenuRole(QAction::AboutRole);
        actionHelpCheckForUpdates = new QAction(SVMainWindow);
        actionHelpCheckForUpdates->setObjectName(QString::fromUtf8("actionHelpCheckForUpdates"));
        actionHelpCheckForUpdates->setEnabled(false);
        actionHelpBugReport = new QAction(SVMainWindow);
        actionHelpBugReport->setObjectName(QString::fromUtf8("actionHelpBugReport"));
        actionHelpVisitDiscussionForum = new QAction(SVMainWindow);
        actionHelpVisitDiscussionForum->setObjectName(QString::fromUtf8("actionHelpVisitDiscussionForum"));
        actionBuildingFloorManager = new QAction(SVMainWindow);
        actionBuildingFloorManager->setObjectName(QString::fromUtf8("actionBuildingFloorManager"));
        actionViewShowSurfaceNormals = new QAction(SVMainWindow);
        actionViewShowSurfaceNormals->setObjectName(QString::fromUtf8("actionViewShowSurfaceNormals"));
        actionViewShowSurfaceNormals->setCheckable(true);
        actionDBSchedules = new QAction(SVMainWindow);
        actionDBSchedules->setObjectName(QString::fromUtf8("actionDBSchedules"));
        actionDBInternalLoadsPerson = new QAction(SVMainWindow);
        actionDBInternalLoadsPerson->setObjectName(QString::fromUtf8("actionDBInternalLoadsPerson"));
        actionDBInternalLoadsElectricEquipment = new QAction(SVMainWindow);
        actionDBInternalLoadsElectricEquipment->setObjectName(QString::fromUtf8("actionDBInternalLoadsElectricEquipment"));
        actionDBInternalLoadsLights = new QAction(SVMainWindow);
        actionDBInternalLoadsLights->setObjectName(QString::fromUtf8("actionDBInternalLoadsLights"));
        actionDBFluids = new QAction(SVMainWindow);
        actionDBFluids->setObjectName(QString::fromUtf8("actionDBFluids"));
        actionViewResetView = new QAction(SVMainWindow);
        actionViewResetView->setObjectName(QString::fromUtf8("actionViewResetView"));
        actionDBInfiltration = new QAction(SVMainWindow);
        actionDBInfiltration->setObjectName(QString::fromUtf8("actionDBInfiltration"));
        actionDBVentilationNatural = new QAction(SVMainWindow);
        actionDBVentilationNatural->setObjectName(QString::fromUtf8("actionDBVentilationNatural"));
        actionDBZoneControlThermostat = new QAction(SVMainWindow);
        actionDBZoneControlThermostat->setObjectName(QString::fromUtf8("actionDBZoneControlThermostat"));
        actionDBZoneControlShading = new QAction(SVMainWindow);
        actionDBZoneControlShading->setObjectName(QString::fromUtf8("actionDBZoneControlShading"));
        actionDBZoneControlVentilationNatural = new QAction(SVMainWindow);
        actionDBZoneControlVentilationNatural->setObjectName(QString::fromUtf8("actionDBZoneControlVentilationNatural"));
        actionDBInternalLoadsOther = new QAction(SVMainWindow);
        actionDBInternalLoadsOther->setObjectName(QString::fromUtf8("actionDBInternalLoadsOther"));
        actionDBWindowGlazingSystems = new QAction(SVMainWindow);
        actionDBWindowGlazingSystems->setObjectName(QString::fromUtf8("actionDBWindowGlazingSystems"));
        actionDBSubSurfaceComponents = new QAction(SVMainWindow);
        actionDBSubSurfaceComponents->setObjectName(QString::fromUtf8("actionDBSubSurfaceComponents"));
        actionDBZoneIdealHeatingCooling = new QAction(SVMainWindow);
        actionDBZoneIdealHeatingCooling->setObjectName(QString::fromUtf8("actionDBZoneIdealHeatingCooling"));
        actionDBZoneTemplates = new QAction(SVMainWindow);
        actionDBZoneTemplates->setObjectName(QString::fromUtf8("actionDBZoneTemplates"));
        actionDBControllers = new QAction(SVMainWindow);
        actionDBControllers->setObjectName(QString::fromUtf8("actionDBControllers"));
        actionDBSubNetworks = new QAction(SVMainWindow);
        actionDBSubNetworks->setObjectName(QString::fromUtf8("actionDBSubNetworks"));
        actionDBSurfaceHeatingSystems = new QAction(SVMainWindow);
        actionDBSurfaceHeatingSystems->setObjectName(QString::fromUtf8("actionDBSurfaceHeatingSystems"));
        actionBuildingSurfaceHeatings = new QAction(SVMainWindow);
        actionBuildingSurfaceHeatings->setObjectName(QString::fromUtf8("actionBuildingSurfaceHeatings"));
        actionDBRemoveDuplicates = new QAction(SVMainWindow);
        actionDBRemoveDuplicates->setObjectName(QString::fromUtf8("actionDBRemoveDuplicates"));
        actionViewShowGrid = new QAction(SVMainWindow);
        actionViewShowGrid->setObjectName(QString::fromUtf8("actionViewShowGrid"));
        actionViewShowGrid->setCheckable(true);
        actionViewShowGrid->setChecked(true);
        actionHelpLinuxDesktopIntegration = new QAction(SVMainWindow);
        actionHelpLinuxDesktopIntegration->setObjectName(QString::fromUtf8("actionHelpLinuxDesktopIntegration"));
        actionViewFromSouth = new QAction(SVMainWindow);
        actionViewFromSouth->setObjectName(QString::fromUtf8("actionViewFromSouth"));
        actionViewFromWest = new QAction(SVMainWindow);
        actionViewFromWest->setObjectName(QString::fromUtf8("actionViewFromWest"));
        actionViewFromNorth = new QAction(SVMainWindow);
        actionViewFromNorth->setObjectName(QString::fromUtf8("actionViewFromNorth"));
        actionViewFromEast = new QAction(SVMainWindow);
        actionViewFromEast->setObjectName(QString::fromUtf8("actionViewFromEast"));
        actionViewFromAbove = new QAction(SVMainWindow);
        actionViewFromAbove->setObjectName(QString::fromUtf8("actionViewFromAbove"));
        actionViewFindSelectedGeometry = new QAction(SVMainWindow);
        actionViewFindSelectedGeometry->setObjectName(QString::fromUtf8("actionViewFindSelectedGeometry"));
        actionSimulationCO2Balance = new QAction(SVMainWindow);
        actionSimulationCO2Balance->setObjectName(QString::fromUtf8("actionSimulationCO2Balance"));
        actionDBSupplySystems = new QAction(SVMainWindow);
        actionDBSupplySystems->setObjectName(QString::fromUtf8("actionDBSupplySystems"));
        actionEditApplicationLog = new QAction(SVMainWindow);
        actionEditApplicationLog->setObjectName(QString::fromUtf8("actionEditApplicationLog"));
        actionEditApplicationLog->setIcon(icon6);
        actionFileImportNetworkGISData = new QAction(SVMainWindow);
        actionFileImportNetworkGISData->setObjectName(QString::fromUtf8("actionFileImportNetworkGISData"));
        actionEditProjectNotes = new QAction(SVMainWindow);
        actionEditProjectNotes->setObjectName(QString::fromUtf8("actionEditProjectNotes"));
        actionViewBirdsEyeViewSouthEast = new QAction(SVMainWindow);
        actionViewBirdsEyeViewSouthEast->setObjectName(QString::fromUtf8("actionViewBirdsEyeViewSouthEast"));
        actionViewBirdsEyeViewSouthWest = new QAction(SVMainWindow);
        actionViewBirdsEyeViewSouthWest->setObjectName(QString::fromUtf8("actionViewBirdsEyeViewSouthWest"));
        actionViewBirdsEyeViewNorthEast = new QAction(SVMainWindow);
        actionViewBirdsEyeViewNorthEast->setObjectName(QString::fromUtf8("actionViewBirdsEyeViewNorthEast"));
        actionViewBirdsEyeViewNorthWest = new QAction(SVMainWindow);
        actionViewBirdsEyeViewNorthWest->setObjectName(QString::fromUtf8("actionViewBirdsEyeViewNorthWest"));
        actionPluginsManager = new QAction(SVMainWindow);
        actionPluginsManager->setObjectName(QString::fromUtf8("actionPluginsManager"));
        actionPluginsManager->setEnabled(false);
        actionExportNetworkAsGeoJSON = new QAction(SVMainWindow);
        actionExportNetworkAsGeoJSON->setObjectName(QString::fromUtf8("actionExportNetworkAsGeoJSON"));
        actionGeometryView = new QAction(SVMainWindow);
        actionGeometryView->setObjectName(QString::fromUtf8("actionGeometryView"));
        actionGeometryView->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/gfx/icons8/icons8-wuerfel-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGeometryView->setIcon(icon10);
        actionSimulationSettings = new QAction(SVMainWindow);
        actionSimulationSettings->setObjectName(QString::fromUtf8("actionSimulationSettings"));
        actionSimulationSettings->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/gfx/icons8/icons8-einstellungen-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSimulationSettings->setIcon(icon11);
        actionOpenPostProcessing = new QAction(SVMainWindow);
        actionOpenPostProcessing->setObjectName(QString::fromUtf8("actionOpenPostProcessing"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/gfx/icons8/icons8-graph-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenPostProcessing->setIcon(icon12);
        actionEPDElements = new QAction(SVMainWindow);
        actionEPDElements->setObjectName(QString::fromUtf8("actionEPDElements"));
        actionEPDElements->setEnabled(false);
        actionDWD_Weather_Data_Converter = new QAction(SVMainWindow);
        actionDWD_Weather_Data_Converter->setObjectName(QString::fromUtf8("actionDWD_Weather_Data_Converter"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/gfx/actions/DWDWeatherDataConverter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDWD_Weather_Data_Converter->setIcon(icon13);
        actionExternal_Post_Processor = new QAction(SVMainWindow);
        actionExternal_Post_Processor->setObjectName(QString::fromUtf8("actionExternal_Post_Processor"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/gfx/actions/32x32/PostProcApp_32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExternal_Post_Processor->setIcon(icon14);
        actionDBAcousticBoundaryConditions = new QAction(SVMainWindow);
        actionDBAcousticBoundaryConditions->setObjectName(QString::fromUtf8("actionDBAcousticBoundaryConditions"));
        actionDBAcousticBoundaryConditions->setEnabled(false);
        actionDBAcousticSoundAbsorptions = new QAction(SVMainWindow);
        actionDBAcousticSoundAbsorptions->setObjectName(QString::fromUtf8("actionDBAcousticSoundAbsorptions"));
        actionDBAcousticSoundAbsorptions->setEnabled(false);
        actionNetwork_GIS_data = new QAction(SVMainWindow);
        actionNetwork_GIS_data->setObjectName(QString::fromUtf8("actionNetwork_GIS_data"));
        actionEneryPlus_IDF = new QAction(SVMainWindow);
        actionEneryPlus_IDF->setObjectName(QString::fromUtf8("actionEneryPlus_IDF"));
        actionExport_plugins = new QAction(SVMainWindow);
        actionExport_plugins->setObjectName(QString::fromUtf8("actionExport_plugins"));
        actionTest = new QAction(SVMainWindow);
        actionTest->setObjectName(QString::fromUtf8("actionTest"));
        actionPlugins = new QAction(SVMainWindow);
        actionPlugins->setObjectName(QString::fromUtf8("actionPlugins"));
        actionTest_2 = new QAction(SVMainWindow);
        actionTest_2->setObjectName(QString::fromUtf8("actionTest_2"));
        centralWidget = new QWidget(SVMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SVMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SVMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1112, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuExport = new QMenu(menuFile);
        menuExport->setObjectName(QString::fromUtf8("menuExport"));
        menuExport_Plugins = new QMenu(menuExport);
        menuExport_Plugins->setObjectName(QString::fromUtf8("menuExport_Plugins"));
        menuImport_2 = new QMenu(menuFile);
        menuImport_2->setObjectName(QString::fromUtf8("menuImport_2"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuLanguage = new QMenu(menuEdit);
        menuLanguage->setObjectName(QString::fromUtf8("menuLanguage"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuDatabases = new QMenu(menuBar);
        menuDatabases->setObjectName(QString::fromUtf8("menuDatabases"));
        menuInternal_Loads = new QMenu(menuDatabases);
        menuInternal_Loads->setObjectName(QString::fromUtf8("menuInternal_Loads"));
        menuVentilationInfiltration = new QMenu(menuDatabases);
        menuVentilationInfiltration->setObjectName(QString::fromUtf8("menuVentilationInfiltration"));
        menuZoneControl = new QMenu(menuDatabases);
        menuZoneControl->setObjectName(QString::fromUtf8("menuZoneControl"));
        menuPlugins = new QMenu(menuBar);
        menuPlugins->setObjectName(QString::fromUtf8("menuPlugins"));
        menuPlugins->setEnabled(true);
        menuImport = new QMenu(menuBar);
        menuImport->setObjectName(QString::fromUtf8("menuImport"));
        SVMainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(SVMainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        toolBar->setAllowedAreas(Qt::LeftToolBarArea);
        toolBar->setIconSize(QSize(32, 32));
        SVMainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuImport->menuAction());
        menuBar->addAction(menuDatabases->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuPlugins->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionFileNew);
        menuFile->addAction(actionFileOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionFileReload);
        menuFile->addAction(actionFileRecentProjects);
        menuFile->addSeparator();
        menuFile->addAction(actionFileSave);
        menuFile->addAction(actionFileSaveAs);
        menuFile->addAction(actionFileClose);
        menuFile->addSeparator();
        menuFile->addAction(menuImport_2->menuAction());
        menuFile->addAction(menuExport->menuAction());
        menuFile->addAction(actionFileOpenProjectDir);
        menuFile->addSeparator();
        menuFile->addAction(actionFileQuit);
        menuFile->addSeparator();
        menuExport->addAction(actionFileExportProjectPackage);
        menuExport->addAction(actionExportNetworkAsGeoJSON);
        menuExport->addAction(menuExport_Plugins->menuAction());
        menuImport_2->addAction(actionFileImportEneryPlusIDF);
        menuImport_2->addAction(actionFileImportNetworkGISData);
        menuEdit->addAction(actionEditTextEditProject);
        menuEdit->addAction(actionEditCleanProject);
        menuEdit->addAction(actionEditProjectNotes);
        menuEdit->addAction(actionEditApplicationLog);
        menuEdit->addSeparator();
        menuEdit->addSeparator();
        menuEdit->addAction(actionEditPreferences);
        menuEdit->addAction(menuLanguage->menuAction());
        menuHelp->addAction(actionHelpOnlineManual);
        menuHelp->addAction(actionHelpKeyboardAndMouseControls);
        menuHelp->addSeparator();
        menuHelp->addAction(actionHelpCheckForUpdates);
        menuHelp->addAction(actionHelpBugReport);
        menuHelp->addAction(actionHelpVisitDiscussionForum);
        menuHelp->addSeparator();
        menuHelp->addAction(actionHelpLinuxDesktopIntegration);
        menuHelp->addSeparator();
        menuHelp->addAction(actionHelpAbout);
        menuHelp->addAction(actionHelpAboutQt);
        menuView->addSeparator();
        menuView->addAction(actionViewFindSelectedGeometry);
        menuView->addSeparator();
        menuView->addAction(actionViewResetView);
        menuView->addSeparator();
        menuView->addAction(actionViewFromNorth);
        menuView->addAction(actionViewFromEast);
        menuView->addAction(actionViewFromSouth);
        menuView->addAction(actionViewFromWest);
        menuView->addSeparator();
        menuView->addAction(actionViewBirdsEyeViewNorthEast);
        menuView->addAction(actionViewBirdsEyeViewNorthWest);
        menuView->addAction(actionViewBirdsEyeViewSouthEast);
        menuView->addAction(actionViewBirdsEyeViewSouthWest);
        menuView->addSeparator();
        menuView->addAction(actionViewFromAbove);
        menuView->addSeparator();
        menuView->addAction(actionViewShowGrid);
        menuView->addAction(actionViewShowSurfaceNormals);
        menuView->addSeparator();
        menuTools->addAction(actionExternal_Post_Processor);
        menuTools->addAction(actionToolsCCMeditor);
        menuTools->addAction(actionDWD_Weather_Data_Converter);
        menuDatabases->addAction(actionDBMaterials);
        menuDatabases->addAction(actionDBConstructions);
        menuDatabases->addAction(actionDBComponents);
        menuDatabases->addAction(actionDBSubSurfaceComponents);
        menuDatabases->addAction(actionDBWindows);
        menuDatabases->addAction(actionDBWindowGlazingSystems);
        menuDatabases->addAction(actionDBBoundaryConditions);
        menuDatabases->addAction(actionDBSchedules);
        menuDatabases->addAction(menuInternal_Loads->menuAction());
        menuDatabases->addAction(menuVentilationInfiltration->menuAction());
        menuDatabases->addAction(menuZoneControl->menuAction());
        menuDatabases->addAction(actionDBZoneIdealHeatingCooling);
        menuDatabases->addAction(actionDBZoneTemplates);
        menuDatabases->addAction(actionDBSurfaceHeatingSystems);
        menuDatabases->addAction(actionDBSupplySystems);
        menuDatabases->addSeparator();
        menuDatabases->addAction(actionEPDElements);
        menuDatabases->addSeparator();
        menuDatabases->addAction(actionDBAcousticBoundaryConditions);
        menuDatabases->addAction(actionDBAcousticSoundAbsorptions);
        menuDatabases->addSeparator();
        menuDatabases->addAction(actionDBNetworkPipes);
        menuDatabases->addAction(actionDBFluids);
        menuDatabases->addAction(actionDBHydraulicComponents);
        menuDatabases->addAction(actionDBSubNetworks);
        menuDatabases->addAction(actionDBControllers);
        menuDatabases->addSeparator();
        menuDatabases->addAction(actionDBRemoveDuplicates);
        menuInternal_Loads->addAction(actionDBInternalLoadsPerson);
        menuInternal_Loads->addAction(actionDBInternalLoadsElectricEquipment);
        menuInternal_Loads->addAction(actionDBInternalLoadsLights);
        menuInternal_Loads->addAction(actionDBInternalLoadsOther);
        menuVentilationInfiltration->addAction(actionDBInfiltration);
        menuVentilationInfiltration->addAction(actionDBVentilationNatural);
        menuZoneControl->addAction(actionDBZoneControlThermostat);
        menuZoneControl->addAction(actionDBZoneControlShading);
        menuZoneControl->addAction(actionDBZoneControlVentilationNatural);
        menuPlugins->addAction(actionPluginsManager);
        menuImport->addAction(actionEneryPlus_IDF);
        menuImport->addAction(actionNetwork_GIS_data);
        toolBar->addAction(actionFileNew);
        toolBar->addAction(actionFileOpen);
        toolBar->addAction(actionFileSave);
        toolBar->addSeparator();
        toolBar->addAction(actionGeometryView);
        toolBar->addAction(actionSimulationSettings);
        toolBar->addSeparator();
        toolBar->addAction(actionOpenPostProcessing);

        retranslateUi(SVMainWindow);

        QMetaObject::connectSlotsByName(SVMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SVMainWindow)
    {
        actionFileNew->setText(QCoreApplication::translate("SVMainWindow", "&New...", nullptr));
#if QT_CONFIG(shortcut)
        actionFileNew->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileOpen->setText(QCoreApplication::translate("SVMainWindow", "&Open...", nullptr));
#if QT_CONFIG(shortcut)
        actionFileOpen->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileSave->setText(QCoreApplication::translate("SVMainWindow", "&Save", nullptr));
#if QT_CONFIG(shortcut)
        actionFileSave->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileSaveAs->setText(QCoreApplication::translate("SVMainWindow", "Save &as...", nullptr));
#if QT_CONFIG(shortcut)
        actionFileSaveAs->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileExportProjectPackage->setText(QCoreApplication::translate("SVMainWindow", "&Export project package...", nullptr));
#if QT_CONFIG(shortcut)
        actionFileExportProjectPackage->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileClose->setText(QCoreApplication::translate("SVMainWindow", "C&lose", nullptr));
#if QT_CONFIG(tooltip)
        actionFileClose->setToolTip(QCoreApplication::translate("SVMainWindow", "Closes current project", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionFileClose->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileQuit->setText(QCoreApplication::translate("SVMainWindow", "&Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionFileQuit->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFileRecentProjects->setText(QCoreApplication::translate("SVMainWindow", "Recent &projects", nullptr));
        actionFileImportEneryPlusIDF->setText(QCoreApplication::translate("SVMainWindow", "EneryPlus IDF...", nullptr));
        actionFileReload->setText(QCoreApplication::translate("SVMainWindow", "&Reload project", nullptr));
        actionFileOpenProjectDir->setText(QCoreApplication::translate("SVMainWindow", "Go to project directory...", nullptr));
#if QT_CONFIG(tooltip)
        actionFileOpenProjectDir->setToolTip(QCoreApplication::translate("SVMainWindow", "Opens file manager with path to project file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionFileOpenProjectDir->setShortcut(QCoreApplication::translate("SVMainWindow", "F8", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEditTextEditProject->setText(QCoreApplication::translate("SVMainWindow", "&Open project in text editor", nullptr));
#if QT_CONFIG(shortcut)
        actionEditTextEditProject->setShortcut(QCoreApplication::translate("SVMainWindow", "F2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEditPreferences->setText(QCoreApplication::translate("SVMainWindow", "&Preferences...", nullptr));
        actionEditCleanProject->setText(QCoreApplication::translate("SVMainWindow", "&Clean project", nullptr));
#if QT_CONFIG(shortcut)
        actionEditCleanProject->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+Shift+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionToolsCCMeditor->setText(QCoreApplication::translate("SVMainWindow", "External Climate Editor...", nullptr));
#if QT_CONFIG(tooltip)
        actionToolsCCMeditor->setToolTip(QCoreApplication::translate("SVMainWindow", "Launches external climate editor (CCMEditor)", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBMaterials->setText(QCoreApplication::translate("SVMainWindow", "&Materials...", nullptr));
        actionDBConstructions->setText(QCoreApplication::translate("SVMainWindow", "Constructions...", nullptr));
        actionDBWindows->setText(QCoreApplication::translate("SVMainWindow", "&Windows...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBWindows->setToolTip(QCoreApplication::translate("SVMainWindow", "Edit window database", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBComponents->setText(QCoreApplication::translate("SVMainWindow", "&Components...", nullptr));
        actionDBBoundaryConditions->setText(QCoreApplication::translate("SVMainWindow", "Boundary conditions...", nullptr));
        actionDBNetworkPipes->setText(QCoreApplication::translate("SVMainWindow", "Pipes...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBNetworkPipes->setToolTip(QCoreApplication::translate("SVMainWindow", "Network Pipes", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBHydraulicComponents->setText(QCoreApplication::translate("SVMainWindow", "Hydraulic components...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBHydraulicComponents->setToolTip(QCoreApplication::translate("SVMainWindow", "Network hydraulic components", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHelpKeyboardAndMouseControls->setText(QCoreApplication::translate("SVMainWindow", "Keyboard and mouse controls...", nullptr));
#if QT_CONFIG(shortcut)
        actionHelpKeyboardAndMouseControls->setShortcut(QCoreApplication::translate("SVMainWindow", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionHelpOnlineManual->setText(QCoreApplication::translate("SVMainWindow", "Online manual...", nullptr));
        actionHelpAboutQt->setText(QCoreApplication::translate("SVMainWindow", "About &Qt...", nullptr));
        actionHelpAbout->setText(QCoreApplication::translate("SVMainWindow", "&About SIM-VICUS...", nullptr));
        actionHelpCheckForUpdates->setText(QCoreApplication::translate("SVMainWindow", "Check for updates...", nullptr));
        actionHelpBugReport->setText(QCoreApplication::translate("SVMainWindow", "Feature request or bug report...", nullptr));
#if QT_CONFIG(tooltip)
        actionHelpBugReport->setToolTip(QCoreApplication::translate("SVMainWindow", "Post a feature request or submit a bug report", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHelpVisitDiscussionForum->setText(QCoreApplication::translate("SVMainWindow", "Visit discussion forum...", nullptr));
        actionBuildingFloorManager->setText(QCoreApplication::translate("SVMainWindow", "Floor manager...", nullptr));
#if QT_CONFIG(tooltip)
        actionBuildingFloorManager->setToolTip(QCoreApplication::translate("SVMainWindow", "Switches to building/level/floor manager property view", nullptr));
#endif // QT_CONFIG(tooltip)
        actionViewShowSurfaceNormals->setText(QCoreApplication::translate("SVMainWindow", "Show surface normals", nullptr));
        actionDBSchedules->setText(QCoreApplication::translate("SVMainWindow", "&Schedules...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBSchedules->setToolTip(QCoreApplication::translate("SVMainWindow", "Schedules", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBInternalLoadsPerson->setText(QCoreApplication::translate("SVMainWindow", "Person...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBInternalLoadsPerson->setToolTip(QCoreApplication::translate("SVMainWindow", "Internal loads: Person", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBInternalLoadsElectricEquipment->setText(QCoreApplication::translate("SVMainWindow", "Electric equipment...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBInternalLoadsElectricEquipment->setToolTip(QCoreApplication::translate("SVMainWindow", "Internal loads: Electric equipment", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBInternalLoadsLights->setText(QCoreApplication::translate("SVMainWindow", "Lights...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBInternalLoadsLights->setToolTip(QCoreApplication::translate("SVMainWindow", "Internal loads: Lights", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBFluids->setText(QCoreApplication::translate("SVMainWindow", "Fluids...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBFluids->setToolTip(QCoreApplication::translate("SVMainWindow", "Network Fluids", nullptr));
#endif // QT_CONFIG(tooltip)
        actionViewResetView->setText(QCoreApplication::translate("SVMainWindow", "Reset view", nullptr));
#if QT_CONFIG(tooltip)
        actionViewResetView->setToolTip(QCoreApplication::translate("SVMainWindow", "Resets view to be pointing north, close to site center.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBInfiltration->setText(QCoreApplication::translate("SVMainWindow", "Infiltration...", nullptr));
        actionDBVentilationNatural->setText(QCoreApplication::translate("SVMainWindow", "Natural ventilation...", nullptr));
        actionDBZoneControlThermostat->setText(QCoreApplication::translate("SVMainWindow", "Thermostat...", nullptr));
        actionDBZoneControlShading->setText(QCoreApplication::translate("SVMainWindow", "Shading...", nullptr));
        actionDBZoneControlVentilationNatural->setText(QCoreApplication::translate("SVMainWindow", "Natural ventilation...", nullptr));
        actionDBInternalLoadsOther->setText(QCoreApplication::translate("SVMainWindow", "Other...", nullptr));
        actionDBWindowGlazingSystems->setText(QCoreApplication::translate("SVMainWindow", "Window glazing systems...", nullptr));
        actionDBSubSurfaceComponents->setText(QCoreApplication::translate("SVMainWindow", "Window/Door (sub-surface) components...", nullptr));
        actionDBZoneIdealHeatingCooling->setText(QCoreApplication::translate("SVMainWindow", "Zone ideal heating/cooling...", nullptr));
        actionDBZoneTemplates->setText(QCoreApplication::translate("SVMainWindow", "Zone templates...", nullptr));
        actionDBControllers->setText(QCoreApplication::translate("SVMainWindow", "Controllers...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBControllers->setToolTip(QCoreApplication::translate("SVMainWindow", "Network controllers", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBSubNetworks->setText(QCoreApplication::translate("SVMainWindow", "Sub networks...", nullptr));
        actionDBSurfaceHeatingSystems->setText(QCoreApplication::translate("SVMainWindow", "Surface Heating Systems...", nullptr));
        actionBuildingSurfaceHeatings->setText(QCoreApplication::translate("SVMainWindow", "Surface heatings...", nullptr));
#if QT_CONFIG(tooltip)
        actionBuildingSurfaceHeatings->setToolTip(QCoreApplication::translate("SVMainWindow", "Switches to surface heating property view", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBRemoveDuplicates->setText(QCoreApplication::translate("SVMainWindow", "Remove duplicates...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBRemoveDuplicates->setToolTip(QCoreApplication::translate("SVMainWindow", "Removes duplicate elements from database", nullptr));
#endif // QT_CONFIG(tooltip)
        actionViewShowGrid->setText(QCoreApplication::translate("SVMainWindow", "Show main grid at z=0", nullptr));
#if QT_CONFIG(tooltip)
        actionViewShowGrid->setToolTip(QCoreApplication::translate("SVMainWindow", "Shows grid at z coordinate 0", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHelpLinuxDesktopIntegration->setText(QCoreApplication::translate("SVMainWindow", "Desktop integration (Linux)...", nullptr));
#if QT_CONFIG(tooltip)
        actionHelpLinuxDesktopIntegration->setToolTip(QCoreApplication::translate("SVMainWindow", "Desktop integration (Linux),  creates .desktop file and vicus-file association", nullptr));
#endif // QT_CONFIG(tooltip)
        actionViewFromSouth->setText(QCoreApplication::translate("SVMainWindow", "View from south", nullptr));
#if QT_CONFIG(tooltip)
        actionViewFromSouth->setToolTip(QCoreApplication::translate("SVMainWindow", "Positions camera to view geometry from north", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionViewFromSouth->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+8", nullptr));
#endif // QT_CONFIG(shortcut)
        actionViewFromWest->setText(QCoreApplication::translate("SVMainWindow", "View from west", nullptr));
#if QT_CONFIG(tooltip)
        actionViewFromWest->setToolTip(QCoreApplication::translate("SVMainWindow", "Positions camera to view geometry from east", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionViewFromWest->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+6", nullptr));
#endif // QT_CONFIG(shortcut)
        actionViewFromNorth->setText(QCoreApplication::translate("SVMainWindow", "View from north", nullptr));
#if QT_CONFIG(tooltip)
        actionViewFromNorth->setToolTip(QCoreApplication::translate("SVMainWindow", "Positions camera to view geometry from south", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionViewFromNorth->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionViewFromEast->setText(QCoreApplication::translate("SVMainWindow", "View from east", nullptr));
#if QT_CONFIG(tooltip)
        actionViewFromEast->setToolTip(QCoreApplication::translate("SVMainWindow", "Positions camera to view geometry from west", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionViewFromEast->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+4", nullptr));
#endif // QT_CONFIG(shortcut)
        actionViewFromAbove->setText(QCoreApplication::translate("SVMainWindow", "View from above", nullptr));
#if QT_CONFIG(tooltip)
        actionViewFromAbove->setToolTip(QCoreApplication::translate("SVMainWindow", "Positions camera to view geometry from above", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionViewFromAbove->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionViewFindSelectedGeometry->setText(QCoreApplication::translate("SVMainWindow", "Find selected geometry", nullptr));
#if QT_CONFIG(tooltip)
        actionViewFindSelectedGeometry->setToolTip(QCoreApplication::translate("SVMainWindow", "Positions camera to close to the currently selected geometry", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionViewFindSelectedGeometry->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSimulationCO2Balance->setText(QCoreApplication::translate("SVMainWindow", "CO2 Balance and Ventilation Control...", nullptr));
#if QT_CONFIG(tooltip)
        actionSimulationCO2Balance->setToolTip(QCoreApplication::translate("SVMainWindow", "Co-Simulation with CO2 balances and CO2-based ventilation control model.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBSupplySystems->setText(QCoreApplication::translate("SVMainWindow", "Supply systems...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBSupplySystems->setToolTip(QCoreApplication::translate("SVMainWindow", "SupplySystems", nullptr));
#endif // QT_CONFIG(tooltip)
        actionEditApplicationLog->setText(QCoreApplication::translate("SVMainWindow", "&Open application log in editor", nullptr));
#if QT_CONFIG(tooltip)
        actionEditApplicationLog->setToolTip(QCoreApplication::translate("SVMainWindow", "Opens an editor window for the application log file", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFileImportNetworkGISData->setText(QCoreApplication::translate("SVMainWindow", "Network GIS data ...", nullptr));
        actionEditProjectNotes->setText(QCoreApplication::translate("SVMainWindow", "Edit project notes", nullptr));
        actionViewBirdsEyeViewSouthEast->setText(QCoreApplication::translate("SVMainWindow", "Bird's eye view south east", nullptr));
#if QT_CONFIG(shortcut)
        actionViewBirdsEyeViewSouthEast->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+3", nullptr));
#endif // QT_CONFIG(shortcut)
        actionViewBirdsEyeViewSouthWest->setText(QCoreApplication::translate("SVMainWindow", "Bird's eye view south west", nullptr));
#if QT_CONFIG(shortcut)
        actionViewBirdsEyeViewSouthWest->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionViewBirdsEyeViewNorthEast->setText(QCoreApplication::translate("SVMainWindow", "Bird's eye view north east", nullptr));
#if QT_CONFIG(shortcut)
        actionViewBirdsEyeViewNorthEast->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+9", nullptr));
#endif // QT_CONFIG(shortcut)
        actionViewBirdsEyeViewNorthWest->setText(QCoreApplication::translate("SVMainWindow", "Bird's eye view north west", nullptr));
#if QT_CONFIG(shortcut)
        actionViewBirdsEyeViewNorthWest->setShortcut(QCoreApplication::translate("SVMainWindow", "Ctrl+7", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPluginsManager->setText(QCoreApplication::translate("SVMainWindow", "Plugin manager...", nullptr));
#if QT_CONFIG(tooltip)
        actionPluginsManager->setToolTip(QCoreApplication::translate("SVMainWindow", "Opens the plugin manager.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExportNetworkAsGeoJSON->setText(QCoreApplication::translate("SVMainWindow", "Export network as geoJSON...", nullptr));
        actionGeometryView->setText(QCoreApplication::translate("SVMainWindow", "Geometry View", nullptr));
#if QT_CONFIG(tooltip)
        actionGeometryView->setToolTip(QCoreApplication::translate("SVMainWindow", "Geometry View", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSimulationSettings->setText(QCoreApplication::translate("SVMainWindow", "Simulation Settings", nullptr));
#if QT_CONFIG(tooltip)
        actionSimulationSettings->setToolTip(QCoreApplication::translate("SVMainWindow", "Simulation Settings", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSimulationSettings->setShortcut(QCoreApplication::translate("SVMainWindow", "F10", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpenPostProcessing->setText(QCoreApplication::translate("SVMainWindow", "External post processing", nullptr));
#if QT_CONFIG(tooltip)
        actionOpenPostProcessing->setToolTip(QCoreApplication::translate("SVMainWindow", "External post processing", nullptr));
#endif // QT_CONFIG(tooltip)
        actionEPDElements->setText(QCoreApplication::translate("SVMainWindow", "EPD elements...", nullptr));
        actionDWD_Weather_Data_Converter->setText(QCoreApplication::translate("SVMainWindow", "DWD Weather Data Download...", nullptr));
        actionExternal_Post_Processor->setText(QCoreApplication::translate("SVMainWindow", "External Post Processor...", nullptr));
        actionDBAcousticBoundaryConditions->setText(QCoreApplication::translate("SVMainWindow", "Acoustic boundary conditions...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBAcousticBoundaryConditions->setToolTip(QCoreApplication::translate("SVMainWindow", "Acoustic boundary conditions", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBAcousticSoundAbsorptions->setText(QCoreApplication::translate("SVMainWindow", "Acoustic sound absorptions...", nullptr));
#if QT_CONFIG(tooltip)
        actionDBAcousticSoundAbsorptions->setToolTip(QCoreApplication::translate("SVMainWindow", "Acoustic sound absorptions", nullptr));
#endif // QT_CONFIG(tooltip)
        actionNetwork_GIS_data->setText(QCoreApplication::translate("SVMainWindow", "Network GIS data ...", nullptr));
        actionEneryPlus_IDF->setText(QCoreApplication::translate("SVMainWindow", "EneryPlus IDF...", nullptr));
        actionExport_plugins->setText(QCoreApplication::translate("SVMainWindow", "Export plugins", nullptr));
        actionTest->setText(QCoreApplication::translate("SVMainWindow", "Test", nullptr));
        actionPlugins->setText(QCoreApplication::translate("SVMainWindow", "Plugins", nullptr));
        actionTest_2->setText(QCoreApplication::translate("SVMainWindow", "Test", nullptr));
        menuFile->setTitle(QCoreApplication::translate("SVMainWindow", "&File", nullptr));
        menuExport->setTitle(QCoreApplication::translate("SVMainWindow", "Export", nullptr));
        menuExport_Plugins->setTitle(QCoreApplication::translate("SVMainWindow", "Export Plugins", nullptr));
        menuImport_2->setTitle(QCoreApplication::translate("SVMainWindow", "Import", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("SVMainWindow", "&Edit", nullptr));
        menuLanguage->setTitle(QCoreApplication::translate("SVMainWindow", "&Application language", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("SVMainWindow", "&Help", nullptr));
        menuView->setTitle(QCoreApplication::translate("SVMainWindow", "&View", nullptr));
        menuTools->setTitle(QCoreApplication::translate("SVMainWindow", "&Tools", nullptr));
        menuDatabases->setTitle(QCoreApplication::translate("SVMainWindow", "&Databases", nullptr));
        menuInternal_Loads->setTitle(QCoreApplication::translate("SVMainWindow", "Internal loads", nullptr));
        menuVentilationInfiltration->setTitle(QCoreApplication::translate("SVMainWindow", "Ventilation/Infiltration", nullptr));
        menuZoneControl->setTitle(QCoreApplication::translate("SVMainWindow", "Zone controls", nullptr));
        menuPlugins->setTitle(QCoreApplication::translate("SVMainWindow", "Plugins", nullptr));
        menuImport->setTitle(QCoreApplication::translate("SVMainWindow", "Import", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("SVMainWindow", "Main tool bar", nullptr));
        (void)SVMainWindow;
    } // retranslateUi

};

namespace Ui {
    class SVMainWindow: public Ui_SVMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVMAINWINDOW_H
