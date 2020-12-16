#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "control/appcontrol.h"
#include "loginform.h"
#include "mainform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_control(new AppControl())
    , m_loginForm(Q_NULLPTR)
{
    ui->setupUi(this);

    if (!m_control->hasAccess()) {
        goLoginPage();
    } else {
        goMainPage();
    }
    connect(m_control, &AppControl::accessGranted, this, &MainWindow::goMainPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goLoginPage()
{
    if (!m_loginForm) {
        m_loginForm = new LoginForm(m_control, this);
    }
    setPage(m_loginForm);
}

void MainWindow::goMainPage()
{
    if (!m_mainForm) {
        m_mainForm = new MainForm(m_control, this);
    }
    setPage(m_mainForm);
}

void MainWindow::setPage(QWidget *w)
{
    if (ui->stackedWidget->indexOf(w) < 0) {
        ui->stackedWidget->addWidget(w);
    }
    ui->stackedWidget->setCurrentWidget(w);
}
