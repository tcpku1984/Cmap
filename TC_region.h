/**
  *@file region.h
  * @author Chao Tong
  * @date 10 Jan 2016
 * @brief The region class
 * This class is to represent a single region node on the layout.
 * It contains all the information of a single CCG region
 * latitude,longtitude,X,Y position on the layout
 * population, and healthcare data
  */
#ifndef REGION_H
#define REGION_H
#include <QString>
#include <QList>
#include <iostream>
#include <QPointF>
using namespace std;
class Region
{
public:
    Region();
    ~Region();
    /**
     * accessing method for class member
     */


    double Lati() const;
    void setLati(double Lati);

    double Longti() const;
    void setLongti(double Longti);

    int poplation() const;
    void setPoplation(int poplation);

    qreal Y() const;
    void setY(qreal Y);

    bool stopIncrease() const;
    void setStopIncrease(bool stopIncrease);



    QString ccgCode() const;
    void setCcgCode(const QString &ccgCode);

    QString ccgName() const;
    void setCcgName(const QString &ccgName);

    qreal X() const;
    void setX(qreal X);

    int getSize() const;
    void setSize(int value);
    /**
     * @brief increase increase region node by 1 piexl
     */
    void increase();
    /**
     * @brief stop stop region node increment when it reach the maximum size
     */
    void stop();
    void moveNorth();
    void moveSouth();
    void moveWest();
    void moveEast();

    void addCrossingRegion(Region * r);

    int color() const;
    void setColor(int color);

    bool detail() const;
    void setDetail(bool detail);

    QList<double> *healthData() const;
    void setHealthData(QList<double> *healthData);

    int getColorIndex() const;
    void setColorIndex(int ColorIndex);

    int getVOrder() const;
    void setVOrder(int value);

    int getHOrder() const;
    void setHOrder(int value);

    int getError() const;
    void setError(int Error);



    QList<Region *> *getCrossing() const;
    void setCrossing(QList<Region *> *Crossing);

    int getRiverSide() const;
    void setRiverSide(int riverSide);

    qreal getLastX() const;
    void setLastX(qreal lastX);

    qreal getLastY() const;
    void setLastY(qreal lastY);

    bool getCrossRiver() const;
    void setCrossRiver(bool crossRiver);

    qreal getCurrentX() const;
    void setCurrentX(qreal currentX);

    qreal getCurrentY() const;
    void setCurrentY(qreal currentY);

    bool getInterSection() const;
    void setInterSection(bool interSection);

    QList<QPointF *> *getPointList() const;
    void setPointList(QList<QPointF *> *value);

    void addPoint();
    void clearPointList();



    QList<int> *getSizeList() const;
    void setSizeList(QList<int> *value);

private:
    /**
     * @brief m_ccgCode information of ccg code
     */
    QString m_ccgCode;
    /**
     * @brief m_ccgName information of ccg name
     */
    QString m_ccgName;
    /**
     * @brief m_Lati information of latitude
     */

    double m_Lati;
    /**
     * @brief m_Longti information of longtitude
     */
    double m_Longti;
    /**
     * @brief m_poplation information of population
     */
    int m_poplation;
    /**
     * @brief m_X information of x position on map
     */

    qreal m_X;
    /**
     * @brief m_Oy information of horizontal order
     */
    qreal m_Y;
    /**
     * @brief m_stopIncrease information of whether point
     * can do increment or not
     */
    bool m_stopIncrease;
    /**
     * @brief m_ColorIndex define the color of region
     */
    int m_ColorIndex;
    /**
     * @brief m_healthData list of health care data
     */

    QList <double> * m_healthData;

    int size;
    int m_color;
    bool m_detail;
    int vOrder;
    int hOrder;
    int m_Error;
    QList<Region *> * m_Crossing;
    int m_riverSide;
    qreal m_lastX;
    qreal m_lastY;
    qreal m_currentX;
    qreal m_currentY;
    bool m_crossRiver;
    bool m_interSection;
    QList <QPointF*> * pointList;
    QList <int>  *sizeList;


};

#endif // Region_H
