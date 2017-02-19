#ifndef SELECTINGPLAYERS_H
#define SELECTINGPLAYERS_H

#include <QWidget>
#include <QtWidgets>
#include "globalvar.h"

class QGroupBox;
class QRadioButton;
class QPushButton;

class SelectingPlayers : public QWidget
{
    Q_OBJECT


public:
    explicit SelectingPlayers(QWidget* parent = 0);

signals:

public slots:
};

#endif // SELECTINGPLAYERS_H
