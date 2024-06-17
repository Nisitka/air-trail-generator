#ifndef GEOGENERATOR_H
#define GEOGENERATOR_H

#include <QObject>

#include "heightmeter.h"
#include "rzinformer.h"
#include "blockinformer.h"

#include "geocolumn.h"

#include "rzcreator.h"

#include "coords.h"
#include "mapdata.h"

class geoGenerator: public QObject,
        public HeightMeter, public RZInformer, public BlockInformer,
        public RZCreator
{
    Q_OBJECT
signals:

    //
    void buildStart();
    void changedProcessBuild(int countPercent); // в %
    void buildFinish(int W, int L, int H);

public:
    geoGenerator(int wArea, int lArea);

    // Редактирование дискрет на наличие РЛ сигнала (RZCreator)
    void toZD(const QVector3D &idBlock) const override final;
    void clearZD(const QVector3D &idBlock) const override final;

    // BlockInformer
    const geoBlock& block(int idX, int idY, int idH) const override final;

    // HeightMeter
    int absolute(int idX, int idY, Map::units u) const override final;
    int max(Map::units u) const override final;
    int heightBlock() const override final;
    int lenghtBlock() const override final;

    // RZInformer
    int countVertZD(int idX, int idY) const override final;

    // В индексах всей карты
    Coords getCoords(int idX, int idY) const;

    // Запуск генерации рельефа
    void buildRandomMap(double setBlockP, int countEpochs,
                        int W, int L, int H,
                        double lenBlock);

    // Создать плоский (пустой) рельеф
    void buildFlatMap(int W = 400, int L = 400, int H = 256);

    // Открыть карту
    void openMap(const QString& dirMapFile);

    // Загрузить рельеф
    void loadTerrain(const QString& dirNameFile);

    // Установить область активных действий
    void setPosActionArea(int idXo, int idYo);

    // Обновить данные по высотам в области
    void updateHeights(int idX, int idY, // Левый верхний угол
                       int W, int L);    // Ширина, длина

    // Отредакутировать рельеф
    void editEarth(int idXo, int idYo,  // Левый верхний угол обл.
                   int w, int l,        // Ширина, длина области
                   int dH, int t = up); // Дельта изм., поднять/опустить
    enum editH{up, down};

    //
    void initMap(int W, int L, int H);

private:

    // mutex
     mutable  bool isLocked;

    // Дискрета в зоне событий?
    bool inActionArea(int idX, int idY) const;

    // Посыпать землей дискрету
    void dropEarth(int idX, int idY, int countLayer);

    // Убрать землю с дискреты
    void removeEarth(int idX, int idY, int countLayer);

    //
    int idBlock(int idX, int idY, int idH) const;

    //  
    int Wmap, Lmap, Hmap;
    QFile* map;
    QString dirNameTmpMap;

    // Кол-во байт в файле карты на:
    qint64 sizeBlock;   // Одну дискрету
    qint64 sizeOptData; // Другие данные

    //
    MapData mapData;

    // Заменить блок
    void updateBlock(int idBlock, const geoBlock& b) const;

    //
    geoBlock readBlock(int idBlock) const;

    //
    mutable geoBlock cacheBlock;

    // Активная зона
    Map* actionArea;
    int idXo;  // Угол
    int idYo;
    int wArea; // Размеры
    int lArea;
    int lastX;
    int lastY;

    // Действия с блоками около указанного
    int  sumEarth(int x, int y, int z); // кол-во с землей
    void builtRandBlock(int x, int y, int z);  // сделать землей случ-й блок
    void removeRandBlock(int x, int y, int z); // удалить случ-й блок

    // Вернуть значение true c указанной вероятностью
    bool P(double p = 0.5);
};

#endif // GEOGENERATOR_H
