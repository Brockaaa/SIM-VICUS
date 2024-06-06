#ifndef SVSUBNETWORKEDITDIALOGH
#define SVSUBNETWORKEDITDIALOGH

#include <QWidget>
#include <VICUS_NetworkComponent.h>

namespace Ui {
class SVSubNetworkEditDialog;
}

namespace VICUS {
class SubNetwork;
class NetworkController;
class BMBlock;
}

class SVBMSceneManager;
class SVBMZoomMeshGraphicsView;
class SVDatabase;
class SVNetworkControllerEditDialog;
class SVSubNetworkEditDialogTable;

class SVSubNetworkEditDialog : public QWidget
{
	Q_OBJECT

public:
	explicit SVSubNetworkEditDialog(QWidget *parent = nullptr, VICUS::SubNetwork * subNetwork = nullptr, SVDatabase * db = nullptr);
	/*! D-tor */
	~SVSubNetworkEditDialog();

	/* Different Modes of the SVSubNetworkEditDialog. Depending if started from SVDBSubNetworkEditWidget
	 *  or SVDBSupplySystemEditWidget a different mode should be chosen. Restricts the available NetworkComponents
	 *  and NetworkComponent Modeltypes in the Toolbox */
	enum SubnetworkMode {
		SM_EditDistrictNetworkPlant, // everything available, chosen when nothing specified
		SM_EditBuildingSupplySystem,
		NUM_SM
	};

