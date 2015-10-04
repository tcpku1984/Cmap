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
    QString AreaCode() const;
    void setAreaCode(const QString &AreaCode);

    QString AreaName() const;
    void setAreaName(const QString &AreaName);

private:
    QList<Region *> * regionList;
    QString m_AreaCode;
    QString m_AreaName;


};

#endif // AREATEAM_H
