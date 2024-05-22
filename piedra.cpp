#include <QGraphicsScene>
#include "piedra.h"

Piedra::Piedra()
{
    setPixmap(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/rock.png"));
    setScale(0.1);
}

void Piedra::advance(int phase)
{
    if (!phase) return;
    setPos(x(), y() + 1);
    if (x() > scene()->width() || y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}
