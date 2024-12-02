#include "flamedetection.h"
#include <QSqlQuery>
#include <QSqlError>

FlameDetection::FlameDetection() : duration(0), status("INACTIVE"), detectionId(-1) {}

FlameDetection::FlameDetection(const QDateTime &detectionTime, double duration, const QString &status)
    : detectionTime(detectionTime), duration(duration), status(status), detectionId(-1) {}

bool FlameDetection::addDetectionToDatabase() {
    QSqlQuery query;
    query.prepare("INSERT INTO FLAME_DETECTION (DETECTION_TIME, DURATION, STATUS) "
                  "VALUES (:detection_time, :duration, :status)");

    query.bindValue(":detection_time", detectionTime);
    query.bindValue(":duration", QVariant());  // Use NULL for duration as the flame is detected
    query.bindValue(":status", status);

    if (!query.exec()) {
        qDebug() << "Error inserting flame detection data into database:" << query.lastError().text();
        return false;
    }

    // The ID will be set automatically by the trigger
    return true;
}

bool FlameDetection::updateExtinguishToDatabase(double duration) {
    if (detectionId == -1) {
        qDebug() << "Error: No detection record found to update.";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE FLAME_DETECTION SET DURATION = :duration, STATUS = :status WHERE ID = :id");

    query.bindValue(":duration", duration);
    query.bindValue(":status", "Flame Extinguished");
    query.bindValue(":id", detectionId);

    if (!query.exec()) {
        qDebug() << "Error updating flame detection data:" << query.lastError().text();
        return false;
    }

    return true;
}

// Getters and Setters
QDateTime FlameDetection::getDetectionTime() const {
    return detectionTime;
}

void FlameDetection::setDetectionTime(const QDateTime &value) {
    detectionTime = value;
}

double FlameDetection::getDuration() const {
    return duration;
}

void FlameDetection::setDuration(double value) {
    duration = value;
}

QString FlameDetection::getStatus() const {
    return status;
}

void FlameDetection::setStatus(const QString &value) {
    status = value;
}
