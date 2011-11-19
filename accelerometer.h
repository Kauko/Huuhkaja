#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include "singleton.h"

#include <QAccelerometer>

class Accelerometer : public QObject, public Singleton<Accelerometer> {
    Q_OBJECT
    QtMobility::QAccelerometer* accelerometer;

    qreal x;
    qreal y;
    qreal z;

    qreal xdelta;
    qreal ydelta;
    qreal zdelta;

    qreal deltaLength;

public:
    explicit Accelerometer(QObject *parent = 0);
    ~Accelerometer();

    qreal getAccelerometerAccelerationDelta();
signals:

public slots:

private slots:
    void accelerometerTimeout();

};

#endif // ACCELEROMETER_H
