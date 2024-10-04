# ---------------------------
# Project for VicOSM library
# ---------------------------

TARGET = VicOSM
TEMPLATE = lib

# this pri must be sourced from all our libraries,
# it contains all functions defined for casual libraries
include( ../../../IBK/projects/Qt/IBK.pri )


QT += core gui

unix|mac {
	VER_MAJ = 0
	VER_MIN = 0
	VER_PAT = 0
	VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}
}

LIBS += -lIBK -lIBKMK -lTiCPP

INCLUDEPATH = \
../../src \
../../../IBK/src \
../../../IBKMK/src \
../../../TiCPP/src \

DEPENDPATH = $${INCLUDEPATH}

SOURCES += \
	../../src/VicOSM_AbstractDrawingObject.cpp \
	../../src/VicOSM_AbstractOSMElement.cpp \
	../../src/VicOSM_AbstractOSMObject.cpp \
	../../src/VicOSM_Amenity.cpp \
	../../src/VicOSM_Barrier.cpp \
	../../src/VicOSM_Bridge.cpp \
	../../src/VicOSM_Building.cpp \
	../../src/VicOSM_Highway.cpp \
	../../src/VicOSM_Land.cpp \
	../../src/VicOSM_Leisure.cpp \
	../../src/VicOSM_Natural.cpp \
	../../src/VicOSM_Node.cpp \
	../../src/VicOSM_Place.cpp \
	../../src/VicOSM_Relation.cpp \
	../../src/VicOSM_Tourism.cpp \
	../../src/VicOSM_Water.cpp \
	../../src/VicOSM_Way.cpp \

HEADERS += \
	../../src/VicOSM_AbstractDrawingObject.h \
	../../src/VicOSM_AbstractOSMElement.h \
	../../src/VicOSM_AbstractOSMObject.h \
	../../src/VicOSM_Amenity.h \
	../../src/VicOSM_Area.h \
	../../src/VicOSM_Barrier.h \
	../../src/VicOSM_BoundingBox.h \
	../../src/VicOSM_Bridge.h \
	../../src/VicOSM_Building.h \
	../../src/VicOSM_Circle.h \
	../../src/VicOSM_Highway.h \
	../../src/VicOSM_Land.h \
	../../src/VicOSM_Leisure.h \
	../../src/VicOSM_LineFromPlanes.h \
	../../src/VicOSM_Multipolygon.h \
	../../src/VicOSM_Natural.h \
	../../src/VicOSM_Node.h \
	../../src/VicOSM_Place.h \
	../../src/VicOSM_Relation.h \
	../../src/VicOSM_Tourism.h \
	../../src/VicOSM_Water.h \
	../../src/VicOSM_Way.h \

