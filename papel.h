#ifndef PAPEL_H
#define PAPEL_H

#include <QGraphicsPixmapItem>

class Papel : public QGraphicsPixmapItem
{
public:
    Papel();
    void advance(int phase) override;
};

#endif // PAPEL_H
