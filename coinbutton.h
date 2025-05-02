#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit CoinButton(QWidget *parent = nullptr);
    CoinButton(QString coinBtnPath);
signals:
};

#endif // COINBUTTON_H
