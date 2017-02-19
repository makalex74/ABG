#include "variantmoves.h"

VariantMoves::VariantMoves(QWidget *parent) : QWidget(parent)
{
      setPicture(":/cheked1.png");
      move(0, 0);
      setAutoFillBackground(true);
}

void VariantMoves::setPicture(const char *pixStr)
{
  QPalette palVariantMoves;
  QPixmap pixVariantMoves(pixStr);
  palVariantMoves.setBrush(backgroundRole(), QBrush(pixVariantMoves));
  setPalette(palVariantMoves);
  //Подгоняем размер виджета под размер картинки
  setFixedSize(pixVariantMoves.width(),pixVariantMoves.height());
}
