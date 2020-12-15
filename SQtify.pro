QT       += core gui network networkauth sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appcontrol.cpp \
    dbconnection.cpp \
    httpdownload.cpp \
    httprequestmanager.cpp \
    jsonparser.cpp \
    loginform.cpp \
    main.cpp \
    mainform.cpp \
    mainwindow.cpp \
    oauth2authorizationservice.cpp \
    playlistmodel.cpp \
    playliststrackmodel.cpp \
    spotifycontrol.cpp \
    spotifyprofile.cpp \
    spotifywebapiclient.cpp

HEADERS += \
    appcontrol.h \
    dbconnection.h \
    httpdownload.h \
    httprequestmanager.h \
    jsonparser.h \
    loginform.h \
    mainform.h \
    mainwindow.h \
    oauth2authorizationservice.h \
    playlistmodel.h \
    playliststrackmodel.h \
    spotifycontrol.h \
    spotifyprofile.h \
    spotifyurls.h \
    spotifywebapiclient.h

FORMS += \
    loginform.ui \
    mainform.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/res.qrc
