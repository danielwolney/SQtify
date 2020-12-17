#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QJsonObject>

class QMediaPlayer;
class QMediaPlaylist;

class MediaPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MediaPlayer(QObject *parent = nullptr);
    enum State
    {
        StoppedState,
        PlayingState,
        PausedState
    };

    Q_PROPERTY(QJsonObject currentTrack READ currentTrack WRITE setCurrentTrack NOTIFY currentTrackChanged)
    QJsonObject currentTrack() const;

    void setBindedPositionObj(QObject *bindedPositionObj);

public slots:
    void startPlaylist(QList<QJsonObject> tracks);
    void resume();
    void play();
    void pause();
    void stop();
    void skip();
    void previous();

    MediaPlayer::State state();

    void setPosition(int position);
    void setPosition(qint64 position);

signals:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void currentTrackChanged(const QJsonObject & track);
    void stateChanged(MediaPlayer::State state);

private:
    void setCurrentTrack(QJsonObject currentTrack);
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
    QHash<QUrl, QJsonObject> m_tracks;
    QJsonObject m_currentTrack;
};

#endif // MEDIAPLAYER_H
