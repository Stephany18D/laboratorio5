#ifndef TIJERA_H
#define TIJERA_H

#include <QGraphicsPixmapItem>

class Tijera : public QGraphicsPixmapItem
{
public:
    Tijera();
    void advance(int phase) override;
};

#endif // TIJERA_H
