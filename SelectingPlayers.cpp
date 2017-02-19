#include <QtWidgets>
#include "SelectingPlayers.h"

SelectingPlayers::SelectingPlayers(QWidget* parent/*= 0*/) : QWidget(parent)

{
    QGroupBox* gbxTypeGame = new QGroupBox("&Тип игры");

    QRadioButton* pradWithComp   = new QRadioButton("Игра против компьютера",gbxTypeGame);
    QRadioButton* pradWithPerson = new QRadioButton("Игра вдвоем на одном компьютере",gbxTypeGame);
    QRadioButton* pradNetGame  = new QRadioButton("Сетевая игра",gbxTypeGame);
    pradWithPerson->setChecked(true);

    QVBoxLayout* pvbxLayoutTypeGame = new QVBoxLayout;
    pvbxLayoutTypeGame->addWidget(pradWithComp);
    pvbxLayoutTypeGame->addWidget(pradWithPerson);
    pvbxLayoutTypeGame->addWidget(pradNetGame);
    gbxTypeGame->setLayout(pvbxLayoutTypeGame);

    QGroupBox* gbxGamerNames = new QGroupBox("&Имена игроков");

    QRadioButton* pradSelectFirstGamer = new QRadioButton("Выбрать первого игрока (право-верх)",gbxGamerNames);
    QRadioButton* pradSelectSecondGamer = new QRadioButton("Выбрать второго игрока (лево-низ)",gbxGamerNames);
    pradSelectFirstGamer->setChecked(true);
    pradSelectSecondGamer->setEnabled(false);

//    QStringList      lst;
//    QListWidget*     plwg = new QListWidget();;
//    lst << "Новый игрок" << "Компьютер";
//    plwg->addItems(lst);

    QComboBox* cbo = new QComboBox;
    cbo->addItem("Первый Игрок");
    cbo->addItem("Второй Игрок");
    cbo->setEditable(true);

    QPushButton* pcmdAdd = new QPushButton("Добавить");
    QPushButton* pcmdEdit = new QPushButton("Изменить");
    QPushButton* pcmdDel = new QPushButton("Удалить");

    QHBoxLayout* pvbxLayoutGamerNamesBtns = new QHBoxLayout;
    pvbxLayoutGamerNamesBtns->addWidget(pcmdAdd);
    pvbxLayoutGamerNamesBtns->addWidget(pcmdEdit);
    pvbxLayoutGamerNamesBtns->addWidget(pcmdDel);

    QVBoxLayout* pvbxLayoutGamerNames = new QVBoxLayout;
    pvbxLayoutGamerNames->addWidget(pradSelectFirstGamer);
    pvbxLayoutGamerNames->addWidget(pradSelectSecondGamer);
    pvbxLayoutGamerNames->addWidget(cbo);
//    pvbxLayoutGamerNames->addWidget(plwg);
    pvbxLayoutGamerNames->addLayout(pvbxLayoutGamerNamesBtns);
    gbxGamerNames->setLayout(pvbxLayoutGamerNames);

    QGroupBox* gbxNetGame = new QGroupBox("&Сетевая игра");
    QRadioButton* pradBeginNewNetGame = new QRadioButton("Начать новый сеанс игры");
    QRadioButton* pradConnectToNetGame = new QRadioButton("Подключиться к");
    pradBeginNewNetGame->setChecked(true);
    pradBeginNewNetGame->setEnabled(false);
    pradConnectToNetGame->setEnabled(false);
    QLineEdit* ptxtCompName   = new QLineEdit;
    ptxtCompName->setText("RemoteComputer");
    ptxtCompName->setEnabled(false);
    QLabel* plblCompName   = new QLabel("(имя удалённого компьютера или IP адрес)");
    plblCompName->setEnabled(false);

    QHBoxLayout* pvbxLayoutCompName = new QHBoxLayout;
    pvbxLayoutCompName->addWidget(pradConnectToNetGame);
    pvbxLayoutCompName->addWidget(ptxtCompName);

    QVBoxLayout* pvbxLayoutBeginNewNetGame = new QVBoxLayout;
    pvbxLayoutBeginNewNetGame->addWidget(pradBeginNewNetGame);
    pvbxLayoutBeginNewNetGame->addLayout(pvbxLayoutCompName);
    pvbxLayoutBeginNewNetGame->addWidget(plblCompName);
    gbxNetGame->setLayout(pvbxLayoutBeginNewNetGame);

    QCheckBox* pchkNotOpen = new QCheckBox("Не открывать данный диалог при запуске");
    pchkNotOpen->setChecked(false);

    QPushButton* pcmdOk = new QPushButton("&Ok");
    connect(pcmdOk, SIGNAL(clicked()), this, SLOT(hide()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(gbxTypeGame);
    pvbxLayout->addWidget(gbxGamerNames);
    pvbxLayout->addWidget(gbxNetGame);
    pvbxLayout->addWidget(pchkNotOpen);
    pvbxLayout->addWidget(pcmdOk);
    setLayout(pvbxLayout);

    setWindowTitle("Выбор игроков");

}




