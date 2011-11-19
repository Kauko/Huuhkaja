#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QList>
#include <qbluetooth.h>
#include <QBluetoothLocalDevice>
#include <QBluetoothAddress>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include "singleton.h"

class Bluetooth : public QObject, public Singleton<Bluetooth> {
    Q_OBJECT
public:
    explicit Bluetooth(QObject *parent = 0);
    void update();
    void start();
    void stop();
    ~Bluetooth();
private:
    QtMobility::QBluetoothAddress *btoothAddress; //device's bluetooth address
    QtMobility::QBluetoothLocalDevice *btoothLocDevice; //local device, used for retrieving for example MAC-address and such
    QtMobility::QBluetoothDeviceDiscoveryAgent *discoveryAgent; //used for discovering other devices
    QList<QtMobility::QBluetoothDeviceInfo> discoveredDevices; //devices discovered, duh

signals:

public slots:

};

#endif // BLUETOOTH_H
