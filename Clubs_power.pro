QT       += core gui
QT +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Tuple_gen.cpp \
    add_client.cpp \
    add_manager.cpp \
    add_medstuff.cpp \
    add_stuff.cpp \
    add_trainer.cpp \
    autorization.cpp \
    clientinfo.cpp \
    dialogemploystuff.cpp \
    main.cpp \
    main_handler.cpp \
    mainwidget.cpp \
    managerinfo.cpp \
    stufflist.cpp

HEADERS += \
    Tuple_gen.h \
    add_client.h \
    add_manager.h \
    add_medstuff.h \
    add_stuff.h \
    add_trainer.h \
    autorization.h \
    clientinfo.h \
    dialogemploystuff.h \
    main_handler.h \
    mainwidget.h \
    managerinfo.h \
    stufflist.h

FORMS += \
    add_client.ui \
    add_manager.ui \
    add_medstuff.ui \
    add_trainer.ui \
    clientinfo.ui \
    dialogemploystuff.ui \
    form.ui \
    mainwidget.ui \
    managerinfo.ui \
    stufflist.ui

TRANSLATIONS += \
    Clubs_power_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
