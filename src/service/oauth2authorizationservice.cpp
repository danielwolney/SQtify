#include "oauth2authorizationservice.h"

#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QUrl>
#include <QDebug>
#include <QDesktopServices>
#include "database/dbconnection.h"
#include "api/spotifyurls.h"
//#include <QWebEngineView>

OAuth2AuthorizationService::OAuth2AuthorizationService(QObject *parent) : QObject(parent)
{
    m_oAuthFlow = new QOAuth2AuthorizationCodeFlow();

    m_oAuthFlow->setToken(readAccessToken());
    m_oAuthFlow->setRefreshToken(readRefreshToken());

    m_oAuthFlow->setReplyHandler(new QOAuthHttpServerReplyHandler(QHostAddress::LocalHost, 8082, this));
    m_oAuthFlow->setAuthorizationUrl(QUrl(SPOTIFY_ACC_AUTH));
    m_oAuthFlow->setAccessTokenUrl(QUrl(SPOTIFY_ACC_TOKEN));

    m_oAuthFlow->setClientIdentifier(SQTIFY_CLIENT_ID);
    m_oAuthFlow->setClientIdentifierSharedKey(SQTIFY_CLIENT_SECRET);

    m_oAuthFlow->setScope("streaming user-read-email user-read-private user-top-read playlist-read-private");

    connect(m_oAuthFlow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,  &QDesktopServices::openUrl);

    connect(m_oAuthFlow, &QOAuth2AuthorizationCodeFlow::granted,
            this, [&, this](){
        qDebug() << "granted" << m_oAuthFlow->token() << m_oAuthFlow->expirationAt();
        saveAccessToken(m_oAuthFlow->token());
        saveRefreshToken(m_oAuthFlow->refreshToken());
        emit accessGranted(m_oAuthFlow->token());
    });

}

bool OAuth2AuthorizationService::hasAccess()
{
    return (!accessToken().isEmpty());
}

QString OAuth2AuthorizationService::accessToken()
{
    return m_oAuthFlow->token();
}

void OAuth2AuthorizationService::grantAccess()
{
    m_oAuthFlow->grant();
}

void OAuth2AuthorizationService::refreshAccessToken()
{
    //QOAuth2AuthorizationCodeFlow::refreshAccessToken(): qt bug - não funciona, a api retorna 'QNetworkReply::ProtocolInvalidOperationError
//    "Error transferring https://accounts.spotify.com/api/token - server replied: Bad Request"'
// aparentemente devido ao CORS. O fluxo de autorização funciona somente server-to-server e o método faz uma simples request
    // ref: https://stackoverflow.com/questions/53218678/spotify-api-bad-request-on-api-token-authorization-error-400

    grantAccess();
}

QString OAuth2AuthorizationService::readAccessToken()
{
    return getVar("at");
}

void OAuth2AuthorizationService::saveAccessToken(QString token)
{
    saveVar("at", token);
}

QString OAuth2AuthorizationService::readRefreshToken()
{
    return getVar("rt");
}

void OAuth2AuthorizationService::saveRefreshToken(QString token)
{
    saveVar("rt", token);
}

void OAuth2AuthorizationService::saveVar(QString varName, QString value)
{
    QSqlQuery insert(DBConnection::database());
    insert.prepare("INSERT OR REPLACE INTO session(var_name, value) VALUES (:name, :value)");
    insert.bindValue(":name", varName);
    insert.bindValue(":value", value);    
    insert.exec();
    qDebug() << "save" << varName;
}

QString OAuth2AuthorizationService::getVar(QString varName)
{
    QSqlQuery select(DBConnection::database());
    select.prepare("SELECT value FROM session WHERE var_name = :name");
    select.bindValue(":name", varName);
    select.exec();
    if (select.first()) {
        qDebug() << "read" << varName << select.value("value").toString();
        return select.value("value").toString();
    }
    return "";
}
