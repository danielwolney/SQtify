#include "httpdownload.h"
#include <QNetworkReply>

HttpDownload::HttpDownload(QNetworkReply *reply, QObject *parent) : QObject(parent),
    m_reply(reply)
{
    m_timer.setSingleShot(true);
    connect(m_reply, &QNetworkReply::downloadProgress, this, [&](qint64 bytesReceived, qint64 bytesTotal){
        if (bytesTotal > 0) {
            setSize(bytesTotal);
            setProgress((bytesReceived * 100)/size());
        }
    });
}

HttpDownload::~HttpDownload()
{
}

qint64 HttpDownload::size() const
{
    return m_size;
}

void HttpDownload::setSize(qint64 size)
{
    if (m_size == size)
        return;

    m_size = size;
    emit sizeChanged(m_size);
}

void HttpDownload::setProgress(int percent)
{
    if (m_percProgress == percent)
        return;

    m_percProgress = percent;
    emit progressChanged(m_percProgress);
}

void HttpDownload::setTimeout(int sec)
{
    if (m_timer.isActive())
        return;

    m_timer.setInterval(sec * 1000);
    connect(m_reply, &QNetworkReply::downloadProgress, &m_timer, [&](qint64 bytesReceived, qint64 bytesTotal){
        m_timer.start();
    });
    connect(&m_timer, &QTimer::timeout, m_reply, &QNetworkReply::abort);
    m_timer.start();
}

int HttpDownload::progress()
{
    return m_percProgress;
}

void HttpDownload::cancel()
{
    m_reply->abort();
    emit canceled();
}
