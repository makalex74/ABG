#include "fish.h"

Fish::Fish(bool white, QWidget *parent) : QWidget(parent), isWhite(white), bFishChecked(false), pAnim(new QPropertyAnimation(this, "pos"))
{
    if (isWhite)
        setPicture(":/white1.png");
    else
        setPicture(":/black1.png");



    move(0, 0);
    setAutoFillBackground(true);
}

void Fish::setPicture(const char *pixStr)
{
  QPalette palFish;
  QPixmap pixFish(pixStr);
  palFish.setBrush(backgroundRole(), QBrush(pixFish));
  setPalette(palFish);
  //Подгоняем размер виджета под размер картинки
  setFixedSize(pixFish.width(),pixFish.height());
}

///*virtual*/ void Fish::enterEvent(QEvent* e)
//{
//    //Курсор над фишкой принимает вид указателя ввиде руки
//    setCursor(Qt::PointingHandCursor);
//    if (!bFishChecked)
//        if (isWhite)
//        {
//            setPicture(":/white_cheked_arrow1.png");
//        }
//        else
//        {
//            setPicture(":/black_cheked_arrow1.png");
//        }

//    QWidget::enterEvent(e); //Передать событие дальше
//}

///*virtual*/ void Fish::leaveEvent(QEvent* e)
//{
//    //Курсор не над фишкой принимает вид указателя ввиде стрелки
//    setCursor(Qt::ArrowCursor);
//    if (!bFishChecked)
//        if (isWhite)
//        {
//            setPicture(":/white1.png");
//        }
//        else
//        {
//            setPicture(":/black1.png");
//        }

//    QWidget::enterEvent(e); //Передать событие дальше
//}

//void Fish::paintEvent(QPaintEvent* pe)
//{
//    QPainter painter(this);
//    QRect r=this->geometry();

//    if (pe->region().contains(r))
//    {
//      painter.drawRect(r);
//    }

//}

///*virtual*/void Fish::mousePressEvent(QMouseEvent* pe)
//{

//    bFishChecked = !bFishChecked;
//    if (bFishChecked) //Фишка выбрана для хода
//        if (isWhite) //Фишка белая
//        {
//            setPicture(":/white_cheked_arrow_ellipse1.png");
//        }
//        else         //Фишка черная
//        {
//            setPicture(":/black_cheked_arrow_ellipse1.png");
//        }
//    else //Фишка не выбрана для хода
//        if (isWhite) //Фишка белая
//        {
//            setPicture(":/white1.png");
//        }
//        else         //Фишка черная
//        {
//            setPicture(":/black1.png");
//        }


//        QWidget::enterEvent(pe); //Передать событие дальше

//}


///*virtual*/void Fish::mouseReleaseEvent(QMouseEvent* pe)
//{

//}

///*virtual*/ void Fish::mouseMoveEvent(QMouseEvent* pe)
//{
//     if (bFishChecked)
//     move(pe->x(),pe->y());
//}
