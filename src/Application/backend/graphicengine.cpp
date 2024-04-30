#include "graphicengine.h"

GraphicEngine::GraphicEngine(QVector<QVector<int> *>* heights_):
    heights(heights_)
{

}

void GraphicEngine::initializeTerrain(int idXo_, int idYo_, int numW, int numL)
{
    // Дискреты углов
    idXo = idXo_;            // Левый верхний
    idYo = idYo_;
    idLastX = idXo + numW; // Правый нижний
    idLastY = idYo + numL;

    // Размер области
    countX = numW; // Ширина
    countY = numL; // Высота

    // Перерасчет матрицы высот
    //heights.clear();
    for (int idX = idXo; idX < idLastX; idX++)
    {
        //heights.push_back(QVector<int>());
        for (int idY = idYo; idY < idLastY; idY++)
        {
            //heights.last().push_back(map->getHeight(idX, idY));
        }
    }
}

void GraphicEngine::updateTerrain(int idXo_, int idYo_, int W, int L)
{
    // Сразу выходим если никак не попадаем в область отображения
    if (idXo_ > idLastX | idYo_ > idLastY) return;

    // Правая нижняя точка зоны изменения
    int lastIdX = idXo_ + W;
    int lastIdY = idYo_ + L;

    // Если частично попадаем в область
    if (idXo_ < idXo) idXo_ = idXo;
    if (idYo_ < idYo) idYo_ = idYo;

    //
    if (lastIdX > idLastX) lastIdX = idLastX;
    if (lastIdY > idLastY) lastIdY = idLastY;

    //
    if (lastIdX < idXo | lastIdY < idYo) return;

    //
    for (int idX = idXo_; idX < lastIdX; idX++)
    {
        for (int idY = idYo_; idY < lastIdY; idY++)
        {
            //heights[idX-idXo][idY-idYo] = map->getHeight(idX, idY);
        }
    }
}

void GraphicEngine::updateTerrain()
{
    for (int idX = 0; idX < countX; idX++)
    {
        for (int idY = 0; idY < countY; idY++)
        {
            //heights[idX][idY] = map->getHeight(idXo + idX, idYo + idY);
        }
    }
}
