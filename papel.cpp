#include <QGraphicsScene>
#include "papel.h"

Papel::Papel()
{
    setPixmap(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/paper.png"));
    setScale(0.1);
    int startCorner = QRandomGenerator::global()->bounded(4);
    switch (startCorner) {
        case 0:
            setPos(0, 0);
            velocityX = 3.0;
            velocityY = 3.0;
            break;
        case 1:
            setPos(700, 0);
            velocityX = -3.0;
            velocityY = 3.0;
            break;
        case 2:
            setPos(0, 600);
            velocityX = 3.0;
            velocityY = -3.0;
            break;
        case 3:
            setPos(700, 600);
            velocityX = -3.0;
            velocityY = -3.0;
            break;
    }

}

void Papel::advance(int phase) {
    if (phase == 0) return;

    qreal newX = x() + velocityX;
    qreal newY = y() + velocityY;
    setPos(newX, newY);

    if (newX <= 0 || newX >= 700) {
        velocityX = -velocityX;
        setPos(newX <= 0 ? 0 : 700, newY);
    }
    if (newY <= 0 || newY >= 600) {
        velocityY = -velocityY;
        setPos(newX, newY <= 0 ? 0 : 600);
    }

    if (newX > scene()->width() || newY > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}
