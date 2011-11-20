#include "mainwindow.h"
#include "chessboardscene.h"
#include "bombitem.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTime>
#include <QTimer>
#include <cassert>

MainWindow::MainWindow(uint cells, uint cellSize, QWidget *parent) :
    QWidget(parent)
{
    using namespace Qt;

    setupUI();

#define QC(x) QColor(x)
    m_colors << QC(black) << QC(yellow) << QC(red) << QC(blue)
             << QC(magenta) << QC(green);
#undef QC

    m_chessboard = new ChessboardScene( cells, cellSize, parent );
    assert( m_colors.size() >= 2 );
    m_chessboard->setFirstColor( m_colors[0] );
    m_chessboard->setSecondColor( m_colors[1] );

    uint sceneSize = m_chessboard->cells() * m_chessboard->cellSize();
    m_ui.graphicsView->setMaximumSize( sceneSize, sceneSize );
    m_ui.graphicsView->setScene( m_chessboard );
    m_ui.graphicsView->setRenderHints( QPainter::Antialiasing );
}

void MainWindow::setupUI()
{
    m_ui.setupUi( this );
    setWindowTitle( "Scacchiera" );

    QHBoxLayout* buttonContainer = new QHBoxLayout;
    buttonContainer->setAlignment( Qt::AlignCenter );

    m_btn_setBomb = m_ui.setBomb;
    m_btn_startMoving = m_ui.startMoving;

    m_disabledButtons = new ButtonList;

    (*m_disabledButtons) << m_ui.bombToggled;
    (*m_disabledButtons) << m_ui.startMoving;

    m_ui.horizontalLayout->setAlignment( Qt::AlignCenter );
    m_ui.verticalLayout->setAlignment( Qt::AlignCenter );
}

void MainWindow::setBombPosition()
{
    qsrand(QTime::currentTime().msec());

    int x = qrand() % m_chessboard->cells();
    x *= m_chessboard->cellSize();

    int y = qrand() % m_chessboard->cells();
    y *= m_chessboard->cellSize();

    m_chessboard->setBombAt( QPointF( x, y ) );
}

void MainWindow::on_changeColors_clicked()
{
    qsrand(QTime::currentTime().msec());

    uint firstColor = qrand() % m_colors.size();
    uint secondColor = qrand() % m_colors.size();

    while( firstColor == secondColor )
    {
        secondColor = qrand() % m_colors.size();
    }

    m_chessboard->setFirstColor( m_colors[firstColor] );
    m_chessboard->setSecondColor( m_colors[secondColor] );
    m_chessboard->update();
}

void MainWindow::on_setBomb_clicked()
{
    m_chessboard->constructBomb();
    setBombPosition();

    foreach( QPushButton* button, *m_disabledButtons )
    {
        button->setEnabled( true );
    }

    delete m_disabledButtons;

    disconnect( m_btn_setBomb, SIGNAL(clicked()), this, SLOT(on_setBomb_clicked()) );
    connect( m_btn_setBomb, SIGNAL(clicked()), SLOT(resetBomb_clicked()) );
}

void MainWindow::resetBomb_clicked()
{
    setBombPosition();
}

void MainWindow::on_bombToggled_clicked(bool checked)
{
    if( checked )
    {
        m_chessboard->showBomb();
    }
    else
    {
        m_chessboard->hideBomb();
    }
}


void MainWindow::on_startMoving_clicked()
{
    QTimer* timer = new QTimer( this );
    connect( timer, SIGNAL(timeout()), this, SLOT(resetBomb_clicked()) );
    timer->start( 20 * 1000 );

    disconnect( m_btn_startMoving, SIGNAL(clicked()), this, SLOT(on_startMoving_clicked()) );
}

