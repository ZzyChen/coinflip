#include "leveldata.h"

LevelData::LevelData(QObject *parent)
    : QObject{parent}
{
    QVector<QVector<int>> v;
    int  array1[4][4] = {{1,1,1,1},
                       {1,1,0,1},
                       {1,0,0,0},
                       {1,1,0,1}};
    int  array2[4][4] = {{1,0,0,1},
                        {1,1,0,1},
                        {1,0,0,0},
                        {1,1,0,1}};
    for (int i = 0; i < 4; ++i) {
        QVector<int> v1;
        for (int j = 0; j < 4; ++j) {
            v1.push_back(array1[i][j]);
        }
        v.push_back(v1);
    }
    data.insert(1,v);
    v.clear();
    for (int i = 0; i < 4; ++i) {
        QVector<int> v2;
        for (int j = 0; j < 4; ++j) {
            v2.push_back(array2[i][j]);
        }
        v.push_back(v2);
    }
    data.insert(2,v);
}
