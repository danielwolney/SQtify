#ifndef SPOTIFYCONTROL_H
#define SPOTIFYCONTROL_H

#include <QObject>
#include "api/spotifyprofile.h"

class SpotifyWebApiClient;
class SearchResult;
class HttpRequestManager;

class SpotifyControl : public QObject
{
    Q_OBJECT
public:
    explicit SpotifyControl(HttpRequestManager *httpManager, QObject *parent = nullptr);
    void setAccessToken(QString accessToken);

public slots:
    void retrieveUsersProfile();
    SearchResult *searchTracks(QString term);

signals:
    void needRefreshAccessToken();
    void profileReady();

private:
    SpotifyWebApiClient *m_apiClient;
    SpotifyProfile m_user;
};

#endif // SPOTIFYCONTROL_H
