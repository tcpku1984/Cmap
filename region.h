/**
  *@file areateam.h
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

    int Y() const;
    void setY(int Y);

    bool stopIncrease() const;
    void setStopIncrease(bool stopIncrease);



    QString ccgCode() const;
    void setCcgCode(const QString &ccgCode);

    QString ccgName() const;
    void setCcgName(const QString &ccgName);

    int X() const;
    void setX(int X);

    int getSize() const;
    void setSize(int value);
    void increase();
    void stop();
    void moveNorth();
    void moveSouth();
    void moveWest();
    void moveEast();

    int color() const;
    void setColor(int color);

    bool detail() const;
    void setDetail(bool detail);

    QList<double> *healthData() const;
    void setHealthData(QList<double> *healthData);

    int getColorIndex() const;
    void setColorIndex(int ColorIndex);

private:
    /**
     * @brief m_ccgCode information of ccg code
     */
    QString m_ccgCode;
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

    int m_X;
    /**
     * @brief m_Oy information of horizontal order
     */
    int m_Y;
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
};

#endif // Region_H
