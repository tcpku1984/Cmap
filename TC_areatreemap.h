#ifndef AREATREEMAP_H
#define AREATREEMAP_H

#include <QWidget>
#include <TC_widget.h>
#include<TC_region.h>

#include<TC_rectholder.h>
#include<QGradient>
#include <QLinearGradient>
#include <TC_areateam.h>
#include<QMouseEvent>
#include<TC_datacolor.h>
namespace Ui {
class areaTreemap;
}
/**
  *@file areaTreemap.h
  * @author Chao Tong
  * @date 10 Jan 2016
 * @brief The AreaTreemap class
 * This class is to display a detail treemap of one area group node
 * It work as similar as treemap class for single region node
  */
class areaTreemap : public QWidget
{
    Q_OBJECT

public:
    explicit areaTreemap(QWidget *parent = 0,
       int color=2, AreaTeam * area=NULL,QList <double>* aver=NULL);
    ~areaTreemap();
    void paintEvent(QPaintEvent * event);

    AreaTeam *Area() const;
    void setArea(AreaTeam *Area);





    QList<double> *getAveragePrevlance() const;
    void setAveragePrevlance(QList<double> *AveragePrevlance);

    void mousePressEvent(QMouseEvent * e);

    QList<rectHolder *> *getRectList() const;
    void setRectList(QList<rectHolder *> *RectList);

    int getWindowsnumber() const;
    void setWindowsnumber(int Windowsnumber);


    bool getMapDifference() const;
    void setMapDifference(bool Mapdifference);

    int getBorder() const;
    void setBorder(int border);

    int getColor() const;
    void setColor(int Color);

    bool getGradient() const;
    void setGradient(bool gradient);

    QColor getBorderColor() const;
    void setBorderColor(const QColor &BorderColor);

    bool getFont() const;
    void setFont(bool Font);

    bool getCgroup() const;
    void setCgroup(bool Cgroup);

    int getFilter() const;
    void setFilter(int Filter);

private:
    Ui::areaTreemap *ui;
    AreaTeam * m_Area;
    QList <rectHolder *> * drawSqTreeMap(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p,int layer);
    QList <rectHolder *> * drawSqTreeMap2(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p);
    qreal calRatio(qreal w, qreal l, int pos, int number, QList<double> *data);
    qreal calRatio2(qreal w, qreal l, int pos, int number, QList<double> *data);
    QList<QColor> dataColor0;
    bool m_lookAhead;
    int m_Color;
    QList <double> * m_AveragePrevlance;
    QList <rectHolder *> * m_RectList;
    int m_Windowsnumber;
    bool m_MapDifference;
    int m_border;
    bool m_gradient;
    QColor m_BorderColor;
    bool m_Font;
    bool m_Cgroup;
    int m_Filter;
    dataColor *m_Datacolor;
private slots:
    void windowClose();



};

#endif // AREATREEMAP_H
