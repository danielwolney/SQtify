#include "localtracksmodel.h"
#include "database/dbconnection.h"
#include <QSqlRecord>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

LocalTracksModel::LocalTracksModel(QObject *parent)
    : QSqlTableModel(parent, DBConnection::database())
{
    setTable("track");
    setFilter("false");
    select();
}

void LocalTracksModel::setCurrentPlaylistID(int playlistID)
{
    setFilter(QString("id_playlist=%1").arg(playlistID));
}

int LocalTracksModel::columnPlaylistIDIndex() const
{
    return fieldIndex("id_playlist");
}

int LocalTracksModel::columnIDIndex() const
{
    return fieldIndex("id");
}

int LocalTracksModel::columnNameIndex() const
{
    return fieldIndex("name");
}

int LocalTracksModel::columnExternalIDIndex() const
{
    return fieldIndex("external_id");
}

int LocalTracksModel::columnUrlIndex() const
{
    return fieldIndex("url_sample");
}

int LocalTracksModel::columnAlbumIndex() const
{
    return fieldIndex("album_name");
}

int LocalTracksModel::columnArtitsIndex() const
{
    return fieldIndex("artists");
}

#include <QSqlError>
bool LocalTracksModel::addPlaylistTrack(int playlistID, QJsonObject trackItem)
{
    if (insertRow(rowCount())) {
        setData(index(rowCount()-1, columnPlaylistIDIndex()), playlistID);
        setData(index(rowCount()-1, columnNameIndex()), trackItem.value("name").toString());
        setData(index(rowCount()-1, columnExternalIDIndex()), trackItem.value("id").toString());
        setData(index(rowCount()-1, columnUrlIndex()), trackItem.value("preview_url").toString());
        setData(index(rowCount()-1, columnAlbumIndex()), trackItem.value("album").toObject().value("name").toString());
        QStringList artists;
        for (QJsonValue v: trackItem.value("artists").toArray()) {
            artists << v.toObject().value("name").toString();
        }
        setData(index(rowCount()-1, columnArtitsIndex()), artists.join(", "));
        bool ok = submitAll();
        if (ok) {
            select();
        } else {
            qDebug() << __PRETTY_FUNCTION__ << lastError();
            revertAll();
        }
    }
    return false;
}

