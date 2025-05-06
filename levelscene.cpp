#include "levelscene.h"
#include "mypushbutton.h"

#include <QPainter>
#include <QMenuBar>
#include <QTimer>
#include <QLabel>
#include <QSoundEffect>

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
    this->setWindowTitle(QString("关卡选择"));
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //关卡按钮点击音效
    QSoundEffect *backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&QPushButton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(200,this,[=](){
            emit backToMainScene();
        });

    });
    //关卡按钮点击音效
    QSoundEffect *clickLevelSound = new QSoundEffect(this);
    clickLevelSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    //关卡按钮
    for (int i = 0; i < 20; i++) {
        MyPushButton *levelBtn = new MyPushButton(":/res/LevelIcon.png");
        levelBtn->setParent(this);
        levelBtn->move(25+i%4*70,130+i/4*70);
        QLabel *label = new QLabel;
        label->setParent(levelBtn);
        label->setFixedSize(levelBtn->width(),levelBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignCenter);

        connect(levelBtn,&MyPushButton::clicked,[=](){
            clickLevelSound->play();
            QTimer::singleShot(200,[=](){
                this->hide();
                p = new PlayScene(i+1);
                p->setGeometry(this->geometry());
                p->show();

                connect(p,&PlayScene::backToLevelScene,[=](){
                    this->show();
                    p->close();
                    delete p;
                    p = nullptr;
                });

            });
        });

    }
    QSoundEffect *levelSound = new QSoundEffect(this);
    levelSound->setSource(QUrl::fromLocalFile(":/res/myDouDZ.wav"));
    levelSound->play();
    levelSound->setLoopCount(QSoundEffect::Infinite);
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
