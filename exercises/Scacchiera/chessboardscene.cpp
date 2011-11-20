#include "chessboardscene.h"
#include "bombitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <cmath>

ChessboardScene::ChessboardScene(uint cells, uint cellSize, QObject *parent):
    QGraphicsScene( 0, 0, cellSize*cells, cellSize*cells, parent ),
    m_cells( cells ),
    m_cellSize( cellSize ),
    m_bombItem( 0 )
{
}

void ChessboardScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    class BitFlipper
    {
    public:
        BitFlipper( bool defaultValue ):
            m_value( !defaultValue )
        {}

        bool operator () ( )
        {
            m_value = !m_value;
            return m_value;
        }

    private:
        bool m_value;
    };

    painter->save();

    painter->fillRect( rect, firstColor() );

    qreal cellWidth = width()/cells();
    qreal cellHeight = height()/cells();

    BitFlipper flipBit( false );
    for( qreal x = 0; x < width(); x += cellWidth )
    {
        for( qreal y = cellHeight * flipBit(); y < height(); y += cellHeight*2 )
        {
            painter->fillRect( x, y, cellWidth, cellHeight, secondColor() );
        }
    }

    painter->restore();
}

void ChessboardScene::constructBomb()
{
    m_bombItem = new BombItem( cellSize(), cellSize() );
    m_bombItem->hide();
    addItem( m_bombItem );
}

void ChessboardScene::setBombAt(const QPointF &pos)
{
    m_bombItem->setPos( pos );
}

void ChessboardScene::showBomb()
{
    m_bombItem->show();
}

void ChessboardScene::hideBomb()
{
    m_bombItem->hide();
}

void ChessboardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if( m_bombItem != 0 )
    {
        QPointF pos = event->scenePos();

        if( m_bombItem->sceneBoundingRect().contains(pos) )
        {
            QMessageBox message;
            message.setText("Bomba trovata");
            message.exec();
        }
    }
}
