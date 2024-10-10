import QtQuick 2.15
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6

////Rectangle {
////	id: mapRectangle
////	property int widgetWidth: 0
////	property int widgetHeight: 0
////	width: widgetWidth
////	height: widgetHeight
////	visible: true
//
	//Plugin {
	//	id: mapPlugin
	//	name: "osm"
	//	PluginParameter { name: "osm.useragent"; value: "SIM-VICUS" }
	//	PluginParameter { name: "osm.mapping.custom.host"; value: "http://tile.openstreetmap.org/" }
	//	PluginParameter { name: "osm.mapping.custom.mapcopyright"; value: "OpenStreetMap contributors" }
	//}

	//Map {
	//	id: map
	//	objectName: "mapObject"
	//	anchors.fill: parent
	//	plugin: mapPlugin
	//	center: QtPositioning.coordinate(52.5162726, 13.3777517) // Berlin, Brandenburger Tor
	//	zoomLevel: 14
	//	activeMapType: supportedMapTypes[supportedMapTypes.length - 1]

	//	PinchHandler {
	//		id: pinch
	//		target: null
	//		onActiveChanged: if (active) {
	//			map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
	//		}
	//		onScaleChanged: (delta) => {
	//			map.zoomLevel += Math.log2(delta)
	//			map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
	//		}
	//		onRotationChanged: (delta) => {
	//			map.bearing -= delta
	//			map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
	//		}
	//		grabPermissions: PointerHandler.TakeOverForbidden
	//	}
	//	WheelHandler {
	//		id: wheel
	//		// workaround for QTBUG-87646 / QTBUG-112394 / QTBUG-112432:
	//		// Magic Mouse pretends to be a trackpad but doesn't work with PinchHandler
	//		// and we don't yet distinguish mice and trackpads on Wayland either
	//		acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
	//						 ? PointerDevice.Mouse | PointerDevice.TouchPad
	//						 : PointerDevice.Mouse
	//		rotationScale: 1/120
	//		property: "zoomLevel"
	//	}

	//	function getBoundingBox() {
	//		var topLeft = map.toCoordinate(Qt.point(0, 0))
	//		var bottomRight = map.toCoordinate(Qt.point(map.width, map.height))
	//		return {
	//			northWest: { latitude: topLeft.latitude, longitude: topLeft.longitude },
	//			southEast: { latitude: bottomRight.latitude, longitude: bottomRight.longitude }
	//		}
	//	}

	//	MouseArea {
	//		id: drag
	//		property var target: null
	//		onMouseXChanged: map.pan(-mouseX, -mouseY)
	//		onMouseYChanged: map.pan(-mouseX, -mouseY)
	//	}
	//	Shortcut {
	//		enabled: map.zoomLevel < map.maximumZoomLevel
	//		sequence: StandardKey.ZoomIn
	//		onActivated: map.zoomLevel = Math.round(map.zoomLevel + 1)
	//	}
	//	Shortcut {
	//		enabled: map.zoomLevel > map.minimumZoomLevel
	//		sequence: StandardKey.ZoomOut
	//		onActivated: map.zoomLevel = Math.round(map.zoomLevel - 1)
	//	}
	//}
//}
