#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include<QGraphicsScene>
#include<region.h>
#include<treemap.h>
#include<iostream>
#include<fstream>
#include<QDesktopWidget>
#include<QMouseEvent>
#include<QTimer>
#include<QElapsedTimer>
#include<QPaintEvent>
#include<QPainter>
#include<generate-constraints.h>
#include<remove_rectangle_overlap.h>
using namespace std;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QList<Region *> *regionListV() const;
    void setRegionListV(QList<Region *> *regionListV);

    QList<Region *> *regionListH() const;
    void setRegionListH(QList<Region *> *regionListH);
    void paintEvent(QPaintEvent * event);
    void regionIncrease();
    void regionIncrease2();
    QList<Region *> * overlap(int k);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent *e);

    void drawTreeMap(qreal x,qreal y,qreal width,qreal length,QList<float> * data, QPainter * p);
    void drawSqTreeMap(qreal x,qreal y,qreal width,qreal length,int pos,QList<float> * data, QPainter * p);
    qreal calRatio(qreal w, qreal l, int pos, int number, QList<float> *data);
    void drawSqTreeMap2(qreal x,qreal y,qreal width,qreal length,int pos,QList<float> * data, QPainter * p);
    qreal calRatio2(qreal w, qreal l, int pos, int number, QList<float> *data);


    int increaseSize() const;
    void setIncreaseSize(int increaseSize);

    int regionMaxsize() const;
    void setRegionMaxsize(int regionMaxsize);

    int population() const;
    void setPopulation(int population);

    bool getPressed() const;
    void setPressed(bool value);

    int searchRange() const;
    void setSearchRange(int searchRange);

    bool getFinished() const;
    void setFinished(bool value);

    bool samesize() const;
    void setSamesize(bool samesize);

    int Windowsnumber() const;
    void setWindowsnumber(int Windowsnumber);

    QList<QColor> getDataColor2() const;
    void setDataColor2(const QList<QColor> &value);

    QList<QColor> getDataColor1() const;
    void setDataColor1(const QList<QColor> &value);

public slots:
    void animate();

private slots:
    void on_start_pressed();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_checkBox_toggled(bool checked);

    void windowClose();

private:
    Ui::Widget *ui;
    void fileRead();
    void addPopulation(int population);
    bool testSouthOverlap(int k);
    void moveNorth(int vOrder);
    bool testNorthOverlap(int k);
    void moveSouth(int vOrder);
    bool testWestOverlap(int k);
    bool testEastOverlap(int k);
    void drawSign(QPainter * p);
    void overlapRemove();
    //void moveWest();


    QTimer  *timer;
    QList <Region *> * m_regionListV= new QList<Region *>;
    QList <Region *> * m_regionListH= new QList<Region *>;
    int count;
    int index=0;
    int m_increaseSize=1;
    int m_regionMaxsize=10;
    int m_searchRange=212;
    int m_population=0;
    QElapsedTimer tCount;
    bool pressed;
    bool finished=false;
    QList<QColor> dataColor;
    QList<QColor> dataColor1;
    QList<QColor> dataColor2;
    bool m_samesize=false;
    int m_Windowsnumber=0;

};

#endif // WIDGET_H
