#ifndef ACTIONLISTVIEW_H
#define ACTIONLISTVIEW_H

#include <QListView>

class QFrame;
class QToolButton;
class ActionListView : public QListView
{
    Q_OBJECT
public:
    explicit ActionListView(QWidget *parent = nullptr);
    void addAction(QAction *action);
    QModelIndex focusIndex() const;

protected:
    bool eventFilter(QObject *obj, QEvent *e) override;

private:
    QWidget *m_btnBox;
    QList<QToolButton*> m_buttons;
    QModelIndex m_focusIndex;
};

#endif // ACTIONLISTVIEW_H
