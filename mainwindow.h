#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AppControl;
class LoginForm;
class MainForm;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void goLoginPage();
    void goMainPage();

    void setPage(QWidget *w);

    Ui::MainWindow *ui;
    AppControl *m_control;
    LoginForm *m_loginForm;
    MainForm *m_mainForm;

};
#endif // MAINWINDOW_H
