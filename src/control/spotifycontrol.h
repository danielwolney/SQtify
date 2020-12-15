#ifndef SPOTIFYCONTROL_H
#define SPOTIFYCONTROL_H

#include <QObject>
#include "api/spotifyprofile.h"

class SpotifyWebApiClient;

class SpotifyControl : public QObject
{
    Q_OBJECT
public:
    explicit SpotifyControl(QObject *parent = nullptr);
    void setAccessToken(QString accessToken);

public slots:
    void retrieveUsersProfile();

signals:
    void needRefreshAccessToken();
    void profileReady();

private:
    SpotifyWebApiClient *m_apiClient;
    SpotifyProfile m_user;
};

#endif // SPOTIFYCONTROL_H
