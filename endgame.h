#ifndef ENDGAME_H
#define ENDGAME_H

#include <QDialog>

class QLabel;
// ======================================================================
class EndGameDialog : public QDialog {
    Q_OBJECT
private:
    QLabel* m_plblVictoryLoss;
    QLabel* m_plblPictVictoryLoss;
    QLabel* m_plblMars;

public:
    EndGameDialog(QWidget* pwgt = 0, const QString& strGamerName ="Игрок №1", const QString& strIsMars="Не Марс");

};


#endif // ENDGAME_H
