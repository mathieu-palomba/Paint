#-------------------------------------------------
#
# Project created by QtCreator 2013-09-19T16:32:29
#
#-------------------------------------------------

QT       += core gui

TARGET = Paint
TEMPLATE = app

INCLUDEPATH += headers/ \
    headers/window/ \
    headers/shapes/ \
    headers/factory/

SOURCES += src/main.cpp \
    src/window/mainwindow.cpp \
    src/myPainter.cpp \
    src/shapes/freehand.cpp \
    src/shapes/line.cpp \
    src/shapes/shape.cpp \
    src/shapes/rectangle.cpp \
    src/shapes/circle.cpp \
    src/factory/shapeFactory.cpp \
    src/shapes/polygon.cpp \
    src/shapes/text.cpp \
    src/shapes/rubber.cpp

HEADERS  += headers/window/mainwindow.h \
    headers/myPainter.h \
    headers/defines.h \
    headers/shapes/shape.h \
    headers/shapes/freehand.h \
    headers/shapes/line.h \
    headers/shapes/rectangle.h \
    headers/shapes/circle.h \
    headers/factory/shapeFactory.h \
    headers/shapes/polygon.h \
    headers/shapes/text.h \
    headers/shapes/rubber.h

FORMS    += mainwindow.ui

RESOURCES += Icones.qrc
