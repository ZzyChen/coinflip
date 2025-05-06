#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "coinbutton.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    int levelIndex;
    void paintEvent(QPaintEvent *);
    int gameArray[4][4];
    CoinButton *coinBtn[4][4];
    QTimer *checkCoinTimer;
    void checkVictory();
    bool isVictory = false;
    QTimer *gameTimer;

signals:
    void backToLevelScene();
};

#endif // PLAYSCENE_H
