#ifndef VARIANTMOVESTRI_H
#define VARIANTMOVESTRI_H

#include <QWidget>

class VariantMovesTri : public QWidget
{
    Q_OBJECT
public:
    explicit VariantMovesTri(QWidget *parent = 0);
    void setPicture(const char *pixStr);
signals:

public slots:
};

#endif // VARIANTMOVESTRI_H
