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
       bool color=false, AreaTeam * area=NULL,QList <float>* aver=NULL);
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

    bool getOtherColor() const;
    void setOtherColor(bool otherColor);





    QList<float> *getAveragePrevlance() const;
    void setAveragePrevlance(QList<float> *AveragePrevlance);

    void mousePressEvent(QMouseEvent * e);

    QList<rectHolder *> *getRectList() const;
    void setRectList(QList<rectHolder *> *RectList);

    int getWindowsnumber() const;
    void setWindowsnumber(int Windowsnumber);


private:
    Ui::areaTreemap *ui;
    AreaTeam * m_Area;
    QList <rectHolder *> * drawSqTreeMap(qreal x,qreal y,qreal width,qreal length,int pos,QList<float> * data, QPainter * p);
    QList <rectHolder *> * drawSqTreeMap2(qreal x,qreal y,qreal width,qreal length,int pos,QList<float> * data, QPainter * p);
    qreal calRatio(qreal w, qreal l, int pos, int number, QList<float> *data);
    qreal calRatio2(qreal w, qreal l, int pos, int number, QList<float> *data);
    QList<QColor> dataColor;
    QList<QColor> dataColor1;
    QList<QColor> dataColor2;
    bool m_lookAhead;
    bool m_otherColor;
    QList <float> * m_AveragePrevlance;
    QList <rectHolder *> * m_RectList;
    int m_Windowsnumber;
private slots:
    void windowClose();


};

#endif // AREATREEMAP_H
