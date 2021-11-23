QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32{
DESTDIR = ../bin_win
}
unix{
DESTDIR = ../bin_linux
}

INCLUDEPATH += ../lib
HEADERS += \
    ../lib/export_library_global.h \

CONFIG += c++17

INCLUDEPATH += WorldController

# EasyShape
SOURCES += \
    WorldController/EasyShape/EasyPoint2D.cpp \
    WorldController/EasyShape/EasyRect2D.cpp \
    WorldController/EasyShape/EasyLine2D.cpp \
    WorldController/EasyShape/EasyIntersection2D.cpp \
    WorldController/EasyShape/EasyPolygon2D.cpp \
    WorldController/EasyShape/EasyComputation.cpp

HEADERS += \
    WorldController/EasyShape/EasyPoint2D.h \
    WorldController/EasyShape/EasyRect2D.h \
    WorldController/EasyShape/EasyLine2D.h \
    WorldController/EasyShape/EasyIntersection2D.h \
    WorldController/EasyShape/EasyPolygon2D.h \
    WorldController/EasyShape/EasyComputation.h

HEADERS += \
    WorldController/EasyShape/EasyShape.h

# EasyWorld
SOURCES += \
    WorldController/EasyWorld/EasyAxis2D.cpp \
    WorldController/EasyWorld/EasyNode.cpp \
    WorldController/EasyWorld/EasyTree.cpp \
    WorldController/EasyWorld/BoundaryLineManager.cpp \
    WorldController/EasyWorld/PointMatrix.cpp \
    WorldController/EasyWorld/WallGenerator.cpp \
    WorldController/EasyWorld/WorldController.cpp \
    WorldController/EasyWorld/WorldPlaceGenerator.cpp \
    WorldController/EasyWorld/WorldDescriptor.cpp \
    WorldController/EasyWorld/WorldEditor.cpp \
    WorldController/EasyWorld/WorldReward.cpp \
    WorldController/EasyWorld/WorldEnvironment.cpp

HEADERS += \
    WorldController/EasyWorld/EasyAxis2D.h \
    WorldController/EasyWorld/EasyNode.h \
    WorldController/EasyWorld/EasyTree.h \
    WorldController/EasyWorld/BoundaryLineManager.h \
    WorldController/EasyWorld/PointMatrix.h \
    WorldController/EasyWorld/WallGenerator.h \
    WorldController/EasyWorld/WorldController.h \
    WorldController/EasyWorld/WorldPlaceGenerator.h \
    WorldController/EasyWorld/WorldDescriptor.h \
    WorldController/EasyWorld/WorldEditor.h \
    WorldController/EasyWorld/WorldReward.h \
    WorldController/EasyWorld/WorldEnvironment.h

HEADERS += \
    WorldController/EasyWorld/EasyWorld.h

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
    SpaceController_zh_CN.ts

CONFIG += lrelease
# CONFIG += debug
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

