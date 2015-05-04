HEADERS += \
    include/Bomberman.h \
    include/Scene.h \
    include/Bomb.h \
    include/MetalBlock.h \
    include/MapLoader.h \
    include/CrackBlock.h \
    include/Floor.h \
    include/Explosion.h

SOURCES += \
    src/Main.cpp \
    src/OBJLoader.cpp \
    src/Vec.cpp \
    src/Bomberman.cpp \
    src/Bomb.cpp \
    src/MetalBlock.cpp \
    src/MapLoader.cpp \
    src/CrackBlock.cpp \
    src/Floor.cpp \
    src/Explosion.cpp

OTHER_FILES += \
    models/Bomberman.obj \
    models/Bomb.obj \
    models/Metal_Block.obj \
    models/Explosion.obj \
    models/Crack_Block.obj \
    models/Floor.obj \
    textures/Bomberman_Texture.png \
    textures/BombTexture.png \
    textures/MetalBlockTexture.png \
    textures/CrackedBlockTexture.png \
    textures/Explosion.png \
    textures/FloorTexture.png \
    data/Map.txt


QT += core
QT -= opengl
CONFIG-=app_bundle
DESTDIR=./
OBJECTS_DIR=obj
INCLUDEPATH += header
INCLUDEPATH += usr/local/lib
INCLUDEPATH += include/
INCLUDEPATH += data/
QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64
linux-g++:QMAKE_CXXFLAGS += -march=native
linux-g++-64:QMAKE_CXXFLAGS += -march=native
QMAKE_CXXFLAGS+=$$system(sdl2-config --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)
LIBS+=$$system(sdl2-config --libs)
LIBS += -lglut -lGLU -lSDL2_image
message(output from sdl2-config --libs added to LIB=$$LIBS)
LIBS += -L/usr/local/lib
macx:LIBS+= -framework OpenGL
macx:DEFINES+=DARWIN
linux-* {
DEFINES += LINUX
LIBS+= -lGLEW
}
linux-clang {
DEFINES += LINUX
LIBS+= -lGLEW
}
