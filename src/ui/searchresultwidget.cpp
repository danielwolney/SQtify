#include "searchresultwidget.h"
#include "ui_searchresultwidget.h"
#include "model/tracksearchresultmodel.h"
#include "model/playlistmodel.h"
#include "api/searchresult.h"

#include <QAction>
#include <QMenu>

SearchResultWidget::SearchResultWidget(SearchResult *searchResult, PlaylistModel *playlistModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchResultWidget),
    m_trackSearchResultModel(new TrackSearchResultModel(searchResult, this)),
    m_playlistModel(playlistModel)
{
    ui->setupUi(this);
    ui->listResult->setModel(m_trackSearchResultModel);

    m_addAction = new QAction("Adicionar à playlist");
    auto menu = new QMenu("Playlists");
    m_addAction->setMenu(menu);

    createPlaylistMenu();

    ui->listResult->addAction(m_addAction);
    ui->listResult->setContextMenuPolicy(Qt::ActionsContextMenu);

    connect(m_playlistModel, &PlaylistModel::rowsInserted, this, &SearchResultWidget::createPlaylistMenu);
    connect(m_playlistModel, &PlaylistModel::rowsRemoved, this, &SearchResultWidget::createPlaylistMenu);
    connect(m_playlistModel, &PlaylistModel::dataChanged, this, &SearchResultWidget::createPlaylistMenu);


    connect(m_trackSearchResultModel, &TrackSearchResultModel::loading, ui->progressBar, &QProgressBar::show);
    connect(m_trackSearchResultModel, &TrackSearchResultModel::loaded, ui->progressBar, &QProgressBar::hide);
    connect(m_trackSearchResultModel, &TrackSearchResultModel::rowsInserted, ui->progressBar, &QProgressBar::hide);
    setWindowTitle("Resultados: " + searchResult->term());
}

SearchResultWidget::~SearchResultWidget()
{
    delete ui;
}

void SearchResultWidget::createPlaylistMenu()
{
    auto menu = m_addAction->menu();
    menu->clear();
    for(int i = 0; i < m_playlistModel->rowCount(); ++i) {
        QAction *playlistItem = menu->addAction(m_playlistModel->name(i));
        playlistItem ->setData(m_playlistModel->id(i));
        connect(playlistItem , &QAction::triggered, this, [&, playlistItem , this](){
           emit addToPlaylist(playlistItem->data().toInt(),
                              ui->listResult->currentIndex().data(TrackSearchResultModel::Item).toJsonObject());
        });
    }
    menu->addSeparator();
    QAction *newPlaylist = menu->addAction("Nova playlist");
    connect(newPlaylist , &QAction::triggered, this, [&, this](){
       emit addToNewPlaylist(ui->listResult->currentIndex().data(TrackSearchResultModel::Item).toJsonObject());
    });
}

