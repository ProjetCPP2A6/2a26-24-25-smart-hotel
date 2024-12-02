#ifndef FLAMEDETECTION_H
#define FLAMEDETECTION_H

#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class FlameDetection
{
public:
    FlameDetection();
    FlameDetection(const QDateTime &detectionTime, double duration, const QString &status);

    bool addDetectionToDatabase();  // Function to add flame detection data to the database
    bool updateExtinguishToDatabase(double duration);  // Function to update flame extinguish data in the database

    // Getters and Setters
    QDateTime getDetectionTime() const;
    void setDetectionTime(const QDateTime &value);

    double getDuration() const;
    void setDuration(double value);

    QString getStatus() const;
    void setStatus(const QString &value);

private:
    QDateTime detectionTime;
    double duration;
    QString status;
    int detectionId; // Store the ID of the detection for updates
};

#endif // FLAMEDETECTION_H
