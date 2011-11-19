#include "accelerometer.h"
#include <qmath.h>
Accelerometer::Accelerometer(QObject *parent) : QObject(parent) {
    qDebug("Accelerometer Construct");
    this->accelerometer = new QtMobility::QAccelerometer(this);
    this->accelerometer->start();
    this->accelerometer->setOutputRange(-1);
    connect(this->accelerometer, SIGNAL(readingChanged()), this, SLOT(accelerometerTimeout()));

    this->x = 0;
    this->y = 0;
    this->z = 0;

    this->xdelta = 0;
    this->ydelta = 0;
    this->zdelta = 0;

    this->deltaLength = 0;
}

Accelerometer::~Accelerometer() {
    qDebug("Accelerometer Destruct");
    this->accelerometer->stop();
}

void Accelerometer::accelerometerTimeout() {
    QtMobility::QAccelerometerReading* reading = this->accelerometer->reading();
    qreal sensorX = reading->x();
    qreal sensorY = reading->y();
    qreal sensorZ = reading->z();

    this->xdelta = sensorX - this->x;
    this->ydelta = sensorY - this->y;
    this->zdelta = sensorZ - this->z;

    this->x = sensorX;
    this->y = sensorY;
    this->z = sensorZ;

    this->deltaLength = qSqrt(qPow(this->xdelta,2) + qPow(this->ydelta,2) + qPow(this->zdelta,2));
}

qreal Accelerometer::getAccelerometerAccelerationDelta() {
    return this->deltaLength;
}
