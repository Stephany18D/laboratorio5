#include "piedra.h"

Piedra::Piedra()
{
    setPixmap(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/rock.png"));
}

void Piedra::advance(int phase)
{
    if (!phase) return;
    setPos(x(), y() + 1);
}
