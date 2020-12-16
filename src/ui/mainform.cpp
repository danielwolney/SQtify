#include "mainform.h"
#include "ui_mainform.h"
#include "control/appcontrol.h"
#include <QInputDialog>
#include "model/playlistmodel.h"
#include "api/searchresult.h"

MainForm::MainForm(AppControl *appControl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm),
    m_control(appControl),
    m_playlistModel(new PlaylistModel())
{
    ui->setupUi(this);
    ui->playlistList->setModel(m_playlistModel);
    ui->playlistList->hideColumn(m_playlistModel->columnIDIndex());

    ui->progressSearch->setVisible(false);
    ui->tabWidget->setTabsClosable(true);

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
    emit loading();
    SearchResult * result = m_control->searchTracks(ui->searchEdit->text());
    connect(result, &SearchResult::ready, [&, result, this](QJsonObject res) {
        qDebug() << result->next().toString();
        if (result->hasNext()) {
            result->getNextPage();
        } else {
            result->deleteLater();
            emit loadingFinished();
        }
    });
}
#include <QDebug>
void MainForm::on_playlistList_clicked(const QModelIndex &index)
{
    qDebug() << __PRETTY_FUNCTION__ << __LINE__ << index << m_playlistModel->id(index.row());
}
