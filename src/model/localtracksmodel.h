#ifndef LOCALTRACKSMODEL_H
#define LOCALTRACKSMODEL_H

#include <QSqlTableModel>
#include <QJsonObject>

class LocalTracksModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit LocalTracksModel(QObject *parent = nullptr);

    int columnPlaylistIDIndex() const;
    int columnIDIndex() const;
    int columnNameIndex() const;
    int columnExternalIDIndex() const;
    int columnUrlIndex() const;
    int columnAlbumIndex() const;
    int columnArtitsIndex() const;

    QString name(int row);

public slots:
    void setCurrentPlaylistID(int playlistID);
    bool addPlaylistTrack(int playlistID, QJsonObject trackItem);
};



#endif // LOCALTRACKSMODEL_H
