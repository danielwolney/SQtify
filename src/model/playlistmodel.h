#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QSqlTableModel>

class PlaylistModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit PlaylistModel(QObject *parent = nullptr);
    int addPlaylist(QString name);
    int columnIDIndex() const;
    int columnNameIndex() const;

    int id(int row) const;
    QString name(int row) const;

};

#endif // PLAYLISTMODEL_H
