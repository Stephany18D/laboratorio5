#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "papel.h"
#include "piedra.h"
#include "tijera.h"
#include "jugador.h"
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QtGlobal>
#include <QRandomGenerator>

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
    scene = new QGraphicsScene(0, 0, 1000, 800, this);
    ui->graphicsView->setScene(scene);


    spawnTimer = new QTimer(this);
    moveTimer = new QTimer(this);
    countdownTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &MainWindow::spawnObjects);
    connect(moveTimer, &QTimer::timeout, this, &MainWindow::moveObjects);
    connect(countdownTimer, &QTimer::timeout, this, &MainWindow::updateCountdown);

    QMessageBox::information(this, "Bienvenido al Juego",
            "¡Bienvenido al juego de Piedra, Papel y Tijera!\n\n"
            "Instrucciones:\n"
            "- Haz clic en los botones 'Piedra', 'Tijera' o 'Papel' para agregarlos al juego y dale en 'Iniciar'.\n"
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addScissorsButton_clicked()
{
    if (scissorsCount < 5) {
        Tijera *scissors = new Tijera();
        qreal xPos = QRandomGenerator::global()->bounded(2) == 0 ? 0 : scene->width() - scissors->boundingRect().width();
        qreal yPos = QRandomGenerator::global()->bounded(scene->height());
        scissors->setPos(xPos, yPos);
        scene->addItem(scissors);
        scissorsCount++;
    }
}

void MainWindow::on_addRockButton_clicked()
{
    if (rockCount < 5) {
        Piedra *rock = new Piedra();
        qreal xPos = QRandomGenerator::global()->bounded(scene->width());
        qreal yPos = QRandomGenerator::global()->bounded(2) == 0 ? 0 : scene->height() - rock->boundingRect().height();
        rock->setPos(xPos, yPos);
        scene->addItem(rock);
        rockCount++;
    }
}

void MainWindow::on_addPaperButton_clicked()
{
    if (paperCount < 5) {
        Papel *paper = new Papel();
        int corner = QRandomGenerator::global()->bounded(4);
        qreal xPos = 0;
        qreal yPos = 0;
        switch(corner) {
            case 0:
                xPos = 0;
                yPos = 0;
                break;
            case 1:
                xPos = scene->width() - paper->boundingRect().width();
                yPos = 0;
                break;
            case 2:
                xPos = 0;
                yPos = scene->height() - paper->boundingRect().height();
                break;
            case 3:
                xPos = scene->width() - paper->boundingRect().width();
                yPos = scene->height() - paper->boundingRect().height();
                break;
        }
        paper->setPos(xPos, yPos);
        scene->addItem(paper);
        paperCount++;
    }
}

void MainWindow::on_addPlayerButton_clicked()
{
    if (!isPlayerActive) {
        playerIndicator = new Jugador();
        playerIndicator->setPos(scene->width() / 2, scene->height() / 2);
        scene->addItem(playerIndicator);
        isPlayerActive = true;
        countdownTimer->start(1000);
        spawnTimer->start(10000);
        moveTimer->start(100);
        ui->addScissorsButton->setEnabled(false);
        ui->addRockButton->setEnabled(false);
        ui->addPaperButton->setEnabled(false);

        QMessageBox::information(this, "Mensaje", "Espera diez segundos para comenzar.");

        QMessageBox::information(this, "Mensaje", "Utiliza las teclas W, A, S, D para moverte, y presiona la barra espaciadora para destruir los objetos.\n"
                                 "- Tu objetivo es recolectar los objetos correspondientes antes de que se acabe el tiempo.\n"
                                 "- ¡Diviértete y buena suerte!");

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
    auto items = scene->items();
    for (auto it = items.cbegin(); it != items.cend(); ++it) {
        if (auto *obj = dynamic_cast<QGraphicsPixmapItem*>(*it)) {
            obj->advance(1);
        }
    }
    checkCollisions();
}

void MainWindow::checkCollisions()
{
    const auto items = scene->items();
    QList<QGraphicsItem*> itemsToRemove;

    for (auto it1 = items.cbegin(); it1 != items.cend(); ++it1) {
        for (auto it2 = items.cbegin(); it2 != items.cend(); ++it2) {
            if (*it1 == *it2 || itemsToRemove.contains(*it1) || itemsToRemove.contains(*it2)) continue;

            if ((*it1)->collidesWithItem(*it2)) {
                if (auto *scissors = dynamic_cast<Tijera*>(*it1)) {
                    if (auto *paper = dynamic_cast<Papel*>(*it2)) {
                        itemsToRemove.append(paper);
                        paperCount--;
                        scissorsCount++;
                        ui->scissorsScoreLabel->setText(QString::number(scissorsCount));
                    } else if (auto *rock = dynamic_cast<Piedra*>(*it2)) {
                        itemsToRemove.append(scissors);
                        scissorsCount--;
                        rockCount++;
                        ui->rockScoreLabel->setText(QString::number(rockCount));
                    }
                } else if (auto *paper = dynamic_cast<Papel*>(*it1)) {
                    if (auto *rock = dynamic_cast<Piedra*>(*it2)) {
                        itemsToRemove.append(rock);
                        rockCount--;
                        paperCount++;
                        ui->paperScoreLabel->setText(QString::number(paperCount));
                    }
                } else if (auto *rock = dynamic_cast<Piedra*>(*it1)) {
                    if (auto *scissors = dynamic_cast<Tijera*>(*it2)) {
                        itemsToRemove.append(scissors);
                        scissorsCount--;
                        rockCount++;
                        ui->rockScoreLabel->setText(QString::number(rockCount));
                    }
                }
            }
        }
    }

    for (auto item : itemsToRemove) {
        scene->removeItem(item);
        delete item;
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


