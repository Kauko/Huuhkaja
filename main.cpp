 #include "mainwindow.h"

#include <QtGui/QApplication>
#include <QThread>
#include "accelerometer.h"
#include "bluetooth.h"
#include "gamelogic.h"

#include <QSystemScreenSaver>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QtMobility::QSystemScreenSaver *sss=new QtMobility::QSystemScreenSaver (&app);
    sss->setScreenSaverInhibited(true);

    Accelerometer::init(0);
    Bluetooth::init(0);
    Bluetooth::instance()->start();

    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    mainWindow.showExpanded();

    GameLogic* gameLogic = new GameLogic();

    //HAX
    gameLogic->initMainWindowItems(&mainWindow);

    int returnCode = app.exec();

    delete gameLogic;
    Bluetooth::instance()->stop();
    Accelerometer::destroy();
    Bluetooth::destroy();
    sss->setScreenSaverInhibited(false);
    return returnCode;
}
