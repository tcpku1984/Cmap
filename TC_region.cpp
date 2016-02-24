/**
  * @file region.cpp
  * @author Chao Tong
  * @date 10 Feb 2016
  * @see region.h
  */
#include "TC_region.h"
enum{
    NORTHBOUND=1,
    SOUTHBOUND=950,
    WESTBOUND=100,
    EASTBOUND=1900,
    HALFSIZE=106
};
Region::Region()
{
    m_healthData= new QList<double>;
    m_stopIncrease=false;
    size=1;
    m_color=0;
    m_detail=false;
    this->setColorIndex(0);
}

Region::~Region()
{

}

double Region::Lati() const
{
    return m_Lati;
}

void Region::setLati(double Lati)
{
    m_Lati = Lati;
}
double Region::Longti() const
{
    return m_Longti;
}

void Region::setLongti(double Longti)
{
    m_Longti = Longti;
}
int Region::poplation() const
{
    return m_poplation;
}

void Region::setPoplation(int poplation)
{
    m_poplation = poplation;
}
int Region::Y() const
{
    return m_Y;
}

void Region::setY(int Y)
{
    m_Y = Y;
}
bool Region::stopIncrease() const
{
    return m_stopIncrease;
}

void Region::setStopIncrease(bool stopIncrease)
{
    m_stopIncrease = stopIncrease;
}
QString Region::ccgCode() const
{
    return m_ccgCode;
}

void Region::setCcgCode(const QString &ccgCode)
{
    m_ccgCode = ccgCode;
}
QString Region::ccgName() const
{
    return m_ccgName;
}

void Region::setCcgName(const QString &ccgName)
{
    m_ccgName = ccgName;
}
int Region::X() const
{
    return m_X;
}

void Region::setX(int X)
{
    m_X = X;
}
int Region::getSize() const
{
    return size;
}

void Region::setSize(int value)
{
    size = value;
}

void Region::increase()
{
    this->setX(this->X()-1);
    this->setY(this->Y()-1);
    this->setSize(this->getSize()+2);

}

void Region::stop()
{
    this->setSize(this->getSize()-2);
    this->setX(this->X()+1);
    this->setY(this->Y()+1);
    this->setStopIncrease(true);
    this->setColor(1);
}

void Region::moveNorth()
{
    if(this->Y()>NORTHBOUND)
    {
        this->setY(this->Y()-1);
    }

}
void Region::moveSouth()
{
    if(this->Y()<SOUTHBOUND)
    {
        this->setY(this->Y()+1);
    }
}

void Region::moveWest()
{
    if(this->X()>WESTBOUND)
    {
        this->setX(this->X()-1);
    }
}

void Region::moveEast()
{
    if(this->X()<EASTBOUND)
    {
        this->setX((this->X()+1));
    }
}

int Region::color() const
{
    return m_color;
}

void Region::setColor(int color)
{
    m_color = color;
}
bool Region::detail() const
{
    return m_detail;
}

void Region::setDetail(bool detail)
{
    m_detail = detail;
}
QList<double> *Region::healthData() const
{
    return m_healthData;
}

void Region::setHealthData(QList<double> *healthData)
{
    m_healthData = healthData;
}
int Region::getColorIndex() const
{
    return m_ColorIndex;
}

void Region::setColorIndex(int ColorIndex)
{
    m_ColorIndex = ColorIndex;
}

int Region::getVOrder() const
{
    return vOrder;
}

void Region::setVOrder(int value)
{
    vOrder = value;
}

int Region::getHOrder() const
{
    return hOrder;
}

void Region::setHOrder(int value)
{
    hOrder = value;
}

















