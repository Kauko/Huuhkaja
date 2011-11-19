#include "accelerometer.h"

Accelerometer::Accelerometer(QObject *parent) : QObject(parent) {
    qDebug("Accelerometer Construct");
    this->accelerometer = new QtMobility::QAccelerometer(this);
}

Accelerometer::~Accelerometer() {
    qDebug("Accelerometer Destruct");
}

void Accelerometer::getAccelerometerAcceleration() {
    QtMobility::QAccelerometerReading* reading = this->accelerometer->reading();
}
