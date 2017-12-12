/**
  *@file widget.h
  * @author Chao Tong
  * @date 10 Jan 2016
 * @brief The widget class is to layout the region node, includes
 * cartergraphy map generation and treemap display
 * with different user options
  */
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include<QGraphicsScene>
#include<TC_areateam.h>
#include<TC_region.h>
#include<TC_treemap.h>
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
#include<TC_rectholder.h>
#include<QGradient>
#include<TC_areatreemap.h>
#include<stdlib.h>
#include<cmath>
#include<QColorDialog>
#include<TC_regionfile.h>
#include<TC_datacolor.h>
#include<TC_statistics.h>
#include<linechart.h>
#include<QWheelEvent>
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
    /**
     * @brief paintEvent main painting method that draw the whole layout
     * @param event
     */
    void paintEvent(QPaintEvent * event);
    /**
     * @brief wheelEvent zoom in and out
     * @param event
     */
    void wheelEvent(QWheelEvent *event);
    /**
     * @brief paintCCg draw for region node display
     * @param painter from main paintevent class
     */
    void paintCCg(QPainter * painter);
    /**
     * @brief paintArea draw for area group display
     * @param painter from main paintevent class
     */
    void paintArea(QPainter * painter);
    /**
     * @brief regionIncrease for region node increase
     */
    void regionIncrease();
    /**
     * @brief regionIncrease2 for region node increase in one loop
     */
    void regionIncrease2();
    /**
     * @brief areaIncrease for area group increase
     */
    void areaIncrease();
    QList<Region *> * overlap(int k);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent * e);

    void drawTreeMap(qreal x,qreal y,qreal width,qreal length,QList<double> * data, QPainter * p);
    QList <rectHolder *> * drawSqTreeMap(qreal x,qreal y,qreal width,qreal length,int pos,QList<double> * data, QPainter * p,int layer,int j);
    void drawLineChart(qreal x,qreal y,qreal s,int j, QPainter * p);
    void drawGlyphChart(qreal x,qreal y,qreal s,int j, QPainter * p);
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

    int getPercent() const;
    void setPercent(int Percent);

    bool getScreen() const;
    void setScreen(bool Screen);

    bool getConer() const;
    void setConer(bool Coner);

    bool getCenterLines() const;
    void setCenterLines(bool CenterLines);

    int getError() const;
    void setError(int Error);

    QList<Region *> *getLastregion() const;
    void setLastregion(QList<Region *> *Lastregion);

    QList<Region *> *getCurrentregion() const;
    void setCurrentregion(QList<Region *> *Currentregion);

    int getLoopCount() const;
    void setLoopCount(int LoopCount);

    bool getCenterPoints() const;
    void setCenterPoints(bool CenterPoints);

    bool getStep() const;
    void setStep(bool Step);

    int getLocalPercentage() const;
    void setLocalPercentage(int LocalPercentage);

    int getLocalError() const;
    void setLocalError(int LocalError);

    QList<Region *> *getLastYregion() const;
    void setLastYregion(QList<Region *> *LastYregion);

    QList<Region *> *getCurrentYregion() const;
    void setCurrentYregion(QList<Region *> *CurrentYregion);

    int getLocalYError() const;
    void setLocalYError(int LocalYError);

    int getYError() const;
    void setYError(int YError);

    bool getXcross() const;
    void setXcross(bool Xcross);

    bool getYcross() const;
    void setYcross(bool Ycross);

    QList<AreaTeam *> *getLastregionA() const;
    void setLastregionA(QList<AreaTeam *> *LastregionA);

    QList<AreaTeam *> *getCurrentregionA() const;
    void setCurrentregionA(QList<AreaTeam *> *CurrentregionA);

    QList<AreaTeam *> *getLastYregionA() const;
    void setLastYregionA(QList<AreaTeam *> *LastYregionA);

    QList<AreaTeam *> *getCurrentYregionA() const;
    void setCurrentYregionA(QList<AreaTeam *> *CurrentYregionA);

    bool getBColor() const;
    void setBColor(bool BColor);

    int getOpacity() const;
    void setOpacity(int Opacity);

    int getDataYear() const;
    void setDataYear(int dataYear);

    int getAspectRatio() const;
    void setAspectRatio(int aspectRatio);


    QList<QList<Region *> *> *getFileList() const;
    void setFileList(QList<QList<Region *> *> *FileList);

    int getTrend() const;
    void setTrend(int Trend);

    bool getBottomStair() const;
    void setBottomStair(bool bottomStair);

    bool getSingleYear() const;
    void setSingleYear(bool singleYear);

    int getGap() const;
    void setGap(int Gap);

    bool getShowDifference() const;
    void setShowDifference(bool showDifference);

    bool getLineChart() const;
    void setLineChart(bool LineChart);

    QList<int> *getDataCheck() const;
    void setDataCheck(QList<int> *dataCheck);

    QList<Region *> *getRegionListSave() const;
    void setRegionListSave(QList<Region *> *regionListSave);

    bool getRiverBoundary() const;
    void setRiverBoundary(bool riverBoundary);

