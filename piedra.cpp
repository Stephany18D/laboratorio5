#include "piedra.h"

Piedra::Piedra() {
    setPixmap(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/rock.png"));
    setScale(0.1);

    int startSide = QRandomGenerator::global()->bounded(2);
    if (startSide == 0) {
        setPos(QRandomGenerator::global()->bounded(700), 0);
        velocityY = 3.0;
    } else {
        setPos(QRandomGenerator::global()->bounded(700), 600);
        velocityY = -3.0;
    }
}

void Piedra::advance(int phase) {
    if (phase == 0) return;

    qreal newY = y() + velocityY;
    setPos(x(), newY);

    if (newY <= 0 || newY >= 600) {
        velocityY = -velocityY;
        setPos(x(), newY <= 0 ? 0 : 600);
    }

    if (x() > scene()->width() || y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}
