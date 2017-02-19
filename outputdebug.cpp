#include "outputdebug.h"

OutputDebug::OutputDebug(QWidget *parent) : QTextEdit(parent)
{

}

void OutputDebug::addText(const QString& strDebug)
{
   //append("<"+ QTime::currentTime().toString()+ "> " + strDebug);
   append(strDebug);
}
