#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QFrame>

namespace Ui {
class PlayerWidget;
}

class MediaPlayer;
class PlayerWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();

    void setPlayer(MediaPlayer *player);

private slots:
    void on_btnSkip_clicked();
    void on_btnPrevious_clicked();

    void on_btnResume_clicked();

private:
    QString time(quint64 ms);
    Ui::PlayerWidget *ui;
    MediaPlayer *m_player;
};



#endif // PLAYERWIDGET_H
