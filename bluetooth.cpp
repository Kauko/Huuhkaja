
#include "bluetooth.h"

Bluetooth::Bluetooth(QObject *parent) : QObject(parent) {
    //initialize objects and values
    qDebug("Bluetooth Construct");
    btoothLocDevice = new QtMobility::QBluetoothLocalDevice(this);
    btoothAddress = new QtMobility::QBluetoothAddress::QBluetoothAddress(btoothLocDevice->address());
    discoveryAgent = new QtMobility::QBluetoothDeviceDiscoveryAgent(this);
    discoveredDevices.clear();  //to ensure that the list is clear, damnit

}

Bluetooth::~Bluetooth() {
    qDebug("Bluetooth Destruct");
}

void Bluetooth::update()
{
    //first, check if enough time has passed since last polling available btooth devices
        //if enough, poll again
        //add new devices to list and remove devices which were not found
    //then, if we polled again, we check the signal strength for all devices we discovered

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
void Bluetooth::stop(){
    discoveryAgent->stop();
}
