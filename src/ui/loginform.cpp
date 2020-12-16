#include "loginform.h"
#include "ui_loginform.h"
#include "control/appcontrol.h"

LoginForm::LoginForm(AppControl *appControl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm),
    m_control(appControl)
{
    ui->setupUi(this);
    ui->btnLogin->setIcon(QIcon());
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_btnLogin_clicked()
{
    m_control->grantAccess();
}
