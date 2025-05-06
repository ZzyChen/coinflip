#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
class LevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelScene(QWidget *parent = nullptr);
     void paintEvent(QPaintEvent *);
    PlayScene *p = nullptr;
signals:
     void backToMainScene();
};

#endif // LEVELSCENE_H
