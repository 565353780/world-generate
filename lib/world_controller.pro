QT -= gui

TEMPLATE = lib
DEFINES += EXPORT_LIBRARY

CONFIG += c++17

HEADERS += \
    export_library_global.h \

INCLUDEPATH += \
    ../src/WorldController

# EasyShape
SOURCES += \
    ../src/WorldController/EasyShape/EasyPoint2D.cpp \
    ../src/WorldController/EasyShape/EasyRect2D.cpp \
    ../src/WorldController/EasyShape/EasyLine2D.cpp \
    ../src/WorldController/EasyShape/EasyIntersection2D.cpp \
    ../src/WorldController/EasyShape/EasyPolygon2D.cpp \
    ../src/WorldController/EasyShape/EasyComputation.cpp

HEADERS += \
    ../src/WorldController/EasyShape/EasyPoint2D.h \
    ../src/WorldController/EasyShape/EasyRect2D.h \
    ../src/WorldController/EasyShape/EasyLine2D.h \
    ../src/WorldController/EasyShape/EasyIntersection2D.h \
    ../src/WorldController/EasyShape/EasyPolygon2D.h \
    ../src/WorldController/EasyShape/EasyComputation.h

HEADERS += \
    ../src/WorldController/EasyShape/EasyShape.h

# EasyWorld
SOURCES += \
    ../src/WorldController/EasyWorld/EasyAxis2D.cpp \
    ../src/WorldController/EasyWorld/EasyNode.cpp \
    ../src/WorldController/EasyWorld/EasyTree.cpp \
    ../src/WorldController/EasyWorld/BoundaryLineManager.cpp \
    ../src/WorldController/EasyWorld/PointMatrix.cpp \
    ../src/WorldController/EasyWorld/WallGenerator.h.cpp \
    ../src/WorldController/EasyWorld/WorldController.cpp \
    ../src/WorldController/EasyWorld/WorldPlaceGenerator.cpp \
    ../src/WorldController/EasyWorld/WorldDescriptor.cpp \
    ../src/WorldController/EasyWorld/WorldEditor.cpp \
    ../src/WorldController/EasyWorld/WorldReward.cpp \
    ../src/WorldController/EasyWorld/WorldEnvironment.cpp

HEADERS += \
    ../src/WorldController/EasyWorld/EasyAxis2D.h \
    ../src/WorldController/EasyWorld/EasyNode.h \
    ../src/WorldController/EasyWorld/EasyTree.h \
    ../src/WorldController/EasyWorld/BoundaryLineManager.h \
    ../src/WorldController/EasyWorld/PointMatrix.h \
    ../src/WorldController/EasyWorld/WallGenerator.h \
    ../src/WorldController/EasyWorld/WorldController.h \
    ../src/WorldController/EasyWorld/WorldPlaceGenerator.h \
    ../src/WorldController/EasyWorld/WorldDescriptor.h \
    ../src/WorldController/EasyWorld/WorldEditor.h \
    ../src/WorldController/EasyWorld/WorldReward.h \
    ../src/WorldController/EasyWorld/WorldEnvironment.h

HEADERS += \
    ../src/WorldController/EasyWorld/EasyWorld.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

