#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QTimer>

class GameLogic : public QObject
{
    Q_OBJECT
    QTimer* gameLoopTimer;
public:
    explicit GameLogic(QObject *parent = 0);
    ~GameLogic();
signals:

public slots:
    void gameLoop();
};

#endif // GAMELOGIC_H