	/*! Getter for private member ZoomMeshGraphicsView */
	SVBMZoomMeshGraphicsView *zoomMeshGraphicsView();
	/*! sets up Subnetwork and calls setNetwork)= */
	void setupSubNetwork(VICUS::SubNetwork * subNetwork, SubnetworkMode mode = SM_EditDistrictNetworkPlant);
	/*! opens window, sets appropriate height and weight values for the Splitter and the Scene */
	void show();

signals:
	void widgetClosed();

private slots:
	/*! gets called when removeBlockOrConnectorButton is clicked, checks if Block or Connector is selected, then forwards request to SVBMSceneManager */
	void on_removeButton_clicked();
	/*! gets called when copyBlockButton is clicked,
	 * checks if there is a Block selected and calls copyBlock, copied relevant Controller and Component
	 * and adds the vectors. Calls setController to ensure that name of Controller is visible in the view*/
	void on_copyBlockButton_clicked();
	/*! gets called when a Component is selected in the QtExtToolBox. Is connected to SVSubNetworkEditTable
	 *  activates or deactivates the removeControllerFromDBButton */
	void on_componentSelected();
	/*! gets called when addToDBButton is clicked,
	 *  adds component of Block to DB */
	void on_addToUserDBButton_clicked();
	/*! get called when changeDBElementNameButton is cliclked
	 * calls small dialog to change name */
	void on_toolButtonRename_clicked();
	/*! gets called when an element in the QtExtToolBox is double clicked
	 *  opens a dialog to edit the Component */
	void on_componentDoubleClicked();
	/*! updates names of screenshots of subnetworks when project is saved */
	void on_projectSaved();
	/*! Connected to styleChanged signal of SVPreferencesDialog */
	void on_styleChanged();
	/*! Connected to signal controllerUpdated() from SVNetworkComponentEditWidget */
	void on_controllerChanged(QString controllerName);
	/*! Connected to signal ccomponentParametrizationChanged(unsigned int id) from SVNetworkComponentEditWidget */
	void on_componentParametrizationChanged(unsigned int id);
	/*! Connected to singal heatExchangeChanged()from SVNetworkComponentEditWidget */
	void on_heatExchangeChanged(VICUS::NetworkHeatExchange::ModelType modelType);
	/*! Connected to singal externallyDefinedStateChanged()from SVNetworkComponentEditWidget */
	void on_externallyDefinedStateChanged(bool checked);

private:
	/*! Connected to slot newBlockSelected() in SVBMSceneManager, updates the widgets displaying informations of selected Block.
		if connectorBlock or Entrance/Exits blocks are selected, reset all widgets displaying informations  */
	void blockSelectedEvent();
	/*! Connected to slot newConnectorSelected(). Evaluates if Connector is deletable, if yes, activate removeButton */
	void connectorSelectedEvent(const QString & sourceSocketName, const QString & targetSocketName);
	/*! Connected to selectionCleared() in SVBMSceneManager, resets all widgets and buttons that were activated when selcting Blocks or Connectors */
	void selectionClearedEvent();
	/*! Creates the ToolBox, also used to update the ToolBox */
	void updateToolBoxPages();
	/*! sets Network of the SVBMSceneManager. Checks if network already filled, if already filled add the the missing values of BMBlock that were not directly saved in the XML from networkElements
	 *   if not filled, create new Block by iterating over all NetworkElements in m_subNetwork, positions the Blocks
	 *   so that each Block following block has the same distance from the previous block*/
	void updateNetwork();
	/*! Checks BMNetwork of m_sceneManager if it is valid. Iterates over all Blocks and checks if all Sockets are connected
	 *  and checks if all blocks are reachable by the globalInlet and globalOutlet*/
	bool checkAcceptedNetwork();
	/*! gets called when the Dialog is accepted and closed. Deletes all unused components from the vector,
	 * updates networkElements in the SubNetwork and copies all components into the SubNetwork */
	void on_buttonBox_accepted();
	/*! gets called when the Dialog is rejected and closed. Closes the Dialog. Any changes will be lost */
	void on_buttonBox_rejected();
	/*! gets called when the name of a Block is changed. Sets the name in the displayName attribute of the BMBlock,
	 *  updates view immediately */
	void on_NameTextChanged(const QString &text);
	/*! gets called when a new Block is dragged from the ToolBox into the scene */
	void on_newBlockAdded(VICUS::BMBlock *block, unsigned int componentID);
	/*! Recognises keyboard presses */
	void keyPressEvent(QKeyEvent *event) override;
	/*! Takes the componentID of a component and returns the index in the component Vector */
	unsigned int componentIndex(unsigned int componentID);
	/*! Generates new unique ComponentID */
	unsigned int newComponentID();
	/*! Convert old Subnetwork (SIM-VICUS version < 1.1) to new Subnetwork by copying components out of Database into Subnetwork */
	void convertSubnetwork();
	/*! Opens a dialog to change or assign the name of a component */
	void openDBComponentNamingDialog(VICUS::NetworkComponent* component);
	/*! Checks for validity of NetworkElements */
	void checkValidityOfNetworkElements();
	/*! Checks if the data in NetworkElement is compatible with the data in BMNetwork, called in updateNetwork() */
	bool checkValidityOfNetworkElementsAndGraphicalNetwork();
	/*! erases previous graphical Network and fills scene with blocks and connectors */
	void createNewScene();
	/*! returns a vector with available NetworkComponent ModelTypes given the current mode */
	std::vector<VICUS::NetworkComponent::ModelType> availableNetworkComponentModelTypes();
	/*! returns all availble database elements given a NetworkComponent ModelType and the current mode */
	std::vector<std::reference_wrapper<VICUS::NetworkComponent>> availableDataBaseElements(VICUS::NetworkComponent::ModelType modelType);

	/*! The UI class. */
	Ui::SVSubNetworkEditDialog									*m_ui;
	/*! SceneManager, handles the objects in the Scene */
	SVBMSceneManager                                            *m_sceneManager = nullptr;
	/*! The database */
	SVDatabase                                                  *m_db = nullptr;
	/*! The Subnetwork that is currently edited */
	VICUS::SubNetwork                                           *m_subNetwork = nullptr;
	/*! Holds all Components of blocks in the Scene. */
	std::vector<VICUS::NetworkComponent>                        m_networkComponents;
	/*! Reference to a table in the Toolbox that currently has a component selected */
	SVSubNetworkEditDialogTable									*m_senderTable = nullptr;
	/*! Holds all Tables in the Toolbox */
	std::vector<SVSubNetworkEditDialogTable*>                   m_tables;
	/*! Current Mode of the Subnetwork. Changes what NetworkComponent Modeltypes and NetworkComponents in the database are available */
	SubnetworkMode												m_mode;
};

#endif // SVSUBNETWORKEDITDIALOGH
