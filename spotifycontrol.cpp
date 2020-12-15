#include "spotifycontrol.h"
#include "spotifyurls.h"
#include "jsonparser.h"
#include "spotifywebapiclient.h"

SpotifyControl::SpotifyControl(QObject *parent) : QObject(parent),
    m_apiClient(new SpotifyWebApiClient())
{
    connect(m_apiClient, &SpotifyWebApiClient::expiredToken, this, &SpotifyControl::needRefreshAccessToken);
    connect(m_apiClient, &SpotifyWebApiClient::accessTokenChanged,
            this, &SpotifyControl::retrieveUsersProfile);
    m_user = SpotifyProfile::load();
}

void SpotifyControl::setAccessToken(QString accessToken)
{
    m_apiClient->setAccesToken(accessToken);
}

void SpotifyControl::retrieveUsersProfile()
{
    m_apiClient->get(API_BASE"/me", [&, this](const HttpResponse response) {
        switch(response.httpStatusCode) {
        case HttpRequestManager::OK:
            QJsonObject me = JSONParser::toObject(response.data);
            SpotifyProfile profile = SpotifyProfile::fromJson(me);
            if (m_user.id().isEmpty() || profile.id() != m_user.id()) {
                m_user = profile;
                SpotifyProfile::save(m_user);
            }
            emit profileReady();
            break;
        }
    });
}
