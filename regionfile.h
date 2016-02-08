/**
  *@file regionfile.h
  * @author Chao Tong
  * @date 10 Jan 2016
 * @brief The regionFile class is to read the region node information from csv file.
  */
#ifndef REGIONFILE_H
#define REGIONFILE_H
#include<fstream>
#include<region.h>
#include<areateam.h>
#include<QString>
#include<QList>
#include<string>
#include<iostream>
using namespace std;
class regionFile
{
public:
    regionFile();
    void readfile();
    QList<Region *> *regionList() const;
    void setRegionList(QList<Region *> *regionList);

    QList<double> *AveragePrevlance() const;
    void setAveragePrevlance(QList<double> *AveragePrevlance);

    QList<AreaTeam *> *AreaGroup() const;
    void setAreaGroup(QList<AreaTeam *> *AreaGroup);

    int populiation() const;
    void setPopuliation(int populiation);

private:
    int searchAreaCode(QString code);
    QList < Region *> * m_regionList;
    int m_populiation;
    QList <AreaTeam *>  * m_AreaGroup;
    QList<double> * m_AveragePrevlance;

};

#endif // REGIONFILE_H
