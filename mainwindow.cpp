#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "papel.h"
#include "piedra.h"
#include "tijera.h"
#include <QGraphicsPixmapItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scissorsCount(0)
    , rockCount(0)
    , paperCount(0)
    , playerScore(0)
    , timeRemaining(300)
    , isPlayerActive(false)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    spawnTimer = new QTimer(this);
    moveTimer = new QTimer(this);
    countdownTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::spawnObjects);
    connect(moveTimer, &QTimer::timeout, this, &MainWindow::moveObjects);
    connect(countdownTimer, &QTimer::timeout, this, &MainWindow::updateCountdown);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addScissorsButton_clicked()
{
    if (scissorsCount < 5) {
        Tijera *scissors = new Tijera();
        scene->addItem(scissors);
        scissorsCount++;
    }
}

void MainWindow::on_addRockButton_clicked()
{
    if (rockCount < 5) {
        Piedra *rock = new Piedra();
        scene->addItem(rock);
        rockCount++;
    }
}

void MainWindow::on_addPaperButton_clicked()
{
    if (paperCount < 5) {
        Papel *paper = new Papel();
        scene->addItem(paper);
        paperCount++;
    }
}

void MainWindow::on_addPlayerButton_clicked()
{
    if (!isPlayerActive) {
        playerIndicator = new QGraphicsPixmapItem(QPixmap("E:/Escritorio/Laboratorio/laboratorio5/StephanyTangarifePalacio-Laboratorio5/images/player.png"));
        playerIndicator->setPos(scene->width() / 2, scene->height() / 2);
        scene->addItem(playerIndicator);
        isPlayerActive = true;
        countdownTimer->start(1000);
        spawnTimer->start(10000);
        moveTimer->start(100);
        ui->addScissorsButton->setEnabled(false);
        ui->addRockButton->setEnabled(false);
        ui->addPaperButton->setEnabled(false);
    }
}

void MainWindow::on_startButton_clicked()
{
    spawnTimer->start(10000);
    moveTimer->start(100);
}

void MainWindow::spawnObjects()
{
    if (scissorsCount < 5) {
        on_addScissorsButton_clicked();
    }
    if (rockCount < 5) {
        on_addRockButton_clicked();
    }
    if (paperCount < 5) {
        on_addPaperButton_clicked();
    }
}

void MainWindow::moveObjects()
{
    for (auto item : scene->items()) {
        if (auto *obj = dynamic_cast<QGraphicsPixmapItem*>(item)) {
            obj->advance(1);
        }
    }
    checkCollisions();
}

void MainWindow::checkCollisions()
{
    QList<QGraphicsItem*> items = scene->items();
    for (auto item1 : items) {
        for (auto item2 : items) {
            if (item1 == item2) continue;

            if (item1->collidesWithItem(item2)) {
                // Implement collision resolution according to the rules
                // Example for scissors and paper:
                if (dynamic_cast<Tijera*>(item1) && dynamic_cast<Papel*>(item2)) {
                    scene->removeItem(item2);
                    delete item2;
                    paperCount--;
                    scissorsCount++; // Increment score for scissors
                } else if (dynamic_cast<Papel*>(item1) && dynamic_cast<Piedra*>(item2)) {
                    scene->removeItem(item2);
                    delete item2;
                    rockCount--;
                    paperCount++; // Increment score for paper
                } else if (dynamic_cast<Piedra*>(item1) && dynamic_cast<Tijera*>(item2)) {
                    scene->removeItem(item2);
                    delete item2;
                    scissorsCount--;
                    rockCount++; // Increment score for rock
                }
            }
        }
    }
}

void MainWindow::updateCountdown()
{
    if (timeRemaining > 0) {
        timeRemaining--;
        ui->timeLabel->setText(QString("Tiempo: %1").arg(timeRemaining));
    } else {
        countdownTimer->stop();
        moveTimer->stop();
        spawnTimer->stop();
        QMessageBox::information(this, "Fin de juego", "Se acabó el tiempo!");
        ui->addScissorsButton->setEnabled(true);
        ui->addRockButton->setEnabled(true);
        ui->addPaperButton->setEnabled(true);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!isPlayerActive) return;

    int step = 10;
    switch (event->key()) {
    case Qt::Key_W:
        playerIndicator->setPos(playerIndicator->x(), playerIndicator->y() - step);
        break;
    case Qt::Key_S:
        playerIndicator->setPos(playerIndicator->x(), playerIndicator->y() + step);
        break;
    case Qt::Key_A:
        playerIndicator->setPos(playerIndicator->x() - step, playerIndicator->y());
        break;
    case Qt::Key_D:
        playerIndicator->setPos(playerIndicator->x() + step, playerIndicator->y());
        break;
    case Qt::Key_Space:
        // Check for collision with player indicator and remove the item
        for (auto item : scene->items(playerIndicator->pos())) {
            if (item != playerIndicator) {
                scene->removeItem(item);
                delete item;
                playerScore++;
                ui->playerScoreLabel->setText(QString("Puntaje: %1").arg(playerScore));
                break;
            }
        }
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}
