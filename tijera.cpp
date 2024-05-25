#include "tijera.h"

Tijera::Tijera() {
    setPixmap(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/scissors.png"));
    setScale(0.1);

    int randomSide = QRandomGenerator::global()->bounded(2);
    if (randomSide == 0) {
        setPos(0, QRandomGenerator::global()->bounded(600));
        velocityX = 4.0;
    } else {
        setPos(800 - boundingRect().width(), QRandomGenerator::global()->bounded(600));
        velocityX = -4.0;
    }
}

void Tijera::advance(int phase) {
    if (phase == 0) return;
    qreal newX = x() + velocityX;
    setPos(newX, y());


    if (newX <= 0 || newX >= 600) {
        velocityX = -velocityX;
        setPos(newX <= 0 ? 0 : 600, y());
    }

    if (x() > scene()->width() || y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}

