#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ui_mainwindow.h>
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
    void setBombPosition();

signals:

public slots:
    void on_changeColors_clicked();
    void on_setBomb_clicked();
    void on_bombToggled_clicked(bool checked);
    void on_startMoving_clicked();
    void resetBomb_clicked();

private:
    typedef QList<QColor> ColorList;
    ColorList m_colors;

    Ui::MainWindow m_ui;

    ChessboardScene* m_chessboard;

    QPushButton* m_btn_setBomb;
    QPushButton* m_btn_startMoving;
    typedef QList<QPushButton*> ButtonList;
    ButtonList* m_disabledButtons;
};

#endif // MAINWINDOW_H
