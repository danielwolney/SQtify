#include "playlistmodel.h"
#include "database/dbconnection.h"
#include <QSqlRecord>

PlaylistModel::PlaylistModel(QObject *parent)
    : QSqlTableModel(parent, DBConnection::database())
{
    setTable("playlist");
    select();
}

int PlaylistModel::addPlaylist(QString name)
{
    if (insertRow(rowCount())) {
        setData(index(rowCount()-1, columnNameIndex()), name);
        bool ok = submitAll();
        int id = query().lastInsertId().toInt();
        if (ok) {
            select();
            return id;
        }
    }
    return 0;
}

int PlaylistModel::columnIDIndex() const
{
    return  fieldIndex("id");
}

int PlaylistModel::columnNameIndex() const
{
    return  fieldIndex("name");
}

int PlaylistModel::id(int row) const
{
    return record(row).value(columnIDIndex()).toInt();
}

QString PlaylistModel::name(int row) const
{
    return record(row).value(columnNameIndex()).toString();
}

