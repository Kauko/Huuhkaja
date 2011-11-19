#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QTimer>

#include <QMainWindow>
#include <QLabel>

class GameLogic : public QObject
{
    Q_OBJECT
    QTimer* gameLoopTimer;

    QLabel* testLabel;
public:
    explicit GameLogic(QObject *parent = 0);
    ~GameLogic();

    void initMainWindowItems(QMainWindow* mw);
signals:

public slots:
    void gameLoop();
};

#endif // GAMELOGIC_H
