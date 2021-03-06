/**
  * @file region.cpp
  * @author Chao Tong
  * @date 10 Feb 2016
  * @see region.h
  */
#include "TC_region.h"
enum{
    NORTHBOUND=1,
    SOUTHBOUND=1000,
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
    this->setError(0);
    m_Crossing=new QList<Region *>;
    m_riverSide=0;
    m_crossRiver=false;
    m_interSection=false;
    pointList=new QList<QPointF*>;
    sizeList= new QList<int>;
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
qreal Region::Y() const
{
    return m_Y;
}

void Region::setY(qreal Y)
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
qreal Region::X() const
{
    return m_X;
}

void Region::setX(qreal X)
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
    //this->setLastX(this->X());
    //this->setLastY(this->Y());
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

void Region::addCrossingRegion(Region *r)
{
    this->getCrossing()->append(r);
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
int Region::getError() const
{
    return m_Error;
}

void Region::setError(int Error)
{
    m_Error = Error;
}

QList<Region *> *Region::getCrossing() const
{
    return m_Crossing;
}

void Region::setCrossing(QList<Region *> *Crossing)
{
    m_Crossing = Crossing;
}
int Region::getRiverSide() const
{
    return m_riverSide;
}

void Region::setRiverSide(int riverSide)
{
    m_riverSide = riverSide;
}
qreal Region::getLastX() const
{
    return m_lastX;
}

void Region::setLastX(qreal lastX)
{
    m_lastX = lastX;
}
qreal Region::getLastY() const
{
    return m_lastY;
}

void Region::setLastY(qreal lastY)
{
    m_lastY = lastY;
}
bool Region::getCrossRiver() const
{
    return m_crossRiver;
}

void Region::setCrossRiver(bool crossRiver)
{
    m_crossRiver = crossRiver;
}
qreal Region::getCurrentX() const
{
    return m_currentX;
}

void Region::setCurrentX(qreal currentX)
{
    m_currentX = currentX;
}
qreal Region::getCurrentY() const
{
    return m_currentY;
}

void Region::setCurrentY(qreal currentY)
{
    m_currentY = currentY;
}
bool Region::getInterSection() const
{
    return m_interSection;
}

void Region::setInterSection(bool interSection)
{
    m_interSection = interSection;
}
QList<QPointF *> *Region::getPointList() const
{
    return pointList;
}

void Region::setPointList(QList<QPointF *> *value)
{
    pointList = value;
}

void Region::addPoint()
{
    QPointF * newPoint=new QPointF(this->X(),this->Y());
    pointList->append(newPoint);
    sizeList->append(this->getSize());
}

void Region::clearPointList()
{
    pointList->clear();
    sizeList->clear();
}
QList<int> *Region::getSizeList() const
{
    return sizeList;
}

void Region::setSizeList(QList<int> *value)
{
    sizeList = value;
}































