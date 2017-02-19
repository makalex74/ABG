#ifndef SELECTPLAYERS_H
#define SELECTPLAYERS_H

#include <QDialog>
#include "globalvar.h"

class QLineEdit;
class QCheckBox;
class QRadioButton;
// ======================================================================
class SelectPlayersDialog : public QDialog {
    Q_OBJECT
private:
    QLineEdit* m_ptxtWhiteName;
    QLineEdit* m_ptxtBlackName;
    QRadioButton* m_pradWithComp;
    QRadioButton* m_pradWithPerson;
    GameTypeEnum m_gameType;

public:
    SelectPlayersDialog(QWidget* pwgt = 0,
                        GameTypeEnum eGameType=GAMEWITHCOMPUTER,
                        const QString& whiteGName="",
                        const QString& blackGName="");

    QString getWhiteName() const;
    QString getBlackName() const;
    void setWhiteName(const QString& str);
    void setBlackName(const QString& str);
    void setGameType(GameTypeEnum gType);
    GameTypeEnum getGameType();

    QCheckBox* m_pchkNotOpen;

public slots:
    void changeGameType();

};


#endif // SELECTPLAYERS_H
