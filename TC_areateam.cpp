/**
  * @file areateam.cpp
  * @author Chao Tong
  * @date 10 Feb 2016
  * @see areateam.h
  */
#include "TC_areateam.h"
enum{
    RATHH=400,
    RATHV=600,
    HH=-400,
    VV=1050
};
AreaTeam::AreaTeam()
{
    m_RegionList=new QList<Region *>;
    m_PopulationList=new QList<double>;
    this->setStopIncrease(false);
}

void AreaTeam::addRegion(Region *region)
{
    m_RegionList->append(region);
}

void AreaTeam::initi()
{
    m_PopulationList=new QList<double>;
    this->setPopulation(0);
    this->setSize(1);
    this->setStopIncrease(false);
    qreal lati=0;
    qreal longti=0;
    for(int i=0;i<this->RegionList()->size();i++)
    {
        lati+=this->RegionList()->at(i)->Lati();
        longti+=this->RegionList()->at(i)->Longti();
        this->setPopulation(
                    this->Population()+this->RegionList()->at(i)->poplation());
        this->PopulationList()->append(double(
                                           this->RegionList()->at(i)->poplation()));
    }
    lati=lati/this->RegionList()->size();
    longti=longti/this->RegionList()->size();
    this->setX(lati/RATHH+HH);
    this->setY(-longti/RATHV+VV);

}

void AreaTeam::increase()
{
    this->setSize(this->Size()+1);
}

QString AreaTeam::AreaCode() const
{
    return m_AreaCode;
}

void AreaTeam::setAreaCode(const QString &AreaCode)
{
    m_AreaCode = AreaCode;
}

QString AreaTeam::AreaName() const
{
    return m_AreaName;
}

void AreaTeam::setAreaName(const QString &AreaName)
{
    m_AreaName = AreaName;
}

QList<Region *> *AreaTeam::RegionList() const
{
    return m_RegionList;
}

void AreaTeam::setRegionList(QList<Region *> *RegionList)
{
    m_RegionList = RegionList;
}

int AreaTeam::X() const
{
    return m_X;
}

void AreaTeam::setX(int X)
{
    m_X = X;
}

int AreaTeam::Y() const
{
    return m_Y;
}

void AreaTeam::setY(int Y)
{
    m_Y = Y;
}

int AreaTeam::Population() const
{
    return m_Population;
}

void AreaTeam::setPopulation(int Population)
{
    m_Population = Population;
}

int AreaTeam::Size() const
{
    return m_Size;
}

void AreaTeam::setSize(int Size)
{
    m_Size = Size;
}

bool AreaTeam::stopIncrease() const
{
    return m_stopIncrease;
}

void AreaTeam::setStopIncrease(bool stopIncrease)
{
    m_stopIncrease = stopIncrease;
}

QList<double> *AreaTeam::PopulationList() const
{
    return m_PopulationList;
}

void AreaTeam::setPopulationList(QList<double> *PopulationList)
{
    m_PopulationList = PopulationList;
}



