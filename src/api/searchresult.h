#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QJsonArray>
#include <QObject>

class SpotifyWebApiClient;

class SearchResult: public QObject
{
    Q_OBJECT
public:
    ~SearchResult();

public:
    QString term();
    int total() const;
    bool hasNext();
    QJsonValue next();

    int limit() const;

public slots:
    void getNextPage();

signals:
    void ready(QJsonArray items);
    void loading();
    void loaded();

private:
    friend class SpotifyControl;

    explicit SearchResult(QString term, QString type, int limit, SpotifyWebApiClient *apiClient, QObject *parent = Q_NULLPTR);

    void setTotal(int total);
    void addResultPage(QJsonObject result);
    void setApiClient(SpotifyWebApiClient *apiClient);
    QString plural(QString word);

    QList<QJsonObject> m_resultPages;
    QString m_term;
    QString m_type;
    int m_limit;
    int m_total;
    bool m_loading;
    SpotifyWebApiClient *m_apiClient;
};

#endif // SEARCHRESULT_H
