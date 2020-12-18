#ifndef MOCKSPOTIFYWEBAPICLIENT_H
#define MOCKSPOTIFYWEBAPICLIENT_H

#include <gmock/gmock.h>
#include "api/spotifywebapiclient.h"

class MockSpotifyWebApiClient: public SpotifyWebApiClient
{
public:
    MOCK_METHOD(void, setAccesToken, (QString accessToken), (override));
    MOCK_METHOD(void, get, (QString apiResource, HttpRequestManager::OnFinished onResponse), (override));
};

#endif // MOCKSPOTIFYWEBAPICLIENT_H
