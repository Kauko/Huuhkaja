#include "bluetooth.h"

Bluetooth::Bluetooth(QObject *parent) : QObject(parent) {
    //initialize objects and values
    qDebug("Bluetooth Construct");
    btoothLocDevice = new QtMobility::QBluetoothLocalDevice(this);
    btoothAddress = new QtMobility::QBluetoothAddress::QBluetoothAddress(btoothLocDevice->address());
    discoveryAgent = new QtMobility::QBluetoothDeviceDiscoveryAgent(this);
    discoveredDevices.clear();  //to ensure that the list is clear, damnit

    updateCycle = 0;    //we start from 0, obviously
    justPolled = false; //well obviously it's going to be false for the first time
    hasBeenStarted = false;

}

Bluetooth::~Bluetooth() {
    qDebug("Bluetooth Destruct");
    delete discoveryAgent;
    delete btoothAddress;
    delete btoothLocDevice;
}

void Bluetooth::update()
{
    //first we check if the polling has been started
    if (!hasBeenStarted){
        //if not, let's do it this way, and shame on the programmer who forgot to use Bluetooth::start()
        discoveryAgent->start();
        hasBeenStarted = true;
    }

    //if we are not searching for devices, let's start doing so
    if (!discoveryAgent->isActive())
        discoveryAgent->start();

    //if enough time has passed, let's poll again all the devices
    if (updateCycle == 0)
        poll();

    //some shenanigans here
    if (justPolled){
        //do something with rssi

        justPolled = false;
    }

    updateCycle++;
    if (updateCycle == 300)
        updateCycle = 0;
}

///
///Start the device polling
///
void Bluetooth::start()
{
    hasBeenStarted = true;
    discoveryAgent->start();
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
///Clears the current QList of items and inserts new items to it. WOO
///
void Bluetooth::poll()
{
    discoveredDevices.clear();
    discoveredDevices = discoveryAgent->discoveredDevices();
    justPolled = true;
}

///
///Forces the device to repoll discoveryAgent for new devices
///
void Bluetooth::forcePoll()
{
    discoveredDevices.clear();
    discoveredDevices = discoveryAgent->discoveredDevices();
    justPolled = true;
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
    //there are no devices, return an empty map
    if (discoveredDevices.empty())
        return QMap<QString, qint16>();
    QMap<QString, qint16> map = QMap<QString, qint16>();

    for (size_t i = 0; i < discoveredDevices.size(); i++){
        //let's create the map
    }
}
