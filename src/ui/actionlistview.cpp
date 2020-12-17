#include "actionlistview.h"
#include <QToolButton>
#include <QAction>
#include <QMouseEvent>
#include <QFrame>
#include <QHBoxLayout>

ActionListView::ActionListView(QWidget *parent) : QListView(parent),
  m_btnBox(new QWidget(viewport()))
{
    viewport()->setMouseTracking(true);
    viewport()->installEventFilter(this);

    m_btnBox->setLayout(new QHBoxLayout());
    m_btnBox->layout()->setSpacing(0);
    m_btnBox->layout()->setContentsMargins(0,0,0,0);
    m_btnBox->setVisible(false);
}

void ActionListView::addAction(QAction *action)
{
    if (action) {
        auto btn = new QToolButton(m_btnBox);
        btn->setIcon(action->icon());
        btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btn->setAutoRaise(true);
        m_btnBox->layout()->addWidget(btn);
        m_btnBox->adjustSize();
        connect(btn, &QToolButton::clicked, action, &QAction::triggered);
    }
    QListView::addAction(action);
}

bool ActionListView::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == viewport()) {
        if(e->type() == QEvent::MouseMove) {
            QMouseEvent *ev = static_cast<QMouseEvent*>(e);
            QModelIndex pointIndex = indexAt(ev->pos());
            if(pointIndex.isValid()) {
                QRect lineRect = visualRect(pointIndex);
                m_btnBox->resize(m_btnBox->width(), lineRect.height());
                m_focusIndex = pointIndex;
                int posY = lineRect.top();
                int posX = lineRect.width() - m_btnBox->width();
                m_btnBox->move(posX, posY);
                m_btnBox->setVisible(true);
            } else {
                 m_btnBox->setVisible(false);
            }
        } else if(e->type() == QEvent::Leave) {
            m_btnBox->setVisible(false);
        }
    }

    return QWidget::eventFilter(obj, e);
}

QModelIndex ActionListView::focusIndex() const
{
    return m_focusIndex;
}
