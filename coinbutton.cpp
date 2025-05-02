#include "coinbutton.h"


CoinButton::CoinButton(QString coinBtnPath)
{
    QPixmap pix;
    pix.load(coinBtnPath);
    pix = pix.scaled(pix.width() * 1.4, pix.height() * 1.4);
    this->setFixedSize(pix.width(),pix.height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setStyleSheet("QPushButton{border:0px}");//无边框
}
