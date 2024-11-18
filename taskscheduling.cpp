#include "taskscheduling.h"
#include <QCalendarWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

TaskScheduling::TaskScheduling(QWidget *parent) : QWidget(parent)
{
    // Initialize UI elements
    calendarWidget = new QCalendarWidget(this);
    eventNameLineEdit = new QLineEdit(this);
    descriptionTextEdit = new QTextEdit(this);
    eventDetailsTextEdit = new QTextEdit(this);
    searchLineEdit = new QLineEdit(this);
    addButton = new QPushButton("Add Event", this);
    searchButton = new QPushButton("Search", this);

    // Layout setup
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *addEventLayout = new QHBoxLayout();
    QHBoxLayout *searchLayout = new QHBoxLayout();

    // Calendar
    mainLayout->addWidget(calendarWidget);

    // Add Event Section
    QLabel *eventNameLabel = new QLabel("Event Name:", this);
    QLabel *descriptionLabel = new QLabel("Description:", this);

    addEventLayout->addWidget(eventNameLabel);
    addEventLayout->addWidget(eventNameLineEdit);
    addEventLayout->addWidget(descriptionLabel);
    addEventLayout->addWidget(descriptionTextEdit);
    addEventLayout->addWidget(addButton);

    mainLayout->addLayout(addEventLayout);

    // Event Details Section
    QLabel *eventDetailsLabel = new QLabel("Event:", this);
    mainLayout->addWidget(eventDetailsLabel);
    mainLayout->addWidget(eventDetailsTextEdit);

    // Search Event Section
    QLabel *searchLabel = new QLabel("Search Event:", this);
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);

    // Signals and slots
    connect(calendarWidget, &QCalendarWidget::clicked, this, &TaskScheduling::onDateSelected);
    connect(addButton, &QPushButton::clicked, this, &TaskScheduling::onAddEvent);
    connect(searchButton, &QPushButton::clicked, this, &TaskScheduling::onSearchEvent);
}

TaskScheduling::~TaskScheduling() {}

void TaskScheduling::onDateSelected(const QDate &date)
{
    if (events.contains(date))
    {
        auto event = events.value(date);
        QString details = "Event Name: " + event.first + "\nDescription: " + event.second;
        eventDetailsTextEdit->setText(details);
    }
    else
    {
        eventDetailsTextEdit->setText("No events for the selected date.");
    }
}

void TaskScheduling::onAddEvent()
{
    QDate date = calendarWidget->selectedDate();
    QString eventName = eventNameLineEdit->text();
    QString description = descriptionTextEdit->toPlainText();

    if (!eventName.isEmpty() && !description.isEmpty())
    {
        events[date] = qMakePair(eventName, description);
        eventDetailsTextEdit->setText("Event added successfully!\n\nEvent Name: " + eventName +
                                      "\nDescription: " + description);
        eventNameLineEdit->clear();
        descriptionTextEdit->clear();
    }
    else
    {
        eventDetailsTextEdit->setText("Please provide both Event Name and Description.");
    }
}

void TaskScheduling::onSearchEvent()
{
    QString searchQuery = searchLineEdit->text();
    bool found = false;

    for (auto it = events.begin(); it != events.end(); ++it)
    {
        if (it.value().first.contains(searchQuery, Qt::CaseInsensitive))
        {
            QString details = "Date: " + it.key().toString("yyyy-MM-dd") + "\nEvent Name: " + it.value().first +
                              "\nDescription: " + it.value().second;
            eventDetailsTextEdit->setText(details);
            found = true;
            break;
        }
    }

    if (!found)
    {
        eventDetailsTextEdit->setText("No events found matching the search query.");
    }
}
