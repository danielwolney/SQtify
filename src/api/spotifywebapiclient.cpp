#include "spotifywebapiclient.h"
#include "networking/httprequestmanager.h"
#include "util/jsonparser.h"

SpotifyWebApiClient::SpotifyWebApiClient(QObject *parent) : SpotifyWebApiClient(Q_NULLPTR,parent)
{
}

SpotifyWebApiClient::SpotifyWebApiClient(HttpRequestManager *httpManager, QObject *parent) : QObject(parent),
    m_httpManager(httpManager)
{
    connect(this, &SpotifyWebApiClient::accessTokenChanged,
            this, &SpotifyWebApiClient::dequeuePendingRequests);
}

SpotifyWebApiClientImpl::SpotifyWebApiClientImpl(HttpRequestManager *httpManager, QObject *parent):
    SpotifyWebApiClient(httpManager, parent)
{
}

void SpotifyWebApiClientImpl::setAccesToken(QString accessToken)
{
    if (accessToken != m_accessToken) {
        m_accessToken = accessToken;
        emit accessTokenChanged();
    }
}

void SpotifyWebApiClientImpl::get(QString apiResource, HttpRequestManager::OnFinished onResponse)
{
    SpotifyWebApiClient::get(apiResource, HttpRequest::RawHeaders(), onResponse);
}

void SpotifyWebApiClient::get(QString apiResource, HttpRequest::RawHeaders headers,
                              HttpRequestManager::OnFinished onResponse)
{
    HttpRequest request = {HttpRequest::GET, apiResource, headers, QByteArray()};
    requestThenCheckAuth(request, onResponse);
}

void SpotifyWebApiClient::requestThenCheckAuth(HttpRequest httpRequest, HttpRequestManager::OnFinished onResponse)
{
    HttpRequest::RawHeaders headers;
    headers["Content-Type"] = "application/json";
    headers["Authorization"] = ("Bearer " + m_accessToken.toUtf8());

    foreach (QByteArray header, httpRequest.rawHeaders.keys()) {
        headers[header] = httpRequest.rawHeaders.value(header);
    }

    HttpRequest newRequest = {httpRequest.verb, httpRequest.url, headers, httpRequest.data};
    request(newRequest, [&, this, newRequest, onResponse]
                          (const HttpResponse response) {
        if (response.httpStatusCode == HttpRequestManager::FORBIDDEN || response.httpStatusCode == HttpRequestManager::UNAUTHORIZED) {
            qDebug() << response.httpStatusCode << QString(response.data);
            addPendingRequest(newRequest, onResponse);
            emit expiredToken();
        } else {
            onResponse(response);
        }
    });
}

void SpotifyWebApiClient::request(HttpRequest request,
                          HttpRequestManager::OnFinished onResponse)
{
    if (m_httpManager) {
        m_httpManager->request(request, onResponse);
    }
}

void SpotifyWebApiClient::addPendingRequest(HttpRequest httpRequest, HttpRequestManager::OnFinished onResponse)
{
    m_pendingsRequests.enqueue(
       qMakePair<HttpRequest, HttpRequestManager::OnFinished>(httpRequest, onResponse)
                );
}

void SpotifyWebApiClient::dequeuePendingRequests()
{
    qDebug() << "dequeuing pending requests..." << m_pendingsRequests.size();
    while (!m_pendingsRequests.isEmpty()) {
        auto pair = m_pendingsRequests.dequeue();
        metaObject()->invokeMethod(this, "request",
                                   Qt::QueuedConnection,
                                   Q_ARG(HttpRequest, pair.first),
                                   Q_ARG(HttpRequestManager::OnFinished, pair.second));
    }
}

