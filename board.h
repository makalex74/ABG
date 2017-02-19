#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QTCore>
#include "fish.h"
#include "triangle.h"
#include "cube.h"
#include "globalvar.h"

class Board : public QWidget
{
    Q_OBJECT

private:
    GameTypeEnum m_gameType;

    QSettings  m_settings;

    QVector<Triangle*> vecTriWhiteFishs;
    QVector<Triangle*> vecTriBlackFishs;

    QVector<Cube*> vectorCubeWhite;
    QVector<Cube*> vectorCubeBlack;
    //Процедура бросания кубика на право первого хода
    int RollTheCubeBlack();
    int RollTheCubeWhite();

    void rollTheCubesWhiteAnimation();
    void rollTheCubesBlackAnimation();
    //Процедура бросания кубиков
    QString RollTheCubesBlack();
    QString RollTheCubesWhite();

    //Убираем все кубики с доски
    void hideAllCubes(void);

    int vectorRandomValuesNextIndex;
    QVector<int> vectorRandomValues;
    void VectorRandomValuesInit(void);

    //Состояние - false - бросаем кубики на право первого хода
    bool m_checkRightOfTheFirstMove;
    int m_valueWhite; //При розыгрыше на право первого хода, значение которое выбросили белые
    int m_valueBlack; //При розыгрыше на право первого хода, значение которое выбросили черные

    //Состояние - бросаем кубики, true - бросают белые, false - бросают черные
    bool m_RollTheCubesForWhiteFish;

    //Флаг первого хода с головы для белых
    bool m_bFirstMoveFromHeadWhite;
    //Флаг первого хода с головы для белых
    bool m_bFirstMoveFromHeadBlack;

    //Количество ходов сделаных с головы
    int m_iCountMoveFromHead;

    //Состояние - ход белых
    bool m_bMoveWhiteFish;
    //Состояние - ход черных
    bool m_bMoveBlackFish;

     //Количество треугольников до конца игры для белых
    int m_iWhiteCount;
     //Количество треугольников до конца игры для черных
    int m_iBlackCount;

    //Текущая строка с подсказкой
    QString m_strHintString;

    void UpdateState(void);
    bool MoveFish(Triangle* fromTri, Triangle* toTri);

    virtual void mousePressEvent  (QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);
    virtual void mouseMoveEvent   (QMouseEvent* pe);

    //Снимаем признак "Выбран для хода" с любой фишки
    void Board::deSelectForMoveAll();

    //Возвращает true если какая-то фишка выбрана для хода и false если не выбрана
    bool existsSelectedForMove(const bool &bIsWhite);

    //Выбрать(снять выбор) белую фишку (треугольник) для хода
    bool selForMoveWhiteFish(const int &x, const int &y);
    //Выбрать(снять выбор) черную фишку (треугольник) для хода
    bool selForMoveBlackFish(const int &x, const int &y);


    //Вычисляем количество неиспользованных ходов при ходе дублем
    //Используется в функции showPossibleWhiteMoves
    int getCountFishMovedCubesForDouble(const bool &bIsWhite);

    //Подсчитать количество оставшихся (доступных) ходов
    int countRemainingMoves(const bool &bIsWhite);

    //Все фишки в доме
    bool inHouse(const bool &bIsWhite);

    bool inHouseNotFishsBefore(const int &inx, bool bIsWhite);


    bool existsOpponentFishAfter(const int &inx, const bool &bIsWhite);
    bool sixFishsInARow(const int &inx, const bool &bIsWhite);

    QString isMars(bool bIsWhite);
    void checkEndGame();

    void showPossibleMovesForAll(const bool &bIsWhite);
    void showPossibleWhiteMoves(const int &inx, const bool &bForAll);
    void showPossibleBlackMoves(const int &inx, const bool &bForAll);

    //Делаем ход белой фишкой на щелкнутый мышкой виджет возможного хода
    bool moveWhiteFish(const int &x, const int &y);
    //Делаем ход белой черной на щелкнутый мышкой виджет возможного хода
    bool moveBlackFish(const int &x, const int &y);

    //Когда выпал дубль, то после сделанного хода надо
    //выставить признак "Сделан ход" для следующего непомеченного кубика
    //Используется в функции cubesWhiteSetFishMoved(const int inxSelected, const int inxMove);
    void setFishMovedNextForDouble(const bool &bIsWhite);

    //Выставляем признак "Сделан ход" для кубика (кубиков) после сделанного хода
    void cubesWhiteSetFishMoved(const int &inxSelected, const int &inxMove);
    void cubesBlackSetFishMoved(const int &inxSelected, const int &inxMove);

    void hidePossibleMoves(const bool &bIsWhite);

    bool opponentFishOccupyTri(const int &inx, const bool &bIsWhite);

    QString firstGamerName;
    QString secondGamerName;


public:
    explicit Board(const char* pixStr, QWidget *parent = 0);
    ~Board();
    void strToHint(const QString& str);
    void strToDebug(const QString& str);
    void setFirstGamerName(const QString& str);
    void setSecondGamerName(const QString& str);
    QString getFirstGamerName() const;
    QString getSecondGamerName() const;
    void setGameType(GameTypeEnum gType);
    GameTypeEnum getGameType();

signals:
    void sendHintString(const QString&);
    void sendDebugString(const QString&);
    void sendDisplayWhiteGamer(const QString&);
    void sendDisplayBlackGamer(const QString&);
    void sendDisplayWhiteCount(const int& cnt);
    void sendDisplayBlackCount(const int& cnt);
    void sendEndGame(const QString& strGamerName, const QString& strIsMars);

public slots:
    void NewGame();
    void loadGame();
    void saveGame();

};

#endif // BOARD_H
