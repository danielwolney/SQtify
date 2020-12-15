#include "spotifyprofile.h"
#include "dbconnection.h"
#include "jsonparser.h"

SpotifyProfile::SpotifyProfile() : m_id(""), m_displayName("")
{

}

SpotifyProfile::SpotifyProfile(QString id, QString displayName, QString imgUrl) :
    m_id(id),
    m_displayName(displayName),
    m_imgUrl(imgUrl)
{
}

SpotifyProfile::SpotifyProfile(const SpotifyProfile &prof)
{
    m_id = prof.id();
    m_displayName = prof.displayName();
}

QString SpotifyProfile::id() const
{
    return m_id;
}

void SpotifyProfile::setId(const QString &id)
{
    m_id = id;
}

QString SpotifyProfile::displayName() const
{
    return m_displayName;
}

void SpotifyProfile::setDisplayName(const QString &displayName)
{
    m_displayName = displayName;
}

QString SpotifyProfile::imgUrl() const
{
    return m_imgUrl;
}

void SpotifyProfile::setImgUrl(const QString &value)
{
    m_imgUrl = value;
}

SpotifyProfile SpotifyProfile::fromJson(QJsonObject json)
{
    QString imgUrl = "";
    if (json["images"].toArray().size() > 0) {
        imgUrl = json["images"].toArray()[0].toObject().value("url").toString();
    }
    return SpotifyProfile(json["id"].toString(),
            json["display_name"].toString(),
            imgUrl);
}

SpotifyProfile SpotifyProfile::load()
{
    QSqlQuery select(DBConnection::database());
    select.prepare("SELECT id, name, img_url FROM user");
    select.exec();
    if (select.first()) {
        return SpotifyProfile(select.value("id").toString(),
                              select.value("name").toString(),
                              select.value("img_url").toString());
    }
    return SpotifyProfile();
}

bool SpotifyProfile::save(const SpotifyProfile& prof)
{
    QSqlQuery insert(DBConnection::database());

    insert.exec("DELETE FROM user");

    insert.prepare("INSERT INTO user (id, name, img_url) VALUES (:id, :name, :img)");
    insert.bindValue(":id", prof.id());
    insert.bindValue(":name", prof.displayName());
    insert.bindValue(":img", prof.imgUrl());

    return insert.exec();
}
