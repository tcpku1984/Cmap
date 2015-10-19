#ifndef TREEMAP_H
#define TREEMAP_H

#include <QWidget>
#include <widget.h>
#include<region.h>
#include<rectholder.h>
#include<QGradient>
#include <QLinearGradient>
namespace Ui {
class treeMap;
}

class treeMap : public QWidget
{
    Q_OBJECT

public:
    explicit treeMap(QWidget *parent = 0,bool treemap = false,
                     bool color = false,Region* region=NULL,QList<double> *aver=NULL);
    ~treeMap();
    void paintEvent(QPaintEvent * event);



    Region *region() const;
    void setRegion(Region *region);

    QList<QColor> getDataColor1() const;
    void setDataColor1(const QList<QColor> &value);

    QList<QColor> getDataColor2() const;
    void setDataColor2(const QList<QColor> &value);

    bool getLookAhead() const;
    void setLookAhead(bool lookAhead);

    bool getOtherColor() const;
    void setOtherColor(bool otherColor);

    qreal getRatioTemp() const;
    void setRatioTemp(const qreal &ratioTemp);

    qreal getTotalAsp() const;
    void setTotalAsp(const qreal &totalAsp);

    QList<double> *getAveragePrevlance() const;
    void setAveragePrevlance(QList<double> *AveragePrevlance);

    int getBorder() const;
    void setBorder(int border);

    bool getMapDifference() const;
    void setMapDifference(bool MapDifference);

private:
    Ui::treeMap *ui;
    Region *m_region;
    QList <rectHolder *> * drawSqTreeMap(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p,int layer);
    QList <rectHolder *> * drawSqTreeMap2(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p);
    qreal calRatio(qreal w, qreal l, int pos, int number, QList<double> *data);
    qreal calRatio2(qreal w, qreal l, int pos, int number, QList<double> *data);
    QList<QColor> dataColor;
    QList<QColor> dataColor1;
    QList<QColor> dataColor2;
    bool m_lookAhead;
    bool m_otherColor;
    qreal m_ratioTemp;
    qreal m_totalAsp;
    bool m_MapDifference;
    int m_border;
    QList <double> * m_AveragePrevlance;

};

#endif // TREEMAP_H
