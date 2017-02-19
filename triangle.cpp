#include "triangle.h"

Triangle::Triangle(bool isWhite, QObject *parent) : QObject(parent), m_bIsWhite(isWhite), m_bSelectedForMove(false)
{

}

bool Triangle::getSelectedForMove(void)
{
  return m_bSelectedForMove;
}
void Triangle::setSelectedForMove(bool isSelected)
{
   m_bSelectedForMove = isSelected;
   if (m_bSelectedForMove) //Если в
   {
       if (m_bIsWhite)
         stkFishs[stkFishs.size()-1]->setPicture(":/white_cheked_ellipse1.png");
       else
         stkFishs[stkFishs.size()-1]->setPicture(":/black_cheked_ellipse1.png");
   } else
   {
       if (m_bIsWhite)
         stkFishs[stkFishs.size()-1]->setPicture(":/white1.png");
       else
         stkFishs[stkFishs.size()-1]->setPicture(":/black1.png");
   }

}
