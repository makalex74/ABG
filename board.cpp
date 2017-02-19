#include "board.h"

Board::Board(const char* pixStr, QWidget *parent) : QWidget(parent)
  , m_gameType(GAMEWITHCOMPUTER)
  , m_settings("MakAlexSoft","ABG")
  , vectorRandomValues(1000)
  , vectorRandomValuesNextIndex(0)
  , vecTriWhiteFishs(25)
  , vecTriBlackFishs(25)
  , firstGamerName("Игрок белыми")
  , secondGamerName("Игрок черными")
  , m_checkRightOfTheFirstMove(false) //ПОПРАВИТЬ НА FALSE
  , m_RollTheCubesForWhiteFish(true)
  , m_valueWhite(0) //При розыгрыше на право первого хода, значение которое выбросили белые
  , m_valueBlack(0) //При розыгрыше на право первого хода, значение которое выбросили черные
  , m_bMoveWhiteFish(false)
  , m_bMoveBlackFish(false)
  , m_bFirstMoveFromHeadWhite(true)//Флаг первого хода с головы для белых
  , m_bFirstMoveFromHeadBlack(true)//Флаг первого хода с головы для черных
  , m_iCountMoveFromHead(0)//Количество ходов сделаных с головы
  , m_iWhiteCount(360) //Количество треугольников до конца игры для белых
  , m_iBlackCount(360) //Количество треугольников до конца игры для черных
  , m_strHintString("") //Текущая строка с подсказкой



{
    QPalette mainPalBoard;
    //QPixmap pixBoard(":/emptyboard1.png");
    QPixmap pixBoard(pixStr);
    mainPalBoard.setBrush(backgroundRole(), QBrush(pixBoard));
    setPalette(mainPalBoard);
    //Подгоняем размер виджета под размер картинки
    setFixedSize(pixBoard.width(),pixBoard.height());
    //resize(803, 709);
    move(0, 0);
    setAutoFillBackground(true);

    //Создаем объекты треугольников и помещаем их в соотв. векторы
    for (int inx=0; inx < 25; inx++){

        //Создаем объекты белых треугольников
        vecTriWhiteFishs[inx] = new Triangle(true, this);

        //Создаем для треугольников объекты отметок вариантов ходов (зеленые кружки) для белых треугольников
        vecTriWhiteFishs[inx]->wgtVarMove = new VariantMoves(this);
        vecTriWhiteFishs[inx]->wgtVarMove->setVisible(false);

        //Создаем для треугольников объекты отметок вариантов ходов (зеленые треугольники с круглым основанием) для белых треугольников
        vecTriWhiteFishs[inx]->wgtVarMoveTri = new VariantMovesTri(this);
        vecTriWhiteFishs[inx]->wgtVarMoveTri->setVisible(false);

        //Создаем объекты черных треугольников
        vecTriBlackFishs[inx] = new Triangle(false, this);


        //Создаем для треугольников объекты отметок вариантов ходов для черных треугольников
        vecTriBlackFishs[inx]->wgtVarMove = new VariantMoves(this);
        vecTriBlackFishs[inx]->wgtVarMove->setVisible(false);

        //Создаем для треугольников объекты отметок вариантов ходов (зеленые треугольники с круглым основанием) для белых треугольников
        vecTriBlackFishs[inx]->wgtVarMoveTri = new VariantMovesTri(this);
        vecTriBlackFishs[inx]->wgtVarMoveTri->setVisible(false);
    }

    for (int i = 0; i<15; i++)
    {
        //Создаем 15 объектов белых фишек и добавляем их в стек 0-го белого треугольника
        Fish* pWhiteFish = new Fish(true, this);
        vecTriWhiteFishs[0]->stkFishs.push(pWhiteFish);

        //Создаем 15 объектов черных фишек и добавляем их в стек 0-го черного треугольника
        Fish* pBlackFish = new Fish(false, this);
        vecTriBlackFishs[0]->stkFishs.push(pBlackFish);
    }

    //Для отладки заполняем стеки всех треугольников фишками
//    for (int inx=1; inx < 25; inx++)
//    {
//        for (int i = 0; i<15; i++)
//        {
//            //Создаем 15 белых фишек и добавляем их в стек i-го белого треугольника
//            Fish* pWhiteFish = new Fish(true, this);
//            vecTriWhiteFishs[inx]->stkFishs.push(pWhiteFish);

//            //Создаем 15 черных фишек и добавляем их в стек i-го черного треугольника
//            Fish* pBlackFish = new Fish(false, this);
//            vecTriBlackFishs[inx]->stkFishs.push(pBlackFish);
//        }
//    }

    //Обновляем состояние доски
    UpdateState();


    //Для белых
    //создаем объекты кубиков - два основных,
    //еще два, чтобы показывать дубли, когда они выпадают
    //и добавляем их в вектор
    for (int i = 0; i<4; i++)
    {
      Cube* pCube = new Cube(i+1, this);
      vectorCubeWhite.push_back(pCube);
    }

    //Для черных
    //создаем объекты кубиков - два основных,
    //еще два, чтобы показывать дубли, когда они выпадают
    //и добавляем их в вектор
    for (int i = 0; i<4; i++)
    {
      Cube* pCube = new Cube(i+1, this);
      vectorCubeBlack.push_back(pCube);
    }

    //Помещаем кубики на их постоянные позиции
    //для белых
     vectorCubeWhite[2]->move(455, 300);
     vectorCubeWhite[2]->setVisible(false);

     vectorCubeWhite[0]->move(505, 300);
     vectorCubeWhite[0]->setVisible(false);

     vectorCubeWhite[1]->move(555, 300);
     vectorCubeWhite[1]->setVisible(false);

     vectorCubeWhite[3]->move(605, 300);
     vectorCubeWhite[3]->setVisible(false);

    //Помещаем кубики на их постоянные позиции
    //для черных
    vectorCubeBlack[2]->move(150, 300);
    vectorCubeBlack[2]->setVisible(false);

    vectorCubeBlack[0]->move(200, 300);
    vectorCubeBlack[0]->setVisible(false);

    vectorCubeBlack[1]->move(250, 300);
    vectorCubeBlack[1]->setVisible(false);

    vectorCubeBlack[3]->move(300, 300);
    vectorCubeBlack[3]->setVisible(false);

    setMouseTracking(true);

}

Board::~Board()
{
   saveGame();
}

void Board::hideAllCubes(void)
{
    vectorCubeWhite[0]->setVisible(false);
    vectorCubeWhite[1]->setVisible(false);
    vectorCubeWhite[2]->setVisible(false);
    vectorCubeWhite[3]->setVisible(false);
    vectorCubeBlack[0]->setVisible(false);
    vectorCubeBlack[1]->setVisible(false);
    vectorCubeBlack[2]->setVisible(false);
    vectorCubeBlack[3]->setVisible(false);
}


bool Board::MoveFish(Triangle* fromTri, Triangle* toTri)
{
    toTri->stkFishs.push(fromTri->stkFishs.pop());

    UpdateState();
    return true;
}

//Вычисляем количество неиспользованных ходов при ходе дублем
//Используется в функции showPossibleWhiteMoves
int Board::getCountFishMovedCubesForDouble(const bool &bIsWhite)
{
    int resultInt=0;
    //Для белых кубиков
    if (bIsWhite)
    {
        for (int i=0;i<4;i++)
        {
          if (!vectorCubeWhite[i]->getFishMoved())
          {
                resultInt++;
          }
        }
    }
    else //Для черных кубиков
    {
        for (int i=0;i<4;i++)
        {
          if (!vectorCubeBlack[i]->getFishMoved())
          {
                resultInt++;
          }
        }
    }
    return resultInt;
}


//Подсчитать количество оставшихся ходов
int Board::countRemainingMoves(const bool &bIsWhite)
{
    int resultInt=0;
    if (bIsWhite)
    {
        //Перебираем все белые треугольники
        for (int inx=0; inx < 25; inx++)
        {
            if (vecTriWhiteFishs[inx]->wgtVarMove->isVisible()) ++resultInt;
        }

    } else
    {
        //Перебираем все черные треугольники
        for (int inx=0; inx < 25; inx++)
        {
            if (vecTriBlackFishs[inx]->wgtVarMove->isVisible()) ++resultInt;
        }
    }
    return resultInt;
}

//True - все фишки в доме
bool Board::inHouse(const bool &bIsWhite)
{
    bool resultBool=true;
    //Для белых
    if (bIsWhite)
    {
        //Перебираем все белые треугольники до дома
        for (int inx=0; inx < 18; inx++)
        {
            //Если хотябы в одном треугольнике есть фишки, возвращаем false
            if (vecTriWhiteFishs[inx]->stkFishs.size()>0)
            {
                resultBool=false;
            }
        }
    } else //Для черных
    {
        //Перебираем все белые треугольники до дома
        for (int inx=0; inx < 18; inx++)
        {
            //Если хотябы в одном треугольнике есть фишки, возвращаем false
            if (vecTriBlackFishs[inx]->stkFishs.size()>0)
            {
                resultBool=false;
            }
        }
    }
    return resultBool;
}

QString Board::isMars(bool bIsWhite)
{
    QString resultStr="";
    if (bIsWhite)
    {
        if (vecTriWhiteFishs[24]->stkFishs.size()==15)
        {
            //Домашний марс - У черных ни одной фишки не выброшено и все черные в доме
            if ((vecTriBlackFishs[24]->stkFishs.size()==0) && inHouse(false))
            {
                resultStr="Домашний Марс";
            }
            //Кокс - У черных ни одной фишки не выброшено
            //и есть хоть одна фишка в первой четверти игрового поля
            else if (vecTriBlackFishs[24]->stkFishs.size()==0 && !inHouse(false) &&
                     ((vecTriBlackFishs[0]->stkFishs.size()>0) ||
                      (vecTriBlackFishs[1]->stkFishs.size()>0) ||
                      (vecTriBlackFishs[2]->stkFishs.size()>0) ||
                      (vecTriBlackFishs[3]->stkFishs.size()>0) ||
                      (vecTriBlackFishs[4]->stkFishs.size()>0) ||
                      (vecTriBlackFishs[5]->stkFishs.size()>0)))
            {
                resultStr="Марс - Кокс";
            }
            //У черных ни одной фишки не выброшено - Марс
            else if (vecTriBlackFishs[24]->stkFishs.size()==0 && !inHouse(false))
            {
                resultStr="Марс";
            }
        }
    } else
    {
        if (vecTriBlackFishs[24]->stkFishs.size()==15)
        {
            //Домашний марс - У белых ни одной фишки не выброшено и все белые в доме
            if ((vecTriWhiteFishs[24]->stkFishs.size()==0)  && inHouse(true))
            {
                resultStr="Домашний Марс";
            }
            //Кокс - У белых ни одной фишки не выброшено
            //и есть хоть одна фишка в первой четверти игрового поля
            else if (vecTriWhiteFishs[24]->stkFishs.size()==0 && !inHouse(false) &&
                     ((vecTriWhiteFishs[0]->stkFishs.size()>0) ||
                      (vecTriWhiteFishs[1]->stkFishs.size()>0) ||
                      (vecTriWhiteFishs[2]->stkFishs.size()>0) ||
                      (vecTriWhiteFishs[3]->stkFishs.size()>0) ||
                      (vecTriWhiteFishs[4]->stkFishs.size()>0) ||
                      (vecTriWhiteFishs[5]->stkFishs.size()>0)))
            {
                resultStr="Марс - Кокс";
            }
            //У белых ни одной фишки не выброшено - Марс
            else if (vecTriWhiteFishs[24]->stkFishs.size()==0  && !inHouse(true))
            {
                resultStr="Марс";

            }
        }
    }
    return resultStr;
}

void Board::checkEndGame()
{
    if (vecTriWhiteFishs[24]->stkFishs.size()==15)
    {
        strToDebug("(ShowPossibleMovesForAll) Игрок "+firstGamerName+" выиграл!");
        strToHint("Победа игрока "+firstGamerName+"! "+isMars(true));
//        m_bMoveWhiteFish=false;
//        m_bMoveBlackFish=false;
//        setCursor(Qt::ArrowCursor);
        emit sendEndGame(firstGamerName, isMars(true));
    }
    if (vecTriBlackFishs[24]->stkFishs.size()==15)
    {
        strToDebug("(ShowPossibleMovesForAll) Игрок "+secondGamerName+" выиграл!");
        strToHint("Победа игрока "+secondGamerName+"! "+isMars(false));
//        m_bMoveWhiteFish=false;
//        m_bMoveBlackFish=false;
//        setCursor(Qt::ArrowCursor);
        emit sendEndGame(secondGamerName, isMars(false));
    }
}

//Показать возможные ходы фишек (треугольников)
void Board::showPossibleMovesForAll(const bool &bIsWhite)
{
    if (bIsWhite)
    {
        //Перебираем все белые треугольники
        for (int inx=0; inx < 25; inx++)
        {
            if (vecTriWhiteFishs[inx]->stkFishs.size()>0)
            {
                showPossibleWhiteMoves(inx, true);
            }
        }
        if (countRemainingMoves(true)==0)
        {
            strToDebug("(ShowPossibleMovesForAll) Доступных ходов больше нет!");
            strToDebug("(ShowPossibleMovesForAll) Все ходы для игрока " + firstGamerName + " сделаны. Передача кубиков.");
            strToHint("Игрок " + firstGamerName + ", у Вас ходов больше нет. Игрок "+secondGamerName+" бросайте кубики.");

            m_bMoveWhiteFish=false;
            m_RollTheCubesForWhiteFish=false;
            setCursor(QCursor(QPixmap(":/cursor_two_cubes_3232.png")));
            strToDebug("(ShowPossibleMovesForAll) setCursor cursor_two_cubes_3232.png");

        } else  strToDebug("(ShowPossibleMovesForAll) Осталось "+QString::number(countRemainingMoves(true))+" возможных ходов.");

        checkEndGame();

    } else
    {
        //Перебираем все черные треугольники
        for (int inx=0; inx < 25; inx++)
        {
            if (vecTriBlackFishs[inx]->stkFishs.size()>0)
            {
               showPossibleBlackMoves(inx, true);
            }
        }
        if (countRemainingMoves(false)==0)
        {
            strToDebug("(ShowPossibleMovesForAll) Доступных ходов больше нет!");
            strToDebug("(ShowPossibleMovesForAll) Все ходы для игрока " + secondGamerName + " сделаны. Передача кубиков.");
            strToHint("Игрок " + secondGamerName + ", у Вас ходов больше нет. Игрок "+firstGamerName+" бросайте кубики.");
            m_bMoveBlackFish=false;
            m_RollTheCubesForWhiteFish=true;
            setCursor(QCursor(QPixmap(":/cursor_two_cubes_3232.png")));
            strToDebug("(ShowPossibleMovesForAll) setCursor cursor_two_cubes_3232.png");

        } else  strToDebug("(ShowPossibleMovesForAll) Осталось "+QString::number(countRemainingMoves(true))+" возможных ходов.");

        checkEndGame();
    }
}

