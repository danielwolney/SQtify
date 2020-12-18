#ifndef APPCONTROL_H
#define APPCONTROL_H

#include <QObject>
#include <QModelIndex>

class OAuth2Authorization;

class SpotifyControl;
class SearchResult;
class MediaPlayer;
class HttpRequestManager;

class AppControl : public QObject
{
    Q_OBJECT
public:
    explicit AppControl(QObject *parent = nullptr);

public:
    bool hasAccess();
    MediaPlayer *player() const;
    HttpRequestManager *requestManager() const;

public slots:
    void grantAccess();
    void refreshAccessToken();
    SearchResult *searchTracks(QString term);
    void startPlaylist(const QModelIndex &index);

signals:
    void accessGranted();

private:
    void setAccessToken(QString accessToken);

    OAuth2Authorization *m_authService;
    HttpRequestManager *m_requestManager;
    SpotifyControl *m_spotifyControl;
    MediaPlayer* m_player;
};

#endif // APPCONTROL_H
