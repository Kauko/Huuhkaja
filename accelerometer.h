#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include "singleton.h"

#include <QAccelerometer>

class Accelerometer : public QObject, public Singleton<Accelerometer> {
    Q_OBJECT
    QtMobility::QAccelerometer* accelerometer;

public:
    explicit Accelerometer(QObject *parent = 0);
    ~Accelerometer();

    void getAccelerometerAcceleration();
signals:

public slots:

};

#endif // ACCELEROMETER_H
