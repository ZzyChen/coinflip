#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <QObject>
#include <QMap>
#include <QVector>
class LevelData : public QObject
{
    Q_OBJECT
public:
    explicit LevelData(QObject *parent = nullptr);
    QMap<int,QVector<QVector<int>>> data;
signals:
};

#endif // LEVELDATA_H
