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
DEPENDPATH += ../lib
HEADERS += \
    ../lib/export_library_global.h \

LIBS += -L../lib/ -lWorldEnvironment

INCLUDEPATH += WorldEnvironment

# EasyShape
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
    WorldEnvironment/EasyWorld/WorldReward.h \
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

