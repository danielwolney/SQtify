#ifndef APPCONTROL_H
#define APPCONTROL_H

#include <QObject>

class OAuth2AuthorizationService;

class SpotifyControl;
class SearchResult;

class AppControl : public QObject
{
    Q_OBJECT
public:
    explicit AppControl(QObject *parent = nullptr);

public:
    bool hasAccess();

public slots:
    void grantAccess();
    void refreshAccessToken();
    SearchResult *searchTracks(QString term);

signals:
    void accessGranted();

private:
    void setAccessToken(QString accessToken);

    OAuth2AuthorizationService *m_authService;
    SpotifyControl *m_spotifyControl;

};

#endif // APPCONTROL_H
