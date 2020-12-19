#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "api/searchresult.h"
#include "tst/api/mockspotifywebapiclient.h"

using namespace testing;

class SearchResultTests : public testing::Test {
 protected:
    void SetUp() override {
        noResults = "{\n  \"tracks\": {\n    \"href\": \"https://api.spotify.com/v1/search?query=no+results&type=track&offset=0&limit=1\",\n    \"items\": [],\n    \"limit\": 1,\n    \"next\": null,\n    \"offset\": 0,\n    \"previous\": null,\n    \"total\": 0\n  }\n}";

        fakeData.insert("https://api.spotify.com/v1/search?&query=going%20inside&type=track&offset=0&limit=1",
                                "{\n  \"tracks\": {\n    \"href\": \"https://api.spotify.com/v1/search?query=going+inside&type=track&offset=0&limit=1\",\n    \"items\": [\n      {\n        \"album\": {\n          \"album_type\": \"album\",\n          \"artists\": [\n            {\n              \"external_urls\": {\n                \"spotify\": \"https://open.spotify.com/artist/7rN3Agir6FaZNfhf5V7mfN\"\n              },\n              \"href\": \"https://api.spotify.com/v1/artists/7rN3Agir6FaZNfhf5V7mfN\",\n              \"id\": \"7rN3Agir6FaZNfhf5V7mfN\",\n              \"name\": \"John Frusciante\",\n              \"type\": \"artist\",\n              \"uri\": \"spotify:artist:7rN3Agir6FaZNfhf5V7mfN\"\n            }\n          ],\n          \"external_urls\": {\n            \"spotify\": \"https://open.spotify.com/album/3a9g6ueh2eVIYGTfmSoKkb\"\n          },\n          \"href\": \"https://api.spotify.com/v1/albums/3a9g6ueh2eVIYGTfmSoKkb\",\n          \"id\": \"3a9g6ueh2eVIYGTfmSoKkb\",\n          \"images\": [\n            {\n              \"height\": 640,\n              \"url\": \"https://i.scdn.co/image/ab67616d0000b2732212a5deaedc7b5060799d83\",\n              \"width\": 640\n            }\n          ],\n          \"name\": \"To Record Only Water For Ten Days (U.S. Version)\",\n          \"release_date\": \"2001-02-12\",\n          \"release_date_precision\": \"day\",\n          \"total_tracks\": 15,\n          \"type\": \"album\",\n          \"uri\": \"spotify:album:3a9g6ueh2eVIYGTfmSoKkb\"\n        },\n        \"artists\": [\n          {\n            \"external_urls\": {\n              \"spotify\": \"https://open.spotify.com/artist/7rN3Agir6FaZNfhf5V7mfN\"\n            },\n            \"href\": \"https://api.spotify.com/v1/artists/7rN3Agir6FaZNfhf5V7mfN\",\n            \"id\": \"7rN3Agir6FaZNfhf5V7mfN\",\n            \"name\": \"John Frusciante\",\n            \"type\": \"artist\",\n            \"uri\": \"spotify:artist:7rN3Agir6FaZNfhf5V7mfN\"\n          }\n        ],\n        \"disc_number\": 1,\n        \"duration_ms\": 215248,\n        \"explicit\": false,\n        \"external_ids\": {\n          \"isrc\": \"USWB10003076\"\n        },\n        \"external_urls\": {\n          \"spotify\": \"https://open.spotify.com/track/7vxlM6ouhpJy5WMEZqU7vV\"\n        },\n        \"href\": \"https://api.spotify.com/v1/tracks/7vxlM6ouhpJy5WMEZqU7vV\",\n        \"id\": \"7vxlM6ouhpJy5WMEZqU7vV\",\n        \"is_local\": false,\n        \"is_playable\": true,\n        \"name\": \"Going Inside\",\n        \"popularity\": 49,\n        \"preview_url\": \"https://p.scdn.co/mp3-preview/ddf7cdb518c9908df98eb7bf2478ba7355b62daf?cid=774b29d4f13844c495f206cafdad9c86\",\n        \"track_number\": 1,\n        \"type\": \"track\",\n        \"uri\": \"spotify:track:7vxlM6ouhpJy5WMEZqU7vV\"\n      }\n    ],\n    \"limit\": 1,\n    \"next\": \"https://api.spotify.com/v1/search?query=going+inside&type=track&offset=1&limit=1\",\n    \"offset\": 0,\n    \"previous\": null,\n    \"total\": 202\n  }\n}");

        fakeData.insert("https://api.spotify.com/v1/search?query=going+inside&type=track&offset=1&limit=1",
                        fakeData.value("https://api.spotify.com/v1/search?&query=going%20inside&type=track&offset=0&limit=1"));

        fakeData.insert("https://api.spotify.com/v1/search?query=going+inside+unique+result&type=track&offset=0&limit=1",
                                "{\n  \"tracks\": {\n    \"href\": \"https://api.spotify.com/v1/search?query=going+inside+unique+result&type=track&offset=0&limit=1\",\n    \"items\": [\n      {\n        \"album\": {\n          \"album_type\": \"album\",\n          \"artists\": [\n            {\n              \"external_urls\": {\n                \"spotify\": \"https://open.spotify.com/artist/7rN3Agir6FaZNfhf5V7mfN\"\n              },\n              \"href\": \"https://api.spotify.com/v1/artists/7rN3Agir6FaZNfhf5V7mfN\",\n              \"id\": \"7rN3Agir6FaZNfhf5V7mfN\",\n              \"name\": \"John Frusciante\",\n              \"type\": \"artist\",\n              \"uri\": \"spotify:artist:7rN3Agir6FaZNfhf5V7mfN\"\n            }\n          ],\n          \"external_urls\": {\n            \"spotify\": \"https://open.spotify.com/album/3a9g6ueh2eVIYGTfmSoKkb\"\n          },\n          \"href\": \"https://api.spotify.com/v1/albums/3a9g6ueh2eVIYGTfmSoKkb\",\n          \"id\": \"3a9g6ueh2eVIYGTfmSoKkb\",\n          \"images\": [\n            {\n              \"height\": 640,\n              \"url\": \"https://i.scdn.co/image/ab67616d0000b2732212a5deaedc7b5060799d83\",\n              \"width\": 640\n            }\n          ],\n          \"name\": \"To Record Only Water For Ten Days (U.S. Version)\",\n          \"release_date\": \"2001-02-12\",\n          \"release_date_precision\": \"day\",\n          \"total_tracks\": 15,\n          \"type\": \"album\",\n          \"uri\": \"spotify:album:3a9g6ueh2eVIYGTfmSoKkb\"\n        },\n        \"artists\": [\n          {\n            \"external_urls\": {\n              \"spotify\": \"https://open.spotify.com/artist/7rN3Agir6FaZNfhf5V7mfN\"\n            },\n            \"href\": \"https://api.spotify.com/v1/artists/7rN3Agir6FaZNfhf5V7mfN\",\n            \"id\": \"7rN3Agir6FaZNfhf5V7mfN\",\n            \"name\": \"John Frusciante\",\n            \"type\": \"artist\",\n            \"uri\": \"spotify:artist:7rN3Agir6FaZNfhf5V7mfN\"\n          }\n        ],\n        \"disc_number\": 1,\n        \"duration_ms\": 215248,\n        \"explicit\": false,\n        \"external_ids\": {\n          \"isrc\": \"USWB10003076\"\n        },\n        \"external_urls\": {\n          \"spotify\": \"https://open.spotify.com/track/7vxlM6ouhpJy5WMEZqU7vV\"\n        },\n        \"href\": \"https://api.spotify.com/v1/tracks/7vxlM6ouhpJy5WMEZqU7vV\",\n        \"id\": \"7vxlM6ouhpJy5WMEZqU7vV\",\n        \"is_local\": false,\n        \"is_playable\": true,\n        \"name\": \"Going Inside\",\n        \"popularity\": 49,\n        \"preview_url\": \"https://p.scdn.co/mp3-preview/ddf7cdb518c9908df98eb7bf2478ba7355b62daf?cid=774b29d4f13844c495f206cafdad9c86\",\n        \"track_number\": 1,\n        \"type\": \"track\",\n        \"uri\": \"spotify:track:7vxlM6ouhpJy5WMEZqU7vV\"\n      }\n    ],\n    \"limit\": 1,\n    \"next\": null,\n    \"offset\": 0,\n    \"previous\": null,\n    \"total\": 1\n  }\n}");
    }

