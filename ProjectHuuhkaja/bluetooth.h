#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include "singleton.h"

class Bluetooth : public QObject, public Singleton<Bluetooth> {
    Q_OBJECT
public:
    explicit Bluetooth(QObject *parent = 0);
private:

signals:

public slots:

};

#endif // BLUETOOTH_H
