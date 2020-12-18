#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "api/spotifywebapiclient.h"
#include "tst/networking/mockhttprequestmanager.h"
#include <QSignalSpy>
#include <QMetaType>

using namespace testing;

class SpotifyWebApiClientTests : public testing::Test {
 protected:
    void SetUp() override {
        registerAllMetaTypes();
    }

  MockHttpRequestManager m_mockHttp;
  void defaultHttpGet() {
      ON_CALL(m_mockHttp, request)
              .WillByDefault([](HttpRequest request, HttpRequestManager::OnFinished onResponse){
          HttpResponse response;
          response.httpStatusCode = HttpRequestManager::UNAUTHORIZED;
          if (request.verb == HttpRequest::GET) {
              if (request.rawHeaders.contains("Authorization") && request.rawHeaders["Authorization"] == "Bearer valid") {
                  response.httpStatusCode = HttpRequestManager::OK;
              }
              response.data = "";
          }
          onResponse(response);
      });
  }
};

TEST_F(SpotifyWebApiClientTests, SuccessfullRequest)
{
    defaultHttpGet();
    EXPECT_CALL(m_mockHttp, request(_,_))
            .Times(1);

    auto client = new SpotifyWebApiClientImpl(&m_mockHttp);
    QSignalSpy spy(client, &SpotifyWebApiClient::expiredToken);
    client->setAccesToken("valid");
    bool done = false;
    bool *ptr = &done;
    client->get("/me", [ptr](const HttpResponse response){
        Q_UNUSED(response)
        (*ptr) = true;
    });

    EXPECT_EQ(spy.count(), 0);
    EXPECT_TRUE(done);
}

TEST_F(SpotifyWebApiClientTests, InvalidAccessToken)
{
    defaultHttpGet();
    EXPECT_CALL(m_mockHttp, request(_,_))
            .Times(1);

    auto client = new SpotifyWebApiClientImpl(&m_mockHttp);
    QSignalSpy spy(client, &SpotifyWebApiClient::expiredToken);
    client->setAccesToken("invalid");
    bool done = false;
    bool *ptr = &done;
    client->get("/me", [ptr](const HttpResponse response){
        Q_UNUSED(response)
        (*ptr) = true;
    });
    EXPECT_EQ(spy.count(), 1);
    EXPECT_FALSE(done);
}

TEST_F(SpotifyWebApiClientTests, RetryRequestAfterRefreshToken)
{
    defaultHttpGet();

    EXPECT_CALL(m_mockHttp, request(_,_))
            .Times(2);

    auto client = new SpotifyWebApiClientImpl(&m_mockHttp);
    QSignalSpy spy(client, &SpotifyWebApiClient::expiredToken);

    client->setAccesToken("invalid");
    bool done = false;
    bool *ptr = &done;
    client->get("/me", [ptr](const HttpResponse response){
        Q_UNUSED(response)
        (*ptr) = true;
    });
    client->setAccesToken("valid");

    EXPECT_EQ(spy.count(), 1);
    EXPECT_TRUE(done);
}
