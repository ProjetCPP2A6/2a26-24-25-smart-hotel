#ifndef TASKSCHEDULING_H
#define TASKSCHEDULING_H

#include <QWidget>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMap>
#include <QPair>
#include <QDate>



class TaskScheduling : public QWidget
{
    Q_OBJECT

public:
    explicit TaskScheduling(QWidget *parent = nullptr);
    ~TaskScheduling();

private:
    // Data structure to store events with their date as the key
    QMap<QDate, QPair<QString, QString>> events;

    // UI Elements
    QCalendarWidget *calendarWidget;
    QLineEdit *eventNameLineEdit;
    QTextEdit *descriptionTextEdit;
    QTextEdit *eventDetailsTextEdit;
    QLineEdit *searchLineEdit;
    QPushButton *addButton;
    QPushButton *searchButton;

private slots:
    void onDateSelected(const QDate &date);
    void onAddEvent();
    void onSearchEvent();
};

#endif // TASKSCHEDULING_H