  QHash<QString,QByteArray> fakeData;
  QByteArray noResults;

  MockSpotifyWebApiClient m_mockApiClient;
  void defaultApiGet() {
      ON_CALL(m_mockApiClient, get)
              .WillByDefault([this](QString url, HttpRequestManager::OnFinished onResponse) {
          HttpResponse response;
          response.httpStatusCode = HttpRequestManager::OK;
          response.data = fakeData.value(url, noResults);
          onResponse(response);
        });
  }
};

TEST_F(SearchResultTests, NoResult)
{
    defaultApiGet();

    EXPECT_CALL(m_mockApiClient, get(_,_))
            .Times(1);

    QString term = "no results";
    QString type = "track";
    int limit = 1;
    QString url = "https://api.spotify.com/v1/search?";

    SearchResult search(url, term, type, limit, &m_mockApiClient);

    EXPECT_EQ(search.pageCount(), 0);
    search.getFirstPage();
    EXPECT_EQ(search.pageCount(), 1);
    EXPECT_EQ(search.itemCount(), 0);
    EXPECT_FALSE(search.hasNext());
}

TEST_F(SearchResultTests, GetSinglePage)
{
    defaultApiGet();

    EXPECT_CALL(m_mockApiClient, get(_,_))
            .Times(1);

    QString term = "going inside";
    QString type = "track";
    int limit = 1;
    QString url = "https://api.spotify.com/v1/search?";

    SearchResult search(url, term, type, limit, &m_mockApiClient);

    EXPECT_EQ(search.pageCount(), 0);
    search.getFirstPage();
    EXPECT_EQ(search.pageCount(), 1);
}

