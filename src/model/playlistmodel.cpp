#include "playlistmodel.h"
#include "database/dbconnection.h"
#include <QSqlRecord>

PlaylistModel::PlaylistModel(QObject *parent)
    : QSqlTableModel(parent, DBConnection::database())
{
    setTable("playlist");
    select();
    setHeaderData(0, Qt::Horizontal, tr("id"));
    setHeaderData(1, Qt::Horizontal, tr("Nome"));
}

bool PlaylistModel::addPlaylist(QString name)
{
    if (insertRow(rowCount())) {
        setData(index(rowCount()-1, columnNameIndex()), name);
        return submit();
    }
    return false;
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
