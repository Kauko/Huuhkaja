#include "gamelogic.h"
#include "accelerometer.h"
#include "bluetooth.h"

GameLogic::GameLogic(QObject *parent) : QObject(parent) {
    this->gameLoopTimer = new QTimer(this);
    connect(this->gameLoopTimer, SIGNAL(timeout()),this,SLOT(gameLoop()));
    this->gameLoopTimer->start(100);

}

GameLogic::~GameLogic() {
    disconnect();
    delete this->gameLoopTimer;
}

void GameLogic::gameLoop() {
    qDebug(QString::number(Accelerometer::instance()->getAccelerometerAccelerationDelta()).toAscii());
    QMap<QString, qint16> dm = Bluetooth::instance()->getDeviceMap();

    QMapIterator<QString,qint16> it(dm);
    while(it.hasNext()) {
        it.next();
        QString str = it.key() + ": " + QString::number(it.value());
        qDebug(str.toAscii());
    }
    //what should happen here:
    //we have a loop, during which both the accelometer and bluetooth will be updated
    //and we should also store the relevant values we can get from these classes
    //then: handling them, for example, how much is acceptable movement without forcefully weakening the perceived signal
    //or what the player should see (meaning, how close they seem to be) depending on the rssi of the target - accelometermodifier
    //and stuff like that
    //also, some sort of animationmanager/screenmanager (what should be drawn, where, what kind of screen is displayed, how does the updatecycle work there? Etc)
    //other opinions?
    return;
}
