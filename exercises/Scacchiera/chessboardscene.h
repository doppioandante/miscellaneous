#ifndef CHESSBOARDSCENE_H
#define CHESSBOARDSCENE_H

#include <QGraphicsScene>
#include <QColor>

QT_FORWARD_DECLARE_CLASS(QPainter)
QT_FORWARD_DECLARE_CLASS(BombItem)

class ChessboardScene: public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ChessboardScene( uint cells, uint cellSize, QObject *parent = 0);

    uint cells() const
    {
        return m_cells;
    }

    uint cellSize() const
    {
        return m_cellSize;
    }

    const QColor& firstColor() const
    {
        return m_firstColor;
    }

    const QColor& secondColor() const
    {
        return m_secondColor;
    }

    void setFirstColor( const QColor& color )
    {
        m_firstColor = color;
    }

    void setSecondColor( const QColor& color )
    {
        m_secondColor = color;
    }

    void constructBomb();
    void setBombAt( const QPointF& pos );
    void showBomb();
    void hideBomb();

protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    uint m_cells;
    uint m_cellSize;

    QColor m_firstColor;
    QColor m_secondColor;

    BombItem* m_bombItem;
};

#endif // CHESSBOARDSCENE_H
