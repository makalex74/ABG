#ifndef OUTPUTDEBUG_H
#define OUTPUTDEBUG_H

#include <QtWidgets>
#include "globalvar.h"

class OutputDebug : public QTextEdit
{
    Q_OBJECT
public:
    explicit OutputDebug(QWidget *parent = 0);

signals:

public slots:
    void addText(const QString& strDebug);
};

#endif // OUTPUTDEBUG_H
