
#include <QtWidgets>
#include "endgame.h"

// ----------------------------------------------------------------------
EndGameDialog::EndGameDialog(QWidget* pwgt/*= 0*/,const QString& strGamerName, const QString& strIsMars)
     : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{   
    m_plblVictoryLoss = new QLabel("Победа игрока "+strGamerName+"!");
    m_plblVictoryLoss->setAlignment(Qt::AlignHCenter);

    m_plblPictVictoryLoss = new QLabel();
    QPixmap pix1;
    pix1.load(":/crownVictory.png");
    m_plblPictVictoryLoss->setPixmap(pix1);
    m_plblPictVictoryLoss->setAlignment(Qt::AlignHCenter);

    m_plblMars = new QLabel(strIsMars);
    m_plblMars->setAlignment(Qt::AlignHCenter);

    QPushButton* pcmdNewGame = new QPushButton("&Новая игра");
    QPushButton* pcmdQuit = new QPushButton("&Выход");

    connect(pcmdNewGame, SIGNAL(clicked()), SLOT(accept()));
    connect(pcmdQuit, SIGNAL(clicked()), SLOT(reject()));

    //Layout setup
    QHBoxLayout* phButtonLayout = new QHBoxLayout;
    phButtonLayout->addWidget(pcmdNewGame);
    phButtonLayout->addWidget(pcmdQuit);

    QVBoxLayout* pvLayout = new QVBoxLayout;
    pvLayout->addWidget(m_plblPictVictoryLoss);
    pvLayout->addWidget(m_plblVictoryLoss);
    pvLayout->addWidget(m_plblMars);
    pvLayout->addLayout(phButtonLayout);
    setLayout(pvLayout);
}

// ----------------------------------------------------------------------
//QString EndGameDialog::getFirstName() const
//{
//    return m_ptxtFirstName->text();
//}

// ----------------------------------------------------------------------
//QString EndGameDialog::getSecondName() const
//{
//    return m_ptxtSecondName->text();
//}

// ----------------------------------------------------------------------
//void EndGameDialog::setFirstName(const QString& str)
//{
//    m_ptxtFirstName->setText(str);
//}

// ----------------------------------------------------------------------
//void EndGameDialog::setSecondName(const QString& str)
//{
//    m_ptxtSecondName->setText(str);
//}
