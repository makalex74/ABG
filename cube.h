#ifndef CUBE_H
#define CUBE_H

//#include <QWidget>
#include <QtWidgets>
#include "globalvar.h"

class Cube : public QWidget
{
    Q_OBJECT
public:
    explicit Cube(int val, QWidget *parent = 0);
    void setValue(int val);
    int getValue();
    bool getFishMoved(void);
    void setFishMoved(bool isSelected);
    //Кубик показывает ход - кандидат на выход из дома
    bool candidateForOut;
    QPropertyAnimation* pAnim;
protected:
    int valueCube; //Выброшенное значение на вершнй грани кубика
    //char* fileNameCube; //Имя файла
    void setPicture(const char *pixStr);
    bool m_bFishMoved; //Для кубика сделан ход фишкой
signals:

public slots:
};

#endif // CUBE_H
