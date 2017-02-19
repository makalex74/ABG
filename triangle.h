#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QTCore>
#include "fish.h"
#include "variantmoves.h"
#include "variantmovestri.h"

class Triangle : public QObject
{
    Q_OBJECT
public:
    explicit Triangle(bool isWhite, QObject *parent = 0);
    //Стек с фишками
    QStack<Fish*> stkFishs;
    //Виджет метки обознчающей вариант хода
    VariantMoves* wgtVarMove;
    VariantMovesTri* wgtVarMoveTri;
    //Список текущих ходов
    QList<int> lstCurrMoves;
    bool getSelectedForMove(void);
    void setSelectedForMove(bool isSelected);

protected:
    bool m_bIsWhite;
    bool m_bSelectedForMove;

signals:

public slots:
};

#endif // TRIANGLE_H
