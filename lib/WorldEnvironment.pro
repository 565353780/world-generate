QT -= gui

TEMPLATE = lib
DEFINES += EXPORT_LIBRARY

CONFIG += c++17

HEADERS += \
    export_library_global.h \

# PyBind11
INCLUDEPATH += \
    /usr/include/python3.8

INCLUDEPATH += \
    ../src/WorldEnvironment

# EasyShape
SOURCES += \
    ../src/WorldEnvironment/EasyShape/EasyPoint2D.cpp \
    ../src/WorldEnvironment/EasyShape/EasyRect2D.cpp \
    ../src/WorldEnvironment/EasyShape/EasyLine2D.cpp \
    ../src/WorldEnvironment/EasyShape/EasyIntersection2D.cpp \
    ../src/WorldEnvironment/EasyShape/EasyPolygon2D.cpp \
    ../src/WorldEnvironment/EasyShape/EasyComputation.cpp

HEADERS += \
    ../src/WorldEnvironment/EasyShape/EasyPoint2D.h \
    ../src/WorldEnvironment/EasyShape/EasyRect2D.h \
    ../src/WorldEnvironment/EasyShape/EasyLine2D.h \
    ../src/WorldEnvironment/EasyShape/EasyIntersection2D.h \
    ../src/WorldEnvironment/EasyShape/EasyPolygon2D.h \
    ../src/WorldEnvironment/EasyShape/EasyComputation.h

HEADERS += \
    ../src/WorldEnvironment/EasyShape/EasyShape.h

# EasyWorld
SOURCES += \
    ../src/WorldEnvironment/EasyWorld/EasyAxis2D.cpp \
    ../src/WorldEnvironment/EasyWorld/EasyNode.cpp \
    ../src/WorldEnvironment/EasyWorld/EasyTree.cpp \
    ../src/WorldEnvironment/EasyWorld/BoundaryLineManager.cpp \
    ../src/WorldEnvironment/EasyWorld/PointMatrix.cpp \
    ../src/WorldEnvironment/EasyWorld/WallGenerator.cpp \
    ../src/WorldEnvironment/EasyWorld/WorldController.cpp \
    ../src/WorldEnvironment/EasyWorld/WorldPlaceGenerator.cpp \
    ../src/WorldEnvironment/EasyWorld/WorldDescriptor.cpp \
    ../src/WorldEnvironment/EasyWorld/WorldEditor.cpp \
    ../src/WorldEnvironment/EasyWorld/WorldReward.cpp \
    ../src/WorldEnvironment/EasyWorld/WorldEnvironment.cpp

HEADERS += \
    ../src/WorldEnvironment/EasyWorld/EasyAxis2D.h \
    ../src/WorldEnvironment/EasyWorld/EasyNode.h \
    ../src/WorldEnvironment/EasyWorld/EasyTree.h \
    ../src/WorldEnvironment/EasyWorld/BoundaryLineManager.h \
    ../src/WorldEnvironment/EasyWorld/PointMatrix.h \
    ../src/WorldEnvironment/EasyWorld/WallGenerator.h \
    ../src/WorldEnvironment/EasyWorld/WorldController.h \
    ../src/WorldEnvironment/EasyWorld/WorldPlaceGenerator.h \
    ../src/WorldEnvironment/EasyWorld/WorldDescriptor.h \
    ../src/WorldEnvironment/EasyWorld/WorldEditor.h \
    ../src/WorldEnvironment/EasyWorld/WorldReward.h \
    ../src/WorldEnvironment/EasyWorld/WorldEnvironment.h

HEADERS += \
    ../src/WorldEnvironment/EasyWorld/EasyWorld.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

