#include "gamelogic.h"
#include "accelerometer.h"
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
}
