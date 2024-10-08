# CMakeLists.txt file for Sim-Vicus data model library
#
# Note: This CMakeLists.txt file is not for stand-alone builds.
#       Requires toplevel CMakeLists.txt file that defines the variable
#       KEYWORDLISTCREATOR.

project( VicOSM )

include_directories(
	${PROJECT_SOURCE_DIR}/../../src
	${PROJECT_SOURCE_DIR}/../../../IBK/src
	${PROJECT_SOURCE_DIR}/../../../IBKMK/src
	${PROJECT_SOURCE_DIR}/../../../TiCPP/src
	${PROJECT_SOURCE_DIR}/../../../Nandrad/src
	${Qt5Widgets_INCLUDE_DIRS}
)

# collect a list of all source files of VicOSM library
file( GLOB VicOSM_LIB_SRCS ${PROJECT_SOURCE_DIR}/../../src/*.cpp )
file( GLOB VicOSM_NCG_LIB_SRCS ${PROJECT_SOURCE_DIR}/../../src/ncg/*.cpp )

# add VICUS_KeywordList.cpp
set( VicOSM_LIB_SRCS
	${VicOSM_LIB_SRCS}
	${VicOSM_NCG_LIB_SRCS}
	${PROJECT_SOURCE_DIR}/../../../VicOSM/src/VicOSM_KeywordList.cpp
)

# collect a list of all header files of VicOSM library
file( GLOB VicOSM_HDRS ${PROJECT_SOURCE_DIR}/../../src/*.h )

# run the KeywordListCreator tool whenever the header files have changed
# to update the VICUS_KeywordList.h and VICUS_KeywordList.cpp file
add_custom_command (
	OUTPUT   ${PROJECT_SOURCE_DIR}/../../../VicOSM/src/VicOSM_KeywordList.cpp
	DEPENDS  ${VicOSM_HDRS} NandradCodeGenerator
	COMMAND  NandradCodeGenerator
	ARGS     VicOSM ${PROJECT_SOURCE_DIR}/../../src 1 VicOSM ncg
)

# build the library
add_library( VicOSM STATIC
	${VicOSM_LIB_SRCS}
)

