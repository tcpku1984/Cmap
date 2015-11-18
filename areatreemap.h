#ifndef AREATREEMAP_H
#define AREATREEMAP_H

#include <QWidget>
#include <widget.h>
#include<region.h>

#include<rectholder.h>
#include<QGradient>
#include <QLinearGradient>
#include <areateam.h>
#include<QMouseEvent>
namespace Ui {
class areaTreemap;
}

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

    QList<QColor> getDataColor() const;
    void setDataColor(const QList<QColor> &value);

    QList<QColor> getDataColor1() const;
    void setDataColor1(const QList<QColor> &value);

    QList<QColor> getDataColor2() const;
    void setDataColor2(const QList<QColor> &value);






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

private:
    Ui::areaTreemap *ui;
    AreaTeam * m_Area;
    QList <rectHolder *> * drawSqTreeMap(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p,int layer);
    QList <rectHolder *> * drawSqTreeMap2(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p);
    qreal calRatio(qreal w, qreal l, int pos, int number, QList<double> *data);
    qreal calRatio2(qreal w, qreal l, int pos, int number, QList<double> *data);
    QList<QColor> dataColor;
    QList<QColor> dataColor0;
    QList<QColor> dataColor1;
    QList<QColor> dataColor2;
    QList<QColor> dataColor3;
    bool m_lookAhead;
    int m_Color;
    QList <double> * m_AveragePrevlance;
    QList <rectHolder *> * m_RectList;
    int m_Windowsnumber;
    bool m_MapDifference;
    int m_border;
    bool m_gradient;
    QColor m_BorderColor;
private slots:
    void windowClose();


};

#endif // AREATREEMAP_H
