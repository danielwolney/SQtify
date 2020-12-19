include(gtest_dependency.pri)

QT += core testlib gui network networkauth sql multimedia svg

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
PKGCONFIG += openssl

DEFINES += TESTS

include(src.pri)

SOURCES += \
    tst/main.cpp \
    tst/api/searchresult_tst.cpp \
    tst/api/spotifywebapiclient_tst.cpp \
    tst/auth/oauth2authorization_tst.cpp

HEADERS += \
    tst/api/mockspotifywebapiclient.h \
    tst/networking/mockhttprequestmanager.h
