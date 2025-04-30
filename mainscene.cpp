#include "mainscene.h"
#include "ui_mainscene.h"
#include "qpainter.h"
#include "mypushbutton.h"
#include "qtimer.h"
#include <QDebug>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    connect(ui->quitAction,&QAction::triggered,[=](){
        this->close();
    });
    this->setFixedSize(320,588);
    this->setWindowTitle(QString("翻金币"));
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    levelScene = new LevelScene(this);
    connect(startBtn,&QPushButton::clicked,[=](){
        //startBtn->up();
        startBtn->down();
        QTimer::singleShot(200,this,[=](){
            this->hide();
            levelScene->show();
        });
    });
    connect(levelScene,&LevelScene::backToMainScene,[=](){
            this->show();
            levelScene->hide();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,this->menuBar()->height(),this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(0,this->menuBar()->height(),pix);
}
