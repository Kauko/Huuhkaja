#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>
#include <QtGlobal>
#include <QTimer>
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
    void stop();
    void forcePoll();
    QList<QtMobility::QBluetoothDeviceInfo> getDevices();
    QtMobility::QBluetoothLocalDevice* getLocalDevice();
    QtMobility::QBluetoothAddress* getDeviceAddress();
    QMap<QString, qint16> getDeviceMap();
    ~Bluetooth();
private:
    //variables and such
    QtMobility::QBluetoothAddress *btoothAddress; //device's bluetooth address
    QtMobility::QBluetoothLocalDevice *btoothLocDevice; //local device, used for retrieving for example MAC-address and such
    QtMobility::QBluetoothDeviceDiscoveryAgent *discoveryAgent; //used for discovering other devices
    QList<QtMobility::QBluetoothDeviceInfo> discoveredDevices; //devices discovered, duh
    QTimer* timer;

    bool justPolled;
    bool hasBeenStarted;

    //private methods

signals:

public slots:
    void start();
private slots:
    void poll();
};

#endif // BLUETOOTH_H
