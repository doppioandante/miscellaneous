#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "mainwindow.h"

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    MainWindow window( 15, 50 );
    window.show();

    return app.exec();
}
