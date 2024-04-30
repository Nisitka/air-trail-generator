#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include <QObject>

#include <QPoint>

class GraphicEngine: public QObject
{
    Q_OBJECT
signals:

public slots:

    // Какую часть карты отображать в 3D
    void initializeTerrain(int idXo, int idYo,  // id левой верхней дискреты
                           int numW, int numL); // ширина, высота

    // Актуализировать значения матрицы высот
    void updateTerrain(int idXo, int idYo, int W, int L); // в области
    void updateTerrain();

public:
    GraphicEngine(QVector<QVector<int> *>* heights);

private:

    // Матрица высот
    QVector<QVector<int> *>* heights;

    //
    enum interVert{Short, Long}; // ближняя, дальняя

    int idXo;
    int idYo;
    int countX = 15;
    int countY = 15;
    int idLastX;
    int idLastY;

};

#endif // GRAPHICENGINE_H
