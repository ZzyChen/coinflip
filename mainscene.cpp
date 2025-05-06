#include "mainscene.h"
#include "ui_mainscene.h"
#include "qpainter.h"
#include "mypushbutton.h"
#include "qtimer.h"
#include <QDebug>
#include <QSoundEffect>
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

    //开始音效
    QSoundEffect *startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    //开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);


    connect(startBtn,&QPushButton::clicked,[=](){
        levelScene = new LevelScene();
        //startBtn->up();
        startBtn->down();
        startSound->play();
        QTimer::singleShot(200,this,[=](){
            this->hide();
            levelScene->setGeometry(this->geometry());
            levelScene->show();
        });
        connect(levelScene,&LevelScene::backToMainScene,[=](){
            levelScene->hide();
            delete levelScene;
            levelScene = nullptr;
            this->show();
        });
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