//Все в доме
//И перед выбранным индексом больше нет фишек
bool Board::inHouseNotFishsBefore(const int &inx, bool bIsWhite)
{
    bool resultBool=true;
    //Для Белых
    if (bIsWhite)
   {
            //Перебираем все белые треугольники в доме до индекса inx
            for (int i=0; i < inx; i++)
            {
                //Если хотябы в одном треугольнике есть фишки, возвращаем false
                if (vecTriWhiteFishs[i]->stkFishs.size()>0)
                {
                    resultBool=false;
                }
            }
    }
     else //Для Черных
    {
            //Перебираем все белые треугольники в доме до индекса inx
            for (int i=0; i < inx; i++)
            {
                //Если хотябы в одном треугольнике есть фишки, возвращаем false
                if (vecTriBlackFishs[i]->stkFishs.size()>0)
                {
                    resultBool=false;
                }
            }
    }
  return resultBool;
}


//Возвращает true если за фишкой с индексом inx есть фишка соперника
bool Board::existsOpponentFishAfter(const int &inx, const bool &bIsWhite)
{
    //Белые   0   1   2   3   4   5   6   7   8   9   10   11   12   13   14   15   16   17   18   19   20   21   22   23
    //Черные  12  13  14  15  16  17  18  19  20  21  22   23   0    1    2    3    4    5    6    7    8    9    10   11

    bool resultBool=false;

    if (bIsWhite)
    {
        if ((inx >= 0) && (inx <= 11))
        {
            for (int i=inx+1; i <= 11; i++)
            {
                if (vecTriBlackFishs[i+12]->stkFishs.size()>0)
                {
                    resultBool=true;
                }
            }
        } else if ((inx >= 12) && (inx <= 23))
        {
            for (int i=inx+1; i <= 23; i++)
            {
                if (vecTriBlackFishs[i-12]->stkFishs.size()>0)
                {
                    resultBool=true;
                }
            }
            for (int i=12; i <= 23; i++)
            {
                if (vecTriBlackFishs[i]->stkFishs.size()>0)
                {
                    resultBool=true;
                }
            }
        }
    } else
    {
        if ((inx >= 0) && (inx <= 11))
        {
            for (int i=inx+1; i <= 11; i++)
            {
                if (vecTriWhiteFishs[i+12]->stkFishs.size()>0)
                {
                    resultBool=true;
                }
            }
        } else if ((inx >= 12) && (inx <= 23))
        {
            for (int i=inx+1; i <= 23; i++)
            {
                if (vecTriWhiteFishs[i-12]->stkFishs.size()>0)
                {
                    resultBool=true;
                }
            }
            for (int i=12; i <= 23; i++)
            {
                if (vecTriWhiteFishs[i]->stkFishs.size()>0)
                {
                    resultBool=true;
                }
            }
        }
    }
    return resultBool;
}


//Возвращает true если мы ходим фишкой на треугольник с
//индексом inx, и при этом создается ЗАТОР из шести фишек
//который не дает противнику пройти в дом
//И ни одной фишки противника нет за индексом inx (за этим ЗАТОРОМ)
bool Board::sixFishsInARow(const int &inx, const bool &bIsWhite)
{
    bool resultBool=false;
    //Для Белых
    if (bIsWhite)
   {
       if (!existsOpponentFishAfter(inx, true)/* && !inHouse(true)*/ && inx!=24)
        {

            int nCountFishs=0;
            //Перебираем 5 белых треугольников перед индексом inx
            for (int i=inx-5; i < inx; i++)
            {
                //Проверяем что индекс i НЕ ОТРИЦАТЕЛЬНЫЙ!
                //Проверяем что индекс 0 <= i <= 23!
                if ((i>=0) && (i<=23))
                    //Считаем белые фишки до индекса inx
                    if (vecTriWhiteFishs[i]->stkFishs.size()>0)
                    {
                        ++nCountFishs;
                    } else //Если в треугольнике фишек нет, то сбрасываем счетчик в 0
                    {
                        nCountFishs=0;
                    }
            }
            //Перебираем 5 белых треугольников после индекса inx
            for (int i=inx+1; i < inx+6; i++)
            {
                //Проверяем что индекс i НЕ ОТРИЦАТЕЛЬНЫЙ!
                //Проверяем что индекс 0 <= i <= 23!
                if ((i>=0) && (i<=23))
                    //Считаем белые фишки после индекса inx
                    if (vecTriWhiteFishs[i]->stkFishs.size()>0)
                    {
                        if (inx+5<=23) ++nCountFishs;

                    } else //Если в треугольнике фишек нет, то сбрасываем счетчик в 0
                    {
                        //Если 5 фишек ПОДРЯД не набралось
                        if (nCountFishs<5) nCountFishs=0;
                    }
            }
            if (nCountFishs>=5)
            {
                resultBool=true;
                strToDebug("  (sixFishsInARow) Если игрок " + firstGamerName+ " пойдет на индекс " +QString::number(inx)+" то будет ЗАТОР!");
            }
        }


    } else //Для Черных
    {
               if (!existsOpponentFishAfter(inx, false) /* && !inHouse(false)*/  && inx!=24)
               {

                   int nCountFishs=0;
                   //Перебираем 5 черных треугольников перед индексом inx
                   for (int i=inx-5; i < inx; i++)
                   {
                       //Проверяем что индекс i НЕ ОТРИЦАТЕЛЬНЫЙ!
                       //Проверяем что индекс 0 <= i <= 23!
                       if ((i>=0) && (i<=23))
                           //Считаем черные фишки до индекса inx
                           if (vecTriBlackFishs[i]->stkFishs.size()>0)
                           {
                               ++nCountFishs;
                           } else //Если в треугольнике фишек нет, то сбрасываем счетчик в 0
                           {
                               nCountFishs=0;
                           }
                   }
                   //Перебираем 5 черных треугольников после индекса inx
                   for (int i=inx+1; i < inx+6; i++)
                   {
                       //Проверяем что индекс i НЕ ОТРИЦАТЕЛЬНЫЙ!
                       //Проверяем что индекс 0 <= i <= 23!
                       if ((i>=0) && (i<=23))
                           //Считаем черные фишки после индекса inx
                           if (vecTriBlackFishs[i]->stkFishs.size()>0)
                           {
                               if (inx+5<=23) ++nCountFishs;

                           } else //Если в треугольнике фишек нет, то сбрасываем счетчик в 0
                           {
                               //Если 5 фишек ПОДРЯД не набралось
                               if (nCountFishs<5) nCountFishs=0;
                           }
                   }
                   if (nCountFishs>=5)
                   {
                       resultBool=true;
                       strToDebug("  (sixFishsInARow) Если игрок " + secondGamerName+ " пойдет на индекс " +QString::number(inx)+" то будет ЗАТОР!");
                   }
               }
    }

    return resultBool;
}


