#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QFrame>

namespace Ui {
class PlayerWidget;
}

class MediaPlayer;
class HttpRequestManager;

class PlayerWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();

    void setPlayer(MediaPlayer *player);
    void setHttpRequestManager(HttpRequestManager *httpManager);

private slots:
    void on_btnSkip_clicked();
    void on_btnPrevious_clicked();

    void on_btnResume_clicked();

private:
    QString time(quint64 ms);
    Ui::PlayerWidget *ui;
    MediaPlayer *m_player;
    HttpRequestManager *m_httpManager;
};



#endif // PLAYERWIDGET_H
