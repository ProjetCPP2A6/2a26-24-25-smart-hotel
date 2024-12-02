#include "notificationwidget.h"
#include "ui_notificationwidget.h"
#include "QLabel"
class NotificationWidget : public QWidget {
public:
    NotificationWidget(const Notification &notification, QWidget *parent = nullptr)
        : QWidget(parent), notification_(notification) {
        setupUi();
    }

private:
    Notification notification_;
    QLabel *titleLabel_;
    QLabel *messageLabel_;

    void setupUi() {
        // ... UI setup code, including layout, stylesheets, etc.
        titleLabel_->setText(notification_.title());
        messageLabel_->setText(notification_.message());
    }

    void closeEvent(QCloseEvent *event) {
        // Emit a signal or perform other actions when the notification is closed
        emit notificationClosed(notification_.title());

    }

signals:
    void notificationClosed(const QString &title);
};
