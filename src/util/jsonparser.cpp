#include "jsonparser.h"

QJsonObject JSONParser::toObject(QByteArray jsonContent)
{
    QJsonDocument rootDocument(QJsonDocument::fromJson(jsonContent));
    QJsonObject object = rootDocument.object();
    return object;
}

QJsonObject JSONParser::toObject(QString jsonContent)
{
    return toObject(jsonContent.toUtf8());
}

QJsonArray JSONParser::toJsonArray(QByteArray jsonContent)
{
    QJsonDocument rootDocument(QJsonDocument::fromJson(jsonContent));
    QJsonArray array = rootDocument.array();
    return array;
}

QByteArray JSONParser::toByteArray(QJsonObject jsonObject)
{
    QJsonDocument rootDocument(jsonObject);
    return rootDocument.toJson(QJsonDocument::Compact);
}
