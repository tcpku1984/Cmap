#ifndef LINECHART_H
#define LINECHART_H

#include <QWidget>
#include<TC_region.h>
#include <TC_datacolor.h>
#include <QPainter>

namespace Ui {
class Linechart;
}

class Linechart : public QWidget
{
    Q_OBJECT

public:
    explicit Linechart(QWidget *parent = 0);
    ~Linechart();

    void paintEvent(QPaintEvent * event);

    int Color() const;
    void setColor(int Color);

    dataColor *Datacolor() const;
    void setDatacolor(dataColor *Datacolor);

    QList<Region *> *getRegionList() const;
    void setRegionList(QList<Region *> *value);

private:
    Ui::Linechart *ui;

    int m_Color;
    dataColor * m_Datacolor;
    QList<Region *> * regionList;
    QList<QColor> dataColor0;

};

#endif // LINECHART_H
