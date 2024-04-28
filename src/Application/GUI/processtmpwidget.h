#ifndef PROCESSTMPWIDGET_H
#define PROCESSTMPWIDGET_H

#include <QLabel>
#include <QMovie>

class processTmpWidget: public QLabel
{
public:
    processTmpWidget(QWidget* backgroundWidget);

    void Show();
    void Hide();

    ~processTmpWidget();

private:

    QMovie* gif;

    QWidget* backgroundWidget;

};

#endif // PROCESSTMPWIDGET_H
