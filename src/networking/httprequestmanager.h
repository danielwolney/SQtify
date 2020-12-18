#ifndef HTTPREQUESTMANAGER_H
#define HTTPREQUESTMANAGER_H

#include <QObject>
#include <functional>
#include <QNetworkRequest>
#include <QNetworkReply>

class HttpDownload;
class QNetworkAccessManager;

class HttpRequest {
    Q_GADGET
public:
    typedef QHash<QByteArray,QByteArray> RawHeaders;
    enum HttpRequestVerb {
        GET = 1,
        POST,
        PUT,
        DELETE,
        HEAD
    };
    Q_ENUM(HttpRequestVerb)

    HttpRequestVerb verb;
    QString url;
    RawHeaders rawHeaders;
    QByteArray data;
};

class HttpResponse {
public:
    int httpStatusCode;
    QByteArray data;
    QNetworkReply::NetworkError error;
    QString errorString;
    HttpRequest::RawHeaders rawHeaders;
};

class HttpRequestManager : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequestManager(QObject *parent = nullptr);

    enum HttpStatusCode {
        OK = 200,
        CREATED = 201,
        ACCEPTED = 202,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        CONFLICT = 409,
        UNPROCESSABLE_ENTITY = 422,
        INTERNAL_ERROR = 500,
    };

    typedef std::function<void (const HttpResponse response)> OnFinished;

public:
    virtual void request(HttpRequest httpRequest, OnFinished onResponse) = 0;
    virtual HttpDownload *download(HttpRequest request, HttpRequestManager::OnFinished onResponse) = 0;

protected:
    QNetworkAccessManager *m_nam;
    QNetworkRequest prepareRequest(HttpRequest request);
    HttpDownload *request(HttpRequest httpRequest, OnFinished onResponse, int timeout);

private:
};

class HttpRequestManagerImpl : public HttpRequestManager
{
    virtual void request(HttpRequest httpRequest, OnFinished onResponse);
    virtual HttpDownload *download(HttpRequest request, HttpRequestManager::OnFinished onResponse);
};

#endif // HTTPREQUESTMANAGER_H
