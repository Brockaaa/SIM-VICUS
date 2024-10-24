import QtQuick 2.15
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Window {
	flags: Qt.Window | Qt.WindowStaysOnTopHint
	modality: Qt.ApplicationModal
	id: mapRectangle
	property int widgetWidth: 800
	property int widgetHeight: 500
	width: widgetWidth
	height: widgetHeight

	signal okClicked()
	signal cancelClicked()

	visible: true
	visibility: Window.Windowed


	Component.onCompleted: {
		mapRectangle.requestActivate()
	}

	Plugin {
		id: mapPlugin
		name: "osm"
		PluginParameter { name: "osm.useragent"; value: "SIM-VICUS" }
		PluginParameter { name: "osm.mapping.custom.host"; value: "http://tile.openstreetmap.org/" }
		PluginParameter { name: "osm.mapping.custom.mapcopyright"; value: "OpenStreetMap contributors" }
	}

	Map {
		id: map
		objectName: "mapObject"
		anchors.fill: parent
		Layout.fillWidth: true
		Layout.fillHeight: true
		plugin: mapPlugin
		center: QtPositioning.coordinate(52.5162726, 13.3777517) // Berlin, Brandenburger Tor
		zoomLevel: 14
		activeMapType: supportedMapTypes[supportedMapTypes.length - 1]

		PinchHandler {
			id: pinch
			target: null
			onActiveChanged: if (active) {
				map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
			}
			onScaleChanged: (delta) => {
				map.zoomLevel += Math.log2(delta)
				map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
			}
			onRotationChanged: (delta) => {
				map.bearing -= delta
				map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
			}
			grabPermissions: PointerHandler.TakeOverForbidden
		}
		WheelHandler {
			id: wheel
			// workaround for QTBUG-87646 / QTBUG-112394 / QTBUG-112432:
			// Magic Mouse pretends to be a trackpad but doesn't work with PinchHandler
			// and we don't yet distinguish mice and trackpads on Wayland either
			acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
							 ? PointerDevice.Mouse | PointerDevice.TouchPad
							 : PointerDevice.Mouse
			rotationScale: 1/120
			property: "zoomLevel"
		}

		function getBoundingBox() {
			var topLeft = map.toCoordinate(Qt.point(0, 0))
			var bottomRight = map.toCoordinate(Qt.point(map.width, map.height))
			return {
				northWest: { latitude: topLeft.latitude, longitude: topLeft.longitude },
				southEast: { latitude: bottomRight.latitude, longitude: bottomRight.longitude }
			}
		}

		MouseArea {
			id: drag
			property var target: null
			onMouseXChanged: map.pan(-mouseX, -mouseY)
			onMouseYChanged: map.pan(-mouseX, -mouseY)
		}
		Shortcut {
			enabled: map.zoomLevel < map.maximumZoomLevel
			sequence: StandardKey.ZoomIn
			onActivated: map.zoomLevel = Math.round(map.zoomLevel + 1)
		}
		Shortcut {
			enabled: map.zoomLevel > map.minimumZoomLevel
			sequence: StandardKey.ZoomOut
			onActivated: map.zoomLevel = Math.round(map.zoomLevel - 1)
		}
	}

	// Container for buttons and text with semi-transparent background
	Rectangle {
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.margins: 0
		width: buttonLayout.width + 31  // Add padding around the content
		height: buttonLayout.height + infoText.height + 10 // Add padding and space for text
		color: "#90000000"  // Semi-transparent black (alpha: 0x80)

		RowLayout {
			id: buttonLayout
			anchors.right: parent.right
			anchors.bottom: parent.bottom
			anchors.margins: 16
			spacing: 5

			Button {
				text: "Import"
				onClicked: {
					mapRectangle.okClicked()
				}
			}

			Button {
				text: "Cancel"
				onClicked: {
					mapRectangle.cancelClicked()
				}
			}
		}

		Text {
			id: infoText
			anchors.top: buttonLayout.bottom
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.margins: 2
			text: "Entire visible map will be imported."
			color: "white"
			font.pixelSize: 12
		}
	}
}
