#ifndef OUTPUTDEV_H
#define OUTPUTDEV_H

#include <QWidget>

class OutputDev : public QWidget
{
    Q_OBJECT
public:
    OutputDev(QWidget *parent = 0);
    ~OutputDev();

};

#endif // OUTPUTDEV_H
