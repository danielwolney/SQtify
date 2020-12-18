#include "searchresult.h"
#include "spotifywebapiclient.h"
#include "util/jsonparser.h"
#include <QUrlQuery>

SearchResult::SearchResult(QString url, QString term, QString type, int limit, SpotifyWebApiClient *apiClient, QObject *parent): QObject(parent),
    m_url(url),
    m_term(term),
    m_type(type),
    m_limit(limit),
    m_apiClient(apiClient),
    m_itemCount(0)
{
}

SearchResult::~SearchResult()
{
}

QString SearchResult::term()
{
    return m_term;
}

void SearchResult::addResultPage(QJsonObject res)
{
    m_resultPages.append(res);
    setTotal(res.value(plural(m_type)).toObject().value("total").toInt());
    QJsonArray items = res.value(plural(m_type)).toObject().value("items").toArray();
    m_itemCount += items.size();
    emit ready(items);
}

QString SearchResult::plural(QString word)
{
    return word + "s";
}

QString SearchResult::type() const
{
    return m_type;
}

int SearchResult::pageCount() const
{
    return m_resultPages.size();
}

int SearchResult::itemCount() const
{
    return m_itemCount;
}

int SearchResult::limit() const
{
    return m_limit;
}

QJsonValue SearchResult::next()
{
    if (m_resultPages.size() > 0) {
        return m_resultPages.last().value(plural(m_type)).toObject().value("next");
    } else {
        return QJsonValue();
    }
}

void SearchResult::setTotal(int total)
{
    m_total = total;
}

int SearchResult::total() const
{
    return m_total;
}

bool SearchResult::hasNext()
{
    if (m_resultPages.size() > 0) {
        return !next().isNull();
    }
    return false;
}

void SearchResult::getFirstPage()
{
    if (!m_loading) {
        if (m_resultPages.size() >0) {
            m_resultPages.clear();
            m_itemCount = 0;
            emit cleared();
        }
        QUrlQuery query(m_url);
        query.addQueryItem("query", term());
        query.addQueryItem("type", type());
        query.addQueryItem("offset", "0");
        query.addQueryItem("limit", QString::number(limit()));
        getPage(query.toString(QUrl::EncodeSpaces));
    }
}

void SearchResult::getNextPage()
{
    if (hasNext() && !m_loading) {
        getPage(next().toString());
    }
}

void SearchResult::getPage(QString url)
{
    m_loading = true;
    emit loading();
    qDebug() << "page" << (m_resultPages.size() + 1) << url;
    m_apiClient->get(url, [&, this](const HttpResponse response) {
        switch(response.httpStatusCode) {
        case HttpRequestManager::OK:
            QJsonObject res = JSONParser::toObject(response.data);
            addResultPage(res);
            m_loading = false;
            emit loaded();
            break;
        }
    });
}
