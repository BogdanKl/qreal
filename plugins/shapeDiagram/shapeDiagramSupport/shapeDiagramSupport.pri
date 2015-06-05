QT += xml widgets

TEMPLATE = lib
CONFIG += c++11

DESTDIR = ../../../bin
MOC_DIR = .moc

INCLUDEPATH += \
	$$PWD/../../.. \
	$$PWD/../../../qrgui/ \

LIBS += -L../../../bin -lqrkernel -lqrutils -lqrmc
DEFINES += SHAPE_DIAGRAM_GENERATOR_LIBRARY

HEADERS = \
	shapeDiagram.h \
	shapeDiagramSupportPlugin.h \
	shapeDiagramGenerator.h \

SOURCES = \
	shapeDiagramSupportPlugin.cpp \
	shapeDiagramGenerator.cpp \
