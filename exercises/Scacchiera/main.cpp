#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "mainwindow.h"

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    MainWindow window( 7, 100 );
    window.show();

    return app.exec();
}
