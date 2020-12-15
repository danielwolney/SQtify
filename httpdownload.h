#ifndef HTTPDOWNLOAD_H
#define HTTPDOWNLOAD_H

#include <QObject>
#include "httprequestmanager.h"
#include <QTimer>

class QNetworkReply;

class HttpDownload : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(qint64 size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)

    qint64 size() const;
    void setSize(qint64 size);
    void setTimeout(int sec);
    int progress();
    ~HttpDownload();

public slots:
    void cancel();

signals:
    void progressChanged(int perc);
    void canceled();
    void finished();

    void sizeChanged(qint64 size);

private:
    explicit HttpDownload(QNetworkReply *reply, QObject *parent = nullptr);
    friend HttpRequestManager;
    void setProgress(int percent);

    QNetworkReply *m_reply;
    QTimer m_timer;
    qint64 m_size;
    int m_percProgress;
};

#endif // HTTPDOWNLOAD_H
