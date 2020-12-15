#include "httprequestmanager.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMetaEnum>
#include <QCoreApplication>
#include "httpdownload.h"

HttpRequestManager::HttpRequestManager(QObject *parent) : QObject(parent)
{
    m_nam =  new QNetworkAccessManager(this);
}

HttpDownload * HttpRequestManager::download(HttpRequest request,
                                   HttpRequestManager::OnFinished onResponse)
{
    return this->request(request, onResponse, 0);
}

void HttpRequestManager::request(HttpRequest httpRequest, OnFinished onResponse)
{
    request(httpRequest, onResponse, 30);
}

HttpDownload *HttpRequestManager::request(HttpRequest httpRequest, OnFinished onResponse, int timeout)
{
    QNetworkRequest request = prepareRequest(httpRequest);
    QNetworkReply *reply;
    QMetaEnum httpRequestTypeMetaEnum = QMetaEnum::fromType<HttpRequest::HttpRequestVerb>();
    reply = m_nam->sendCustomRequest(request, httpRequestTypeMetaEnum.valueToKey(httpRequest.verb), httpRequest.data);
    connect(reply, &QNetworkReply::finished, this, [&, reply,onResponse]() {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        HttpResponse response = {statusCode, reply->readAll(), reply->error(), reply->errorString()};
        HttpRequest::RawHeaders rawHeaders;
        foreach (QByteArray header, reply->rawHeaderList()) {
            response.rawHeaders[header] = reply->rawHeader(header);
        }
        onResponse(response);
        delete reply;
    });
    HttpDownload *downloadItem = new HttpDownload(reply, reply);
    if (timeout > 0) {
        downloadItem->setTimeout(timeout);
    }
    return downloadItem;
}

QNetworkRequest HttpRequestManager::prepareRequest(HttpRequest httpRequest)
{
    QUrl url(httpRequest.url);
    QNetworkRequest request;
    request.setUrl(url);
    if (!httpRequest.rawHeaders.isEmpty()) {
        foreach (QByteArray header, httpRequest.rawHeaders.keys()) {
            request.setRawHeader(header, httpRequest.rawHeaders.value(header));
        }
    }
    return request;
}

Q_DECLARE_METATYPE(HttpResponse)
void registerMetaTypeHttpResponse() {
    qMetaTypeId<HttpResponse>();
}
Q_COREAPP_STARTUP_FUNCTION(registerMetaTypeHttpResponse)

Q_DECLARE_METATYPE(HttpRequest)
void registerMetaTypeHttpRequest() {
    qMetaTypeId<HttpRequest>();
}
Q_COREAPP_STARTUP_FUNCTION(registerMetaTypeHttpRequest)

Q_DECLARE_METATYPE(HttpRequest::HttpRequestVerb)
void registerMetaTypeHttpVerb() {
    qMetaTypeId<HttpRequest::HttpRequestVerb>();
}
Q_COREAPP_STARTUP_FUNCTION(registerMetaTypeHttpVerb)

Q_DECLARE_METATYPE(HttpRequest::RawHeaders)
void registerMetaTypeRawHeaders() {
    qMetaTypeId<HttpRequest::RawHeaders>();
}
Q_COREAPP_STARTUP_FUNCTION(registerMetaTypeRawHeaders)

Q_DECLARE_METATYPE(HttpRequestManager::OnFinished)
void registerMetaTypeOnFinished() {
    qMetaTypeId<HttpRequestManager::OnFinished>();
}
Q_COREAPP_STARTUP_FUNCTION(registerMetaTypeOnFinished)
