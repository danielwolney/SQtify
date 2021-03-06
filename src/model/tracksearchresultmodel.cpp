#include "tracksearchresultmodel.h"
#include <QJsonValue>
#include <QJsonObject>
#include "api/searchresult.h"

TrackSearchResultModel::TrackSearchResultModel(SearchResult *result, QObject *parent)
    : QAbstractListModel(parent),
      m_searchResult(Q_NULLPTR),
      m_count(0)
{
    setSearchResult(result);
}

int TrackSearchResultModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_count;
}

QVariant TrackSearchResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() <= m_count) {
        int page = (int)(index.row() / (double)pageSize());
        int itemIndex = (int)(index.row() % pageSize());
        QJsonObject item = m_itens.value(page).at(itemIndex).toObject();
        switch (role) {
        case Qt::DisplayRole:
            return QString::number(index.row()+1) + " - " + item.value("name").toString();
        case Item:
            return item;
        case Qt::ToolTipRole:
            return QString("Album: %1\nLançamento: %2\nArtista: %3")
                    .arg(item.value("album").toObject().value("name").toString())
                    .arg(item.value("album").toObject().value("release_date").toString())
                    .arg(item.value("artists").toArray()[0].toObject().value("name").toString());
        }
    }
    return QVariant();
}

bool TrackSearchResultModel::TrackSearchResultModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if (m_searchResult) {
        return m_searchResult->hasNext();
    }
    return false;
}

void TrackSearchResultModel::fetchMore(const QModelIndex &parent)
{
    //LAZY LOAD
    Q_UNUSED(parent)
    if (m_searchResult) {
        m_searchResult->getNextPage();
    }
}

void TrackSearchResultModel::appendItems(const QJsonArray & items)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.size() - 1);
    m_itens.append(items);
    m_count += items.size();
    endInsertRows();
}

int TrackSearchResultModel::pageSize() const
{
    return m_pageSize;
}

void TrackSearchResultModel::setPageSize(int pageSize)
{
    m_pageSize = pageSize;
}

void TrackSearchResultModel::clear()
{
    beginResetModel();
    m_itens.clear();
    m_count = 0;
    endResetModel();
}

SearchResult *TrackSearchResultModel::searchResult() const
{
    return m_searchResult;
}

void TrackSearchResultModel::setSearchResult(SearchResult *searchResult)
{
    clear();
    if (m_searchResult) {
        m_searchResult->blockSignals(true);
        m_searchResult->deleteLater();
    }
    if (searchResult) {
        m_searchResult = searchResult;
        m_searchResult->setParent(this);
        setPageSize(m_searchResult->limit());

        connect(m_searchResult, &SearchResult::loading, this, &TrackSearchResultModel::loading);
        connect(m_searchResult, &SearchResult::loaded, this, &TrackSearchResultModel::loaded);
        connect(m_searchResult, &SearchResult::cleared, this, &TrackSearchResultModel::clear);

        connect(m_searchResult, &SearchResult::ready, [&, this](QJsonArray items) {
            appendItems(items);
        });
    }
}
