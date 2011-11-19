 #include "mainwindow.h"

#include <QtGui/QApplication>
#include <QThread>
#include "accelerometer.h"
#include "bluetooth.h"
#include "gamelogic.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Accelerometer::init(0);
    Bluetooth::init(0);

    GameLogic* gameLogic = new GameLogic();

    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationLockPortrait);
    mainWindow.showExpanded();

    int returnCode = app.exec();

    delete gameLogic;
    Accelerometer::destroy();
    Bluetooth::destroy();

    return returnCode;
}
