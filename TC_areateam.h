/**
  *@file areateam.h
  * @author Chao Tong
  * @date 10 Jan 2016
 * @brief The AreaTeam class
 * This class is area group function that put several region nodes
 * with same name and area code into one group and work as one node in the layout
 * It is similar with region class having latitude,longtitude,x,y,population
  */
#ifndef AREATEAM_H
#define AREATEAM_H
#include <QString>
#include <QList>
#include<TC_region.h>
class AreaTeam
{
public:
    AreaTeam();
    ~AreaTeam();
    /**
     * @brief addRegion add a new region into group
     * @param region a region node
     */
    void addRegion(Region * region);

    void initi();
    /**
     * @brief increase increase the size of area by 1 pixel.
     */

    void increase();
    /**
     * @brief AreaCode accessor method
     */

    QString AreaCode() const;
    void setAreaCode(const QString &AreaCode);

    /**
     * @brief AreaName accessor method
     */
    QString AreaName() const;
    void setAreaName(const QString &AreaName);



    QList<Region *> *RegionList() const;
    void setRegionList(QList<Region *> *RegionList);

    int X() const;
    void setX(int X);

    int Y() const;
    void setY(int Y);

    int Population() const;
    void setPopulation(int Population);

    int Size() const;
    void setSize(int Size);

    bool stopIncrease() const;
    void setStopIncrease(bool stopIncrease);

    QList<double> *PopulationList() const;
    void setPopulationList(QList<double> *PopulationList);

private:
    /**
     * @brief m_RegionList a List for region node group
     */
    QList<Region *> * m_RegionList;
    /**
     * @brief m_AreaCode region nodes with same are code are put in same group
     */
    QString m_AreaCode;
    /**
     * @brief m_AreaName region nodes with same area name are put in same group
     */
    QString m_AreaName;
    /**
     * @brief m_lati average latitude for group
     */
    qreal m_lati;
    /**
     * @brief m_longti average longtitude for group
     */
    qreal m_longti;
    /**
     * @brief m_PopulationList list represent population of each region node
     */
    QList<double > * m_PopulationList;
    /**
     * @brief m_X area X position on layout
     */
    int m_X;
    /**
     * @brief m_Y area Y position on layout
     */
    int m_Y;
    /**
     * @brief m_Population total population of area group
     */
    int m_Population;
    /**
     * @brief m_Size the size of population of area on layout
     */
    int m_Size;
    /**
     * @brief m_stopIncrease When reach maximum size, area stop increase
     */
    bool m_stopIncrease;


};

#endif // AREATEAM_H
