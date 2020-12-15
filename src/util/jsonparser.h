#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

namespace JSONParser {
QJsonObject toObject(QByteArray jsonContent);
QJsonObject toObject(QString jsonContent);
QJsonArray toJsonArray(QByteArray jsonContent);
QByteArray toByteArray(QJsonObject jsonObject);
}

#endif // JSONPARSER_H
