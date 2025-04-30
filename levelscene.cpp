#include "levelscene.h"
#include "mypushbutton.h"
#include "QPainter"
#include "QMenuBar"
#include "QTimer"
#include <QTimer>
LevelScene::LevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    QMenuBar *menu = menuBar();
    setMenuBar(menu);
    QMenu *startMenu = menu->addMenu("开始");
    QAction *quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    this->setFixedSize(320,588);
    this->setWindowTitle(QString("翻金币"));
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&QPushButton::clicked,[=](){
        QTimer::singleShot(200,this,[=](){
            emit backToMainScene();
        });

    });

    //关卡按钮
    for (int i = 0; i < 20; i++) {
        MyPushButton *levelBtn = new MyPushButton(":/res/LevelIcon.png");
        levelBtn->setParent(this);
        levelBtn->move(i%4*50,i/40*50);
    }
}

void LevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,this->menuBar()->height(),this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap(0,this->menuBar()->height(),pix);
}
