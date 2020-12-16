#include "mainform.h"
#include "ui_mainform.h"
#include "control/appcontrol.h"
#include "model/playlistmodel.h"
#include "model/tracksearchresultmodel.h"
#include "api/searchresult.h"

#include <QInputDialog>
#include <QJsonArray>

MainForm::MainForm(AppControl *appControl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm),
    m_control(appControl),
    m_playlistModel(new PlaylistModel()),
    m_trackSearchResultModel(new TrackSearchResultModel())
{
    ui->setupUi(this);
    ui->playlistList->setModel(m_playlistModel);
    ui->playlistList->hideColumn(m_playlistModel->columnIDIndex());

    ui->playslistTracksList->setModel(m_trackSearchResultModel);

    ui->progressSearch->setVisible(false);
    ui->tabWidget->setTabsClosable(true);

    connect(m_trackSearchResultModel, &TrackSearchResultModel::loading, this, &MainForm::loading);
    connect(m_trackSearchResultModel, &TrackSearchResultModel::loaded, this, &MainForm::loadingFinished);

    connect(this, &MainForm::loading, ui->progressSearch, &QProgressBar::show);
    connect(this, &MainForm::loadingFinished, ui->progressSearch, &QProgressBar::hide);
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
    SearchResult * result = m_control->searchTracks(ui->searchEdit->text());
    m_trackSearchResultModel->setSearchResult(result);
}

#include <QDebug>
void MainForm::on_playlistList_clicked(const QModelIndex &index)
{
    qDebug() << __PRETTY_FUNCTION__ << __LINE__ << index << m_playlistModel->id(index.row());
}
