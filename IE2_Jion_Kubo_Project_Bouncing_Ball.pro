TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/Users/kuboj/Documents/GitHub/Information_Engineering_2/SFML-2.5.1/include"

LIBS += -L"C:/Users/kuboj/Documents/GitHub/Information_Engineering_2/SFML-2.5.1/lib"
LIBS += -L"C:/Users/kuboj/Documents/GitHub/Information_Engineering_2/SFML-2.5.1/bin"

# Linking SFML libraries
LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window

# Debug configuration
# Uncomment the following lines if you want to link debug SFML libraries for debug builds
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
}

# List your source files here
SOURCES += \
        Ball.cpp \
        Game.cpp \
        Paddle.cpp \
        Wall.cpp \
        main.cpp

HEADERS += \
    Ball.h \
    Game.h \
    Paddle.h \
    Wall.h
