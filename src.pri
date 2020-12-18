INCLUDEPATH += $$PWD/src/

SOURCES += \
    src/api/searchresult.cpp \
    src/control/appcontrol.cpp \
    src/database/dbconnection.cpp \
    src/media/mediaplayer.cpp \
    src/model/localtracksmodel.cpp \
    src/model/tracksearchresultmodel.cpp \
    src/networking/httpdownload.cpp \
    src/networking/httprequestmanager.cpp \
    src/ui/actionlistview.cpp \
    src/ui/playerwidget.cpp \
    src/ui/searchresultwidget.cpp \
    src/util/jsonparser.cpp \
    src/ui/loginform.cpp \
    src/ui/mainform.cpp \
    src/ui/mainwindow.cpp \
    src/auth/oauth2authorization.cpp \
    src/model/playlistmodel.cpp \
    src/control/spotifycontrol.cpp \
    src/api/spotifyprofile.cpp \
    src/api/spotifywebapiclient.cpp

HEADERS += \
    src/api/searchresult.h \
    src/control/appcontrol.h \
    src/database/dbconnection.h \
    src/media/mediaplayer.h \
    src/model/localtracksmodel.h \
    src/model/tracksearchresultmodel.h \
    src/networking/httpdownload.h \
    src/networking/httprequestmanager.h \
    src/ui/actionlistview.h \
    src/ui/playerwidget.h \
    src/ui/searchresultwidget.h \
    src/util/jsonparser.h \
    src/ui/loginform.h \
    src/ui/mainform.h \
    src/ui/mainwindow.h \
    src/auth/oauth2authorization.h \
    src/model/playlistmodel.h \
    src/control/spotifycontrol.h \
    src/api/spotifyprofile.h \
    src/api/spotifyurls.h \
    src/api/spotifywebapiclient.h

FORMS += \
    src/ui/loginform.ui \
    src/ui/mainform.ui \
    src/ui/mainwindow.ui \
    src/ui/playerwidget.ui \
    src/ui/searchresultwidget.ui

RESOURCES += \
    res/res.qrc
