QT += qml quick opengl

CONFIG += qmltypes
QML_IMPORT_NAME = OpenGLUnderQML
QML_IMPORT_MAJOR_VERSION = 1

HEADERS += \
    OpenGLScene.h \
    Vertex.h \
    color.h \
    cubebuffer.h \
    cubeobject.h \
    graphicalobject.h \
    position.h \
    rotation.h \
    shaderprogram.h \
    spaceshipbuffer.h \
    spaceshipobject.h \
    treebuffer.h \
    treeobject.h \
    vertexbuffer.h
SOURCES += main.cpp \
    OpenGLScene.cpp \
    cubebuffer.cpp \
    cubeobject.cpp \
    graphicalobject.cpp \
    shaderprogram.cpp \
    spaceshipbuffer.cpp \
    spaceshipobject.cpp \
    treebuffer.cpp \
    treeobject.cpp \
    vertexbuffer.cpp
RESOURCES += openglunderqml.qrc

LIBS += -lopengl32 -lglu32

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/openglunderqml
INSTALLS += target
