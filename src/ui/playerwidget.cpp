#include "playerwidget.h"
#include "ui_playerwidget.h"
#include "media/mediaplayer.h"
#include <QJsonObject>

PlayerWidget::PlayerWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PlayerWidget),
    m_player(Q_NULLPTR)
{
    ui->setupUi(this);
    ui->sliderPosition->setPageStep(1);
    ui->sliderPosition->setTickInterval(1);
    ui->sliderPosition->setTracking(false);
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void PlayerWidget::setPlayer(MediaPlayer *player)
{
    m_player = player;

    connect(m_player, &MediaPlayer::durationChanged, [&,this](qint64 durationMS){
        ui->lblDuration->setText(time(durationMS));
        ui->sliderPosition->setMaximum(durationMS/1000);
    });

    connect(m_player, &MediaPlayer::positionChanged, this, [&,this](qint64 positionMS){
        ui->lblCurrenPosition->setText(time(positionMS));
        if (!ui->sliderPosition->isSliderDown()) {
            ui->sliderPosition->blockSignals(true);
            ui->sliderPosition->setValue(positionMS/1000);
            ui->sliderPosition->blockSignals(false);
        }
    });
    connect(ui->sliderPosition, &QSlider::valueChanged, this, [&,this](int position){
        if (!ui->sliderPosition->isSliderDown()) {
            m_player->setPosition(position);
        }
    });

    connect(m_player, &MediaPlayer::currentTrackChanged, this, [&,this](const QJsonObject &track){
        ui->lblImage->setPixmap(track.value("img_url").toString());
        ui->lblName->setText(track.value("name").toString());
        ui->lblArtist->setText(track.value("artists").toString());
    });
    connect(m_player, &MediaPlayer::stateChanged, this, [&,this](MediaPlayer::State state) {
        if (state == MediaPlayer::PlayingState) {
            ui->btnResume->setIcon(QIcon(":/pause_circle-green-24dp.svg"));
        } else {
            ui->btnResume->setIcon(QIcon(":/play_circle-green-24dp.svg"));
        }
    });
}

QString PlayerWidget::time(quint64 ms)
{
    quint64 s = ms/1000;
    return QString::number((int)(s / 60))
           + ":"
           +QString::number((int)(s % 60)).rightJustified(2,'0');
}

void PlayerWidget::on_btnSkip_clicked()
{
    m_player->skip();
}

void PlayerWidget::on_btnPrevious_clicked()
{
    m_player->previous();
}

void PlayerWidget::on_btnResume_clicked()
{
    m_player->resume();
}
