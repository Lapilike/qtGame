QT       += core gui opengl
QT += openglwidgets

LIBS += -lopengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animation.cpp \
    chest.cpp \
    collisionbox.cpp \
    enemy.cpp \
    entity.cpp \
    inventory.cpp \
    item.cpp \
    main.cpp \
    gamewindow.cpp \
    map.cpp \
    obj.cpp \
    opengl.cpp \
    player.cpp \
    spriterenderer.cpp \
    stats.cpp \
    tile.cpp

HEADERS += \
    animation.h \
    chest.h \
    collisionbox.h \
    enemy.h \
    entity.h \
    gamewindow.h \
    inventory.h \
    item.h \
    map.h \
    obj.h \
    opengl.h \
    player.h \
    spriterenderer.h \
    stats.h \
    tile.h

FORMS += \
    gamewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Textures.qrc
