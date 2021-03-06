#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QJsonArray>
#include <QObject>

class SpotifyWebApiClient;

class SearchResult: public QObject
{
    Q_OBJECT
public:
    explicit SearchResult(QString url, QString term, QString type, int limit, SpotifyWebApiClient *apiClient, QObject *parent = Q_NULLPTR);
    ~SearchResult();

public:
    QString term();
    int total() const;
    bool hasNext();
    QJsonValue next();
    int limit() const;
    QString type() const;   
    int pageCount() const;
    int itemCount() const;

public slots:
    void getFirstPage();
    void getNextPage();

signals:
    void ready(QJsonArray items);
    void loading();
    void loaded();
    void cleared();

protected:
    void getPage(QString url);
    void setTotal(int total);
    void addResultPage(QJsonObject result);
    void setApiClient(SpotifyWebApiClient *apiClient);
    QString plural(QString word);

    QString m_url;
    QList<QJsonObject> m_resultPages;
    QString m_term;
    QString m_type;
    int m_limit;
    int m_total;
    bool m_loading;
    SpotifyWebApiClient *m_apiClient;
    int m_itemCount;
};

#endif // SEARCHRESULT_H
