#include "mypushbutton.h"
#include "QPropertyAnimation"
// MyPushButton::MyPushButton(QWidget *parent)
//     : QPushButton{parent}
// {}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalPath = normalImg;
    this->pressPath  = pressImg;
    QPixmap pix;
    pix.load(normalPath);
    this->setFixedSize(pix.width(),pix.height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setStyleSheet("QPushButton{border:0px}");//无边框
}

void MyPushButton::up()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::down()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressPath!=""){
        QPixmap pix;
        pix.load(this->pressPath);
        pix = pix.scaled(pix.width(),pix.height());
        this->setFixedSize(pix.width(),pix.height());
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        this->setStyleSheet("QPushButton{border:0px}");//无边框
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressPath!=""){
        QPixmap pix;
        pix.load(this->normalPath);
        this->setFixedSize(pix.width(),pix.height());
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        this->setStyleSheet("QPushButton{border:0px}");//无边框
        qDebug()<<"释放";
    }
    return QPushButton::mouseReleaseEvent(e);
}
