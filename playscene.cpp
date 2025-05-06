#include "playscene.h"
#include "leveldata.h"
#include "mypushbutton.h"
#include "coinbutton.h"
#include <QMenuBar>
#include <QTimer>
#include <QPainter>
#include <QLabel>
#include <QFont>
#include <QPropertyAnimation>
#include <QRect>
#include <QSoundEffect>
PlayScene::PlayScene(int levelNum)
{
    QElapsedTimer timer;
    timer.start();
    // ...初始化代码...
    qDebug() << "PlayScene 初始化耗时：" << timer.elapsed() << "ms";
    levelIndex = levelNum;
    //窗口及菜单栏
    QMenuBar *menu = menuBar();
    setMenuBar(menu);
    QMenu *startMenu = menu->addMenu("开始");
    QAction *quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    this->setFixedSize(320,588);
    this->setWindowTitle(QString("第%1关").arg(levelIndex));
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //左下角关卡等级标签
    QFont f;
    f.setFamily("Arial Black");
    f.setPixelSize(24);
    QLabel *levelLabel = new QLabel;
    levelLabel->setParent(this);
    levelLabel->setText("Level: " + QString::number(levelIndex));
    levelLabel->move(10,333);
    levelLabel->setFont(f);
    //鼠标穿透
    //levelLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    //返回音效
    QSoundEffect *backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&QPushButton::clicked,[=](){
        gameTimer->stop();
        backSound->play();
        QTimer::singleShot(200,this,[=](){
            emit backToLevelScene();
        });
    });

    //存储关卡数据
    LevelData ld;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            gameArray[i][j] = ld.data[levelIndex][i][j];
        }
    }

    //点击金币音效
    QSoundEffect *clickCoinSound = new QSoundEffect(this);
    clickCoinSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));

    //金币图标按钮
    QPixmap bgPix(":/res/BoardNode.png");
    bgPix = bgPix.scaled(bgPix.width() * 1.4, bgPix.height() * 1.4, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            QLabel *bg = new QLabel;
            bg->setGeometry(0,0,bgPix.width(),bgPix.height());
            bg->setPixmap(bgPix);
            bg->setParent(this);
            bg->move(20+i*bgPix.width(),180+j*bgPix.height());
            QString str;
            if(gameArray[i][j]==1)
            {
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            CoinButton *coin = new CoinButton(str);
            coin->setParent(this);
            coin->move(23+i*bgPix.width(),186+j*bgPix.height());
            coin->x = i;
            coin->y = j;
            coin->flag = gameArray[i][j];
            coinBtn[i][j] = coin;
            connect(coin,&QPushButton::clicked,[=](){
                if(coin->isChange)
                {
                    return;   //禁用按钮连击
                }
                coin->changeCoin();
                clickCoinSound->play();
                coin->isChange = true;
                QTimer::singleShot(500,[=](){
                    coin->isChange = false;
                });
                gameArray[i][j] = gameArray[i][j] == 0 ? 1:0;
                //翻转周围金币
                auto flipNeighbor = [=](int x,int y){
                    if(x>=0 && x<=3 && y>=0 && y<=3)
                    {
                        coinBtn[x][y]->changeCoin();
                        coinBtn[x][y]->isChange = true;
                        gameArray[x][y] = gameArray[x][y] == 0 ? 1:0;
                        QTimer::singleShot(500,[=](){
                            coinBtn[coin->x][coin->y]->isChange = false;
                        });
                    }
                };
                QTimer::singleShot(20,[=](){
                    flipNeighbor(i+1,j);
                    flipNeighbor(i-1,j);
                    flipNeighbor(i,j+1);
                    flipNeighbor(i,j-1);
                });
            });
        }
    }

    //计时器
    int time = 0;
    QLabel *timeLabel = new QLabel(this);
    timeLabel->setFixedSize(100,50);
    timeLabel->move(10,500);
    timeLabel->setFont(f);
    gameTimer = new QTimer;
    gameTimer->start(1000);
    connect(gameTimer,&QTimer::timeout,[=]()mutable{
        time++;
        int min = time/60;
        int sec = time%60;
        QString timeText = QString("%1 : %2").arg(min, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0')) ;
        timeLabel->setText(timeText);
        qDebug()<<timeText;
    });

    //胜利音效
    QSoundEffect *winSound = new QSoundEffect(this);
    winSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));

    QLabel *winLabel = new QLabel(this);
    QPixmap winPix(":/res/LevelCompletedDialogBg.png");
    winLabel->setFixedSize(winPix.width(),winPix.height());
    winLabel->setPixmap(winPix);
    winLabel->move((this->width()-winPix.width())*0.5,-winPix.height()-22);
    checkCoinTimer = new QTimer(this);
    checkCoinTimer->start(50);
    connect(checkCoinTimer,&QTimer::timeout,[=](){
        checkVictory();
        if(isVictory)
        {
            QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
            animation->setDuration(1000);
            animation->setStartValue(QRect((this->width()-winPix.width())*0.5,-winPix.height()-30,winPix.width(),winPix.height()));
            animation->setEndValue(QRect((this->width()-winPix.width())*0.5,winPix.height()-22,winPix.width(),winPix.height()));
            animation->setEasingCurve(QEasingCurve::OutBounce);
            animation->start();
            winSound->play();
            gameTimer->stop();
        }
    });


 }

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,this->menuBar()->height(),this->width(),this->height(),pix);
}

void PlayScene::checkVictory()
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(gameArray[i][j]!=1)
            {
                return;
            }
        }
    }
    qDebug()<<"胜利";
    isVictory = true;
    checkCoinTimer->stop();
    //禁用按钮
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            coinBtn[i][j]->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        }
    }
}
