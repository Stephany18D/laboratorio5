#include <QGraphicsScene>
#include "tijera.h"

Tijera::Tijera()
{
    setPixmap(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/scissors.png"));
    setScale(0.1);
}

void Tijera::advance(int phase)
{
    if (!phase) return;
    setPos(x() + 1, y());
    if (x() > scene()->width() || y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
     }
}
