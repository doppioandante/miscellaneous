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
#define QC(x) QColor(x)
    m_colors << QC(black) << QC(yellow) << QC(red) << QC(blue)
             << QC(magenta) << QC(green);
#undef QC

    m_chessboard = new ChessboardScene( cells, cellSize, parent );
    assert( m_colors.size() >= 2 );
    m_chessboard->setFirstColor( m_colors[0] );
    m_chessboard->setSecondColor( m_colors[1] );
    setupUI();
    m_view->setScene( m_chessboard );
    m_view->setRenderHints( QPainter::Antialiasing );
}

void MainWindow::setupUI()
{
    setWindowTitle( "Scacchiera" );

    QHBoxLayout* buttonContainer = new QHBoxLayout;
    buttonContainer->setAlignment( Qt::AlignCenter );

    createAndAddButton( tr("cambia colori"), SLOT(on_changeColors_clicked()), buttonContainer, true );
    m_btn_setBomb = createAndAddButton( tr("posiziona bomba"), SLOT(on_setBomb_clicked()), buttonContainer, true );
    m_disabledButtons = new ButtonList;
    (*m_disabledButtons) << createAndAddButton( tr("mostra bomba"), SLOT(on_showBomb_clicked()), buttonContainer, false );
    (*m_disabledButtons) << createAndAddButton( tr("nascondi bomba"), SLOT(on_hideBomb_clicked()), buttonContainer, false );
    m_btn_startMoving = createAndAddButton( tr("spostamento temporizzato"), SLOT(on_startMoving_clicked()), buttonContainer, false );
    (*m_disabledButtons) << m_btn_startMoving;

    m_view = new QGraphicsView( this );
    m_view->setFrameStyle( QFrame::NoFrame );
    uint sceneSize = m_chessboard->cells() * m_chessboard->cellSize();
    m_view->setMaximumSize( sceneSize, sceneSize );

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setAlignment( Qt::AlignCenter );
    vbox->addLayout( buttonContainer );
    vbox->addWidget( m_view );

    setLayout( vbox );
}

inline QPushButton* MainWindow::createAndAddButton( const QString& text, const char* member, QLayout* layout, bool isEnabled )
{
    QPushButton* button = new QPushButton( text, this );
    button->setEnabled( isEnabled );
    connect( button, SIGNAL(clicked()), this, member );
    layout->addWidget( button );
    return button;
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
    connect( m_btn_setBomb, SIGNAL(clicked()), SLOT(on_resetBomb_clicked()) );
}

void MainWindow::on_resetBomb_clicked()
{
    setBombPosition();
}

void MainWindow::on_showBomb_clicked()
{
    m_chessboard->showBomb();
}

void MainWindow::on_hideBomb_clicked()
{
    m_chessboard->hideBomb();
}

void MainWindow::on_startMoving_clicked()
{
    QTimer* timer = new QTimer( this );
    connect( timer, SIGNAL(timeout()), this, SLOT(on_resetBomb_clicked()) );
    timer->start( 20 * 1000 );

    disconnect( m_btn_startMoving, SIGNAL(clicked()), this, SLOT(on_startMoving_clicked()) );
}
