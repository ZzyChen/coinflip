#include "coinbutton.h"
#include <QTimer>

CoinButton::CoinButton(QString coinBtnPath)
{
    QPixmap pix;
    pix.load(coinBtnPath);
    pix = pix.scaled(pix.width() * 1.4, pix.height() * 1.4);
    this->setFixedSize(pix.width(),pix.height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setStyleSheet("QPushButton{border:0px}");//无边框

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(min++);
        pix.load(str);
        pix = pix.scaled(pix.width() * 1.4, pix.height() * 1.4);
        this->setFixedSize(pix.width(),pix.height());
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        this->setStyleSheet("QPushButton{border:0px}");//无边框
        isChange = true;
        if(min>max)
        {
            min = 1;
            timer1->stop();
            isChange = false;
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%8.png").arg(max--);
        pix.load(str);
        pix = pix.scaled(pix.width() * 1.4, pix.height() * 1.4);
        this->setFixedSize(pix.width(),pix.height());
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        this->setStyleSheet("QPushButton{border:0px}");//无边框
        isChange = true;
        if(max<min)
        {
            max = 8;
            timer2->stop();
            isChange = false;
        }
    });
}


void CoinButton::changeCoin()
{
    if(flag)
    {
        flag = false;
        timer1->start(50);
    }
    else
    {
        flag = true;
        timer2->start(50);
    }
}
