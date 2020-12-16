#include "spotifycontrol.h"
#include "api/spotifyurls.h"
#include "util/jsonparser.h"
#include "api/spotifywebapiclient.h"
#include "api/spotifyprofile.h"
#include "api/searchresult.h"
#include <QUrlQuery>

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
    m_apiClient->get(URL_BASE"/me", [&, this](const HttpResponse response) {
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

SearchResult *SpotifyControl::searchTracks(QString term)
{
    QUrlQuery query(URL_BASE"/search?");
    query.addQueryItem("q", term);
    query.addQueryItem("type", "track");
    query.addQueryItem("offset", "0");
    query.addQueryItem("limit", "50");
    auto result = new SearchResult(term, "track", m_apiClient);
    m_apiClient->get(query.toString(QUrl::EncodeSpaces), [&, result](const HttpResponse response) {
        switch(response.httpStatusCode) {
        case HttpRequestManager::OK:
            QJsonObject res = JSONParser::toObject(response.data);
            result->addResultPage(res);
            break;
        }
    });
    return result;
}

