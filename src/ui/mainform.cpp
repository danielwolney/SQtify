#include "mainform.h"
#include "ui_mainform.h"
#include "control/appcontrol.h"
#include "model/playlistmodel.h"
#include "api/searchresult.h"
#include <ui/searchresultwidget.h>

#include <QInputDialog>
#include <QJsonArray>

MainForm::MainForm(AppControl *appControl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm),
    m_control(appControl),
    m_playlistModel(new PlaylistModel())
{
    ui->setupUi(this);
    ui->playlistList->setModel(m_playlistModel);
    ui->playlistList->hideColumn(m_playlistModel->columnIDIndex());

//    ui->playslistTracksList->setModel(m_trackSearchResultModel);

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

#include <QDebug>
void MainForm::on_playlistList_clicked(const QModelIndex &index)
{
    qDebug() << __PRETTY_FUNCTION__ << __LINE__ << index << m_playlistModel->id(index.row());
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
        ui->tabWidget->setCurrentIndex(ui->tabWidget->addTab(new SearchResultWidget(result), "Resultados: '" + searchTerm + "'"));
    }
}
