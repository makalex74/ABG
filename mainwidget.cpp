#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      m_settings("MakAlexSoft","ABG"),
      m_pBoard(new Board(":/emptyboard2.png")),
      m_ptxtEditHint(new QTextEdit()),
      m_ptxtEditDebug(new QTextEdit()),
      m_plblDisplayFirstGamer(new QLabel()),
      m_plblDisplaySecondGamer(new QLabel()),
      m_plcdDisplayFirstGamer(new QLCDNumber),
      m_plcdDisplaySecondGamer(new QLCDNumber),
      m_bChkNotOpenDlgSelPlayers(false)
{

        setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
        setWindowTitle("Длинные нарды от Алексея (бета-версия)");
        setWindowIcon(QIcon(":/cursor_two_cubes_3232.png"));

        QMenuBar* pmnuBar = new QMenuBar();

        QMenu*   pmnuGame   = new QMenu("&Игра");
        pmnuGame->addAction(//QPixmap(":/new_game.png"),
                            "&Начать новую игру",
                            this,
                            SLOT(NewGame()),
                            Qt::CTRL + Qt::Key_N
                            );
        pmnuGame->addAction(
                            "&Сохранить игру",
                            this,
                            SLOT(saveGame()),
                            Qt::CTRL + Qt::Key_S
                            );
        pmnuGame->addAction(
                            "&Загрузить игру",
                            this,
                            SLOT(loadGame()),
                            Qt::CTRL + Qt::Key_L
                            );
        pmnuGame->addAction(//QPixmap(":/white_black1.png"),
                            "&Выбор игроков...",
                            this,
                            SLOT(selectPlayersShow()),
                            Qt::CTRL + Qt::Key_G
                            );
        pmnuGame->addSeparator();
        pmnuGame->addAction(//QPixmap(":/exit.png"),
                            "&Выход",
                            this,
                            SLOT(close()),
                            Qt::CTRL + Qt::Key_Q
                            );
        pmnuBar->addMenu(pmnuGame);

        QMenu*   pmnuAbout   = new QMenu("&Справка");
        pmnuAbout->addAction("&О программе...",
                             this,
                             SLOT(showAbout()),
                             Qt::CTRL + Qt::Key_P
                             );
        pmnuBar->addMenu(pmnuAbout);


        QLabel* plblTitleGamers = new QLabel("Игрок");
        plblTitleGamers->setAlignment(Qt::AlignHCenter);
        plblTitleGamers->setFrameStyle(QFrame::Box | QFrame::Raised);

        QLabel* plblTitleColorFishs = new QLabel("");
        //plblTitleColorFishs->setAlignment(Qt::AlignHCenter);
        plblTitleColorFishs->setFrameStyle(QFrame::Box | QFrame::Raised);

        QLabel* plblTitlePointsBeforeEndGame = new QLabel("Осталось точек");
        plblTitlePointsBeforeEndGame->setAlignment(Qt::AlignHCenter);
        plblTitlePointsBeforeEndGame->setFrameStyle(QFrame::Box | QFrame::Raised);

        QLabel* plblSeparator = new QLabel("");
        plblSeparator->setFrameStyle(QFrame::Box | QFrame::Raised);

        QLabel* plblHint = new QLabel("Подсказка");
        plblHint->setAlignment(Qt::AlignHCenter);
        plblHint->setFrameStyle(QFrame::Box | QFrame::Raised);

        m_ptxtEditHint->setReadOnly(true);
        m_ptxtEditHint->setFrameStyle(QFrame::Box | QFrame::Raised);

        QLabel* plblDebug = new QLabel("Отладка:");
        plblDebug->setAlignment(Qt::AlignHCenter);
        plblDebug->setFrameStyle(QFrame::Box | QFrame::Raised);
        //
        //plblDebug->setVisible(false);

        m_ptxtEditDebug->setReadOnly(true);
        m_ptxtEditDebug->setFrameStyle(QFrame::Box | QFrame::Raised);
        //
        //m_ptxtEditDebug->setVisible(false);

        m_plblDisplayFirstGamer->setAlignment(Qt::AlignHCenter);
        m_plblDisplayFirstGamer->setFrameStyle(QFrame::Box | QFrame::Raised);

        Fish* pwgtDisplayFishWhite = new Fish(true);
        pwgtDisplayFishWhite->setPicture(":/white_display1.png");

        m_plcdDisplayFirstGamer->setSegmentStyle(QLCDNumber::Flat);
        m_plcdDisplayFirstGamer->setMode(QLCDNumber::Dec);
        m_plcdDisplayFirstGamer->setDigitCount(3);
        m_plcdDisplayFirstGamer->display(360);

        m_plblDisplaySecondGamer->setAlignment(Qt::AlignHCenter);
        m_plblDisplaySecondGamer->setFrameStyle(QFrame::Box | QFrame::Raised);

        Fish* pwgtDisplayFishBlack = new Fish(false);
        pwgtDisplayFishBlack->setPicture(":/black_display1.png");

        m_plcdDisplaySecondGamer->setSegmentStyle(QLCDNumber::Flat);
        m_plcdDisplaySecondGamer->setMode(QLCDNumber::Dec);
        m_plcdDisplaySecondGamer->setDigitCount(3);
        m_plcdDisplaySecondGamer->display(360);

        //Layout setup
        QGridLayout* pGridLayoutDisplay = new QGridLayout;
        pGridLayoutDisplay->addWidget(plblTitleGamers, 0, 0);
        pGridLayoutDisplay->addWidget(m_plblDisplayFirstGamer, 1, 0);
        pGridLayoutDisplay->addWidget(m_plblDisplaySecondGamer, 2, 0);
        pGridLayoutDisplay->addWidget(plblTitleColorFishs, 0, 1);
        pGridLayoutDisplay->addWidget(pwgtDisplayFishWhite, 1, 1);
        pGridLayoutDisplay->addWidget(pwgtDisplayFishBlack, 2, 1);
        pGridLayoutDisplay->addWidget(plblTitlePointsBeforeEndGame, 0, 2);
        pGridLayoutDisplay->addWidget(m_plcdDisplayFirstGamer, 1,2);
        pGridLayoutDisplay->addWidget(m_plcdDisplaySecondGamer, 2, 2);
        //pGridLayoutDisplay->setSpacing(7);
        //pGridLayoutDisplay->setMargin(7);


        QVBoxLayout* pvbxLayoutHintDisplay = new QVBoxLayout;
        pvbxLayoutHintDisplay->addLayout(pGridLayoutDisplay);
        pvbxLayoutHintDisplay->addWidget(plblSeparator);
        pvbxLayoutHintDisplay->addWidget(plblHint);
        pvbxLayoutHintDisplay->addWidget(m_ptxtEditHint);
        pvbxLayoutHintDisplay->addWidget(plblDebug);
        pvbxLayoutHintDisplay->addWidget(m_ptxtEditDebug);
        pvbxLayoutHintDisplay->addStretch(1);

        QHBoxLayout* phbxLayoutBoardPlusHintDisplay = new QHBoxLayout;
        phbxLayoutBoardPlusHintDisplay->addWidget(m_pBoard);
        phbxLayoutBoardPlusHintDisplay->addLayout(pvbxLayoutHintDisplay);

        QVBoxLayout* pvbxLayoutFinal = new QVBoxLayout;
        pvbxLayoutFinal->setMargin(0);
        pvbxLayoutFinal->setSpacing(0);
        pvbxLayoutFinal->addWidget(pmnuBar);
        pvbxLayoutFinal->addLayout(phbxLayoutBoardPlusHintDisplay);
        setLayout(pvbxLayoutFinal);

        move(75, 75);
        //resize(803, 859);
        resize(1000, 709);

        QObject::connect(m_pBoard, SIGNAL(sendHintString(const QString&)),
                         m_ptxtEditHint, SLOT(setHtml(const QString&))
                         );
        QObject::connect(m_pBoard, SIGNAL(sendDebugString(const QString&)),
                         m_ptxtEditDebug, SLOT(append(const QString&))
                         );
        QObject::connect(m_pBoard, SIGNAL(sendDisplayWhiteGamer(const QString&)),
                         m_plblDisplayFirstGamer, SLOT(setText(const QString&))
                         );
        QObject::connect(m_pBoard, SIGNAL(sendDisplayBlackGamer(const QString&)),
                         m_plblDisplaySecondGamer, SLOT(setText(const QString&))
                         );
        QObject::connect(m_pBoard, SIGNAL(sendDisplayWhiteCount(const int&)),
                         m_plcdDisplayFirstGamer, SLOT(display(const int&))
                         );
        QObject::connect(m_pBoard, SIGNAL(sendDisplayBlackCount(const int&)),
                         m_plcdDisplaySecondGamer, SLOT(display(const int&))
                         );
        QObject::connect(m_pBoard, SIGNAL(sendEndGame(const QString&,const QString&)),
                         this, SLOT(endGameShow(const QString&, const QString&))
                         );
}

