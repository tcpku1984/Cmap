/**
  *@file regionfile.h
  * @author Chao Tong
  * @date 10 Jan 2016
 * @brief The regionFile class is to read the region node information from csv file.
  */
#ifndef REGIONFILE_H
#define REGIONFILE_H
#include<fstream>
#include<TC_region.h>
#include<TC_areateam.h>
#include<QString>
#include<QList>
#include<string>
#include<iostream>
#include<QPolygonF>
using namespace std;
class regionFile
{
public:
    regionFile();
    void readfile(int year);
    void readPolygon();
    void readRiverPolygon();
    void readRiver();
    QList<Region *> *regionList() const;
    void setRegionList(QList<Region *> *regionList);

    QList<double> *AveragePrevlance() const;
    void setAveragePrevlance(QList<double> *AveragePrevlance);

    QList<AreaTeam *> *AreaGroup() const;
    void setAreaGroup(QList<AreaTeam *> *AreaGroup);

    int populiation() const;
    void setPopuliation(int populiation);

    bool display() const;
    void setDisplay(bool display);

    QList<QPolygonF *> *PolygonList() const;
    void setPolygonList(QList<QPolygonF *> *PolygonList);

    QList<QString> *River() const;
    void setRiver(QList<QString> *River);

    QList<QPolygonF *> *RiverPolygonList() const;
    void setRiverPolygonList(QList<QPolygonF *> *RiverPolygonList);

    QList<double> *MinPrevlance() const;
    void setMinPrevlance(QList<double> *MinPrevlance);

    QList<double> *MaxPrevlance() const;
    void setMaxPrevlance(QList<double> *MaxPrevlance);

private:
    int searchAreaCode(QString code);
    QList < Region *> * m_regionList;
    int m_populiation;
    QList <AreaTeam *>  * m_AreaGroup;
    QList<double> * m_AveragePrevlance;
    QList<double> * m_MinPrevlance;
    QList<double> * m_MaxPrevlance;
    bool m_display;
    QList<QPolygonF *> * m_PolygonList;
    QList<QPolygonF *> * m_RiverPolygonList;
    QList<QString> * m_River;



};

#endif // REGIONFILE_H
