#ifndef FISH_H
#define FISH_H

//#include <QWidget>
#include <QtWidgets>
#include "globalvar.h"

class Fish : public QWidget
{
    Q_OBJECT
public:
    explicit Fish(bool white, QWidget *parent = 0);
    QPropertyAnimation* pAnim;

protected:
//    virtual void enterEvent(QEvent* e);
//    virtual void leaveEvent(QEvent* e);
    bool isWhite;
//    void paintEvent(QPaintEvent* pe);
//    virtual void mousePressEvent  (QMouseEvent* pe);
//    virtual void mouseReleaseEvent(QMouseEvent* pe);
//    virtual void mouseMoveEvent   (QMouseEvent* pe);
    bool bFishChecked;

signals:

public slots:
    void setPicture(const char *pixStr);
};

#endif // FISH_H
