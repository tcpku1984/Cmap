#ifndef LINECHART_H
#define LINECHART_H

#include <QWidget>
#include<TC_region.h>
#include <TC_datacolor.h>
#include <QPainter>
#include<QString>

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

    bool getShowDifference() const;
    void setShowDifference(bool showDifference);

private:
    Ui::Linechart *ui;

    int m_Color;
    dataColor * m_Datacolor;
    QList<Region *> * regionList;
    QList<QColor> dataColor0;
    QList<QString> m_HealthName;
    bool m_showDifference;

};

#endif // LINECHART_H
