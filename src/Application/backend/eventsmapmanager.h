#ifndef EVENTSMAPMANAGER_H
#define EVENTSMAPMANAGER_H

#include <QObject>

// Класс информатор об событиях в менеджере карт
class EventsMapManager: public QObject
{
    Q_OBJECT
signals:

    //
    void error(int codeError);

    //
    void changedCurrentMap();

    //
    void removeMap(const QString& nameMap);

    //
    void startCreateMap();
    void finishCreateMap();

    //
    void startOpenMap();
    void finishOpenMap();

public:

    // Коды ошибок
    enum errors{open, create, remove,
                none, fatal};

    EventsMapManager() {}
};

#endif // EVENTSMAPMANAGER_H
