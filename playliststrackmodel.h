#ifndef PLAYLISTTRACKMODEL_H
#define PLAYLISTTRACKMODEL_H

#include <QSqlTableModel>

class PlaylistTrackModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit PlaylistTrackModel(QObject *parent = nullptr);

private:
};


class Track {

};

#endif // PLAYLISTTRACKMODEL_H
