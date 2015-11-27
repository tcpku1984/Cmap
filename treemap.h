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
                     int color = 2,Region* region=NULL,QList<double> *aver=NULL);
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

    int getColor() const;
    void setColor(int Color);

    bool getGradient() const;
    void setGradient(bool gradient);
    bool getFont() const;
    void setFont(bool Font);

    bool getCgroup() const;
    void setCgroup(bool Cgroup);

private:
    Ui::treeMap *ui;
    Region *m_region;
    QList <rectHolder *> * drawSqTreeMap(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p,int layer);
    QList <rectHolder *> * drawSqTreeMap2(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p);
    qreal calRatio(qreal w, qreal l, int pos, int number, QList<double> *data);
    qreal calRatio2(qreal w, qreal l, int pos, int number, QList<double> *data);
    QList<QColor> dataColor;
    QList<QColor> dataColor0;
    QList<QColor> dataColor1;
    QList<QColor> dataColor2;
    QList<QColor> dataColor3;
    QList<QColor> dataColor4;
    bool m_lookAhead;
    int m_Color;
    qreal m_ratioTemp;
    qreal m_totalAsp;
    bool m_MapDifference;
    int m_border;
    bool m_gradient;
    QList <double> * m_AveragePrevlance;
    bool m_Font;
    bool m_Cgroup;

};

#endif // TREEMAP_H
