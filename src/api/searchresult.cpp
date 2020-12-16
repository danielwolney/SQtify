#include "searchresult.h"
#include "spotifywebapiclient.h"
#include "util/jsonparser.h"

SearchResult::SearchResult(QString term, QString type, int limit, SpotifyWebApiClient *apiClient, QObject *parent): QObject(parent),
    m_term(term),
    m_type(type),
    m_limit(limit),
    m_apiClient(apiClient)
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
    emit ready(res.value(plural(m_type)).toObject().value("items").toArray());
}

QString SearchResult::plural(QString word)
{
    return word + "s";
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

void SearchResult::getNextPage()
{
    if (hasNext() && !m_loading) {
        m_loading = true;
        emit loading();
        qDebug() << next().toString();
        m_apiClient->get(next().toString(), [&, this](const HttpResponse response) {
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
}
