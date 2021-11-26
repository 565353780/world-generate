QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win32{
DESTDIR = ../bin_win
}
unix{
DESTDIR = ../bin_linux
}

INCLUDEPATH += ../lib
HEADERS += \
    ../lib/export_library_global.h \

INCLUDEPATH += WorldEnvironment

# EasyShape
SOURCES += \
    WorldEnvironment/EasyShape/EasyPoint2D.cpp \
    WorldEnvironment/EasyShape/EasyRect2D.cpp \
    WorldEnvironment/EasyShape/EasyLine2D.cpp \
    WorldEnvironment/EasyShape/EasyIntersection2D.cpp \
    WorldEnvironment/EasyShape/EasyPolygon2D.cpp \
    WorldEnvironment/EasyShape/EasyComputation.cpp

HEADERS += \
    WorldEnvironment/EasyShape/EasyPoint2D.h \
    WorldEnvironment/EasyShape/EasyRect2D.h \
    WorldEnvironment/EasyShape/EasyLine2D.h \
    WorldEnvironment/EasyShape/EasyIntersection2D.h \
    WorldEnvironment/EasyShape/EasyPolygon2D.h \
    WorldEnvironment/EasyShape/EasyComputation.h

HEADERS += \
    WorldEnvironment/EasyShape/EasyShape.h

# EasyWorld
SOURCES += \
    WorldEnvironment/EasyWorld/EasyAxis2D.cpp \
    WorldEnvironment/EasyWorld/EasyNode.cpp \
    WorldEnvironment/EasyWorld/EasyTree.cpp \
    WorldEnvironment/EasyWorld/BoundaryLineManager.cpp \
    WorldEnvironment/EasyWorld/PointMatrix.cpp \
    WorldEnvironment/EasyWorld/WallGenerator.cpp \
    WorldEnvironment/EasyWorld/WorldController.cpp \
    WorldEnvironment/EasyWorld/WorldPlaceGenerator.cpp \
    WorldEnvironment/EasyWorld/WorldDescriptor.cpp \
    WorldEnvironment/EasyWorld/WorldEditor.cpp \
    WorldEnvironment/EasyWorld/WorldObservation.cpp \
    WorldEnvironment/EasyWorld/WorldEnvironment.cpp

HEADERS += \
    WorldEnvironment/EasyWorld/EasyAxis2D.h \
    WorldEnvironment/EasyWorld/EasyNode.h \
    WorldEnvironment/EasyWorld/EasyTree.h \
    WorldEnvironment/EasyWorld/BoundaryLineManager.h \
    WorldEnvironment/EasyWorld/PointMatrix.h \
    WorldEnvironment/EasyWorld/WallGenerator.h \
    WorldEnvironment/EasyWorld/WorldController.h \
    WorldEnvironment/EasyWorld/WorldPlaceGenerator.h \
    WorldEnvironment/EasyWorld/WorldDescriptor.h \
    WorldEnvironment/EasyWorld/WorldEditor.h \
    WorldEnvironment/EasyWorld/WorldObservation.h \
    WorldEnvironment/EasyWorld/WorldEnvironment.h

HEADERS += \
    WorldEnvironment/EasyWorld/EasyWorld.h

SOURCES += \
    main.cpp \
    EasyWorldWidget.cpp \
    MainWindow.cpp

HEADERS += \
    EasyWorldWidget.h \
    MainWindow.h

FORMS += \
    EasyWorldWidget.ui \
    MainWindow.ui

TRANSLATIONS += \
    WorldEnvironment_zh_CN.ts

CONFIG += lrelease
# CONFIG += debug
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

