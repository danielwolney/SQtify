#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "auth/oauth2authorization.h"
#include "database/dbconnection.h"
#include <QSignalSpy>
#include <QGuiApplication>

using namespace testing;

class OAuth2AuthorizationTests : public testing::Test {
 protected:
    void SetUp() override {
//        initDb();
    }
};

TEST_F(OAuth2AuthorizationTests, GetAccessToken)
{
    // uma instância de QGuiApplication é exigido pela QDesktopServices
    // para abrir a pagina no navegador
    int argc = 1;
    const auto arg0 = "dummy";
    char* argv0 = const_cast<char*>(arg0);
    char** argv = &argv0;
    QGuiApplication app(argc, argv);
    // ----------------------------------------------------------------

    OAuth2Authorization auth;
    EXPECT_FALSE(auth.hasAccess());
    QSignalSpy spy(&auth, &OAuth2Authorization::accessGranted);
    auth.grantAccess();
    EXPECT_TRUE(spy.wait(10 * 1000));
    EXPECT_EQ(spy.count(), 1);
    EXPECT_TRUE(auth.hasAccess());
}

