#include "dbconnection.h"
#include <QCoreApplication>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include "util/jsonparser.h"

#define CONNECTION_NAME "sqtify"

QSqlDatabase DBConnection::database()
{
    return QSqlDatabase::database(CONNECTION_NAME);
}

void initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
    QString fileName = "data.db3";
    db.setDatabaseName(fileName);
    QFile dbFile(fileName);
    bool fileExists = dbFile.exists(fileName);
    db.open();
    QSqlQuery query(db);
    if (!fileExists || dbFile.size() < 1) {
        QFile srcFile(":/db.json");
        srcFile.open(QFile::ReadOnly);
        QJsonObject obj = JSONParser::toObject(srcFile.readAll());
        QJsonArray tables = obj.value("tables").toArray();
        QSqlQuery query(db);
        for (QJsonValue create: tables) {
            query.exec(create.toString());
            if (query.lastError().type() != QSqlError::NoError) {
//                qDebug() << query.lastError();
            }
        }
    } else {
        //todo: estrutura de migration
    }
}
Q_COREAPP_STARTUP_FUNCTION(initDb);
