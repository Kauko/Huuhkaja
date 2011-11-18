#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include "accelerometer.h"
#include "bluetooth.h"

Q_DECL_EXPORT int main(int argc, char *argv[]) {
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    Accelerometer::init(0);
    Bluetooth::init(0);

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait);
    viewer->setMainQmlFile(QLatin1String("qml/ProjectHuuhkaja/main.qml"));
    viewer->showExpanded();

    int status = app->exec();

    Accelerometer::destroy();
    Bluetooth::destroy();

    return status;
}