TEST_F(SearchResultTests, GetTwoPages)
{
    defaultApiGet();

    EXPECT_CALL(m_mockApiClient, get(_,_))
            .Times(2);

    QString term = "going inside";
    QString type = "track";
    int limit = 1;
    QString url = "https://api.spotify.com/v1/search?";

    SearchResult search(url, term, type, limit, &m_mockApiClient);

    EXPECT_EQ(search.pageCount(), 0);
    search.getFirstPage();
    EXPECT_EQ(search.pageCount(), 1);

    EXPECT_TRUE(search.hasNext());
    search.getNextPage();
    EXPECT_EQ(search.pageCount(), 2);
}

TEST_F(SearchResultTests, OnLastPage)
{
    defaultApiGet();

    EXPECT_CALL(m_mockApiClient, get(_,_))
            .Times(1);

    QString term = "going inside unique result";
    QString type = "track";
    int limit = 1;
    QString url = "https://api.spotify.com/v1/search?";

    SearchResult search(url, term, type, limit, &m_mockApiClient);

    EXPECT_EQ(search.pageCount(), 0);
    search.getFirstPage();
    EXPECT_EQ(search.pageCount(), 1);

    EXPECT_FALSE(search.hasNext());
    search.getNextPage();
    EXPECT_EQ(search.pageCount(), 1);
}

TEST_F(SearchResultTests, ResetSearch)
{
    defaultApiGet();

    EXPECT_CALL(m_mockApiClient, get(_,_))
            .Times(3);

    QString term = "going inside";
    QString type = "track";
    int limit = 1;
    QString url = "https://api.spotify.com/v1/search?";

    SearchResult search(url, term, type, limit, &m_mockApiClient);

    ASSERT_EQ(term, search.term());
    ASSERT_EQ(type, search.type());
    ASSERT_EQ(limit, search.limit());

    EXPECT_EQ(search.pageCount(), 0);
    EXPECT_EQ(search.itemCount(), 0);

    search.getFirstPage();
    int firstItemCont = search.itemCount();
    EXPECT_EQ(search.pageCount(), 1);

    EXPECT_TRUE(search.hasNext());
    search.getNextPage();
    EXPECT_EQ(search.pageCount(), 2);
    EXPECT_GT(search.itemCount(), firstItemCont);

    search.getFirstPage();
    EXPECT_EQ(search.pageCount(), 1);
    EXPECT_EQ(search.itemCount(), firstItemCont);
}
