#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QWidget>

class Notification {
public:
    Notification(const QString &title, const QString &message, QWidget *parent = nullptr)
        : title_(title), message_(message), parent_(parent) {}

    QString title() const { return title_; }
    QString message() const { return message_; }

private:
    QString title_;
    QString message_;
    QWidget *parent_;
};
#endif // NOTIFICATIONWIDGET_H
