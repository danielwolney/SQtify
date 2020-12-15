#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

namespace Ui {
class LoginForm;
}

class AppControl;

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(AppControl *appControl, QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void on_btnLogin_clicked();

private:
    Ui::LoginForm *ui;
    AppControl *m_control;
};

#endif // LOGINFORM_H
