#ifndef BOMBITEM_H
#define BOMBITEM_H

#include <QGraphicsPixmapItem>

class BombItem: public QGraphicsPixmapItem
{
public:
    explicit BombItem(qreal width, qreal height);
};

#endif // BOMBITEM_H
