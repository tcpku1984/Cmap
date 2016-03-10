/**
  * @file regionfile.cpp
  * @author Chao Tong
  * @date 10 Feb 2016
  * @see regionfile.h
  */
#include "TC_regionfile.h"
enum{
    ATTNUM=14,
    RATHH=400,
    RATHV=600,
    HH=-400,
    VV=1050
};
regionFile::regionFile()
{
    m_regionList=new QList<Region *>;
    m_AreaGroup=new QList<AreaTeam *>;
    m_AveragePrevlance=new QList<double>;
    for(int i=0;i<14;i++)
    {
        this->AveragePrevlance()->append(0);
    }
    this->setPopuliation(0);

}

void regionFile::readfile()
{
    ifstream inFlow;
    inFlow.open("D:/Cmap/centerp3.csv");
    string input;
    int i = 0;

    if (!inFlow)
    {
        cout << "widegt::fileRead() inFlow ERRor"<<endl;
    }
    else
    {
    cout << "\n Reading" <<endl;
    }
    while (!inFlow.eof())
    {
        //cout<<i<<"region"<<endl;
        QList<double> *tempList=new QList<double>;
        Region * temp=new Region();
        AreaTeam * areaTemp;
        getline(inFlow,input, ',');
        temp->setCcgCode(QString::fromStdString(input));
        getline(inFlow,input, ',');
        temp->setCcgName(QString::fromStdString(input));
        getline(inFlow,input, ',');
        temp->setLati(atof(input.c_str()));
        getline(inFlow,input, ',');
        temp->setLongti(atof(input.c_str()));
        for(int j=0;j<14;j++)
        {
            getline(inFlow,input, ',');
            double b=atof(input.c_str());
            this->AveragePrevlance()->replace(j,
                                              this->AveragePrevlance()->at(j)+b);
            tempList->append(b);
        }
        temp->setHealthData(tempList);
        getline(inFlow,input, ',');
        QString areaCode=QString::fromStdString(input);
        int index=this->searchAreaCode(areaCode);
        if(index<0)
        {
            areaTemp=new AreaTeam();
            areaTemp->setAreaCode(areaCode);
            getline(inFlow,input, ',');
            areaTemp->setAreaName(QString::fromStdString(input));
            this->AreaGroup()->append(areaTemp);
        }
        else
        {
            areaTemp=this->AreaGroup()->at(index);
            getline(inFlow,input, ',');
        }
        getline(inFlow,input, ',');
        temp->setColorIndex(atoi(input.c_str()));
        int a;
        inFlow>>a;
        this->setPopuliation(this->populiation()+a);
        temp->setPoplation(a);
        temp->setX(temp->Lati()/RATHH+HH);
        temp->setY(-temp->Longti()/RATHV+VV);
        this->regionList()->append(temp);
        areaTemp->addRegion(temp);
        i++;

    }
    inFlow.close();

    for(int i=0;i<14;i++)
    {
        this->AveragePrevlance()->replace(i,
             this->AveragePrevlance()->at(i)/this->regionList()->size());
        cout<<"average data: "<<this->AveragePrevlance()->at(i)<<endl;
    }



}

QList<Region *> *regionFile::regionList() const
{
    return m_regionList;
}

void regionFile::setRegionList(QList<Region *> *regionList)
{
    m_regionList = regionList;
}

QList<double> *regionFile::AveragePrevlance() const
{
    return m_AveragePrevlance;
}

void regionFile::setAveragePrevlance(QList<double> *AveragePrevlance)
{
    m_AveragePrevlance = AveragePrevlance;
}

QList<AreaTeam *> *regionFile::AreaGroup() const
{
    return m_AreaGroup;
}

void regionFile::setAreaGroup(QList<AreaTeam *> *AreaGroup)
{
    m_AreaGroup = AreaGroup;
}

int regionFile::searchAreaCode(QString code)
{
    for(int i=0;i<this->AreaGroup()->size();i++)
    {
        if(this->AreaGroup()->at(i)->AreaCode()==code)
        {
            return i;
        }
    }
    return -1;
}

int regionFile::populiation() const
{
    return m_populiation;
}

void regionFile::setPopuliation(int populiation)
{
    m_populiation = populiation;
}

