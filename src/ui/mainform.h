#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

namespace Ui {
class MainForm;
}

class AppControl;
class PlaylistModel;

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

private:
    Ui::MainForm *ui;
    AppControl *m_control;
    PlaylistModel *m_playlistModel;
};

#endif // MAINFORM_H
