#ifndef TIJERA_H
#define TIJERA_H

#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QGraphicsScene>

class Tijera : public QGraphicsPixmapItem {
public:
    Tijera();
    void advance(int phase) override;

private:
    int velocityX;
};

#endif // TIJERA_H