MainWidget::~MainWidget()
{
    writeSettings();
}

// ----------------------------------------------------------------------
void MainWidget::readSettings()
{
    m_settings.beginGroup("/Settings");
     m_settings.beginGroup("/SelectPlayers");

//      GameTypeEnum eGameType = static_cast<GameTypeEnum>(m_settings.value("/GameType",0).toInt());
//      m_pBoard->setGameType(eGameType);

//      QString strFirstGamerName  = m_settings.value("/FirstGamerName", "").toString();
//      QString strSecondGamerName = m_settings.value("/SecondGamerName", "").toString();

//      m_pBoard->setFirstGamerName(strFirstGamerName);
//      m_pBoard->setSecondGamerName(strSecondGamerName);
//      m_plblDisplayFirstGamer->setText(strFirstGamerName);
//      m_plblDisplaySecondGamer->setText(strSecondGamerName);

      m_bChkNotOpenDlgSelPlayers = m_settings.value("/m_bChkNotOpenDlgSelPlayers", "").toBool();

     m_settings.endGroup();

    m_settings.endGroup();
}

// ----------------------------------------------------------------------
void MainWidget::writeSettings()
{
    m_settings.beginGroup("/Settings");
     m_settings.beginGroup("/SelectPlayers");
//      m_settings.setValue("/GameType", m_pBoard->getGameType());
//      m_settings.setValue("/FirstGamerName", m_plblDisplayFirstGamer->text());
//      m_settings.setValue("/SecondGamerName", m_plblDisplaySecondGamer->text());
      m_settings.setValue("/m_bChkNotOpenDlgSelPlayers", m_bChkNotOpenDlgSelPlayers);
     m_settings.endGroup();
    m_settings.endGroup();


}

