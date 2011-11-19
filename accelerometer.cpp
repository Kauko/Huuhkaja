#include "accelerometer.h"

Accelerometer::Accelerometer(QObject *parent) : QObject(parent) {
    qDebug("Accelerometer Construct");
}

Accelerometer::~Accelerometer() {
    qDebug("Accelerometer Destruct");
}
