#include "bluetooth.h"

Bluetooth::Bluetooth(QObject *parent) : QObject(parent) {
    //initialize objects and values
    qDebug("Bluetooth Construct");
    btoothLocDevice = new QtMobility::QBluetoothLocalDevice(this);
    btoothAddress = new QtMobility::QBluetoothAddress::QBluetoothAddress(btoothLocDevice->address());
    discoveryAgent = new QtMobility::QBluetoothDeviceDiscoveryAgent(this);
    timer = new QTimer(this);
    //connect discoveryAgent to finished()-signal so that when this signal is received, we start again
    connect(discoveryAgent, SIGNAL(finished()),
            this, SLOT(start()));
    //and then connect timer to timeout signal, so that when timeout happens, we poll the devices again
    connect(timer, SIGNAL(timeout()),
            this, SLOT(poll()));

    discoveredDevices.clear();  //to ensure that the list is clear, damnit

    justPolled = false; //well obviously it's going to be false for the first time
    hasBeenStarted = false;

    this->mapMutex = new QMutex();
}

Bluetooth::~Bluetooth() {
    qDebug("Bluetooth Destruct");
    delete discoveryAgent;
    delete btoothAddress;
    delete btoothLocDevice;
    delete timer;
    delete mapMutex;
}

void Bluetooth::update()
{
    //first we check if the polling has been started
    if (!hasBeenStarted)
        start();

    //some shenanigans here
    if (justPolled){
        //do something with rssi?

        justPolled = false;
    }
}

///
///Start the device polling
///
void Bluetooth::start()
{
    hasBeenStarted = true;
    discoveryAgent->start();
    timer->start(1000);
}

///
///Stop device polling
///
void Bluetooth::stop()
{
    discoveryAgent->stop();
}

///
///Polls discoveryAgent to seek for new devices
///Clears the current QList of items and inserts new items to it.
///DON'T CALL THIS METHOD OUTSIDE OF THIS CLASS
///
void Bluetooth::poll()
{
    this->mapMutex->lock();
    discoveredDevices.clear();
    discoveredDevices = discoveryAgent->discoveredDevices();
    justPolled = true;
    this->mapMutex->unlock();
}

///
///Forces the device to repoll discoveryAgent for new devices
///
void Bluetooth::forcePoll()
{
    this->mapMutex->lock();
    discoveredDevices.clear();
    discoveredDevices = discoveryAgent->discoveredDevices();
    justPolled = true;
    this->mapMutex->unlock();
}

///
///Returns a QList containing all the devices nearby
///WARNING: May be an empty list
///
QList<QtMobility::QBluetoothDeviceInfo> Bluetooth::getDevices()
{
    return discoveredDevices;
}

///
///Returns a pointer to this local bluetooth device, granting access to its name and such information
///
QtMobility::QBluetoothLocalDevice * Bluetooth::getLocalDevice()
{
    return btoothLocDevice;
}

///
///Returns a pointer to this local device's address
///
QtMobility::QBluetoothAddress * Bluetooth::getDeviceAddress()
{
    return btoothAddress;
}

///
///Returns a map of devices in the form of <Name, rssi>, where name is in QString and rssi is in qint16
///If no devices are detected, returns empty map
///
QMap<QString, qint16> Bluetooth::getDeviceMap()
{
    this->mapMutex->lock();

    QMap<QString, qint16> map = QMap<QString, qint16>();

    for (int i = 0; i < discoveredDevices.size(); i++){
        //let's create the map
        map.insert(discoveredDevices[i].name(), discoveredDevices[i].rssi());
    }

    this->mapMutex->unlock();

    return map;
}
