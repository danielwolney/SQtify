#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class MainForm;
}

class AppControl;
class PlaylistModel;
class LocalTracksModel;

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(AppControl *appControl, QWidget *parent = nullptr);
    ~MainForm();

private slots:
    void on_addPlaylist_clicked();
    void on_btnSearch_clicked();
    void on_playlistList_clicked(const QModelIndex &index);
    void removeSearchTab(int tabIndex);
    void createSearchTab(QString searchTerm);
    void addTrack(int playlistID, QJsonObject trackItem);

    void on_playslistTracksList_doubleClicked(const QModelIndex &index);
    void removeTrack(const QModelIndex &index);

private:
    Ui::MainForm *ui;
    AppControl *m_control;
    PlaylistModel *m_playlistModel;
    LocalTracksModel *m_tracksModel;
    int createPlaylist();
};

#endif // MAINFORM_H
