#ifndef SEARCHRESULTWIDGET_H
#define SEARCHRESULTWIDGET_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class SearchResultWidget;
}

class SearchResult;
class TrackSearchResultModel;
class PlaylistModel;
class QAction;

class SearchResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchResultWidget(SearchResult *searchResult, PlaylistModel *playlistModel, QWidget *parent = nullptr);
    ~SearchResultWidget();

signals:
    void addToPlaylist(int playlistID, QJsonObject item);
    void addToNewPlaylist(QJsonObject item);

private slots:
    void createPlaylistMenu();

private:
    Ui::SearchResultWidget *ui;
    TrackSearchResultModel *m_trackSearchResultModel;
    PlaylistModel *m_playlistModel;
    QAction *m_addAction;
};

#endif // SEARCHRESULTWIDGET_H
