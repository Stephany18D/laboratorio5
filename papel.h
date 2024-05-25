#ifndef PAPEL_H
#define PAPEL_H

#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QGraphicsScene>

class Papel : public QGraphicsPixmapItem {
public:
    Papel();
    void advance(int phase) override;

private:
    qreal velocityX;
    qreal velocityY;
};

#endif // PAPEL_H
