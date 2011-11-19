#include "gamelogic.h"
#include "accelerometer.h"
#include "bluetooth.h"

GameLogic::GameLogic(QObject *parent) : QObject(parent) {
    this->gameLoopTimer = new QTimer(this);
    connect(this->gameLoopTimer, SIGNAL(timeout()),this,SLOT(gameLoop()));
    this->gameLoopTimer->start(100);

    this->testLabel = NULL;
    this->testLabel2 = NULL;
}

GameLogic::~GameLogic() {
    disconnect();
    delete this->gameLoopTimer;
}

void GameLogic::gameLoop() {
    QString accel = QString::number(Accelerometer::instance()->getAccelerometerAccelerationDelta());
    //qDebug(accel.toAscii());
    QMap<QString, qint16> dm = Bluetooth::instance()->getDeviceMap();

    if(dm.count() == 0 && this->testLabel != NULL) this->testLabel->setText(":D");
    else if(this->testLabel != NULL) this->testLabel->setText(":O");

    QString superStr = "";
    QMapIterator<QString,qint16> it(dm);
    superStr += "accel: "+accel+"\n";

    bool foundok=false;
    while(it.hasNext()) {
        it.next();
        QString str = it.key() + ": " + QString::number(it.value());
        if(it.value()>-65) foundok=true;
        superStr += str + "\n";
        //qDebug(str.toAscii());
    }

    if(foundok==true && this->testLabel != NULL) this->testLabel->setText("^_^");

    if(this->testLabel2 != NULL) this->testLabel2->setText(superStr);
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

void GameLogic::initMainWindowItems(QMainWindow *mw) {
    this->testLabel = new QLabel("sup!",mw->centralWidget());
    this->testLabel->setFont(QFont("Fixed",48,1,false));
    //this->testLabel->setMargin(10);
    this->testLabel->setFixedSize(360,640);
    this->testLabel->setVisible(true);
    this->testLabel->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);

    this->testLabel2 = new QLabel("sup!",mw->centralWidget());
    this->testLabel2->setMargin(60);
    this->testLabel2->setFixedSize(1000,400);
    this->testLabel2->setVisible(true);
    this->testLabel2->setAlignment(Qt::AlignTop|Qt::AlignLeft);
}
