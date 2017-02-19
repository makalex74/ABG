
#include <QtWidgets>
#include "selectplayers.h"

// ----------------------------------------------------------------------
SelectPlayersDialog::SelectPlayersDialog(QWidget* pwgt/*= 0*/,
                                         GameTypeEnum eGameType,
                                         const QString& whiteGName,
                                         const QString& blackGName)
     : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
       m_gameType(eGameType),
       m_ptxtWhiteName(new QLineEdit(whiteGName)),
       m_ptxtBlackName(new QLineEdit(blackGName))
{   

    QGroupBox* gbxTypeGame = new QGroupBox("&Тип игры");

    m_pradWithComp   = new QRadioButton("Игра против компьютера",gbxTypeGame);
    m_pradWithPerson = new QRadioButton("Игра вдвоем на одном компьютере",gbxTypeGame);
    //QRadioButton* pradNetGame  = new QRadioButton("Сетевая игра",gbxTypeGame);

    QVBoxLayout* pvbxLayoutTypeGame = new QVBoxLayout;
    pvbxLayoutTypeGame->addWidget(m_pradWithComp);
    pvbxLayoutTypeGame->addWidget(m_pradWithPerson);
    //pvbxLayoutTypeGame->addWidget(pradNetGame);
    gbxTypeGame->setLayout(pvbxLayoutTypeGame);

    QLabel* plblWhiteName    = new QLabel("&Первый игрок (лево-верх):");
    QLabel* plblBlackName     = new QLabel("&Второй игрок (право-низ):");

    plblWhiteName->setBuddy(m_ptxtWhiteName);
    plblBlackName->setBuddy(m_ptxtBlackName);

    m_pchkNotOpen = new QCheckBox("Не открывать данный диалог при запуске");
    m_pchkNotOpen->setChecked(false);

    QPushButton* pcmdOk     = new QPushButton("&Ok");
    QPushButton* pcmdCancel = new QPushButton("&Отмена");

    connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));

    //Layout setup
    QGridLayout* pgridLayout = new QGridLayout;
    pgridLayout->addWidget(plblWhiteName, 0, 0);
    pgridLayout->addWidget(plblBlackName, 1, 0);
    pgridLayout->addWidget(m_ptxtWhiteName, 0, 1);
    pgridLayout->addWidget(m_ptxtBlackName, 1, 1);

    QHBoxLayout* pbuttonLayout = new QHBoxLayout;
    pbuttonLayout->addWidget(pcmdOk);
    pbuttonLayout->addWidget(pcmdCancel);

    QVBoxLayout* pmainLayout = new QVBoxLayout;
    pmainLayout->addWidget(gbxTypeGame);
    pmainLayout->addLayout(pgridLayout);
    pmainLayout->addWidget(m_pchkNotOpen);
    pmainLayout->addLayout(pbuttonLayout);
    setLayout(pmainLayout);

    QObject::connect(m_pradWithComp, SIGNAL(clicked(bool)), m_ptxtBlackName, SLOT(setDisabled(bool)));
    QObject::connect(m_pradWithPerson, SIGNAL(clicked(bool)), m_ptxtBlackName, SLOT(setEnabled(bool)));
    QObject::connect(m_pradWithComp, SIGNAL(clicked(bool)), this, SLOT(changeGameType()));
    QObject::connect(m_pradWithPerson, SIGNAL(clicked(bool)), this, SLOT(changeGameType()));

    if (getWhiteName()=="")
        setWhiteName("Белый");
    if (getBlackName()=="")
        setBlackName("Черный");

    if (m_gameType==GAMEWITHCOMPUTER)
    {
      m_pradWithComp->setChecked(true);
      m_ptxtBlackName->setText("Компьютер");
      m_ptxtBlackName->setEnabled(false);
    }
    else if (m_gameType==GAMEWITHPERSON)
    {
      m_pradWithPerson->setChecked(true);
    }
}

// ----------------------------------------------------------------------
QString SelectPlayersDialog::getWhiteName() const
{
    return m_ptxtWhiteName->text();
}

// ----------------------------------------------------------------------
QString SelectPlayersDialog::getBlackName() const
{
    return m_ptxtBlackName->text();
}

// ----------------------------------------------------------------------
void SelectPlayersDialog::setWhiteName(const QString& str)
{
    m_ptxtWhiteName->setText(str);
}

// ----------------------------------------------------------------------
void SelectPlayersDialog::setBlackName(const QString& str)
{
    m_ptxtBlackName->setText(str);
}

void SelectPlayersDialog::setGameType(GameTypeEnum gType)
{
  m_gameType=gType;
}

GameTypeEnum SelectPlayersDialog::getGameType()
{
    return m_gameType;
}

void SelectPlayersDialog::changeGameType()
{
    if (m_pradWithComp->isChecked())
    {
        setGameType(GAMEWITHCOMPUTER);
        m_ptxtBlackName->setText("Компьютер");

    } else if (m_pradWithPerson->isChecked())
    {
        setGameType(GAMEWITHPERSON);
        m_ptxtBlackName->setText("Черный");
    }
}
