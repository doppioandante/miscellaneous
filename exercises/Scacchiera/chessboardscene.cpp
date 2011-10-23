#include "chessboardscene.h"
#include "bombitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <cmath>

ChessboardScene::ChessboardScene(uint cells, uint cellSize, QObject *parent):
    QGraphicsScene( 0, 0, cellSize*cells, cellSize*cells ),
    m_cells( cells ),
    m_cellSize( cellSize ),
    m_bombItem( 0 )
{
}

void ChessboardScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->save();

    painter->fillRect( rect, firstColor() );

    qreal cellWidth = width()/cells();
    qreal cellHeight = height()/cells();

    for( qreal x = 0; x < width(); x += cellWidth )
    {
        for( qreal y = std::fmod( x, cellHeight*2 ); y < height(); y += cellHeight*2 )
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
