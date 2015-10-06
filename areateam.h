#ifndef AREATEAM_H
#define AREATEAM_H
#include <QString>
#include <QList>
#include<region.h>
class AreaTeam
{
public:
    AreaTeam();
    ~AreaTeam();
    void addRegion(Region * region);

    void initi();

    QString AreaCode() const;
    void setAreaCode(const QString &AreaCode);

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

private:
    QList<Region *> * m_RegionList;
    QString m_AreaCode;
    QString m_AreaName;
    qreal m_lati;
    qreal m_longti;
    int m_X;
    int m_Y;
    int m_Population;
    int m_Size;


};

#endif // AREATEAM_H
