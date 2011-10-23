#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QColor>
#include <QPoint>

QT_FORWARD_DECLARE_CLASS(QLayout)
QT_FORWARD_DECLARE_CLASS(QGraphicsView)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(ChessboardScene)

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(uint cells, uint cellSize, QWidget *parent = 0);

private:
    void setupUI();
    QPushButton* createAndAddButton( const QString& text, const char* member, QLayout* layout, bool isEnabled );

    void setBombPosition();

signals:

public slots:
    void on_changeColors_clicked();
    void on_setBomb_clicked();
    void on_resetBomb_clicked();
    void on_showBomb_clicked();
    void on_hideBomb_clicked();
    void on_startMoving_clicked();

private:
    typedef QList<QColor> ColorList;
    ColorList m_colors;

    QGraphicsView* m_view;
    ChessboardScene* m_chessboard;

    QPushButton* m_btn_setBomb;
    QPushButton* m_btn_startMoving;
    typedef QList<QPushButton*> ButtonList;
    ButtonList* m_disabledButtons;
};

#endif // MAINWINDOW_H
