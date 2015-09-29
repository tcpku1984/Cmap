#ifndef TREEMAP_H
#define TREEMAP_H

#include <QWidget>
#include <widget.h>
#include<region.h>
namespace Ui {
class treeMap;
}

class treeMap : public QWidget
{
    Q_OBJECT

public:
    explicit treeMap(QWidget *parent = 0,Region* region=NULL);
    ~treeMap();
    void paintEvent(QPaintEvent * event);



    Region *region() const;
    void setRegion(Region *region);

    QList<QColor> getDataColor1() const;
    void setDataColor1(const QList<QColor> &value);

    QList<QColor> getDataColor2() const;
    void setDataColor2(const QList<QColor> &value);

private:
    Ui::treeMap *ui;
    Region *m_region;
    void drawSqTreeMap(qreal x,qreal y,qreal width,qreal length,int pos,QList<float> * data, QPainter * p);
    void drawSqTreeMap2(qreal x,qreal y,qreal width,qreal length,int pos,QList<float> * data, QPainter * p);
    qreal calRatio(qreal w, qreal l, int pos, int number, QList<float> *data);
    qreal calRatio2(qreal w, qreal l, int pos, int number, QList<float> *data);
    QList<QColor> dataColor;
    QList<QColor> dataColor1;
    QList<QColor> dataColor2;

};

#endif // TREEMAP_H
