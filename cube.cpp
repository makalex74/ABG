#include "cube.h"

Cube::Cube(int val, QWidget *parent) : QWidget(parent),
    valueCube(val),
    m_bFishMoved(false),
    candidateForOut(false),
    pAnim(new QPropertyAnimation(this, "pos"))
{
    setValue(valueCube);
    //resize(803, 709);
    move(0, 300);
    setAutoFillBackground(true);
}

void Cube::setValue(int val)
{
    valueCube=val;
    switch (valueCube)
    {
    case 1:
        setPicture(":/one.png");
        break;
    case 2:
        setPicture(":/two.png");
        break;
    case 3:
        setPicture(":/three.png");
        break;
    case 4:
        setPicture(":/four.png");
        break;
    case 5:
        setPicture(":/five.png");
        break;
    case 6:
        setPicture(":/six.png");
        break;
    }
}

int Cube::getValue()
{
    return valueCube;
}

void Cube::setPicture(const char *pixStr)
{
  QPalette palCube;
  QPixmap pixCube(pixStr);
  palCube.setBrush(backgroundRole(), QBrush(pixCube));
  setPalette(palCube);
  //Подгоняем размер виджета под размер картинки
  setFixedSize(pixCube.width(),pixCube.height());
}

bool Cube::getFishMoved(void)
{
    return m_bFishMoved;

}
void Cube::setFishMoved(bool isSelected)
{
    m_bFishMoved=isSelected;
    if (m_bFishMoved)
    {
        switch (valueCube)
        {
        case 1:
            setPicture(":/oneGrey.png");
            break;
        case 2:
            setPicture(":/twoGrey.png");
            break;
        case 3:
            setPicture(":/threeGrey.png");
            break;
        case 4:
            setPicture(":/fourGrey.png");
            break;
        case 5:
            setPicture(":/fiveGrey.png");
            break;
        case 6:
            setPicture(":/sixGrey.png");
            break;
        }
    }
    else
    {
        switch (valueCube)
        {
        case 1:
            setPicture(":/one.png");
            break;
        case 2:
            setPicture(":/two.png");
            break;
        case 3:
            setPicture(":/three.png");
            break;
        case 4:
            setPicture(":/four.png");
            break;
        case 5:
            setPicture(":/five.png");
            break;
        case 6:
            setPicture(":/six.png");
            break;
        }
    }
}