public slots:
    void animate();
    void animation();
    void animationRiver();

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


    void on_checkBox_10_toggled(bool checked);

    void on_checkBox_11_toggled(bool checked);

    void on_checkBox_12_toggled(bool checked);

    void on_checkBox_13_toggled(bool checked);

    void on_start_2_pressed();

    void on_horizontalSlider_5_valueChanged(int value);

    void on_start_3_clicked();

    void on_checkBox_14_toggled(bool checked);

    void on_checkBox_15_toggled(bool checked);

    void on_checkBox_16_toggled(bool checked);

    void on_horizontalSlider_6_valueChanged(int value);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_horizontalSlider_7_valueChanged(int value);

    void on_comboBox_4_currentIndexChanged(int index);

    void on_checkBox_17_toggled(bool checked);

    void on_start_4_clicked();

    void on_checkBox_35_toggled(bool checked);

    void on_horizontalSlider_8_valueChanged(int value);

    void on_checkBox_18_toggled(bool checked);

    void on_checkBox_36_toggled(bool checked);

    void on_checkBox_20_toggled(bool checked);

    void on_checkBox_19_toggled(bool checked);

    void on_checkBox_21_toggled(bool checked);

    void on_checkBox_22_toggled(bool checked);

    void on_checkBox_23_toggled(bool checked);

    void on_checkBox_24_toggled(bool checked);

    void on_checkBox_25_toggled(bool checked);

    void on_checkBox_26_toggled(bool checked);

    void on_checkBox_27_toggled(bool checked);

    void on_checkBox_28_toggled(bool checked);

    void on_checkBox_29_toggled(bool checked);

    void on_checkBox_30_toggled(bool checked);

    void on_checkBox_31_toggled(bool checked);

    void on_checkBox_32_toggled(bool checked);

    void on_start_5_pressed();

    void on_checkBox_37_toggled(bool checked);

private:
    Ui::Widget *ui;
    void addPopulation(int population);
    bool testSouthOverlap(int k);
    void moveNorth(int vOrder);
    bool testNorthOverlap(int k);
    void moveSouth(int vOrder);
    bool testWestOverlap(int k);
    bool testEastOverlap(int k);
    void drawSign(QPainter * p);
    /**
     * @brief overlapRemove using overlap removal to remove region node overlaop
     */
    void overlapRemove();
    /**
     * @brief overlapRemoveArea using overlap removal to remove area group overlap
     */
    void overlapRemoveArea();
    void refreshColor();
    int errorCount(QList<Region *> * r1, QList<Region *> * r2);
    int errorYCount(QList<Region *> * r1, QList<Region *> * r2);
    int errorCountA(QList<AreaTeam *> * r1, QList<AreaTeam *> * r2);
    int errorYCountA(QList<AreaTeam *> * r1, QList<AreaTeam *> * r2);
    //void moveWest();


    QTimer  *timer;
    QTimer *timer2;
    QTimer * timer3;
    QList <Region *> * m_regionListV;
    QList <Region *> * m_regionListH;
    QList <Region *> * m_regionListSave;
    QList <Region *> * m_Lastregion;
    QList <Region *> * m_Currentregion;
    QList <Region *> * m_LastYregion;
    QList <Region *> * m_CurrentYregion;

    QList <AreaTeam *> * m_LastregionA;
    QList <AreaTeam *> * m_CurrentregionA;
    QList <AreaTeam *> * m_LastYregionA;
    QList <AreaTeam *> * m_CurrentYregionA;
    int count;
    int index;
    QList <int> index2;
    int index3;
    int m_increaseSize;
    int m_regionMaxsize;
    int m_searchRange;
    int m_population;
    QElapsedTimer tCount;
    bool pressed;
    bool finished;
    QList<QColor> dataColor0;
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
    QList <QString> m_HealthName;
    int m_Percent;
    dataColor * m_Datacolor;
    bool m_Screen;
    bool m_Coner;
    bool m_CenterLines;
    bool m_CenterPoints;
    int m_Error;
    int m_LocalError;
    int m_LocalYError;
    int m_YError;
    int m_LoopCount;
    bool m_Step;
    int m_LocalPercentage;
    TC_statistics * sta;
    bool m_Xcross;
    bool m_Ycross;
    bool m_BColor;
    int m_Opacity;
    int m_dataYear;
    int m_aspectRatio;
    QList <QList <Region *> *> * m_FileList;
    int m_Trend;
    bool m_bottomStair;
    bool m_singleYear;
    int m_Gap;
    bool m_showDifference;
    bool m_LineChart;
    bool m_riverBoundary;
    QList <int> * m_dataCheck;
    QList <QPolygonF *> * m_polygonList;
    QList <QString> * m_River;
    QPolygonF * riverPoly;
    int m_crossCount;
    int m_same;
    QList <QPointF *> * sameList;
    QList <int> * sameListIndex;
    bool m_pushingLine=false;
    QPointF P0,P1;
    QList <QPointF *> * m_pushingList;
    qreal scale;


};

#endif // WIDGET_H
