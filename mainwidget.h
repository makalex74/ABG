#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "globalvar.h"
#include "board.h"
//#include "outputdebug.h"
#include "SelectingPlayers.h"
#include "about.h"
#include "globalvar.h"
#include "selectplayers.h"
#include "endgame.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void writeSettings();
    void readSettings ();
    bool m_bChkNotOpenDlgSelPlayers;

private:
    QSettings  m_settings;
    Board* m_pBoard;
    QTextEdit* m_ptxtEditHint;
    QTextEdit* m_ptxtEditDebug;
    QLabel* m_plblDisplayFirstGamer;
    QLabel* m_plblDisplaySecondGamer;
    QLCDNumber* m_plcdDisplayFirstGamer;
    QLCDNumber* m_plcdDisplaySecondGamer;

public slots:
    void NewGame();
    void saveGame();
    void loadGame();
    void showAbout();
    void selectPlayersShow();
    void endGameShow(const QString& strGamerName, const QString& strIsMars);
};

#endif // MAINWIDGET_H
