#ifndef PIEDRA_H
#define PIEDRA_H

#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QGraphicsScene>

class Piedra : public QGraphicsPixmapItem {
public:
    Piedra();
    void advance(int phase) override;

private:
    qreal velocityY;
};

#endif // PIEDRA_H
