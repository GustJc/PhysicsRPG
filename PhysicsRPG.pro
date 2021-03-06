TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/TextureManager.cpp \
    src/TestState.cpp \
    src/State.cpp \
    src/SpriteBody.cpp \
    src/PolygonBody.cpp \
    src/MapState.cpp \
    src/main.cpp \
    src/Globals.cpp \
    src/GameState.cpp \
    src/GameObject.cpp \
    src/GameManager.cpp \
    src/Flag.cpp \
    src/Entity.cpp \
    src/Engine.cpp \
    src/DebugRender.cpp \
    src/ContactListenner.cpp \
    src/Character.cpp \
    src/BoxBody.cpp \
    src/Body.cpp \
    src/Animation.cpp \
    src/MenuState.cpp \
    src/UiButton.cpp \
    src/EditorState.cpp \
    src/PlayerEntity.cpp \
    src/Map.cpp \
    src/Spawner.cpp \
    src/Effects.cpp \
    src/Wall.cpp \
    src/Shot.cpp \
    src/WinState.cpp \
    src/LoseState.cpp \
    src/WeakOrc.cpp \
    src/ShotArrow.cpp

HEADERS += \
    include/Animation.h \
    include/Body.h \
    include/BoxBody.h \
    include/Character.h \
    include/ContactListenner.h \
    include/DebugRender.h \
    include/Engine.h \
    include/Entity.h \
    include/Flag.h \
    include/GameManager.h \
    include/GameObject.h \
    include/GameState.h \
    include/Globals.h \
    include/MapState.h \
    include/PolygonBody.h \
    include/SpriteBody.h \
    include/State.h \
    include/TestState.h \
    include/TextureManager.h \
    include/MenuState.h \
    include/UiButton.h \
    include/EditorState.h \
    include/PlayerEntity.h \
    include/Map.h \
    include/Spawner.h \
    include/Effects.h \
    include/Wall.h \
    include/Shot.h \
    include/WinState.h \
    include/LoseState.h \
    include/map.h \
    include/WeakOrc.h \
    include/ShotArrow.h

#SFML
QMAKE_CXXFLAGS += -std=c++11
unix: LIBS += -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
win32: LIBS += -LC:\Library\SFML\SFML-2.1\lib -lsfml-main -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

#Others
LIBS += -lsfml-system -lsfml-graphics -lsfml-window -lBox2D

INCLUDEPATH += include
