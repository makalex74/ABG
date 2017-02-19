#include "mainwidget.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWidget mainWgt;

    mainWgt.show();
    mainWgt.readSettings();
    mainWgt.NewGame();
    mainWgt.loadGame();

    if (!mainWgt.m_bChkNotOpenDlgSelPlayers)
        mainWgt.selectPlayersShow();

//    SelectingPlayers sPlayers;
//    sPlayers.move(330,275);
//    sPlayers.show();
//     AboutProgram wgtAboutProgram;
//     wgtAboutProgram.move(330,275);
//     wgtAboutProgram.show();

    return app.exec();
}
