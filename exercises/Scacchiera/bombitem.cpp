#include "bombitem.h"

BombItem::BombItem( qreal width, qreal height ):
    QGraphicsPixmapItem()
{
    setAcceptHoverEvents(true);
    QImage image(":/images/bomb.png");
    setPixmap( QPixmap::fromImage(image).scaled( width, height ) );
}
