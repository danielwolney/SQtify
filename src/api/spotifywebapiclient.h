#ifndef SPOTIFYWEBAPICLIENT_H
#define SPOTIFYWEBAPICLIENT_H

#include <QObject>
#include "networking/httprequestmanager.h"
#include <QQueue>
#include <QPair>

class SpotifyWebApiClient : public QObject
{
    Q_OBJECT
public:
    explicit SpotifyWebApiClient(QObject *parent = nullptr);
    virtual void setAccesToken(QString accessToken) = 0;
    virtual void get(QString apiResource, HttpRequestManager::OnFinished onResponse) = 0;
    virtual void get(QString apiResource, HttpRequest::RawHeaders headers,
             HttpRequestManager::OnFinished onResponse) = 0;

signals:
    void accessTokenChanged();
    void expiredToken();

protected:
    void requestThenCheckAuth(HttpRequest httpRequest, HttpRequestManager::OnFinished onResponse);
    Q_INVOKABLE void request(HttpRequest request,
                 HttpRequestManager::OnFinished onResponse);
    void addPendingRequest(HttpRequest httpRequest, HttpRequestManager::OnFinished onResponse);
    void dequeuePendingRequests();

    HttpRequestManager *m_httpManager;
    QString m_accessToken;
    QQueue<QPair<HttpRequest, HttpRequestManager::OnFinished> > m_pendingsRequests;
};

class SpotifyWebApiClientImpl : public SpotifyWebApiClient
{
    virtual void setAccesToken(QString accessToken) override;
    virtual void get(QString apiResource, HttpRequestManager::OnFinished onResponse) override;
    virtual void get(QString apiResource, HttpRequest::RawHeaders headers,
             HttpRequestManager::OnFinished onResponse) override;
};

#endif // SPOTIFYWEBAPICLIENT_H
