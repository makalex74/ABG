#include "variantmovestri.h"

VariantMovesTri::VariantMovesTri(QWidget *parent) : QWidget(parent)
{
    setPicture(":/triangleBottomTop1.png");
    move(0, 0);
    setAutoFillBackground(true);
}

void VariantMovesTri::setPicture(const char *pixStr)
{
  QPalette palVariantMovesTri;
  QPixmap pixVariantMovesTri(pixStr);
  palVariantMovesTri.setBrush(backgroundRole(), QBrush(pixVariantMovesTri));
  setPalette(palVariantMovesTri);
  //Подгоняем размер виджета под размер картинки
  setFixedSize(pixVariantMovesTri.width(),pixVariantMovesTri.height());
}
