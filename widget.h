#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include<QGraphicsScene>
#include<areateam.h>
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
#include<rectholder.h>
#include<QGradient>
#include<areatreemap.h>
#include<stdlib.h>
#include<cmath>
#include<QColorDialog>
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
    void paintCCg(QPainter * painter);
    void paintArea(QPainter * painter);
    void regionIncrease();
    void regionIncrease2();
    void areaIncrease();
    QList<Region *> * overlap(int k);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent * e);

    void drawTreeMap(qreal x,qreal y,qreal width,qreal length,QList<double> * data, QPainter * p);
    QList <rectHolder *> * drawSqTreeMap(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p,int layer);
    qreal calRatio(qreal w, qreal l, int pos, int number, QList<double> *data);
    QList <rectHolder *> * drawSqTreeMap2(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p);
    qreal calRatio2(qreal w, qreal l, int pos, int number, QList<double> *data);


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

    bool getAlgorithm() const;
    void setAlgorithm(bool algorithm);

    bool getLookAhead() const;
    void setLookAhead(bool lookAhead);

    QList<AreaTeam *> *getAreaGroup() const;
    void setAreaGroup(QList<AreaTeam *> *AreaGroup);

    bool getGroup() const;
    void setGroup(bool group);


    QList<double> *getAveragePrevlance() const;
    void setAveragePrevlance(QList<double> *AveragePrevlance);

    int getBorder() const;
    void setBorder(int border);

    bool getMapDifference() const;
    void setMapDifference(bool mapDifference);

    int getColor() const;
    void setColor(int Color);

    bool getGradient() const;
    void setGradient(bool gradient);

    QColor getBorderColor() const;
    void setBorderColor(const QColor &BorderColor);

    QList<QColor> getDataColor0() const;
    void setDataColor0(const QList<QColor> &value);

    bool getFont() const;
    void setFont(bool Font);

    bool getCgroup() const;
    void setCgroup(bool Cgroup);

    int getFilter() const;
    void setFilter(int Filter);

    bool getColorFilter() const;
    void setColorFilter(bool ColorFilter);

    bool getMouseOver() const;
    void setMouseOver(bool MouseOver);

    int getMouseOverIndex() const;
    void setMouseOverIndex(int MouseOverIndex);

public slots:
    void animate();

private slots:
    void on_start_pressed();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_checkBox_toggled(bool checked);

    void windowClose();

    void on_checkBox_2_toggled(bool checked);

    void on_checkBox_3_toggled(bool checked);


    void on_checkBox_5_toggled(bool checked);


    void on_horizontalSlider_4_valueChanged(int value);

    void on_checkBox_6_toggled(bool checked);

    void on_checkBox_4_toggled(bool checked);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_checkBox_7_toggled(bool checked);

    void on_checkBox_9_toggled(bool checked);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_checkBox_8_toggled(bool checked);

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
    void overlapRemoveArea();
    int searchAreaCode(QString code);
    void refreshColor();
    //void moveWest();


    QTimer  *timer;
    QList <Region *> * m_regionListV;
    QList <Region *> * m_regionListH;
    int count;
    int index;
    int m_increaseSize;
    int m_regionMaxsize;
    int m_searchRange;
    int m_population;
    QElapsedTimer tCount;
    bool pressed;
    bool finished;
    QList<QColor> dataColor;
    QList<QColor> dataColor0;
    QList<QColor> dataColor1;
    QList<QColor> dataColor2;
    QList<QColor> dataColor3;
    QList<QColor> dataColor4;
    bool m_samesize;
    bool m_algorithm;
    bool m_lookAhead;
    bool m_group;
    bool m_mapDifference;
    int m_Windowsnumber;
    QList <AreaTeam *>  * m_AreaGroup;
    QList <double> * m_AveragePrevlance;
    int m_border;
    int m_Color;
    bool m_gradient;
    QColor m_BorderColor;
    bool m_Font;
    bool m_Cgroup;
    int m_Filter;
    bool m_ColorFilter;
    QList <bool> *colorlegend;
    QList<QColor> regionColor;
    bool m_MouseOver;
    int m_MouseOverIndex;


};

#endif // WIDGET_H
