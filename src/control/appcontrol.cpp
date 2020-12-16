#include "appcontrol.h"
#include "service/oauth2authorizationservice.h"
#include "spotifycontrol.h"

AppControl::AppControl(QObject *parent) : QObject(parent),
    m_authService(new OAuth2AuthorizationService(this)),
    m_spotifyControl(new SpotifyControl())
{
    connect(m_authService, &OAuth2AuthorizationService::accessGranted,
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

void AppControl::setAccessToken(QString accessToken)
{
    m_spotifyControl->setAccessToken(accessToken);
}
