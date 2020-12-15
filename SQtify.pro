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

INCLUDEPATH += $$PWD/src/

SOURCES += \
    src/control/appcontrol.cpp \
    src/database/dbconnection.cpp \
    src/networking/httpdownload.cpp \
    src/networking/httprequestmanager.cpp \
    src/util/jsonparser.cpp \
    src/ui/loginform.cpp \
    main.cpp \
    src/ui/mainform.cpp \
    src/ui/mainwindow.cpp \
    src/service/oauth2authorizationservice.cpp \
    src/model/playlistmodel.cpp \
    src/model/playliststrackmodel.cpp \
    src/control/spotifycontrol.cpp \
    src/api/spotifyprofile.cpp \
    src/api/spotifywebapiclient.cpp

HEADERS += \
    src/control/appcontrol.h \
    src/database/dbconnection.h \
    src/networking/httpdownload.h \
    src/networking/httprequestmanager.h \
    src/util/jsonparser.h \
    src/ui/loginform.h \
    src/ui/mainform.h \
    src/ui/mainwindow.h \
    src/service/oauth2authorizationservice.h \
    src/model/playlistmodel.h \
    src/model/playliststrackmodel.h \
    src/control/spotifycontrol.h \
    src/api/spotifyprofile.h \
    src/api/spotifyurls.h \
    src/api/spotifywebapiclient.h

FORMS += \
    src/ui/loginform.ui \
    src/ui/mainform.ui \
    src/ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/res.qrc
