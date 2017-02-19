
#include <QtWidgets>
#include "about.h"

// ----------------------------------------------------------------------
AboutDialog::AboutDialog(QWidget* pwgt/*= 0*/)
     : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{   
    setWindowTitle("О программе");

    QPalette palAbout;
    QPixmap pixAbout(":/faceBoard1.png");
    palAbout.setBrush(backgroundRole(), QBrush(pixAbout));
    setPalette(palAbout);
    //Подгоняем размер виджета под размер картинки
    setFixedSize(pixAbout.width(),pixAbout.height());
    setAutoFillBackground(true);

    QWidget* pwgtNull1   = new QWidget();

    QPalette palNull1;
    QPixmap pixNull1(":/null157_317.png");
    palNull1.setBrush(backgroundRole(), QBrush(pixNull1));
    pwgtNull1->setPalette(palNull1);
    //Подгоняем размер виджета под размер картинки
    pwgtNull1->setFixedSize(pixNull1.width(),pixNull1.height());
    pwgtNull1->setAutoFillBackground(true);

    QWidget* pwgtNull2   = new QWidget();

    QPalette palNull2;
    QPixmap pixNull2(":/null364_317.png");
    palNull2.setBrush(backgroundRole(), QBrush(pixNull2));
    pwgtNull2->setPalette(palNull2);
    //Подгоняем размер виджета под размер картинки
    pwgtNull2->setFixedSize(pixNull2.width(),pixNull2.height());
    pwgtNull2->setAutoFillBackground(true);

    QLabel* plblAbout1   = new QLabel("Длинные нарды от Алексея");
    plblAbout1->setAlignment(Qt::AlignHCenter);
    QLabel* plblAbout2   = new QLabel("(бета-версия).");
    plblAbout2->setAlignment(Qt::AlignHCenter);
    QLabel* plblAbout3   = new QLabel("Copyright(c)");
    plblAbout3->setAlignment(Qt::AlignHCenter);
    QLabel* plblAbout4   = new QLabel("Алексей Макаенко,2016.");
    plblAbout4->setAlignment(Qt::AlignHCenter);
    QLabel* plblAbout5   = new QLabel("");
    plblAbout5->setAlignment(Qt::AlignHCenter);

    QPushButton* pcmdOk     = new QPushButton("&Ok");

    connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));

    QVBoxLayout* pvLayout = new QVBoxLayout;
    pvLayout->addWidget(plblAbout1);
    pvLayout->addWidget(plblAbout2);
    pvLayout->addStretch(1);
    pvLayout->addWidget(plblAbout3);
    pvLayout->addWidget(plblAbout4);
    pvLayout->addWidget(plblAbout5);
    pvLayout->addStretch(1);
    pvLayout->addWidget(pcmdOk);
    pvLayout->setMargin(15);

    QHBoxLayout* phLayout = new QHBoxLayout;
    phLayout->addWidget(pwgtNull1);
    phLayout->addWidget(pwgtNull2);
    phLayout->addLayout(pvLayout);

    setLayout(phLayout);
}

