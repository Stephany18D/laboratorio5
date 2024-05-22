#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include "jugador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_addScissorsButton_clicked();
    void on_addRockButton_clicked();
    void on_addPaperButton_clicked();
    void on_addPlayerButton_clicked();
    void on_startButton_clicked();
    void spawnObjects();
    void moveObjects();
    void checkCollisions();
    void updateCountdown();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *spawnTimer;
    QTimer *moveTimer;
    QTimer *countdownTimer;
    int scissorsCount;
    int rockCount;
    int paperCount;
    int playerScore;
    int timeRemaining;
    bool isPlayerActive;
    Jugador *playerIndicator;
};

#endif // MAINWINDOW_H




