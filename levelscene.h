#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QMainWindow>

class LevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelScene(QWidget *parent = nullptr);
     void paintEvent(QPaintEvent *);
signals:
     void backToMainScene();
};

#endif // LEVELSCENE_H
