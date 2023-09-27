#ifndef SVSUBNETWORKEDITDIALOGH
#define SVSUBNETWORKEDITDIALOGH

#include <QDialog>

namespace Ui {
class SVSubNetworkEditDialog;
}

namespace VICUS {
class SubNetwork;
class NetworkComponent;
class NetworkController;
class BMBlock;
}

class SVBMSceneManager;
class SVBMZoomMeshGraphicsView;
class SVDatabase;
class SVNetworkControllerEditDialog;
class SVSubNetworkEditDialogTable;

class SVSubNetworkEditDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SVSubNetworkEditDialog(QWidget *parent = nullptr, VICUS::SubNetwork * subNetwork = nullptr, SVDatabase * db = nullptr);
	/*! D-tor */
	~SVSubNetworkEditDialog();
	/*! Getter for private member ZoomMeshGraphicsView */
	SVBMZoomMeshGraphicsView *zoomMeshGraphicsView();
	/*! sets up Subnetwork and calls setNetwork)= */
	void setupSubNetwork(VICUS::SubNetwork * subNetwork);
	/*! opens window, sets appropriate height and weight values for the Splitter and the Scene */
	void show();
	/*! Gets called whenever the QDialog Window is resized, sets appropriate height values for a wrapper Widget of a QtExtToolBox */
	void resize(int w, int h);


private slots:
	/*! gets called when removeBlockOrConnectorButton is clicked, checks if Block or Connector is selected, then forwards request to SVBMSceneManager */
	void on_removeBlockOrConnectorButton_clicked();
	/*! gets called when the ControllerEditWidgetButton is clicked. Creates new Widget when previously not existed. Also creates new Controller
	 *  when selectedBlock does not previously have one */
	void on_openControllerWidgetButton_clicked();
	/*! get called when removeControllerButton is clicked,
	 *  checks if there is a Controller and afterwards deletes it from the block and vektor */
	void on_removeControllerButton_clicked();
	/*! gets called when copyBlockButton is clicked,
	 * checks if there is a Block selected and calls copyBlock, copied relevant Controller and Component
	 * and adds the vectors. Calls setController to ensure that name of Controller is visible in the view*/
	void on_copyBlockButton_clicked();
	/*! gets called when a Component is selected in the QtExtToolBox. Is connected to SVSubNetworkEditTable
	 *  activates or deactivates the removeControllerFromDBButton */
	void on_componentSelected();
	/*! gets called when addToDBButton is clicked,
	 *  adds component of Block to DB */
	void on_addToDBButton_clicked();
	/*! gets called when removeFromDBButton is clicked,
	 *  removes selected Component from DB if it is not builtIn */
	void on_removeFromUserDBButton_clicked();

private:
	/*! Connected to slot newBlockSelected() in SVBMSceneManager, updates the widgets displaying informations of selected Block.
		if connectorBlock or Entrance/Exits blocks are selected, reset all widgets displaying informations  */
	void blockSelectedEvent();
	/*! Connected to slot newConnectorSelected(). Evaluates if Connector is deletable, if yes, activate removeButton */
	void connectorSelectedEvent(const QString & sourceSocketName, const QString & targetSocketName);
	/*/ Connected to selectionCleared() in SVBMSceneManager, resets all widgets and buttons that were activated when selcting Blocks or Connectors */
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
	 * updates networkElements in the SubNetwork and copies all components and controllers into the SubNetwork */
	void on_buttonBox_accepted();
	/*! gets called when the Dialog is rejected and closed. Closes the Dialog. Any changes will be lost */
	void on_buttonBox_rejected();
	/*! gets called in the controllerDialog window. The updated controller is copied into the Block
	 * and the name of the controller is set in the view */
	void on_controllerDialog_accepted(VICUS::BMBlock *block, VICUS::NetworkController controller);
	/*! gets called when the name of a Block is changed. Sets the name in the displayName attribute of the BMBlock,
	 *  updates view immediately */
	void on_NameTextChanged(const QString &text);
	/*! gets called when a new Block is dragged from the ToolBox into the scene */
	void on_newBlockAdded(VICUS::BMBlock *block, unsigned int componentID);
	/*! Takes the componentID of a component and returns the index in the component Vector */
	unsigned int componentIndex(unsigned int componentID);
	/*! Generates new unique ComponentID */
	unsigned int createNewComponentID();
	/*! Takes tje controllerID of a controller and returns the index in the controller Vector */
	unsigned int controllerIndex(unsigned int controllerID);
	/*! Generates new unique ControllerID */
	unsigned int newControllerID();

	// TODO Maik: transformations funktion: SubNetwork altes format mit db Referenz in neues Format umwandeln bei Aufruf der edit Funktion

	/*! The UI class. */
	Ui::SVSubNetworkEditDialog									*m_ui;
	/*! SceneManager, handles the objects in the Scene */
	SVBMSceneManager                                            *m_sceneManager = nullptr;
	/*! Dialog to create and edit Controller */
	SVNetworkControllerEditDialog                             *m_controllerEditDialog = nullptr;
	/*! The database */
	SVDatabase                                                  *m_db = nullptr;
	/*! The Subnetwork that is currently edited */
	VICUS::SubNetwork                                           *m_subNetwork = nullptr;
	/*! Holds all Components of blocks in the Scene. */
	std::vector<VICUS::NetworkComponent>                        m_networkComponents;
	/*! Holds all Controllers of blocks in the Scene */
	std::vector<VICUS::NetworkController>                       m_networkControllers;
	/*! Reference to a table in the Toolbox that currently has a component selected */
	SVSubNetworkEditDialogTable									*m_senderTable = nullptr;
	/*! Holds all Tables in the Toolbox */
	std::vector<SVSubNetworkEditDialogTable*>                   m_tables;
};

#endif // SVSUBNETWORKEDITDIALOGH
