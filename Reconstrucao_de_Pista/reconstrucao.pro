QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    menu.cpp \
    qcustomplot.cpp

HEADERS += \
    menu.h \
    qcustomplot.h

FORMS += \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:/Users/USER/Downloads/SFML-2.6.1-sources/SFML-2.6.1/include \
               C:/Users/USER/Documents/Reconstrucao_de_Pista/header \
               C:/Users/USER/Documents/Reconstrucao_de_Pista/source \

DEPENDPATH += C:/Users/USER/Downloads/SFML-2.6.1-sources/SFML-2.6.1/include \

QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)

LIBS += -LC:/Users/USER/Downloads/SFML-2.6.1-sources/build-SFML-2.6.1-Desktop_Qt_6_6_0_MinGW_64_bit-Release/lib \
        -LC:/Users/USER/Downloads/SFML-2.6.1-sources/build-SFML-2.6.1-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/libc

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d  -lsfml-graphics-d  -lsfml-main-d  -lsfml-network-d  -lsfml-system-d  -lsfml-window-d
CONFIG(release, debug|release): LIBS += -lsfml-audio  -lsfml-graphics  -lsfml-main  -lsfml-network  -lsfml-system  -lsfml-window

DISTFILES += \
    QXlsx.pri \
    naosei.xlsx

SUBDIRS += \
    QXlsx.pro
