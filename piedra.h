#ifndef PIEDRA_H
#define PIEDRA_H

#include <QGraphicsPixmapItem>

class Piedra : public QGraphicsPixmapItem
{
public:
    Piedra();
    void advance(int phase) override;
};

#endif // PIEDRA_H
