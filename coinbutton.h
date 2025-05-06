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
    int x;
    int y;
    bool flag;
    void changeCoin();
    QTimer *timer1;
    QTimer *timer2;
    int min = 1;
    int max = 8;
    bool isChange = false;
signals:
};

#endif // COINBUTTON_H
