#include "mainform.h"
#include "ui_mainform.h"
#include "control/appcontrol.h"
#include "model/playlistmodel.h"
#include "api/searchresult.h"
#include <ui/searchresultwidget.h>
#include "model/localtracksmodel.h"

#include <QInputDialog>

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

    ui->playslistTracksList->setModel(m_tracksModel);
    ui->playslistTracksList->setModelColumn(m_tracksModel->columnNameIndex());


    ui->progressSearch->setVisible(false);

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainForm::removeSearchTab);
    ui->tabWidget->setTabsClosable(true);

}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_addPlaylist_clicked()
{
    bool ok = false;
    QString name = QInputDialog::getText(this, "Nova playlist", "Nova playlist:", QLineEdit::Normal
                          ,"", &ok, (Qt::Popup));
    if (ok && !name.isEmpty()) {
        m_playlistModel->addPlaylist(name);
    }
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
        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(tab, "Resultados: '" + searchTerm + "'"));
    }
}

void MainForm::addTrack(int playlistID, QJsonObject trackItem)
{
    m_tracksModel->addPlaylistTrack(playlistID, trackItem);
}
