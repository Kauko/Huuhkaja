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
        discoveryAgent->start();
        hasBeenStarted = true;
    }

    if (!discoveryAgent->isActive())
        discoveryAgent->start();

    //first, check if enough time has passed since last polling available btooth devices
        //if enough, poll again
        //add new devices to list and remove devices which were not found
    //then, if we polled again, we check the signal strength for all devices we discovered
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
