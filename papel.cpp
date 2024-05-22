#include <QGraphicsScene>
#include "papel.h"

Papel::Papel()
{
    setPixmap(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/paper.png"));
    setScale(0.1);
}

void Papel::advance(int phase)
{
    if (!phase) return;
    setPos(x() + 1, y() + 1);
    if (x() > scene()->width() || y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}