void MainWidget::NewGame()
{
    m_ptxtEditDebug->clear();
    m_pBoard->NewGame();

}

void MainWidget::saveGame()
{
    //m_ptxtEditDebug->clear();
    m_pBoard->saveGame();
}

void MainWidget::loadGame()
{
    //m_ptxtEditDebug->clear();
    m_pBoard->loadGame();
}

void MainWidget::selectPlayersShow()
{
    SelectPlayersDialog* pSelectPlayersDialog =
            new SelectPlayersDialog(this,m_pBoard->getGameType(),
                                         m_pBoard->getFirstGamerName(),
                                         m_pBoard->getSecondGamerName()
                                         );
    pSelectPlayersDialog->setWindowTitle("Выбор игроков");

    pSelectPlayersDialog->m_pchkNotOpen->setChecked(m_bChkNotOpenDlgSelPlayers);


    if (pSelectPlayersDialog->exec() == QDialog::Accepted) {
        m_pBoard->setFirstGamerName(pSelectPlayersDialog->getWhiteName());
        m_pBoard->setSecondGamerName(pSelectPlayersDialog->getBlackName());
        m_plblDisplayFirstGamer->setText(pSelectPlayersDialog->getWhiteName());
        m_plblDisplaySecondGamer->setText(pSelectPlayersDialog->getBlackName());

        m_pBoard->setGameType(pSelectPlayersDialog->getGameType());

        m_bChkNotOpenDlgSelPlayers = pSelectPlayersDialog->m_pchkNotOpen->isChecked();

    }
    delete pSelectPlayersDialog;
}

void MainWidget::endGameShow(const QString &strGamerName, const QString &strIsMars)
{
    bool bExit=false;
    EndGameDialog* pEndGameDialog = new EndGameDialog(this,strGamerName,strIsMars);
    pEndGameDialog->setWindowTitle("Конец игры");
    if (pEndGameDialog->exec() == QDialog::Accepted) {
        m_pBoard->NewGame();
    } else
    {
        bExit=true;
    }

    delete pEndGameDialog;
    if (bExit) close();
}


void MainWidget::showAbout()
{
    //m_pBoard->setVisible(false);
    AboutDialog* pAboutDialog = new AboutDialog(this);
    if (pAboutDialog->exec() == QDialog::Accepted) {
        //m_pBoard->setVisible(true);
    }

    delete pAboutDialog;
}
