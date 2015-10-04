#include "areateam.h"

AreaTeam::AreaTeam()
{
    regionList=new QList<Region *>;
}

void AreaTeam::addRegion(Region *region)
{
    regionList->append(region);
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

