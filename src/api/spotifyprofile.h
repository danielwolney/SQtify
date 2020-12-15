#ifndef SPOTIFYPROFILE_H
#define SPOTIFYPROFILE_H

#include <QJsonObject>

class SpotifyProfile
{
public:
    explicit SpotifyProfile();
    SpotifyProfile(QString id, QString displayName, QString imgUrl);
    SpotifyProfile(const SpotifyProfile & prof);


    QString id() const;
    void setId(const QString &id);

    QString displayName() const;
    void setDisplayName(const QString &displayName);

    QString imgUrl() const;
    void setImgUrl(const QString &value);

    static SpotifyProfile fromJson(QJsonObject json);
    static SpotifyProfile load();
    static bool save(const SpotifyProfile &prof);
private:
    QString m_id;
    QString m_displayName;
    QString m_imgUrl;
};

#endif // SPOTIFYPROFILE_H
