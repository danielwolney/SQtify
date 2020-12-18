#include "appcontrol.h"
#include "auth/oauth2authorization.h"
#include "spotifycontrol.h"
#include "model/localtracksmodel.h"
#include "media/mediaplayer.h"

AppControl::AppControl(QObject *parent) : QObject(parent),
    m_authService(new OAuth2Authorization(this)),
    m_spotifyControl(new SpotifyControl()),
    m_player(new MediaPlayer(this))
{
    connect(m_authService, &OAuth2Authorization::accessGranted,
            this, [&, this](QString accessToken){
        setAccessToken(accessToken);
        emit accessGranted();
    });
    connect(m_spotifyControl, &SpotifyControl::needRefreshAccessToken,
            this, &AppControl::refreshAccessToken);

    setAccessToken(m_authService->accessToken());
}

bool AppControl::hasAccess()
{
    return m_authService->hasAccess();
}

void AppControl::grantAccess()
{
    m_authService->grantAccess();
}

void AppControl::refreshAccessToken()
{
    m_authService->refreshAccessToken();
}

SearchResult *AppControl::searchTracks(QString term)
{
    return m_spotifyControl->searchTracks(term);
}

void AppControl::startPlaylist(const QModelIndex &index)
{
    QJsonObject track;
    QModelIndex currentIndex = index;
    QList<QJsonObject> tracks;
    QString url;
    do {
        track = currentIndex.data(LocalTracksModel::Track).toJsonObject();
        tracks << track;
        currentIndex = currentIndex.siblingAtRow(currentIndex.row()+1);
    } while (currentIndex.isValid());
    m_player->startPlaylist(tracks);
}

void AppControl::setAccessToken(QString accessToken)
{
    m_spotifyControl->setAccessToken(accessToken);
}

MediaPlayer *AppControl::player() const
{
    return m_player;
}
