#ifndef VARIANTMOVES_H
#define VARIANTMOVES_H

#include <QWidget>

class VariantMoves : public QWidget
{
    Q_OBJECT
public:
    explicit VariantMoves(QWidget *parent = 0);
    void setPicture(const char *pixStr);
signals:

public slots:
};

#endif // VARIANTMOVES_H
