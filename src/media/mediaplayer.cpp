#include "mediaplayer.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaContent>

MediaPlayer::MediaPlayer(QObject *parent) : QObject(parent),
    m_player(new QMediaPlayer(this, QMediaPlayer::StreamPlayback)),
    m_playlist(new QMediaPlaylist(this))
{
    m_player->setPlaylist(m_playlist);
    connect(m_player, &QMediaPlayer::durationChanged, this, &MediaPlayer::durationChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &MediaPlayer::positionChanged);
    connect(m_player, &QMediaPlayer::stateChanged, this, [&,this](QMediaPlayer::State state){
        emit stateChanged(static_cast<MediaPlayer::State>(state));
    });
    connect(m_player, &QMediaPlayer::currentMediaChanged, this, [&,this](const QMediaContent &media){
        setCurrentTrack(m_tracks[media.request().url()]);
    });

    m_player->setVolume(50);
}

QJsonObject MediaPlayer::currentTrack() const
{
    return m_currentTrack;
}

void MediaPlayer::startPlaylist(QList<QJsonObject> tracks)
{
    stop();
    QUrl url;
    for (QJsonObject track: tracks) {
        url = QUrl(track.value("url_sample").toString());
        if (url.isValid()) {
            m_playlist->addMedia(QMediaContent(url));
            m_tracks.insert(url, track);
        }
    }
    play();
}

void MediaPlayer::resume()
{
    if (state() == PausedState) {
        play();
    } else if (state() == PlayingState) {
        pause();
    }
}

void MediaPlayer::play()
{
    m_player->play();
}

void MediaPlayer::pause()
{
    m_player->pause();
}

void MediaPlayer::stop()
{
    m_playlist->clear();
    m_player->stop();
}

void MediaPlayer::skip()
{
    m_playlist->next();
}

void MediaPlayer::previous()
{
    m_playlist->previous();
}

MediaPlayer::State MediaPlayer::state()
{
    return static_cast<MediaPlayer::State>(m_player->state());
}

void MediaPlayer::setPosition(int position)
{
    setPosition((qint64) position);
}

void MediaPlayer::setPosition(qint64 position)
{
    m_player->setPosition(position);
}

void MediaPlayer::setCurrentTrack(QJsonObject currentTrack)
{
    if (m_currentTrack == currentTrack)
        return;

    m_currentTrack = currentTrack;
    emit currentTrackChanged(m_currentTrack);
}
