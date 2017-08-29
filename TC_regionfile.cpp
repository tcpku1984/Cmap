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
    m_PolygonList=new QList<QPolygonF *>;
    m_AreaGroup=new QList<AreaTeam *>;
    m_AveragePrevlance=new QList<double>;
    m_River=new QList<QString>;
    for(int i=0;i<14;i++)
    {
        this->AveragePrevlance()->append(0);
    }
    this->setPopuliation(0);
    this->setDisplay(true);
}

void regionFile::readfile(int year)
{
    regionFile();
    ifstream inFlow;
    if(year==2011)
    {
        inFlow.open("D:/Cmap/centerp2011.csv");
    }
    else if(year==2012)
    {
        inFlow.open("D:/Cmap/centerp2012.csv");
    }
    else
    {
        inFlow.open("D:/Cmap/centerp2013.csv");
    }
    string input;
    int i = 0;

    if (!inFlow)
    {
        cout << "widegt::fileRead() inFlow ERRor"<<endl;
    }
    else
    {
    cout << "\n Reading" <<endl;
    cout<<year<<endl;
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
            if(b<0.01||b>30)
            {
                cout<<b<<endl;
                b=0.05;
            }
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
    cout<<"Reading finished"<<endl;

    for(int i=0;i<14;i++)
    {
        this->AveragePrevlance()->replace(i,
             this->AveragePrevlance()->at(i)/this->regionList()->size());
        cout<<"average data: "<<this->AveragePrevlance()->at(i)<<endl;
    }



}

void regionFile::readPolygon()
{
    ifstream inFlow;
    inFlow.open("D:/Cmap/poly.csv");
    string input;
    int number=-1;
    QPolygonF * tempPolygon;
    float tempx,tempy;
    while (!inFlow.eof())
    {
        getline(inFlow,input, ',');
        if(number!=atoi(input.c_str()))
        {
            number=atoi(input.c_str());
            tempPolygon=new QPolygonF();
            m_PolygonList->append(tempPolygon);
        }

        getline(inFlow,input, ',');
        tempx=atof(input.c_str())/RATHH+HH;
        inFlow>>tempy;
        tempy=-tempy/RATHV+VV;
        tempPolygon->append(QPointF(tempx,tempy));
    }
    inFlow.close();
    cout<<"Reading finished::"<<number<<endl;



}

void regionFile::readRiver()
{
    ifstream inFlow;
    inFlow.open("D:/Cmap/Thames.csv");
    string input;
    int a;
    while (!inFlow.eof())
    {
        getline(inFlow,input, ',');
        getline(inFlow,input, ',');
        //cout<<input<<endl;
        m_River->append(QString::fromStdString(input));
        getline(inFlow,input, ',');
        //cout<<input<<endl;
        m_River->append(QString::fromStdString(input));
        inFlow>>a;

    }
    inFlow.close();
    cout<<"River Reading finished"<<endl;


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

QList<QString> *regionFile::River() const
{
    return m_River;
}

void regionFile::setRiver(QList<QString> *River)
{
    m_River = River;
}
QList<QPolygonF *> *regionFile::PolygonList() const
{
    return m_PolygonList;
}

void regionFile::setPolygonList(QList<QPolygonF *> *PolygonList)
{
    m_PolygonList = PolygonList;
}

bool regionFile::display() const
{
    return m_display;
}

void regionFile::setDisplay(bool display)
{
    m_display = display;
}


int regionFile::populiation() const
{
    return m_populiation;
}

void regionFile::setPopuliation(int populiation)
{
    m_populiation = populiation;
}

