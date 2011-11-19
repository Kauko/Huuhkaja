#include "bluetooth.h"

Bluetooth::Bluetooth(QObject *parent) : QObject(parent) {
    qDebug("Bluetooth Construct");
}

Bluetooth::~Bluetooth() {
    qDebug("Bluetooth Destruct");
}
