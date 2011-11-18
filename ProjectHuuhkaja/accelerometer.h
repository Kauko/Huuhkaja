#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include "singleton.h"

class Accelerometer : public QObject, public Singleton<Accelerometer> {
    Q_OBJECT
public:
    explicit Accelerometer(QObject *parent = 0);

    int test() {
        return 1;
    }
signals:

public slots:

};

#endif // ACCELEROMETER_H