//Показать возможные ходы для белой фишки (треугольника), выбранной для хода
//bForAll=true - для всех треугольников, bForAll=false - только для одного (показывать или нет wgtVarMoveTri)
void Board::showPossibleWhiteMoves(const int &inx, const bool &bForAll)
{
    //Получаем значения кубиков
    int valCube0 = vectorCubeWhite[0]->getValue();
    int valCube1 = vectorCubeWhite[1]->getValue();

    //Если выпал дубль
    if (valCube0 == valCube1)
    {
        //Если снимаем с головы
        //и еще не сделано ни одного хода с головы и это не ход с головы в начале игры
        if (((inx==0) && (m_iCountMoveFromHead==0) && (!m_bFirstMoveFromHeadWhite))

                //Если снимаем с головы
                //и еще сделано ни одного хода с головы, и это ход с головы в начале игры, и значение кубика 1 или 2 или 5
                || ((inx==0) && (m_iCountMoveFromHead==0) && m_bFirstMoveFromHeadWhite && ((valCube0==1) || (valCube0==2) || (valCube0==5)))

                    //Если снимаем с головы
                    //и еще сделано <= одного хода с головы, и это ход с головы в начале игры, и значение кубика 3 или 4 или 6
                    || ((inx==0) && (m_iCountMoveFromHead<=1) && m_bFirstMoveFromHeadWhite && ((valCube0==3) || (valCube0==4) || (valCube0==6)))

                        //Или если ходим не с головы
                        || (inx!=0)
                        )
        {

            //(Если хотя бы для одного из кубиков с 0-м, 1-м, 2-м, 3-м индексом ход еще не сделан) и
            //((все в доме) и (его значение + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение + индекс с которого производится ход <24))
            //Проверяем что треугольник, в который хотим сделать ход, не занят соперником
            if ((getCountFishMovedCubesForDouble(true)>0) &&
                    (!sixFishsInARow(inx + valCube0, true)) &&
                    ((inHouse(true) && (inx + valCube0 < 25)) || (!inHouse(true) && (inx + valCube0 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0, true)))
            {
                    vecTriWhiteFishs[inx + valCube0]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriWhiteFishs[inx + valCube0]->wgtVarMoveTri->setVisible(true);
            }
            //Если количество оставшихся ходов >=2
            //((все в доме) и (его значение*2 + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение*2 + индекс с которого производится ход <24))
            //Проверяем что треугольник, в который хотим сделать ход, не занят соперником
            //и 1-й треугольник (лунка), через который будет делаться ход тоже не занят!
            if ((getCountFishMovedCubesForDouble(true)>=2) &&
                (!sixFishsInARow(inx + valCube0, true) && !sixFishsInARow(inx + valCube0*2, true)) &&
                 ((inHouse(true) && (inx + valCube0*2 < 25)) || (!inHouse(true) && (inx + valCube0*2 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0*2, true)  && !opponentFishOccupyTri(inx + valCube0, true)))
            {
                    vecTriWhiteFishs[inx + valCube0*2]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriWhiteFishs[inx + valCube0*2]->wgtVarMoveTri->setVisible(true);
            }
            //Если количество оставшихся ходов >=3
            //((все в доме) и (его значение*3 + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение*3 + индекс с которого производится ход <24))
            //Проверяем что треугольник, в который хотим сделать ход, не занят соперником
            //и все треугольники (лунки), через которые будет делаться ход тоже не заняты!
            if ((getCountFishMovedCubesForDouble(true)>=3) &&
                (!sixFishsInARow(inx + valCube0, true) && !sixFishsInARow(inx + valCube0*2, true) && !sixFishsInARow(inx + valCube0*3, true)) &&
               ((inHouse(true) && (inx + valCube0*3 < 25)) || (!inHouse(true) && (inx + valCube0*3 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0*3, true)  && !opponentFishOccupyTri(inx + valCube0, true) && !opponentFishOccupyTri(inx + valCube0*2, true)))
            {
                    vecTriWhiteFishs[inx + valCube0*3]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriWhiteFishs[inx + valCube0*3]->wgtVarMoveTri->setVisible(true);
            }
            //Если количество оставшихся ходов =4
            //((все в доме) и (его значение*4 + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение*4 + индекс с которого производится ход <24))
            //Проверяем что треугольник, в который хотим сделать ход, не занят соперником
            //и все треугольники (лунки), через которые будет делаться ход тоже не заняты!
            if ((getCountFishMovedCubesForDouble(true)==4) &&
                (!sixFishsInARow(inx + valCube0, true) && !sixFishsInARow(inx + valCube0*2, true) && !sixFishsInARow(inx + valCube0*3, true)  &&  !sixFishsInARow(inx + valCube0*4, true)) &&
               ((inHouse(true) && (inx + valCube0*4 < 25)) || (!inHouse(true) && (inx + valCube0*4 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0*4, true) && !opponentFishOccupyTri(inx + valCube0, true) && !opponentFishOccupyTri(inx + valCube0*2, true) && !opponentFishOccupyTri(inx + valCube0*3, true)))
            {
                    vecTriWhiteFishs[inx + valCube0*4]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriWhiteFishs[inx + valCube0*4]->wgtVarMoveTri->setVisible(true);
            }

            //Если для кубика с i-м индексом ход еще не сделан
            //и (все в доме) и (его значение + индекс с которого производится ход > 24)
            //И перед выбранным индексом в доме больше нет фишек
            for (int i=0;i<4;i++)
                if ((!vectorCubeWhite[i]->getFishMoved()) && inHouse(true) && (inx + valCube0 > 24) && inHouseNotFishsBefore(inx, true))
                {
                    //Показывем виджет возможного хода
                    vecTriWhiteFishs[24]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriWhiteFishs[24]->wgtVarMoveTri->setVisible(true);
                    //Выставляем для кубика признак "Кандидат на выход"
                    vectorCubeWhite[i]->candidateForOut=true;
                    strToDebug("(showPossibleWhiteMoves) Кубик vectorCubeWhite["+QString::number(i)+"]: "+ QString::number(vectorCubeWhite[i]->getValue())+" кандидат на выход!");
                }
        }
    } else //Если выпал НЕ дубль
    {
        //Если снимаем с головы
        //и еще не сделано ни одного хода с головы
        if (((inx==0) && (m_iCountMoveFromHead==0))
        //Или если ходим не с головы
                || (inx!=0))
        {
            //Если для кубика с 0-м индексом ход еще не сделан
            //((все в доме) и (его значение + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение + индекс с которого производится ход <24))
            //и треугольник, в который хотим сделать ход, не занят соперником
            if ((!vectorCubeWhite[0]->getFishMoved()) &&
                    (!sixFishsInARow(inx + valCube0, true)) &&
                    ((inHouse(true) && (inx + valCube0 < 25)) || (!inHouse(true) && (inx + valCube0 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0, true)))
            {
                    //Показывем виджет возможного хода
                    vecTriWhiteFishs[inx + valCube0]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriWhiteFishs[inx + valCube0]->wgtVarMoveTri->setVisible(true);
            }
            //Если для кубика с 1-м индексом ход еще не сделан
            //((все в доме) и (его значение + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение + индекс с которого производится ход <24))
            //и треугольник, в который хотим сделать ход, не занят соперником
            if ((!vectorCubeWhite[1]->getFishMoved()) &&
                    (!sixFishsInARow(inx + valCube1, true)) &&
                    ((inHouse(true) && (inx + valCube1 < 25)) || (!inHouse(true) && (inx + valCube1 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube1, true)))
            {
                    //Показывем виджет возможного хода
                    vecTriWhiteFishs[inx + valCube1]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriWhiteFishs[inx + valCube1]->wgtVarMoveTri->setVisible(true);
            }
            //Если для кубиков с 0-м и 1-м индексом ход еще не сделан
            //((все в доме) и (сумма значений кубиков с 0-м и 1-м + индекс с которого производится ход <25))
            //или ((не все в доме) и (сумма значений кубиков с 0-м и 1-м + индекс с которого производится ход <24))
            //И что треугольник, в который хотим сделать ход, не занят соперником
            //и хотя бы один треугольник(лунка) через которые будет делаться ход тоже не заняты!
            if ((!vectorCubeWhite[0]->getFishMoved()) && (!vectorCubeWhite[1]->getFishMoved())
                    && (!sixFishsInARow(inx + valCube0 + valCube1, true))
                    && ((inHouse(true) && (inx + valCube0 + valCube1 < 25)) || (!inHouse(true) && (inx + valCube0 + valCube1 < 24)))
                    && (!opponentFishOccupyTri(inx + valCube0 + valCube1, true) && (!opponentFishOccupyTri(inx + valCube0, true) || !opponentFishOccupyTri(inx + valCube1, true)))
                    )
            {
                    //Показывем виджет возможного хода
                    vecTriWhiteFishs[inx + valCube0 + valCube1]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriWhiteFishs[inx + valCube0 + valCube1]->wgtVarMoveTri->setVisible(true);
            }

            //Если для кубика с i-м индексом ход еще не сделан
            //и (все в доме) и (его значение + индекс с которого производится ход > 24)
            //И перед выбранным индексом в доме больше нет фишек
            for (int i=0;i<2;i++)
                if ((!vectorCubeWhite[i]->getFishMoved()) && inHouse(true) && (inx + vectorCubeWhite[i]->getValue() > 24) && inHouseNotFishsBefore(inx, true))
                {
                    //Показывем виджет возможного хода
                    vecTriWhiteFishs[24]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriWhiteFishs[24]->wgtVarMoveTri->setVisible(true);
                    //Выставляем для кубика признак "Кандидат на выход"
                    vectorCubeWhite[i]->candidateForOut=true;
                    strToDebug("(showPossibleWhiteMoves) Кубик vectorCubeWhite["+QString::number(i)+"]: "+
                               QString::number(vectorCubeWhite[i]->getValue())+" кандидат на выход!");
                }
        }
    }
}

//Показать возможные ходы для черной фишки (треугольника), выбранной для хода
//bForAll=true - для всех треугольников, bForAll=false - только для одного (показывать или нет wgtVarMoveTri)
void Board::showPossibleBlackMoves(const int &inx, const bool &bForAll)
{
    //Получаем значения кубиков
    int valCube0 = vectorCubeBlack[0]->getValue();
    int valCube1 = vectorCubeBlack[1]->getValue();

    //Если выпал дубль
    if (valCube0 == valCube1)
    {
        //Если снимаем с головы
        //и еще не сделано ни одного хода с головы и это не ход с головы в начале игры
        if (((inx==0) && (m_iCountMoveFromHead==0) && (!m_bFirstMoveFromHeadBlack))

                //Если снимаем с головы
                //и еще сделано ни одного хода с головы, и это ход с головы в начале игры, и значение кубика 1 или 2 или 5
                || ((inx==0) && (m_iCountMoveFromHead==0) && m_bFirstMoveFromHeadBlack && ((valCube0==1) || (valCube0==2) || (valCube0==5)))

                    //Если снимаем с головы
                    //и еще сделано <= одного хода с головы, и это ход с головы в начале игры, и значение кубика 3 или 4 или 6
                    || ((inx==0) && (m_iCountMoveFromHead<=1) && m_bFirstMoveFromHeadBlack && ((valCube0==3) || (valCube0==4) || (valCube0==6)))

                        //Или если ходим не с головы
                        || (inx!=0)
                        )
        {

            //(Если хотя бы для одного из кубиков с 0-м, 1-м, 2-м, 3-м индексом ход еще не сделан) и
            //((все в доме) и (его значение + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение + индекс с которого производится ход <24))
            //Проверяем что треугольник, в который хотим сделать ход, не занят соперником
            if ((getCountFishMovedCubesForDouble(false)>0) &&
                (!sixFishsInARow(inx + valCube0, false)) &&
                    ((inHouse(false) && (inx + valCube0 < 25)) || (!inHouse(false) && (inx + valCube0 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0, false)))
            {
                    vecTriBlackFishs[inx + valCube0]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriBlackFishs[inx + valCube0]->wgtVarMoveTri->setVisible(true);
            }
            //Если количество оставшихся ходов >=2
            //((все в доме) и (его значение*2 + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение*2 + индекс с которого производится ход <24))
            //Проверяем что треугольник, в который хотим сделать ход, не занят соперником
            //и 1-й треугольник (лунка), через который будет делаться ход тоже не занят!
            if ((getCountFishMovedCubesForDouble(false)>=2) &&
                (!sixFishsInARow(inx + valCube0, false)) && (!sixFishsInARow(inx + valCube0*2, false)) &&
                 ((inHouse(false) && (inx + valCube0*2 < 25)) || (!inHouse(false) && (inx + valCube0*2 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0*2, false)  && !opponentFishOccupyTri(inx + valCube0, false)))
            {
                    vecTriBlackFishs[inx + valCube0*2]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriBlackFishs[inx + valCube0*2]->wgtVarMoveTri->setVisible(true);
            }
            //Если количество оставшихся ходов >=3
            //((все в доме) и (его значение*3 + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение*3 + индекс с которого производится ход <24))
            //Проверяем что треугольник, в который хотим сделать ход, не занят соперником
            //и все треугольники (лунки), через которые будет делаться ход тоже не заняты!
            if ((getCountFishMovedCubesForDouble(false)>=3) &&
                (!sixFishsInARow(inx + valCube0, false)) && (!sixFishsInARow(inx + valCube0*2, false)) && (!sixFishsInARow(inx + valCube0*3, false)) &&
               ((inHouse(false) && (inx + valCube0*3 < 25)) || (!inHouse(false) && (inx + valCube0*3 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0*3, false)  && !opponentFishOccupyTri(inx + valCube0, false) && !opponentFishOccupyTri(inx + valCube0*2, false)))
            {
                    vecTriBlackFishs[inx + valCube0*3]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriBlackFishs[inx + valCube0*3]->wgtVarMoveTri->setVisible(true);
            }
            //Если количество оставшихся ходов =4
            //((все в доме) и (его значение*4 + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение*4 + индекс с которого производится ход <24))
            //Проверяем что треугольник, в который хотим сделать ход, не занят соперником
            //и все треугольники (лунки), через которые будет делаться ход тоже не заняты!
            if ((getCountFishMovedCubesForDouble(false)==4) &&
                (!sixFishsInARow(inx + valCube0, false)) && (!sixFishsInARow(inx + valCube0*2, false)) && (!sixFishsInARow(inx + valCube0*3, false)) && (!sixFishsInARow(inx + valCube0*4, false)) &&
               ((inHouse(false) && (inx + valCube0*4 < 25)) || (!inHouse(false) && (inx + valCube0*4 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0*4, false) && !opponentFishOccupyTri(inx + valCube0, false) && !opponentFishOccupyTri(inx + valCube0*2, false) && !opponentFishOccupyTri(inx + valCube0*3, false)))
            {
                    vecTriBlackFishs[inx + valCube0*4]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriBlackFishs[inx + valCube0*4]->wgtVarMoveTri->setVisible(true);
            }

            //Если для кубика с i-м индексом ход еще не сделан
            //и (все в доме) и (его значение + индекс с которого производится ход > 24)
            //И перед выбранным индексом в доме больше нет фишек
            for (int i=0;i<4;i++)
                if ((!vectorCubeBlack[i]->getFishMoved()) && inHouse(false) && (inx + valCube0 > 24) && inHouseNotFishsBefore(inx, false))
                {
                    //Показывем виджет возможного хода
                    vecTriBlackFishs[24]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriBlackFishs[24]->wgtVarMoveTri->setVisible(true);
                    //Выставляем для кубика признак "Кандидат на выход"
                    vectorCubeBlack[i]->candidateForOut=true;
                    strToDebug("(showPossibleBlackMoves) Кубик vectorCubeBlack["+QString::number(i)+"]: "+ QString::number(vectorCubeBlack[i]->getValue())+" кандидат на выход!");
                }
        }
    } else //Если выпал НЕ дубль
    {
        //Если снимаем с головы
        //и еще не сделано ни одного хода с головы
        if (((inx==0) && (m_iCountMoveFromHead==0))
        //Или если ходим не с головы
                || (inx!=0))
        {
            //Если для кубика с 0-м индексом ход еще не сделан
            //((все в доме) и (его значение + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение + индекс с которого производится ход <24))
            //и треугольник, в который хотим сделать ход, не занят соперником
            if ((!vectorCubeBlack[0]->getFishMoved()) &&
                    (!sixFishsInARow(inx + valCube0, false)) &&
                    ((inHouse(false) && (inx + valCube0 < 25)) || (!inHouse(false) && (inx + valCube0 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube0, false)))
            {
                    //Показывем виджет возможного хода
                    vecTriBlackFishs[inx + valCube0]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriBlackFishs[inx + valCube0]->wgtVarMoveTri->setVisible(true);
            }
            //Если для кубика с 1-м индексом ход еще не сделан
            //((все в доме) и (его значение + индекс с которого производится ход <25))
            //или ((не все в доме) и (его значение + индекс с которого производится ход <24))
            //и треугольник, в который хотим сделать ход, не занят соперником
            if ((!vectorCubeBlack[1]->getFishMoved()) &&
                    (!sixFishsInARow(inx + valCube1, false)) &&
                    ((inHouse(false) && (inx + valCube1 < 25)) || (!inHouse(false) && (inx + valCube1 < 24))) &&
                    (!opponentFishOccupyTri(inx + valCube1, false)))
            {
                    //Показывем виджет возможного хода
                    vecTriBlackFishs[inx + valCube1]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriBlackFishs[inx + valCube1]->wgtVarMoveTri->setVisible(true);
            }
            //Если для кубиков с 0-м и 1-м индексом ход еще не сделан
            //((все в доме) и (сумма значений кубиков с 0-м и 1-м + индекс с которого производится ход <25))
            //или ((не все в доме) и (сумма значений кубиков с 0-м и 1-м + индекс с которого производится ход <24))
            //И что треугольник, в который хотим сделать ход, не занят соперником
            //и хотя бы один треугольник(лунка) через которые будет делаться ход тоже не заняты!
            if ((!vectorCubeBlack[0]->getFishMoved()) && (!vectorCubeBlack[1]->getFishMoved())
                    && (!sixFishsInARow(inx + valCube0 + valCube1, false))
                    && ((inHouse(false) && (inx + valCube0 + valCube1 < 25)) || (!inHouse(false) && (inx + valCube0 + valCube1 < 24)))
                    && (!opponentFishOccupyTri(inx + valCube0 + valCube1, false) && (!opponentFishOccupyTri(inx + valCube0, false) || !opponentFishOccupyTri(inx + valCube1, false)))
                    )
            {
                    //Показывем виджет возможного хода
                    vecTriBlackFishs[inx + valCube0 + valCube1]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriBlackFishs[inx + valCube0 + valCube1]->wgtVarMoveTri->setVisible(true);
            }

            //Если для кубика с i-м индексом ход еще не сделан
            //и (все в доме) и (его значение + индекс с которого производится ход > 24)
            //И перед выбранным индексом в доме больше нет фишек
            for (int i=0;i<2;i++)
                if ((!vectorCubeBlack[i]->getFishMoved()) && inHouse(false) && (inx + vectorCubeBlack[i]->getValue() > 24) && inHouseNotFishsBefore(inx, false))
                {
                    //Показывем виджет возможного хода
                    vecTriBlackFishs[24]->wgtVarMove->setVisible(true);
                    if (!bForAll) vecTriBlackFishs[24]->wgtVarMoveTri->setVisible(true);
                    //Выставляем для кубика признак "Кандидат на выход"
                    vectorCubeBlack[i]->candidateForOut=true;
                    strToDebug("(showPossibleBlackMoves) Кубик vectorCubeBlack["+QString::number(i)+"]: "+
                               QString::number(vectorCubeBlack[i]->getValue())+" кандидат на выход!");
                }
        }
    }
}



//Скрыть возможные ходы для любых фишек
//Скрываем метки возможных ходов
void Board::hidePossibleMoves(const bool &bIsWhite)
{
    if (bIsWhite)
    {
        //Скрываем возможные ходы для белых фишек
        for (int j=0; j < 25; j++)
        {
            vecTriWhiteFishs[j]->wgtVarMove->setVisible(false);
            vecTriWhiteFishs[j]->wgtVarMoveTri->setVisible(false);
        }
        //Снимаем признак кандидат на выход с белых кубиков
        for (int i=0; i < 4; i++)
            vectorCubeWhite[i]->candidateForOut=false;
    } else
    {
        //Скрываем возможные ходы для черных фишек
        for (int j=0; j < 25; j++)
        {
            vecTriBlackFishs[j]->wgtVarMove->setVisible(false);
            vecTriBlackFishs[j]->wgtVarMoveTri->setVisible(false);
        }
        //Снимаем признак кандидат на выход с черных кубиков
        for (int i=0; i < 4; i++)
            vectorCubeBlack[i]->candidateForOut=false;
    }
}

//Проверяем не занимает ли соперник (оппонент) треугольник по адресу (индексу) inx
bool Board::opponentFishOccupyTri(const int &inx, const bool &bIsWhite)
{

    bool resultBool=false;
    //Белые   0   1   2   3   4   5   6   7   8   9   10   11   12   13   14   15   16   17   18   19   20   21   22   23
    //Черные  12  13  14  15  16  17  18  19  20  21  22   23   0    1    2    3    4    5    6    7    8    9    10   11

    //Для белых
    if (bIsWhite)
    {
        if ((inx >= 0) && (inx <= 11))
        {
            if (vecTriBlackFishs[inx+12]->stkFishs.size()>0)
            {
                strToDebug("(opponentFishOccupyTri) Индекс "+ QString::number(inx)+ " занят черными!");
                resultBool=true;
            }
        } else if ((inx >= 12) && (inx <= 23))
        {
            if (vecTriBlackFishs[inx-12]->stkFishs.size()>0)
            {
                strToDebug("(opponentFishOccupyTri) Индекс "+ QString::number(inx)+ " занят черными!");
                resultBool=true;
            }
        }
    } else //Для черных
    {
        if ((inx >= 0) && (inx <= 11))
        {
            if (vecTriWhiteFishs[inx+12]->stkFishs.size()>0)
            {
                strToDebug("(opponentFishOccupyTri) Индекс "+ QString::number(inx)+ " занят белыми!");
                resultBool=true;
            }
        } else if ((inx >= 12) && (inx <= 23))
        {
            if (vecTriWhiteFishs[inx-12]->stkFishs.size()>0)
            {
                strToDebug("(opponentFishOccupyTri) Индекс "+ QString::number(inx)+ " занят белыми!");
                resultBool=true;
            }
        }
    }

    return resultBool;
}

//Снимаем признак "Выбран для хода" с любой фишки
void Board::deSelectForMoveAll()
{
    for (int inx=0; inx < 25; inx++)
    {
        if (vecTriWhiteFishs[inx]->getSelectedForMove()) vecTriWhiteFishs[inx]->setSelectedForMove(false);
        if (vecTriBlackFishs[inx]->getSelectedForMove()) vecTriBlackFishs[inx]->setSelectedForMove(false);

    }
}

//Возвращает true если какая-то фишка выбрана для хода и false если не выбрана
bool Board::existsSelectedForMove(const bool &bIsWhite)
{
    bool resultBool=false;
    //Для белых фишек
    if (bIsWhite)
    {
        for (int inx=0; inx < 25; inx++)
        {
            if (vecTriWhiteFishs[inx]->getSelectedForMove()) resultBool=true;
        }
    } else //Для черных фишек
    {
        for (int inx=0; inx < 25; inx++)
        {
            if (vecTriBlackFishs[inx]->getSelectedForMove()) resultBool=true;
        }
    }
    return resultBool;
}

//Выбрать(снять выбор) белую фишку (треугольник) для хода
bool Board::selForMoveWhiteFish(const int &x, const int &y)
{
    //True - щелчок мыши нашел белую фишку, False - щелчок мыши не нашел белую фишку
    bool resultBool=false;

    QString resultString="";
    for (int inx=0; inx < 25; inx++){
        for (int i=0; i < vecTriWhiteFishs[inx]->stkFishs.size(); i++)
        {
            if (vecTriWhiteFishs[inx]->stkFishs[i]->geometry().contains(x,y))
            {
                //Щелчок мыши нашел белую фишку
                resultBool=true;

                resultString = "Белая фишка № "+ QString::number(vecTriWhiteFishs[inx]->stkFishs.size()) + " белого треугольника № " + QString::number(inx);
                //Если фишка по которой щелкаем мышкой не помечена для хода
                //и ни одна из фишек не помечена для хода (для того чтобы не пометить для хода сразу несколько фишек)
                if ((!vecTriWhiteFishs[inx]->getSelectedForMove()) && (!existsSelectedForMove(true)))
                {
                        vecTriWhiteFishs[inx]->setSelectedForMove(true);

                        //Скрываем метки возможных ходов
                        hidePossibleMoves(true);
                        //Показываем возможные ходы для белой фишки (треугольника), выбранной для хода
                        showPossibleWhiteMoves(inx, false);
                        resultString += "  выбрана для хода";
                        //strToDebug("(selForMoveWhiteTriFish) ")
                }
                //Если фишка по которой щелкаем мышкой помечена для хода
                else if (vecTriWhiteFishs[inx]->getSelectedForMove())
                {
                    vecTriWhiteFishs[inx]->setSelectedForMove(false);
                    resultString += "  снят выбор для хода";
                    //Скрываем метки возможных ходов
                    hidePossibleMoves(true);
                    showPossibleMovesForAll(true);
                }
            }
        }
    }
    strToDebug("(selForMoveWhiteTriFish) "+resultString);
    return resultBool;
}


//Выбрать(снять выбор) черную фишку (треугольник) для хода
bool Board::selForMoveBlackFish(const int &x, const int &y)
{
    //True - щелчок мыши нашел черную фишку, False - щелчок мыши не нашел черную фишку
    bool resultBool=false;

    QString resultString="";
    for (int inx=0; inx < 25; inx++){
        for (int i=0; i < vecTriBlackFishs[inx]->stkFishs.size(); i++)
        {
            if (vecTriBlackFishs[inx]->stkFishs[i]->geometry().contains(x,y))
            {
                //Щелчок мыши нашел белую фишку
                resultBool=true;

                resultString = "Черная фишка № "+ QString::number(vecTriBlackFishs[inx]->stkFishs.size()) + " черного треугольника № " + QString::number(inx);
                //Если фишка по которой щелкаем мышкой не помечена для хода
                //и ни одна из фишек не помечена для хода (для того чтобы не пометить для хода сразу несколько фишек)
                if ((!vecTriBlackFishs[inx]->getSelectedForMove()) && (!existsSelectedForMove(false)))
                {
                        vecTriBlackFishs[inx]->setSelectedForMove(true);

                        //Скрываем метки возможных ходов
                        hidePossibleMoves(false);
                        //Показываем возможные ходы для белой фишки (треугольника), выбранной для хода
                        showPossibleBlackMoves(inx, false);
                        resultString += "  выбрана для хода";
                        //strToDebug("(selForMoveBlackTriFish) ")
                }
                //Если фишка по которой щелкаем мышкой помечена для хода
                else if (vecTriBlackFishs[inx]->getSelectedForMove())
                {
                    vecTriBlackFishs[inx]->setSelectedForMove(false);
                    resultString += "  снят выбор для хода";
                    //Скрываем метки возможных ходов
                    hidePossibleMoves(false);
                    showPossibleMovesForAll(false);
                }
            }
        }
    }
    strToDebug("(selForMoveBlackTriFish) "+resultString);
    return resultBool;
}



//Когда выпал дубль, то после сделанного хода надо
//выставить признак "Сделан ход" для следующего непомеченного кубика
void Board::setFishMovedNextForDouble(const bool &bIsWhite)
{
    //Для белых кубиков
    if (bIsWhite)
    {
        for (int i=0;i<4;i++)
        {
          if (!vectorCubeWhite[i]->getFishMoved())
          {
            vectorCubeWhite[i]->setFishMoved(true);
            strToDebug("(setFishMovedNextForDouble) Сделан ход для кубика vectorCubeWhite["+QString::number(i)+"]: "+ QString::number(vectorCubeWhite[i]->getValue()));
            break;
          }
        }
    }
    else //Для черных кубиков
    {
        for (int i=0;i<4;i++)
        {
          if (!vectorCubeBlack[i]->getFishMoved())
          {
            vectorCubeBlack[i]->setFishMoved(true);
            strToDebug("(setFishMovedNextForDouble) Сделан ход для кубика vectorCubeBlack["+QString::number(i)+"]: "+ QString::number(vectorCubeBlack[i]->getValue()));
            break;
          }
        }
    }
}

//Необходимо сделать прозрачным кубик (кубики) для которого ход уже сделан
//Выставляем признак "Сделан ход" для кубика (кубиков) после сделанного хода
void Board::cubesWhiteSetFishMoved(const int &inxSelected, const int &inxMove)
{
    //Перебираем кубики для нахождения того, которым сделан ход
    //Если дубль (четыре хода)
    if (vectorCubeWhite[0]->getValue()==vectorCubeWhite[1]->getValue())
    {
        if ((inxMove-inxSelected == vectorCubeWhite[0]->getValue())
                || vectorCubeWhite[0]->candidateForOut
                || vectorCubeWhite[1]->candidateForOut
                || vectorCubeWhite[2]->candidateForOut
                || vectorCubeWhite[3]->candidateForOut)
        {
            setFishMovedNextForDouble(true);
        }
        else if (inxMove-inxSelected == vectorCubeWhite[0]->getValue()*2)
        {
            setFishMovedNextForDouble(true);
            setFishMovedNextForDouble(true);

        }
        else if (inxMove-inxSelected == vectorCubeWhite[0]->getValue()*3)
        {
            setFishMovedNextForDouble(true);
            setFishMovedNextForDouble(true);
            setFishMovedNextForDouble(true);
        }
        else if (inxMove-inxSelected == vectorCubeWhite[0]->getValue()*4)
        {
            setFishMovedNextForDouble(true);
            setFishMovedNextForDouble(true);
            setFishMovedNextForDouble(true);
            setFishMovedNextForDouble(true);
        }
    } else //Если не дубль (два хода)
    {
        if ((inxMove-inxSelected == vectorCubeWhite[0]->getValue() || vectorCubeWhite[0]->candidateForOut)
                && !vectorCubeWhite[0]->getFishMoved())

        {
            strToDebug("(cubesWhiteSetFishMoved) Сделан ход для кубика vectorCubeWhite[0]: "+ QString::number(vectorCubeWhite[0]->getValue()));
            vectorCubeWhite[0]->setFishMoved(true);
        }
        else if ((inxMove-inxSelected == vectorCubeWhite[1]->getValue() || vectorCubeWhite[1]->candidateForOut)
                  && !vectorCubeWhite[1]->getFishMoved())
        {
            strToDebug("(cubesWhiteSetFishMoved) Сделан ход для кубика vectorCubeWhite[1]: "+ QString::number(vectorCubeWhite[1]->getValue()));
            vectorCubeWhite[1]->setFishMoved(true);
        }
        else if (inxMove-inxSelected == vectorCubeWhite[0]->getValue() + vectorCubeWhite[1]->getValue())
        {
            strToDebug("(cubesWhiteSetFishMoved) Сделан ход для обоих кубиков vectorCubeWhite[0] и vectorCubeWhite[1]: "+
                       QString::number(vectorCubeWhite[0]->getValue() + vectorCubeWhite[1]->getValue()));
            vectorCubeWhite[0]->setFishMoved(true);
            vectorCubeWhite[1]->setFishMoved(true);
        }
    }
}


//Необходимо сделать прозрачным кубик (кубики) для которого ход уже сделан
//Выставляем признак "Сделан ход" для кубика (кубиков) после сделанного хода
void Board::cubesBlackSetFishMoved(const int &inxSelected, const int &inxMove)
{
    //Перебираем кубики для нахождения того, которым сделан ход
    //Если дубль (четыре хода)
    if (vectorCubeBlack[0]->getValue()==vectorCubeBlack[1]->getValue())
    {
        if ((inxMove-inxSelected == vectorCubeBlack[0]->getValue())
                || vectorCubeBlack[0]->candidateForOut
                || vectorCubeBlack[1]->candidateForOut
                || vectorCubeBlack[2]->candidateForOut
                || vectorCubeBlack[3]->candidateForOut)
        {
            setFishMovedNextForDouble(false);
        }
        else if (inxMove-inxSelected == vectorCubeBlack[0]->getValue()*2)
        {
            setFishMovedNextForDouble(false);
            setFishMovedNextForDouble(false);

        }
        else if (inxMove-inxSelected == vectorCubeBlack[0]->getValue()*3)
        {
            setFishMovedNextForDouble(false);
            setFishMovedNextForDouble(false);
            setFishMovedNextForDouble(false);
        }
        else if (inxMove-inxSelected == vectorCubeBlack[0]->getValue()*4)
        {
            setFishMovedNextForDouble(false);
            setFishMovedNextForDouble(false);
            setFishMovedNextForDouble(false);
            setFishMovedNextForDouble(false);
        }
    } else //Если не дубль (два хода)
    {
        if ((inxMove-inxSelected == vectorCubeBlack[0]->getValue() || vectorCubeBlack[0]->candidateForOut)
                && !vectorCubeBlack[0]->getFishMoved())

        {
            strToDebug("(cubesBlackSetFishMoved) Сделан ход для кубика vectorCubeBlack[0]: "+ QString::number(vectorCubeBlack[0]->getValue()));
            vectorCubeBlack[0]->setFishMoved(true);
        }
        else if ((inxMove-inxSelected == vectorCubeBlack[1]->getValue() || vectorCubeBlack[1]->candidateForOut)
                  && !vectorCubeBlack[1]->getFishMoved())
        {
            strToDebug("(cubesBlackSetFishMoved) Сделан ход для кубика vectorCubeBlack[1]: "+ QString::number(vectorCubeBlack[1]->getValue()));
            vectorCubeBlack[1]->setFishMoved(true);
        }
        else if (inxMove-inxSelected == vectorCubeBlack[0]->getValue() + vectorCubeBlack[1]->getValue())
        {
            strToDebug("(cubesBlackSetFishMoved) Сделан ход для обоих кубиков vectorCubeBlack[0] и vectorCubeBlack[1]: "+
                       QString::number(vectorCubeBlack[0]->getValue() + vectorCubeBlack[1]->getValue()));
            vectorCubeBlack[0]->setFishMoved(true);
            vectorCubeBlack[1]->setFishMoved(true);
        }
    }
}

//Делаем ход белой фишкой на щелкнутый мышкой виджет возможного хода (в виде белого треугольника)
bool Board::moveWhiteFish(const int &x, const int &y)
{
    //Выставляем признак "Щелчок мыши попал в виждет метки возможного хода"
    bool resultBoolMove=false;

    //Индекс треугольника выбранного для хода
    int inxSelected=-1;
    //Перебираем белые треугольники для поиска выбранного для хода
    for (int inxSel=0; inxSel < 25; inxSel++)
    {
        if (vecTriWhiteFishs[inxSel]->getSelectedForMove())
            inxSelected=inxSel;
    }

    //Перебираем белые треугольники для поиска метки возможного хода, геометрия виджета которой содержат координаты щелчка мыши
    for (int inxMove=0; inxMove < 25; inxMove++)
    {
        //Если координаты щелчка мыши "входят в геометрию" виждета возможного хода (в виде белого треугольника), и этот виджет видим
        if (
                (vecTriWhiteFishs[inxMove]->wgtVarMove->geometry().contains(x,y) && vecTriWhiteFishs[inxMove]->wgtVarMove->isVisible())
                ||
                (vecTriWhiteFishs[inxMove]->wgtVarMoveTri->geometry().contains(x,y) && vecTriWhiteFishs[inxMove]->wgtVarMoveTri->isVisible())
                )
        {
            //Выполняем ход
            //Если найден индекс треугольника выбранного для хода
            if (inxSelected >= 0)
            {
                //Выставляем признак "Щелчок мыши попал в виждет метки возможного хода, Ход Сделан!"
                resultBoolMove=true;

                //Снимаем признак "Выбран для хода" с треугольника
                vecTriWhiteFishs[inxSelected]->setSelectedForMove(false);
                //Скрываем метку хода на которую ходим
//                vecTriWhiteFishs[inxMove]->wgtVarMove->setVisible(false);
//                vecTriWhiteFishs[inxMove]->wgtVarMoveTri->setVisible(false);

                //Собственно перемещаем фишку
                //begin Animation
                int lastIndexFish=vecTriWhiteFishs[inxSelected]->stkFishs.size()-1;
                vecTriWhiteFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->setDuration(500);
                vecTriWhiteFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->setStartValue(vecTriWhiteFishs[inxSelected]->stkFishs[lastIndexFish]->pos());
                vecTriWhiteFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->setEndValue(vecTriWhiteFishs[inxMove]->wgtVarMove->pos());
                vecTriWhiteFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->setEasingCurve(QEasingCurve::OutQuad);
                vecTriWhiteFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->start();
                //end Animation
                MoveFish(vecTriWhiteFishs[inxSelected], vecTriWhiteFishs[inxMove]);

                //Если ходим с головы, увеличиваем счетчик ходов с головы
                if (inxSelected==0) ++m_iCountMoveFromHead;

                strToDebug("(moveWhiteFish) Выполняем ход для "+ firstGamerName+ " в точку : " + QString::number(x) + ",  " + QString::number(y));

                m_iWhiteCount = m_iWhiteCount - (inxMove-inxSelected);
                //Обновляем информацию на дисплее
                if (m_iWhiteCount >=0)
                    emit sendDisplayWhiteCount(m_iWhiteCount);
                else
                    emit sendDisplayWhiteCount(0);

                //Выставляем признак "Сделан ход" для кубика (кубиков) после сделанного хода
                cubesWhiteSetFishMoved(inxSelected, inxMove);
                //Скрываем метки возможных ходов
                hidePossibleMoves(true);
                showPossibleMovesForAll(true);

            }
        }
    }
    return resultBoolMove;
}

//Делаем ход черной фишкой на щелкнутый мышкой виджет возможного хода (в виде белого треугольника)
bool Board::moveBlackFish(const int &x, const int &y)
{
    //Выставляем признак "Щелчок мыши попал в виждет метки возможного хода"
    bool resultBoolMove=false;

    //Индекс треугольника выбранного для хода
    int inxSelected=-1;
    //Перебираем белые треугольники для поиска выбранного для хода
    for (int inxSel=0; inxSel < 25; inxSel++)
    {
        if (vecTriBlackFishs[inxSel]->getSelectedForMove())
            inxSelected=inxSel;
    }

    //Перебираем белые треугольники для поиска метки возможного хода, геометрия виджета которой содержат координаты щелчка мыши
    for (int inxMove=0; inxMove < 25; inxMove++)
    {
        //Если координаты щелчка мыши "входят в геометрию" виждета возможного хода (в виде белого треугольника), и этот виджет видим
        if (
                (vecTriBlackFishs[inxMove]->wgtVarMove->geometry().contains(x,y) && vecTriBlackFishs[inxMove]->wgtVarMove->isVisible())
                ||
                (vecTriBlackFishs[inxMove]->wgtVarMoveTri->geometry().contains(x,y) && vecTriBlackFishs[inxMove]->wgtVarMoveTri->isVisible())
                )
        {
            //Выполняем ход
            //Если найден индекс треугольника выбранного для хода
            if (inxSelected >= 0)
            {
                //Выставляем признак "Щелчок мыши попал в виждет метки возможного хода, Ход Сделан!"
                resultBoolMove=true;

                //Снимаем признак "Выбран для хода" с треугольника
                vecTriBlackFishs[inxSelected]->setSelectedForMove(false);
                //Скрываем метку хода на которую ходим
//                vecTriBlackFishs[inxMove]->wgtVarMove->setVisible(false);
//                vecTriBlackFishs[inxMove]->wgtVarMoveTri->setVisible(false);

                //Собственно перемещаем фишку
                //begin Animation
                int lastIndexFish=vecTriBlackFishs[inxSelected]->stkFishs.size()-1;
                vecTriBlackFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->setDuration(500);
                vecTriBlackFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->setStartValue(vecTriBlackFishs[inxSelected]->stkFishs[lastIndexFish]->pos());
                vecTriBlackFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->setEndValue(vecTriBlackFishs[inxMove]->wgtVarMove->pos());
                vecTriBlackFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->setEasingCurve(QEasingCurve::OutQuad);
                vecTriBlackFishs[inxSelected]->stkFishs[lastIndexFish]->pAnim->start();
                //end Animation
                MoveFish(vecTriBlackFishs[inxSelected], vecTriBlackFishs[inxMove]);
                //Если ходим с головы, увеличиваем счетчик ходов с головы
                if (inxSelected==0) ++m_iCountMoveFromHead;
                //Скрываем метки возможных ходов
                strToDebug("(moveBlackFish) Выполняем ход для "+ secondGamerName+ " в точку : " + QString::number(x) + ",  " + QString::number(y));

                //Обновляем информацию на дисплее
                m_iBlackCount= m_iBlackCount-(inxMove-inxSelected);
                if (m_iBlackCount >=0)
                    emit sendDisplayBlackCount(m_iBlackCount);

                else
                    emit sendDisplayBlackCount(0);

                //Выставляем признак "Сделан ход" для кубика (кубиков) после сделанного хода
                cubesBlackSetFishMoved(inxSelected, inxMove);
                hidePossibleMoves(false);
                showPossibleMovesForAll(false);

            }
        }
    }
    return resultBoolMove;
}




// ----------------------------------------------------------------------
/*virtual*/void Board::mousePressEvent(QMouseEvent* pe)
{
        if (!m_checkRightOfTheFirstMove)  //Проверяем, что было разыграно право первого хода
        {
            if (m_RollTheCubesForWhiteFish) //Для белых
            {
                m_valueWhite = RollTheCubeWhite();
                strToDebug("У игрока "+ firstGamerName +" выпало: "+ QString::number(m_valueWhite));
                strToHint("У игрока "+ firstGamerName +" выпало: "+ QString::number(m_valueWhite));
                m_RollTheCubesForWhiteFish = false;
            }
            else
            {
                m_valueBlack = RollTheCubeBlack();
                strToDebug("У игрока "+ secondGamerName +" выпало: "+ QString::number(m_valueBlack));
                strToHint("У игрока "+ firstGamerName +" выпало: "+ QString::number(m_valueWhite));
                m_RollTheCubesForWhiteFish = true;
            }

            if ((m_valueWhite != 0) && (m_valueBlack) != 0) //Кубик должен быть брошен и для белых и для черных
                if (m_valueWhite > m_valueBlack)
                {
                    strToDebug("Право первого хода у игрока "+ firstGamerName+ ".");
                    strToHint("Право первого хода у игрока "+ firstGamerName+ ".");
                    m_checkRightOfTheFirstMove = true;
                    m_RollTheCubesForWhiteFish = true;
                }
                else if (m_valueWhite < m_valueBlack)
                {
                    strToDebug("Право первого хода у игрока "+ secondGamerName+ ".");
                    strToHint("Право первого хода у игрока "+ secondGamerName+ ".");
                    m_checkRightOfTheFirstMove = true;
                    m_RollTheCubesForWhiteFish = false;
                }
                else if (m_valueWhite = m_valueBlack)
                {
                    strToDebug("У "+ firstGamerName+ " и у "+ secondGamerName+ " выпало одинаково - перекидываем.");
                    strToHint("У "+ firstGamerName+ " и у "+ secondGamerName+ " выпало одинаково - перекидываем.");
                    m_valueWhite = m_valueBlack = 0; //Обнуляем
                }
        }
        //Право первого хода разыграно, выигравший это право бросает кубики
        else if ((m_bMoveWhiteFish==false) && (m_bMoveBlackFish==false))
        {
             //Убираем кубики с доски
            if (m_RollTheCubesForWhiteFish) //Для белых
            {
                m_bMoveWhiteFish=true;
                hideAllCubes();
                QString str = RollTheCubesWhite();
                strToDebug("У "+ firstGamerName+ " выпало: " + str);
                //m_RollTheCubesForWhiteFish=!m_RollTheCubesForWhiteFish;

            }
            else //Для черных
            {
                m_bMoveBlackFish=true;
                hideAllCubes();
                QString str = RollTheCubesBlack();
                strToDebug("У "+ secondGamerName+ " выпало: " + str);
                //m_RollTheCubesForWhiteFish=!m_RollTheCubesForWhiteFish;

            }
        }
        //Ход белых
        else if ((m_bMoveWhiteFish==true) && (m_bMoveBlackFish==false))
        {
            //            strToDebug("(mousePressEvent) Игрок "+ firstGamerName+ " выбирает фишку и ходит.");
            //            strToDebug("(mousePressEvent) pe->x() "+ QString::number(pe->x()));
            //            strToDebug("(mousePressEvent) pe->y() "+ QString::number(pe->y()));

            //(1)Левым кликом выделяем фишку (треугольник) которой будем ходить
            //(1)На фишку (треугольник) устанавливается признак "Выбран для хода"
            //(1)Показываются все возможные ходы для этой фишки (треугольника)
            //(2)Если фишка (треугольник) выбрана для хода, и мы щелкаем по ней, то снимаем выделение Левым кликом
            //(2)С фишки (треугольника) снимается признак "Выбран для хода"
            //(2)Снимается показ всех возможных ходов для этой фишки (треугольника)

            //Если щелчок мыши НЕ нашел белую фишку
            if (!selForMoveWhiteFish(pe->x(),pe->y()))
            {
                //(3)Если (хотябы одна) БЕЛАЯ фишка выбрана для хода
                if (existsSelectedForMove(true))
                {
                    //Если ход сделан
                    if (moveWhiteFish(pe->x(),pe->y()))
                    {
                        //Если все ходы сделаны
                        //Если дубль (четыре хода)
                        if (vectorCubeWhite[0]->getValue()==vectorCubeWhite[1]->getValue())
                        {
                            //Все четыре кубика "сходили"
                            if (vectorCubeWhite[0]->getFishMoved() && vectorCubeWhite[1]->getFishMoved() &&
                                    vectorCubeWhite[2]->getFishMoved() && vectorCubeWhite[3]->getFishMoved())
                            {
                                strToDebug("(mousePressEvent) Все ходы для игрока " + firstGamerName + " сделаны. Передача кубиков.");
                                m_bMoveWhiteFish=false;
                                //Выставляем флаг броска кубиков для черных
                                m_RollTheCubesForWhiteFish=false;
//                                setCursor(QCursor(QPixmap(":/cursor_two_cubes_3232.png")));
//                                strToDebug("(mousePressEvent) setCursor cursor_two_cubes_3232.png");
                                //Выставляем флаг первого хода с головы
                                m_bFirstMoveFromHeadWhite=false;
                            }

                        } else //Если не дубль (два хода)
                            //Оба кубика "сходили"
                            if (vectorCubeWhite[0]->getFishMoved() && vectorCubeWhite[1]->getFishMoved())
                            {
                                strToDebug("(mousePressEvent) Все ходы для игрока " + firstGamerName + " сделаны. Передача кубиков.");
                                m_bMoveWhiteFish=false;
                                m_RollTheCubesForWhiteFish=false;
//                                setCursor(QCursor(QPixmap(":/cursor_two_cubes_3232.png")));
//                                strToDebug("(mousePressEvent) setCursor cursor_two_cubes_3232.png");
                                //Выставляем флаг первого хода с головы
                                m_bFirstMoveFromHeadWhite=false;
                            }
                    } else //Если ход не сделан, то щелчок мыши не попал в виждет метки возможного хода (или нет возможных ходов?), а попал на пустое место или в другую фишку
                    {
                        //В этом случае надо снять признак "Выбран для хода" с треугольника (со всех треугольников)
                        deSelectForMoveAll();
                        //Скрыть метки возможных ходов                        
                        hidePossibleMoves(true);
                        //Показать ментки возможных ходов для белых
                        showPossibleMovesForAll(true);

                    }
                }
            }
        }
        //Ход черных
        else if ((m_bMoveWhiteFish==false) && (m_bMoveBlackFish==true))
        {
            //strToDebug("(mousePressEvent) Игрок "+ secondGamerName+ " выбирает фишку и ходит.");
//            strToDebug("(mousePressEvent) pe->x() "+ QString::number(pe->x()));
//            strToDebug("(mousePressEvent) pe->y() "+ QString::number(pe->y()));

            //(1)Левым кликом выделяем фишку (треугольник) которой будем ходить
            //(1)На фишку (треугольник) устанавливается признак "Выбран для хода"
            //(1)Показываются все возможные ходы для этой фишки (треугольника)
            //(2)Если фишка (треугольник) выбрана для хода, и мы щелкаем по ней, то снимаем выделение Левым кликом
            //(2)С фишки (треугольника) снимается признак "Выбран для хода"
            //(2)Снимается показ всех возможных ходов для этой фишки (треугольника)

            //Если щелчок мыши НЕ нашел черную фишку
            if (!selForMoveBlackFish(pe->x(),pe->y()))
            {
                 //(3)Если (хотябы одна) Черная фишка выбрана для хода
                if (existsSelectedForMove(false))
                {
                    //Если ход сделан
                    if (moveBlackFish(pe->x(),pe->y()))
                    {
                        //Если все ходы сделаны
                        //Если дубль (четыре хода)
                        if (vectorCubeBlack[0]->getValue()==vectorCubeBlack[1]->getValue())
                        {
                            //Все четыре кубика "сходили"
                            if (vectorCubeBlack[0]->getFishMoved() && vectorCubeBlack[1]->getFishMoved() &&
                                    vectorCubeBlack[2]->getFishMoved() && vectorCubeBlack[3]->getFishMoved())
                            {
                                strToDebug("(mousePressEvent) Все ходы для игрока " + secondGamerName + " сделаны. Передача кубиков.");
                                m_bMoveBlackFish=false;
                                //Выставляем флаг броска кубиков для белых
                                m_RollTheCubesForWhiteFish=true;
//                                setCursor(QCursor(QPixmap(":/cursor_two_cubes_3232.png")));
//                                strToDebug("(mousePressEvent) setCursor cursor_two_cubes_3232.png (Если дубль");
                                //Выставляем флаг первого хода с головы
                                m_bFirstMoveFromHeadBlack=false;
                            }

                        } else //Если не дубль (два хода)
                            //Оба кубика "сходили"
                            if (vectorCubeBlack[0]->getFishMoved() && vectorCubeBlack[1]->getFishMoved())
                            {
                                strToDebug("(mousePressEvent) Все ходы для игрока " + secondGamerName + " сделаны. Передача кубиков.");
                                m_bMoveBlackFish=false;
                                m_RollTheCubesForWhiteFish=true;
//                                setCursor(QCursor(QPixmap(":/cursor_two_cubes_3232.png")));
//                                strToDebug("(mousePressEvent) setCursor cursor_two_cubes_3232.png (Если не дубль");
                                //Выставляем флаг первого хода с головы
                                m_bFirstMoveFromHeadBlack=false;
                            }
                    } else //Если ход не сделан, то щелчок мыши не попал в виждет метки возможного хода (или нет возможных ходов?), а попал на пустое место или в другую фишку
                    {
                        //В этом случае надо снять признак "Выбран для хода" с треугольника (со всех треугольников)
                        deSelectForMoveAll();
                        //Скрыть метки возможных ходов
                        hidePossibleMoves(false);
                        showPossibleMovesForAll(false);
                    }
                }
            }

        }

        QWidget::enterEvent(pe); //Передать событие дальше

}

// ----------------------------------------------------------------------
/*virtual*/void Board::mouseReleaseEvent(QMouseEvent* pe)
{

    if (!m_checkRightOfTheFirstMove)  //Проверяем, что было разыграно право первого хода
    {
        if (m_RollTheCubesForWhiteFish)
        {
            strToDebug("Игрок "+ firstGamerName +" бросайте кубик на право первого хода.");
            strToHint("Игрок "+ firstGamerName +" бросайте кубик на право первого хода.");
        }
        else
        {
            strToDebug("Игрок "+ secondGamerName +" бросайте кубик на право первого хода.");
            strToHint("Игрок "+ secondGamerName +" бросайте кубик на право первого хода.");
        }
    }
    //Право первого хода разыграно, выигравший это право бросает кубики
    else if ((m_bMoveWhiteFish==false) && (m_bMoveBlackFish==false))
    {
        setCursor(QCursor(QPixmap(":/cursor_two_cubes_3232.png")));
        strToDebug("(mouseReleaseEvent) setCursor cursor_two_cubes_3232.png");

        if (m_RollTheCubesForWhiteFish)
        {
            strToDebug("Игрок "+ firstGamerName +" бросает кубики.");
            strToHint("Игрок "+ firstGamerName +" Ваш ход, бросайте кубики.");
        }
        else
        {
            strToDebug("Игрок "+ secondGamerName +" бросает кубики.");
            strToHint("Игрок "+ secondGamerName +" Ваш ход, бросайте кубики.");
        }
    }
    //Ход белых
    else if ((m_bMoveWhiteFish==true) && (m_bMoveBlackFish==false))
    {
        setCursor(Qt::ArrowCursor);
        //strToDebug("(mouseReleaseEvent) Курсор мыши принимает вид стрелки.");
        strToDebug("(mouseReleaseEvent) Игрок "+ firstGamerName+ " выбирает фишку и ходит.");
        strToHint("Игрок "+ firstGamerName+ " выберите фишку и ходите.");

    }
    //Ход черных
    else if ((m_bMoveWhiteFish==false) && (m_bMoveBlackFish==true))
    {
        setCursor(Qt::ArrowCursor);
        //strToDebug("(mouseReleaseEvent) Курсор мыши принимает вид стрелки.");
        strToDebug("(mouseReleaseEvent) Игрок "+ secondGamerName+ " выбирает фишку и ходит.");
        strToHint("Игрок "+ secondGamerName+ " выберите фишку и ходите.");
    }
    QWidget::enterEvent(pe); //Передать событие дальше

}

/*virtual*/void Board::mouseMoveEvent(QMouseEvent* pe)
{
       QWidget::enterEvent(pe); //Передать событие дальше
}

void Board::rollTheCubesWhiteAnimation()
{
    /*
     vectorCubeWhite[0]->move(505, 300);
     vectorCubeWhite[0]->setVisible(false);

     vectorCubeWhite[1]->move(555, 300);
     vectorCubeWhite[1]->setVisible(false);
    */

    vectorCubeWhite[0]->pAnim->setDuration(700);
    vectorCubeWhite[0]->pAnim->setStartValue(QPoint(655, 500));
    vectorCubeWhite[0]->pAnim->setEndValue(QPoint(505, 300));
    vectorCubeWhite[0]->pAnim->setEasingCurve(QEasingCurve::OutQuad);
    vectorCubeWhite[0]->pAnim->start();

    vectorCubeWhite[1]->pAnim->setDuration(700);
    vectorCubeWhite[1]->pAnim->setStartValue(QPoint(655, 500));
    vectorCubeWhite[1]->pAnim->setEndValue(QPoint(555, 300));
    vectorCubeWhite[1]->pAnim->setEasingCurve(QEasingCurve::OutExpo);
    vectorCubeWhite[1]->pAnim->start();
}

QString Board::RollTheCubesWhite()
{
    QString resultString;

//    rollTheCubesWhiteAnimation();

    //Снимаем с кубиков признак сделанного хода
    for (int i=0; i < 4; i++) vectorCubeWhite[i]->setFishMoved(false);
    //Обнуляем счетчик ходов с головы
    m_iCountMoveFromHead=0;

//    vectorCubeWhite[0]->setValue(4);
    vectorCubeWhite[0]->setValue(vectorRandomValues[vectorRandomValuesNextIndex++]);
    vectorCubeWhite[0]->setVisible(true);
//    vectorCubeWhite[1]->setValue(4);
    vectorCubeWhite[1]->setValue(vectorRandomValues[vectorRandomValuesNextIndex++]);
    vectorCubeWhite[1]->setVisible(true);
    vectorCubeWhite[2]->setValue(0);
    vectorCubeWhite[3]->setValue(0);

    resultString = QString::number(vectorCubeWhite[0]->getValue()) + " " + QString::number(vectorCubeWhite[1]->getValue());

    //Когда выпал КУШ (дубль)
    if (vectorCubeWhite[0]->getValue() == vectorCubeWhite[1]->getValue())
    {

        //Если делаем первый ход с головы
        //Для 6-6 показываем только 2 кубика
        if (m_bFirstMoveFromHeadWhite && vectorCubeWhite[0]->getValue()==6)
        {
            vectorCubeWhite[2]->setFishMoved(true);
            vectorCubeWhite[3]->setFishMoved(true);
            //m_bFirstMoveFromHeadWhite=false;
        } else
        {
            vectorCubeWhite[2]->setValue(vectorCubeWhite[0]->getValue());
            vectorCubeWhite[2]->setVisible(true);
            vectorCubeWhite[3]->setValue(vectorCubeWhite[0]->getValue());
            vectorCubeWhite[3]->setVisible(true);

            resultString = QString::number(vectorCubeWhite[0]->getValue()) + " " +
                    QString::number(vectorCubeWhite[0]->getValue()) + " " +
                    QString::number(vectorCubeWhite[0]->getValue()) + " " +
                    QString::number(vectorCubeWhite[0]->getValue());
        }
    }

    //Показать возможные ходы для всех белых фишек
    showPossibleMovesForAll(true);
    return resultString;
}

void Board::rollTheCubesBlackAnimation()
{
    /*
    vectorCubeBlack[0]->move(200, 300);
    vectorCubeBlack[0]->setVisible(false);

    vectorCubeBlack[1]->move(250, 300);
    vectorCubeBlack[1]->setVisible(false);
    */

    vectorCubeBlack[0]->pAnim->setDuration(700);
    vectorCubeBlack[0]->pAnim->setStartValue(QPoint(100, 500));
    vectorCubeBlack[0]->pAnim->setEndValue(QPoint(200, 300));
    vectorCubeBlack[0]->pAnim->setEasingCurve(QEasingCurve::OutQuad);
    vectorCubeBlack[0]->pAnim->start();

    vectorCubeBlack[1]->pAnim->setDuration(700);
    vectorCubeBlack[1]->pAnim->setStartValue(QPoint(100, 500));
    vectorCubeBlack[1]->pAnim->setEndValue(QPoint(250, 300));
    vectorCubeBlack[1]->pAnim->setEasingCurve(QEasingCurve::OutExpo);
    vectorCubeBlack[1]->pAnim->start();
}

QString Board::RollTheCubesBlack()
{
    QString resultString;

//    rollTheCubesBlackAnimation();

    //Снимаем с кубиков признак сделанного хода
    for (int i=0; i < 4; i++) vectorCubeBlack[i]->setFishMoved(false);
    //Обнуляем счетчик ходов с головы
    m_iCountMoveFromHead=0;

//    vectorCubeBlack[0]->setValue(5);
    vectorCubeBlack[0]->setValue(vectorRandomValues[vectorRandomValuesNextIndex++]);
    vectorCubeBlack[0]->setVisible(true);
//    vectorCubeBlack[1]->setValue(5);
    vectorCubeBlack[1]->setValue(vectorRandomValues[vectorRandomValuesNextIndex++]);
    vectorCubeBlack[1]->setVisible(true);
    vectorCubeBlack[2]->setValue(0);
    vectorCubeBlack[3]->setValue(0);

    resultString = QString::number(vectorCubeBlack[0]->getValue()) + " " + QString::number(vectorCubeBlack[1]->getValue());

    //Когда выпал КУШ (дубль)
    if (vectorCubeBlack[0]->getValue() == vectorCubeBlack[1]->getValue())
    {

        //Если делаем первый ход с головы
        //Для 6-6 показываем только 2 кубика
        if (m_bFirstMoveFromHeadBlack && vectorCubeBlack[0]->getValue()==6)
        {
            vectorCubeBlack[2]->setFishMoved(true);
            vectorCubeBlack[3]->setFishMoved(true);
            //m_bFirstMoveFromHeadBlack=false;
        } else
        {
            vectorCubeBlack[2]->setValue(vectorCubeBlack[0]->getValue());
            vectorCubeBlack[2]->setVisible(true);
            vectorCubeBlack[3]->setValue(vectorCubeBlack[0]->getValue());
            vectorCubeBlack[3]->setVisible(true);

            resultString = QString::number(vectorCubeBlack[0]->getValue()) + " " +
                    QString::number(vectorCubeBlack[0]->getValue()) + " " +
                    QString::number(vectorCubeBlack[0]->getValue()) + " " +
                    QString::number(vectorCubeBlack[0]->getValue());
        }
    }

    //Показать возможные ходы для всех черных фишек
    showPossibleMovesForAll(false);
    return resultString;
}

int Board::RollTheCubeWhite()
{
    vectorCubeWhite[1]->setValue(vectorRandomValues[vectorRandomValuesNextIndex++]);
    vectorCubeWhite[1]->setVisible(true);

    return vectorCubeWhite[1]->getValue();
}

int Board::RollTheCubeBlack()
{
    vectorCubeBlack[0]->setValue(vectorRandomValues[vectorRandomValuesNextIndex++]);
    vectorCubeBlack[0]->setVisible(true);

    return vectorCubeBlack[0]->getValue();
}

/*
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
 */

void Board::NewGame()
{
    //Заполняем вектор случайных значений новыми случайными значениями
    VectorRandomValuesInit();

    //Выставляем в начальные значения для дисплея
    m_iWhiteCount=360;
    m_iBlackCount=360;
    emit sendDisplayWhiteCount(m_iWhiteCount);
    emit sendDisplayBlackCount(m_iBlackCount);

    //Выставляем флаг состояния разыграно ли право первого хода
    m_checkRightOfTheFirstMove=false;
    m_RollTheCubesForWhiteFish=true;
    //При розыгрыше на право первого хода, значение которое выбросили белые
    m_valueWhite=0;
    //При розыгрыше на право первого хода, значение которое выбросили черные
    m_valueBlack=0;
    //Выставляем флаг первого хода с головы
    m_bFirstMoveFromHeadWhite=true;
    m_bFirstMoveFromHeadBlack=true;
    //Количество ходов сделаных с головы
    m_iCountMoveFromHead=0;
    //Выставляем флаг состояния - ход белых
    m_bMoveWhiteFish=false;
    //Выставляем флаг состояние - ход черных
    m_bMoveBlackFish=false;

    //Скрываем все кубики
    hideAllCubes();

    //Скрываем все метки возможных ходов для белых
    hidePossibleMoves(true);
    //Скрываем все метки возможных ходов для черных
    hidePossibleMoves(false);

    for (int i=1; i < 25; i++)
    {
        //Если хотябы в одном белом треугольнике есть фишки перемещаем их в нулевой треугольник
        while (vecTriWhiteFishs[i]->stkFishs.size()>0)  MoveFish(vecTriWhiteFishs[i],vecTriWhiteFishs[0]);
    }

    for (int i=1; i < 25; i++)
    {
        //Если хотябы в одном черном треугольнике есть фишки перемещаем их в нулевой треугольник
        while (vecTriBlackFishs[i]->stkFishs.size()>0)  MoveFish(vecTriBlackFishs[i],vecTriBlackFishs[0]);
    }


    strToDebug("Игрок "+ firstGamerName +" бросайте кубик на право первого хода");
    strToHint("Игрок "+ firstGamerName +" бросайте кубик на право первого хода");
    //Меняем курсор
    setCursor(QCursor(QPixmap(":/cursor_one_cube_3232.png")));

    //Процедура бросания кубика на право первого хода для белых
//    int resultCubeB = RollTheCubeBlack();

    //Для отладки делаем 4 хода белыми и 4 хода черными
//    MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[13]);
//    MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[14]);
//    MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[15]);
//    MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[16]);
//    MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[17]);
//    MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[18]);
    //MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[21]);

//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[13]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[14]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[15]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[16]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[17]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[18]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[10]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[11]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[14]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[10]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[18]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[19]);
//    MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[20]);


//Все в доме
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[23]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[23]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriWhiteFishs[0], vecTriWhiteFishs[24]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[21]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[21]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[21]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[21]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[21]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[22]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[23]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[21]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[21]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[18]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[18]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[18]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[18]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[18]);
//        MoveFish(vecTriBlackFishs[0], vecTriBlackFishs[18]);
}

void Board::saveGame()
{
    m_settings.beginGroup("/SavedGame");

     //Сохраняем имена игроков
     m_settings.beginGroup("/SelectPlayers");

      m_settings.setValue("GameType", getGameType());
      m_settings.setValue("WhiteGamerName", getFirstGamerName());
      m_settings.setValue("BlackGamerName", getSecondGamerName());

     m_settings.endGroup();

     //Сохраняем значения для дисплея
     m_settings.setValue("m_iWhiteCount", m_iWhiteCount);
     m_settings.setValue("m_iBlackCount", m_iBlackCount);
     //Сохраняем флаг состояния разыграно ли право первого хода
     m_settings.setValue("m_checkRightOfTheFirstMove",m_checkRightOfTheFirstMove);
     //Сохраняем флаг состояния кто бросает кубики
     m_settings.setValue("m_RollTheCubesForWhiteFish",m_RollTheCubesForWhiteFish);
     //Сохраняем при розыгрыше на право первого хода, значение которое выбросили белые
     m_settings.setValue("m_valueWhite",m_valueWhite);
     //Сохраняем при розыгрыше на право первого хода, значение которое выбросили черные
     m_settings.setValue("m_valueBlack",m_valueBlack);
     //Сохраняем флаг первого хода с головы
     m_settings.setValue("m_bFirstMoveFromHeadWhite",m_bFirstMoveFromHeadWhite);
     m_settings.setValue("m_bFirstMoveFromHeadBlack",m_bFirstMoveFromHeadBlack);
     //Сохраняем Количество ходов сделаных с головы
     m_settings.setValue("m_iCountMoveFromHead",m_iCountMoveFromHead);
     //Сохраняем флаг состояния - ход белых
     m_settings.setValue("m_bMoveWhiteFish",m_bMoveWhiteFish);
     //Сохраняем флаг состояния - ход черных
     m_settings.setValue("m_bMoveBlackFish",m_bMoveBlackFish);
     //Сохраняем текущую строку подсказки
     m_settings.setValue("m_strHintString", m_strHintString);

     m_settings.beginGroup("/WhiteTriangles");
      for (int i=0; i < 25; i++)
      {
         m_settings.setValue(QString::number(i), vecTriWhiteFishs[i]->stkFishs.size());
      }
     m_settings.endGroup();
     m_settings.beginGroup("/BlackTriangles");
      for (int i=0; i < 25; i++)
      {
         m_settings.setValue(QString::number(i), vecTriBlackFishs[i]->stkFishs.size());
      }
     m_settings.endGroup();
     m_settings.beginGroup("/WhiteCubesValues");
      for (int i=0; i < 4; i++)
      {
        if (vectorCubeWhite[i]->isVisible())
          m_settings.setValue(QString::number(i), vectorCubeWhite[i]->getValue());
        else
          m_settings.setValue(QString::number(i), 0);
      }
     m_settings.endGroup();
     m_settings.beginGroup("/BlackCubesValues");
      for (int i=0; i < 4; i++)
      {
        if (vectorCubeBlack[i]->isVisible())
          m_settings.setValue(QString::number(i), vectorCubeBlack[i]->getValue());
        else
          m_settings.setValue(QString::number(i), 0);
      }
     m_settings.endGroup();
     //FishMoved
     m_settings.beginGroup("/WhiteCubesFishMoved");
      for (int i=0; i < 4; i++)
      {
          m_settings.setValue(QString::number(i), vectorCubeWhite[i]->getFishMoved());
      }
     m_settings.endGroup();
     m_settings.beginGroup("/BlackCubesFishMoved");
      for (int i=0; i < 4; i++)
      {
          m_settings.setValue(QString::number(i), vectorCubeBlack[i]->getFishMoved());
      }
     m_settings.endGroup();
     //candidateForOut
     m_settings.beginGroup("/WhiteCubesCandidateForOut");
      for (int i=0; i < 4; i++)
      {
          m_settings.setValue(QString::number(i), vectorCubeWhite[i]->candidateForOut);
      }
     m_settings.endGroup();
     m_settings.beginGroup("/BlackCubesCandidateForOut");
      for (int i=0; i < 4; i++)
      {
          m_settings.setValue(QString::number(i), vectorCubeBlack[i]->candidateForOut);
      }
     m_settings.endGroup();
    m_settings.endGroup();
}

void Board::loadGame()
{

    NewGame();

    m_settings.beginGroup("/SavedGame");
     m_settings.beginGroup("/SelectPlayers");

       GameTypeEnum eGameType = static_cast<GameTypeEnum>(m_settings.value("GameType",0).toInt());
       setGameType(eGameType);

       QString strWhiteGamerName  = m_settings.value("WhiteGamerName", "").toString();
       QString strBlackGamerName = m_settings.value("BlackGamerName", "").toString();

       setFirstGamerName(strWhiteGamerName);
       emit sendDisplayWhiteGamer(strWhiteGamerName);
       setSecondGamerName(strBlackGamerName);
       emit sendDisplayBlackGamer(strBlackGamerName);

     m_settings.endGroup();

     //Выставляем значения для дисплея
     m_iWhiteCount = m_settings.value("m_iWhiteCount", 360).toInt();
     m_iBlackCount = m_settings.value("m_iBlackCount", 360).toInt();
     emit sendDisplayWhiteCount(m_iWhiteCount);
     emit sendDisplayBlackCount(m_iBlackCount);

     //Выставляем флаг состояния разыграно ли право первого хода
     m_checkRightOfTheFirstMove = m_settings.value("m_checkRightOfTheFirstMove", false).toBool();
     //Выставляем чей ход белых или черных
     m_RollTheCubesForWhiteFish = m_settings.value("m_RollTheCubesForWhiteFish", false).toBool();
     //При розыгрыше на право первого хода, значение которое выбросили белые
     m_valueWhite = m_settings.value("m_valueWhite", 0).toInt();
     //При розыгрыше на право первого хода, значение которое выбросили черные
     m_valueBlack = m_settings.value("m_valueBlack", 0).toInt();
     //Выставляем флаг первого хода с головы
     m_bFirstMoveFromHeadWhite = m_settings.value("m_bFirstMoveFromHeadWhite", false).toBool();
     m_bFirstMoveFromHeadBlack = m_settings.value("m_bFirstMoveFromHeadBlack", false).toBool();
     //Количество ходов сделаных с головы
     m_iCountMoveFromHead = m_settings.value("m_iCountMoveFromHead", 0).toInt();
     //Выставляем флаг состояния - ход белых
     m_bMoveWhiteFish = m_settings.value("m_bMoveWhiteFish", false).toBool();
     //Выставляем флаг состояние - ход черных
     m_bMoveBlackFish = m_settings.value("m_bMoveBlackFish", false).toBool();

     emit sendHintString("<html><body><table><tr><td align = center>"+ m_settings.value("m_strHintString", "").toString()+"</td></tr></table></body></html>");

     m_settings.beginGroup("/WhiteTriangles");
      for (int i=1; i < 25; i++)
      {
          int iCountFishs = m_settings.value(QString::number(i),0).toInt();
          //strToDebug("(loadGame) WhiteTriangles["+QString::number(i)+"]="+QString::number(iCountFishs));
          if (iCountFishs)
          {
              //strToDebug("(loadGame) j!=0");
              for (int j=0; j < iCountFishs; j++)
              {
                //strToDebug("(loadGame) j="+QString::number(j));
                MoveFish(vecTriWhiteFishs[0],vecTriWhiteFishs[i]);
              }
          }
      }
     m_settings.endGroup();
     m_settings.beginGroup("/BlackTriangles");
      for (int i=1; i < 25; i++)
      {
          int iCountFishs = m_settings.value(QString::number(i),0).toInt();
          //strToDebug("(loadGame) BlackTriangles["+QString::number(i)+"]="+QString::number(iCountFishs));
          if (iCountFishs)
          {
              //strToDebug("(loadGame) j!=0");
              for (int j=0; j < iCountFishs; j++)
              {
                //strToDebug("(loadGame) j="+QString::number(j));
                MoveFish(vecTriBlackFishs[0],vecTriBlackFishs[i]);
              }
          }
      }
     m_settings.endGroup();
     m_settings.beginGroup("/WhiteCubesValues");
      for (int i=0; i < 4; i++)
      {
        int iCubeValue = m_settings.value(QString::number(i),0).toInt();
        if (iCubeValue)
        {
           vectorCubeWhite[i]->setValue(iCubeValue);
           vectorCubeWhite[i]->setVisible(true);
        }
      }
     m_settings.endGroup();
     m_settings.beginGroup("/BlackCubesValues");
      for (int i=0; i < 4; i++)
      {
        int iCubeValue = m_settings.value(QString::number(i),0).toInt();
        if (iCubeValue)
        {
            vectorCubeBlack[i]->setValue(iCubeValue);
            vectorCubeBlack[i]->setVisible(true);
        }
      }
     m_settings.endGroup();
     m_settings.beginGroup("/WhiteCubesFishMoved");
      for (int i=0; i < 4; i++)
      {
          if ((vectorCubeWhite[i]->isVisible()) && (vectorCubeWhite[i]->getValue()))
            vectorCubeWhite[i]->setFishMoved(m_settings.value(QString::number(i), false).toBool());
      }
     m_settings.endGroup();
     m_settings.beginGroup("/BlackCubesFishMoved");
      for (int i=0; i < 4; i++)
      {
          if ((vectorCubeBlack[i]->isVisible()) && (vectorCubeBlack[i]->getValue()))
            vectorCubeBlack[i]->setFishMoved(m_settings.value(QString::number(i), false).toBool());
      }
     m_settings.endGroup();
     m_settings.beginGroup("/WhiteCubesCandidateForOut");
      for (int i=0; i < 4; i++)
      {
          vectorCubeWhite[i]->candidateForOut = m_settings.value(QString::number(i), false).toBool();
      }
     m_settings.endGroup();
     m_settings.beginGroup("/BlackCubesCandidateForOut");
      for (int i=0; i < 4; i++)
      {
          vectorCubeBlack[i]->candidateForOut = m_settings.value(QString::number(i), false).toBool();
      }
     m_settings.endGroup();

    m_settings.endGroup();

    if (!m_checkRightOfTheFirstMove)  //Проверяем, что было разыграно право первого хода
    {
        setCursor(QCursor(QPixmap(":/cursor_one_cube_3232.png")));
        strToDebug("(loadGame) setCursor cursor_one_cube_3232.png");
    }
    //Право первого хода разыграно, выигравший это право бросает кубики
    else if ((m_bMoveWhiteFish==false) && (m_bMoveBlackFish==false))
    {
        setCursor(QCursor(QPixmap(":/cursor_two_cubes_3232.png")));
        strToDebug("(loadGame) setCursor cursor_two_cubes_3232.png");

    }
    //Ход белых
    if ((m_bMoveWhiteFish==true) && (m_bMoveBlackFish==false))
    {
        setCursor(Qt::ArrowCursor);
        strToDebug("(loadGame) setCursor Qt::ArrowCursor");
        showPossibleMovesForAll(true);
    }
    //Ход черных
    else if ((m_bMoveWhiteFish==false) && (m_bMoveBlackFish==true))
    {
        setCursor(Qt::ArrowCursor);
        strToDebug("(loadGame) setCursor Qt::ArrowCursor");
        showPossibleMovesForAll(false);
    }

}



void Board::VectorRandomValuesInit(void) {

    vectorRandomValuesNextIndex = 0;
    // Инициализируем генератор случайных чисел
//	srand(static_cast<unsigned int>(time(0)));
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    //Заполняем контейнер-вектор тысячей случайных значений типа int от 1 до 6
//    generate(vectorRandomValues.rbegin(), vectorRandomValues.rend(),
//        [=]() { return static_cast<int>(static_cast<double>(*rand()*) / RAND_MAX * 6 + 1); });

    QVector<int>::iterator iter = vectorRandomValues.end();
    for (;iter != vectorRandomValues.begin();)
    {
       --iter;
        *iter = static_cast<int>(static_cast<double>(qrand()) / RAND_MAX * 6 + 1);
    }
}


void Board::strToHint(const QString& str)
{
    m_strHintString=str;
    emit sendHintString("<html><body><table><tr><td align = \"center\" width = \"100%\">"+str+"</td></tr></table></body></html>");
    //emit sendHintString("<html><body><table><tr><td align = center>"+str+"</td></tr></table></body></html>");
    //emit sendHintString("<"+ QTime::currentTime().toString()+ "> " + str);
    //emit sendHintString(QTime::currentTime().toString()+ "- " + str);
}
void Board::strToDebug(const QString& str)
{
    //emit sendDebugString(str);
    //emit sendDebugString("<"+ QTime::currentTime().toString()+ "> " + str);
    emit sendDebugString(QTime::currentTime().toString()+ "- " + str);
}

void Board::setGameType(GameTypeEnum gType)
{
  m_gameType=gType;
}

GameTypeEnum Board::getGameType()
{
    return m_gameType;
}

void Board::setFirstGamerName(const QString& str)
{
    firstGamerName=str;
}
void Board::setSecondGamerName(const QString& str)
{
    secondGamerName=str;
}
QString Board::getFirstGamerName() const
{
    return firstGamerName;
}
QString Board::getSecondGamerName() const
{
    return secondGamerName;
}


//Обновляем состояние доски
//перемещаем (расставляем) фишки и отметки вариантов ходов
//в зависимости от их принадлежности
//конкретному треугольнику
void Board::UpdateState(void)
{
    //Обновляем состояние доски для всех треугольников
    int betweenTri=48; //Расстояние между треугольниками

    int cXTriW=0; //Коордитата X отметки варианта хода (зеленые треугольники с круглым основанием) для белых
    int cYTriW=0; //Коордитата Y отметки варианта хода (зеленые треугольники с круглым основанием) для белых
    int cXTriB=0; //Коордитата X отметки варианта хода (зеленые треугольники с круглым основанием) для черных
    int cYTriB=0; //Коордитата Y отметки варианта хода (зеленые треугольники с круглым основанием) для черных

    //Перемещаем отметки вариантов ходов (зеленые треугольники с круглым основанием)
    for (int inx=0; inx < 25; inx++)
    {
        //Вычисляем координаты отметок вариантов ходов (зеленые треугольники с круглым основанием) для белых треугольников
        switch (inx)
        {
        case 0:  cXTriW=675-betweenTri*inx-3; cYTriW=42; break;
        case 1:  cXTriW=675-betweenTri*inx; cYTriW=42; break;
        case 2:  cXTriW=675-betweenTri*inx-3; cYTriW=42; break;
        case 3:  cXTriW=675-betweenTri*inx-3; cYTriW=42; break;
        case 4:  cXTriW=675-betweenTri*inx-3; cYTriW=42; break;
        case 5:  cXTriW=675-betweenTri*inx-3; cYTriW=42; break;

        case 6:  cXTriW=675-betweenTri*inx-62-9; cYTriW=42-5; break;
        case 7:  cXTriW=675-betweenTri*inx-62-9; cYTriW=42-6; break;
        case 8:  cXTriW=675-betweenTri*inx-62-5; cYTriW=42-6; break;
        case 9:  cXTriW=675-betweenTri*inx-62-5; cYTriW=42-6; break;
        case 10: cXTriW=675-betweenTri*inx-62-5; cYTriW=42-7; break;
        case 11: cXTriW=675-betweenTri*inx-62-6; cYTriW=42-7; break;

        case 12: cXTriW=80+betweenTri*(inx-12); cYTriW=350; break;
        case 13: cXTriW=80+betweenTri*(inx-12); cYTriW=350; break;
        case 14: cXTriW=80+betweenTri*(inx-12); cYTriW=350; break;
        case 15: cXTriW=80+betweenTri*(inx-12); cYTriW=350; break;
        case 16: cXTriW=80+betweenTri*(inx-12)-3; cYTriW=350; break;
        case 17: cXTriW=80+betweenTri*(inx-12)-3; cYTriW=350; break;

        case 18: cXTriW=80+betweenTri*(inx-12)+62+2; cYTriW=350; break;
        case 19: cXTriW=80+betweenTri*(inx-12)+62+2; cYTriW=350; break;
        case 20: cXTriW=80+betweenTri*(inx-12)+62+2; cYTriW=350; break;
        case 21: cXTriW=80+betweenTri*(inx-12)+62+2; cYTriW=350; break;
        case 22: cXTriW=80+betweenTri*(inx-12)+62+4; cYTriW=350; break;
        case 23: cXTriW=80+betweenTri*(inx-12)+62+2; cYTriW=350; break;

        case 24: cXTriW=80+betweenTri*(inx-12)+97; cYTriW=420; break;


        default:;
        }

        if ((inx>=0) && (inx<=11))
        {
            vecTriWhiteFishs[inx]->wgtVarMoveTri->setPicture(":/triangleTopBottom1.png");
        }
        else
        {
            vecTriWhiteFishs[inx]->wgtVarMoveTri->setPicture(":/triangleBottomTop1.png");

        }
        //Перемещаем отметку вариантов ходов (зеленые треугольники с круглым основанием) для белого треугольника
        vecTriWhiteFishs[inx]->wgtVarMoveTri->move(cXTriW,cYTriW);

        //Вычисляем координаты отметок вариантов ходов (зеленые треугольники с круглым основанием) для черных треугольников
        switch (inx)
        {
        case 0: cXTriB=80+betweenTri*inx; cYTriB=350; break;
        case 1: cXTriB=80+betweenTri*inx; cYTriB=350; break;
        case 2: cXTriB=80+betweenTri*inx; cYTriB=350; break;
        case 3: cXTriB=80+betweenTri*inx; cYTriB=350; break;
        case 4: cXTriB=80+betweenTri*inx-3; cYTriB=350; break;
        case 5: cXTriB=80+betweenTri*inx-3; cYTriB=350; break;

        case 6: cXTriB=80+betweenTri*inx+62+2; cYTriB=350; break;
        case 7: cXTriB=80+betweenTri*inx+62+2; cYTriB=350; break;
        case 8: cXTriB=80+betweenTri*inx+62+2; cYTriB=350; break;
        case 9: cXTriB=80+betweenTri*inx+62+2; cYTriB=350; break;
        case 10: cXTriB=80+betweenTri*inx+62+4; cYTriB=350; break;
        case 11: cXTriB=80+betweenTri*inx+62+2; cYTriB=350; break;


        case 12:  cXTriB=675-betweenTri*(inx-12)-3; cYTriB=42; break;
        case 13:  cXTriB=675-betweenTri*(inx-12); cYTriB=42; break;
        case 14:  cXTriB=675-betweenTri*(inx-12)-3; cYTriB=42; break;
        case 15:  cXTriB=675-betweenTri*(inx-12)-3; cYTriB=42; break;
        case 16:  cXTriB=675-betweenTri*(inx-12)-3; cYTriB=42; break;
        case 17:  cXTriB=675-betweenTri*(inx-12)-3; cYTriB=42; break;

        case 18:  cXTriB=675-betweenTri*(inx-12)-62-9; cYTriB=42-5; break;
        case 19:  cXTriB=675-betweenTri*(inx-12)-62-9; cYTriB=42-6; break;
        case 20:  cXTriB=675-betweenTri*(inx-12)-62-5; cYTriB=42-6; break;
        case 21:  cXTriB=675-betweenTri*(inx-12)-62-5; cYTriB=42-6; break;
        case 22: cXTriB=675-betweenTri*(inx-12)-62-5; cYTriB=42-7; break;
        case 23: cXTriB=675-betweenTri*(inx-12)-62-6; cYTriB=42-7; break;

        case 24: cXTriB=675-betweenTri*(inx-12)-100; cYTriB=-30; break;

        default:;
        }

        if ((inx>=0) && (inx<=11))
        {
            vecTriBlackFishs[inx]->wgtVarMoveTri->setPicture(":/triangleBottomTop1.png");
        }
        else
        {
            vecTriBlackFishs[inx]->wgtVarMoveTri->setPicture(":/triangleTopBottom1.png");
        }
        //Перемещаем отметку вариантов ходов (зеленые треугольники с круглым основанием) для черного треугольника
        vecTriBlackFishs[inx]->wgtVarMoveTri->move(cXTriB,cYTriB);

    }

    //Перемещаем фишки и отметки вариантов ходов (зеленые кружки)
    for (int inx=0; inx < 25; inx++)
    {
        //Для треугольников с белыми фишками
        int maxWhiteX(0); //Координата X для отметок вариантов ходов (wgtVarMove)
        int maxWhiteY(0); //Координата Y для отметок вариантов ходов (wgtVarMove)
        //Для треугольников с белыми фишками
        for (int i=0; i < vecTriWhiteFishs[inx]->stkFishs.size(); i++)
        {
            int cX(0); //Координата X для i-й фишки треугольника idx
            int cY(0); //Координата Y для i-й фишки треугольника idx
            switch (inx)
            {
            case 0:  cX=675-betweenTri*inx; cY=45 + 38 * i; break;
            case 1:  cX=675-betweenTri*inx; cY=45 + 38 * i; break;
            case 2:  cX=675-betweenTri*inx; cY=45 + 38 * i; break;
            case 3:  cX=675-betweenTri*inx; cY=45 + 38 * i; break;
            case 4:  cX=675-betweenTri*inx; cY=45 + 38 * i; break;
            case 5:  cX=675-betweenTri*inx; cY=45 + 38 * i; break;

            case 6:  cX=675-betweenTri*inx-62; cY=47 + 38 * i -5; break;
            case 7:  cX=675-betweenTri*inx-62; cY=47 + 38 * i -6; break;
            case 8:  cX=675-betweenTri*inx-62; cY=47 + 38 * i -6; break;
            case 9:  cX=675-betweenTri*inx-62; cY=47 + 38 * i -6; break;
            case 10: cX=675-betweenTri*inx-62; cY=47 + 38 * i -7; break;
            case 11: cX=675-betweenTri*inx-62; cY=47 + 38 * i -7; break;

            case 12: cX=80+betweenTri*(inx-12); cY=625 - 38 * i; break;
            case 13: cX=80+betweenTri*(inx-12); cY=625 - 38 * i; break;
            case 14: cX=80+betweenTri*(inx-12)+2; cY=625 - 38 * i; break;
            case 15: cX=80+betweenTri*(inx-12)+3; cY=625 - 38 * i; break;
            case 16: cX=80+betweenTri*(inx-12)+3; cY=625 - 38 * i; break;
            case 17: cX=80+betweenTri*(inx-12)+4; cY=625 - 38 * i; break;

            case 18: cX=80+betweenTri*(inx-12)+62+1; cY=625 - 38 * i; break;
            case 19: cX=80+betweenTri*(inx-12)+62+2; cY=625 - 38 * i; break;
            case 20: cX=80+betweenTri*(inx-12)+62+5; cY=625 - 38 * i; break;
            case 21: cX=80+betweenTri*(inx-12)+62+5; cY=625 - 38 * i; break;
            case 22: cX=80+betweenTri*(inx-12)+62+5; cY=625 - 38 * i; break;
            case 23: cX=80+betweenTri*(inx-12)+62+5; cY=625 - 38 * i; break;

            case 24: cX=80+betweenTri*(inx-12)+62+40; cY=625 - 38 * i + 40; break;


            default:;
            }
            //Перемещаем белую фишку
            vecTriWhiteFishs[inx]->stkFishs[i]->move(cX,cY);

            maxWhiteX=cX;
            if (inx <=11)
                maxWhiteY=cY+40;
            else
                maxWhiteY=cY-40;
        }

        //Если в белом треугольнике нет фишек
        if (vecTriWhiteFishs[inx]->stkFishs.size()==0)
        {
            switch (inx)
            {
            case 0:  maxWhiteX=675-betweenTri*inx; maxWhiteY=45; break;
            case 1:  maxWhiteX=675-betweenTri*inx; maxWhiteY=45; break;
            case 2:  maxWhiteX=675-betweenTri*inx; maxWhiteY=45; break;
            case 3:  maxWhiteX=675-betweenTri*inx; maxWhiteY=45; break;
            case 4:  maxWhiteX=675-betweenTri*inx; maxWhiteY=45; break;
            case 5:  maxWhiteX=675-betweenTri*inx; maxWhiteY=45; break;

            case 6:  maxWhiteX=675-betweenTri*inx-62; maxWhiteY=47 -5; break;
            case 7:  maxWhiteX=675-betweenTri*inx-62; maxWhiteY=47 -6; break;
            case 8:  maxWhiteX=675-betweenTri*inx-62; maxWhiteY=47 -6; break;
            case 9:  maxWhiteX=675-betweenTri*inx-62; maxWhiteY=47 -6; break;
            case 10: maxWhiteX=675-betweenTri*inx-62; maxWhiteY=47 -7; break;
            case 11: maxWhiteX=675-betweenTri*inx-62; maxWhiteY=47 -7; break;

            case 12: maxWhiteX=80+betweenTri*(inx-12); maxWhiteY=625; break;
            case 13: maxWhiteX=80+betweenTri*(inx-12); maxWhiteY=625; break;
            case 14: maxWhiteX=80+betweenTri*(inx-12)+2; maxWhiteY=625; break;
            case 15: maxWhiteX=80+betweenTri*(inx-12)+3; maxWhiteY=625; break;
            case 16: maxWhiteX=80+betweenTri*(inx-12)+3; maxWhiteY=625; break;
            case 17: maxWhiteX=80+betweenTri*(inx-12)+4; maxWhiteY=625; break;

            case 18: maxWhiteX=80+betweenTri*(inx-12)+62+1; maxWhiteY=625; break;
            case 19: maxWhiteX=80+betweenTri*(inx-12)+62+2; maxWhiteY=625; break;
            case 20: maxWhiteX=80+betweenTri*(inx-12)+62+5; maxWhiteY=625; break;
            case 21: maxWhiteX=80+betweenTri*(inx-12)+62+5; maxWhiteY=625; break;
            case 22: maxWhiteX=80+betweenTri*(inx-12)+62+5; maxWhiteY=625; break;
            case 23: maxWhiteX=80+betweenTri*(inx-12)+62+5; maxWhiteY=625; break;

            case 24: maxWhiteX=80+betweenTri*(inx-12)+62+40; maxWhiteY=625 + 40; break;


            default:;
            }
        }

        //Перемещаем отметку вариантов ходов (wgtVarMove) для белого треугольника
        vecTriWhiteFishs[inx]->wgtVarMove->move(maxWhiteX,maxWhiteY);

        //Для треугольников с черными фишками
        int maxBlackX(0); //Координата X для отметок вариантов ходов (wgtVarMove)
        int maxBlackY(0); //Координата Y для отметок вариантов ходов (wgtVarMove)
        //Для треугольников с черными фишками
        for (int i=0; i < vecTriBlackFishs[inx]->stkFishs.size(); i++)
        {
            int cX(0); //Координата X
            int cY(0); //Координата Y
            switch (inx)
            {
            case 0: cX=80+betweenTri*inx; cY=625 - 38 * i; break;
            case 1: cX=80+betweenTri*inx; cY=625 - 38 * i; break;
            case 2: cX=80+betweenTri*inx+2; cY=625 - 38 * i; break;
            case 3: cX=80+betweenTri*inx+3; cY=625 - 38 * i; break;
            case 4: cX=80+betweenTri*inx+3; cY=625 - 38 * i; break;
            case 5: cX=80+betweenTri*inx+4; cY=625 - 38 * i; break;

            case 6: cX=80+betweenTri*inx+62+1; cY=625 - 38 * i; break;
            case 7: cX=80+betweenTri*inx+62+2; cY=625 - 38 * i; break;
            case 8: cX=80+betweenTri*inx+62+5; cY=625 - 38 * i; break;
            case 9: cX=80+betweenTri*inx+62+5; cY=625 - 38 * i; break;
            case 10: cX=80+betweenTri*inx+62+5; cY=625 - 38 * i; break;
            case 11: cX=80+betweenTri*inx+62+5; cY=625 - 38 * i; break;

            case 12:  cX=675-betweenTri*(inx-12); cY=45 + 38 * i; break;
            case 13:  cX=675-betweenTri*(inx-12); cY=45 + 38 * i; break;
            case 14:  cX=675-betweenTri*(inx-12); cY=45 + 38 * i; break;
            case 15:  cX=675-betweenTri*(inx-12); cY=45 + 38 * i; break;
            case 16:  cX=675-betweenTri*(inx-12); cY=45 + 38 * i; break;
            case 17:  cX=675-betweenTri*(inx-12); cY=45 + 38 * i; break;

            case 18:  cX=675-betweenTri*(inx-12)-62; cY=47 + 38 * i -5; break;
            case 19:  cX=675-betweenTri*(inx-12)-62; cY=47 + 38 * i -6; break;
            case 20:  cX=675-betweenTri*(inx-12)-62; cY=47 + 38 * i -6; break;
            case 21:  cX=675-betweenTri*(inx-12)-62; cY=47 + 38 * i -6; break;
            case 22: cX=675-betweenTri*(inx-12)-62; cY=47 + 38 * i -7; break;
            case 23: cX=675-betweenTri*(inx-12)-62; cY=47 + 38 * i -7; break;

            case 24: cX=675-betweenTri*(inx-12)-62-30; cY=47 + 38 * i -7 -40; break;

            default:;
            }
            //Перемещаем черную фишку
            vecTriBlackFishs[inx]->stkFishs[i]->move(cX,cY);

            maxBlackX=cX;
            if (inx <=11)
                maxBlackY=cY-40;
            else
                maxBlackY=cY+40;
        }

        //Если в черном треугольнике нет фишек
        if (vecTriBlackFishs[inx]->stkFishs.size()==0)
        {
            switch (inx)
            {
            case 0: maxBlackX=80+betweenTri*inx; maxBlackY=625; break;
            case 1: maxBlackX=80+betweenTri*inx; maxBlackY=625; break;
            case 2: maxBlackX=80+betweenTri*inx+2; maxBlackY=625; break;
            case 3: maxBlackX=80+betweenTri*inx+3; maxBlackY=625; break;
            case 4: maxBlackX=80+betweenTri*inx+3; maxBlackY=625; break;
            case 5: maxBlackX=80+betweenTri*inx+4; maxBlackY=625; break;

            case 6: maxBlackX=80+betweenTri*inx+62+1; maxBlackY=625; break;
            case 7: maxBlackX=80+betweenTri*inx+62+2; maxBlackY=625; break;
            case 8: maxBlackX=80+betweenTri*inx+62+5; maxBlackY=625; break;
            case 9: maxBlackX=80+betweenTri*inx+62+5; maxBlackY=625; break;
            case 10: maxBlackX=80+betweenTri*inx+62+5; maxBlackY=625; break;
            case 11: maxBlackX=80+betweenTri*inx+62+5; maxBlackY=625; break;

            case 12:  maxBlackX=675-betweenTri*(inx-12); maxBlackY=45; break;
            case 13:  maxBlackX=675-betweenTri*(inx-12); maxBlackY=45; break;
            case 14:  maxBlackX=675-betweenTri*(inx-12); maxBlackY=45; break;
            case 15:  maxBlackX=675-betweenTri*(inx-12); maxBlackY=45; break;
            case 16:  maxBlackX=675-betweenTri*(inx-12); maxBlackY=45; break;
            case 17:  maxBlackX=675-betweenTri*(inx-12); maxBlackY=45; break;

            case 18:  maxBlackX=675-betweenTri*(inx-12)-62; maxBlackY=47 -5; break;
            case 19:  maxBlackX=675-betweenTri*(inx-12)-62; maxBlackY=47 -6; break;
            case 20:  maxBlackX=675-betweenTri*(inx-12)-62; maxBlackY=47 -6; break;
            case 21:  maxBlackX=675-betweenTri*(inx-12)-62; maxBlackY=47 -6; break;
            case 22: maxBlackX=675-betweenTri*(inx-12)-62; maxBlackY=47 -7; break;
            case 23: maxBlackX=675-betweenTri*(inx-12)-62; maxBlackY=47 -7; break;

            case 24: maxBlackX=675-betweenTri*(inx-12)-62-30; maxBlackY=47 -7 -40; break;

            default:;
            }
        }

        //Перемещаем отметку вариантов ходов (wgtVarMove) для черного треугольника
        vecTriBlackFishs[inx]->wgtVarMove->move(maxBlackX,maxBlackY);
    }
}


