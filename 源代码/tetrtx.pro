QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changebackground.cpp \
    changebgm.cpp \
    changeboard.cpp \
    changecolor.cpp \
    changekey.cpp \
    file.cpp \
    instruction.cpp \
    key.cpp \
    main.cpp \
    rank.cpp \
    saverank.cpp \
    selectmode.cpp \
    setting.cpp \
    tetrixboard.cpp \
    tetrixboard1.cpp \
    tetrixboard2.cpp \
    tetrixdoublewindow.cpp \
    tetrixeasywindow.cpp \
    tetrixpiece.cpp \
    tetrixwindow.cpp \
    widget.cpp

HEADERS += \
    changebackground.h \
    changebgm.h \
    changeboard.h \
    changecolor.h \
    changekey.h \
    file.h \
    instruction.h \
    key.h \
    rank.h \
    saverank.h \
    selectmode.h \
    setting.h \
    tetrixboard.h \
    tetrixboard1.h \
    tetrixboard2.h \
    tetrixdoublewindow.h \
    tetrixeasywindow.h \
    tetrixpiece.h \
    tetrixwindow.h \
    widget.h

FORMS += \
    changebackground.ui \
    changebgm.ui \
    changeboard.ui \
    changecolor.ui \
    changekey.ui \
    file.ui \
    instruction.ui \
    key.ui \
    rank.ui \
    saverank.ui \
    selectmode.ui \
    setting.ui \
    tetrixdoublewindow.ui \
    tetrixeasywindow.ui \
    tetrixwindow.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
