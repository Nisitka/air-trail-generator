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

    void setValProgress(int percent);

    ~processTmpWidget();

private:

    QLabel* textLabel;
    bool textIsShow;

    QMovie* gif;
    QWidget* backgroundWidget;

};

#endif // PROCESSTMPWIDGET_H
