#include "papel.h"

Papel::Papel()
{
    setPixmap(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/paper.png"));
}

void Papel::advance(int phase)
{
    if (!phase) return;
    setPos(x() + 1, y() + 1);
}
