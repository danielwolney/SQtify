#ifndef SEARCHRESULTWIDGET_H
#define SEARCHRESULTWIDGET_H

#include <QWidget>

namespace Ui {
class SearchResultWidget;
}

class SearchResult;
class TrackSearchResultModel;

class SearchResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchResultWidget(SearchResult *searchResult, QWidget *parent = nullptr);
    ~SearchResultWidget();

private:
    Ui::SearchResultWidget *ui;
    TrackSearchResultModel *m_trackSearchResultModel;
};

#endif // SEARCHRESULTWIDGET_H
