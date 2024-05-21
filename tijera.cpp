#include "tijera.h"

Tijera::Tijera()
{
    setPixmap(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/scissors.png"));
}

void Tijera::advance(int phase)
{
    if (!phase) return;
    setPos(x() + 1, y());
}
