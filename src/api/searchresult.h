#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QJsonObject>
#include <QObject>

class SpotifyWebApiClient;
class SearchResult: public QObject
{
    Q_OBJECT
public:
    explicit SearchResult(QString term, QString type, SpotifyWebApiClient *apiClient, QObject *parent = Q_NULLPTR);
    ~SearchResult();

public:
    QString term();
    int total() const;
    bool hasNext();
    QJsonValue next();

public slots:
    void getNextPage();

signals:
    void ready(QJsonObject res);

private:
    friend class SpotifyControl;
    void setTotal(int total);
    void addResultPage(QJsonObject result);
    void setApiClient(SpotifyWebApiClient *apiClient);
    QString plural(QString word);

    QList<QJsonObject> m_resultPages;
    QString m_term;
    QString m_type;
    int m_total;
    SpotifyWebApiClient *m_apiClient;
};

#endif // SEARCHRESULT_H
