#ifndef UKUIMENU_H
#define UKUIMENU_H

#include <QMenu>
class Ukuimenu : public QMenu
{
public:
    Ukuimenu();
public:
    explicit Ukuimenu(QWidget *parent = 0): QMenu(parent) {}
    explicit Ukuimenu(const QString &title, QWidget *parent = 0): QMenu(title, parent) {}

    QAction* addTitle(const QIcon &icon, const QString &text);
    QAction* addTitle(const QString &text);

    bool eventFilter(QObject *object, QEvent *event);

protected:
    virtual void keyPressEvent(QKeyEvent* e);
};

#endif // UKUIMENU_H
