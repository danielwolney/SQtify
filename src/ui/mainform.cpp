#include "mainform.h"
#include "ui_mainform.h"
#include "control/appcontrol.h"
#include "api/searchresult.h"
#include "ui/searchresultwidget.h"
#include "model/playlistmodel.h"
#include "model/localtracksmodel.h"

#include <QInputDialog>
#include <QMessageBox>

#include <QAction>
#include <QIcon>

MainForm::MainForm(AppControl *appControl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm),
    m_control(appControl),
    m_playlistModel(new PlaylistModel()),
    m_tracksModel(new LocalTracksModel())
{
    ui->setupUi(this);
    ui->playlistList->setModel(m_playlistModel);
    ui->playlistList->setModelColumn(m_playlistModel->columnNameIndex());

    auto action = new QAction(QIcon(":/delete-black-24dp.svg"), "Remover");
    connect(action, &QAction::triggered, this, &MainForm::removePlaylist);
    ui->playlistList->addAction(action);

    ui->playslistTracksList->setModel(m_tracksModel);
    ui->playslistTracksList->setModelColumn(m_tracksModel->columnNameIndex());
    action = new QAction(QIcon(":/play_arrow-green-24dp.svg"), "Play");
    connect(action, &QAction::triggered, this, &MainForm::playCurrentTrack);
    ui->playslistTracksList->addAction(action);
    action = new QAction(QIcon(":/delete-black-24dp.svg"), "Remover");
    connect(action, &QAction::triggered, this, &MainForm::removeCurrentTrack);
    ui->playslistTracksList->addAction(action);

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainForm::removeSearchTab);
    ui->tabWidget->setTabsClosable(true);

    ui->playerWidget->setPlayer(m_control->player());
}

MainForm::~MainForm()
{
    delete ui;
}

int MainForm::createPlaylist()
{
    bool ok = false;
    QString name = QInputDialog::getText(this, "Nova playlist", "Nova playlist:", QLineEdit::Normal
                          ,"", &ok, (Qt::Popup));
    if (ok && !name.isEmpty()) {
        return m_playlistModel->addPlaylist(name);
    }
    return 0;
}

void MainForm::on_addPlaylist_clicked()
{
    createPlaylist();
}

void MainForm::on_btnSearch_clicked()
{
    createSearchTab(ui->searchEdit->text());
    ui->searchEdit->clear();
}

void MainForm::on_playlistList_clicked(const QModelIndex &index)
{
    m_tracksModel->setCurrentPlaylistID(m_playlistModel->id(index.row()));
}

void MainForm::removeSearchTab(int tabIndex)
{
    if (tabIndex > 0) {
        ui->tabWidget->removeTab(tabIndex);
    }
}

void MainForm::createSearchTab(QString searchTerm)
{
    if (!searchTerm.isEmpty()) {
        SearchResult * result = m_control->searchTracks(ui->searchEdit->text());
        auto tab = new SearchResultWidget(result, m_playlistModel);
        connect(tab, &SearchResultWidget::addToPlaylist, this, &MainForm::addTrack);
        connect(tab, &SearchResultWidget::addToNewPlaylist, this, [&, this](QJsonObject item) {
            int id = createPlaylist();
            addTrack(id, item);
        });
        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(tab, "Resultados: '" + searchTerm + "'"));
    }
}

void MainForm::addTrack(int playlistID, QJsonObject trackItem)
{
    m_tracksModel->addPlaylistTrack(playlistID, trackItem);
}

void MainForm::on_playslistTracksList_doubleClicked(const QModelIndex &index)
{
    playTrack(index);
}

void MainForm::removeTrack(const QModelIndex &index)
{
    if (QMessageBox::question(this, "Remover música",
                              QString("Remover '%1' da playlist?").arg(m_tracksModel->name(index.row()))) == QMessageBox::Yes) {
        if (m_tracksModel->removeRow(index.row())) {
            m_tracksModel->select();
        }
    }
}

void MainForm::playTrack(const QModelIndex &index)
{
    m_control->startPlaylist(index);
}

void MainForm::removePlaylist()
{
    QModelIndex index = ui->playlistList->focusIndex();
    if (QMessageBox::question(this, "Remover playlist",
                              QString("Remover playlist '%1'?").arg(m_playlistModel->name(index.row()))) == QMessageBox::Yes) {
        if (m_playlistModel->removeRow(index.row())) {
            m_playlistModel->select();
        }
    }
}

void MainForm::removeCurrentTrack()
{
    QModelIndex index = ui->playslistTracksList->focusIndex();
    removeTrack(index);
}

void MainForm::playCurrentTrack()
{
    QModelIndex index = ui->playslistTracksList->focusIndex();
    playTrack(index);
}

