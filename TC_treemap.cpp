/**
  * @file treemap.cpp
  * @author Chao Tong
  * @date 10 Feb 2016
  * @see treemap.h
  */
#include "TC_treemap.h"
#include "ui_treemap.h"
enum{
    GRAY=85
};
treeMap::treeMap(QWidget *parent, bool treemap, int color, Region *region, QList<double> * aver) :
    QWidget(parent),
    ui(new Ui::treeMap)
{
    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::white);
    this->setPalette(pal);
    m_AveragePrevlance=new QList<double>;
    m_lookAhead=false;
    m_ratioTemp=0;
    m_totalAsp=0;
    this->setMapDifference(true);
    this->setBorder(4);
    ui->setupUi(this);
    this->setLookAhead(treemap);
    this->setColor(color);
    this->setRegion(region);
    this->setAveragePrevlance(aver);
    this->setMouseOver(false);
    this->setMouseX(0);
    this->setMouseY(0);
    this->setMouseIndex(0);
    this->setMouseTracking(true);
    this->setAspectRatio(1);
    m_Datacolor=new dataColor();
    m_HealthName<<"Coronary-heart-disease"<<"Heart Failure"<<"Stroke"
               <<"Chronic-kidney-disease"<<"Diabetes"<<"Hypertension"
              <<"COPD"<<"Mental-Health"<<"Osteoporosis"<<"Rheumatoid-Arthritis"
             <<"Cancer"<<"Epilepsy"<<"Hypothyroidism"<<"Asthma";
}


treeMap::~treeMap()
{
    delete ui;
}

void treeMap::paintEvent(QPaintEvent *event)
{

    this->dataColor0=m_Datacolor->getColor(this->getColor());
    QPainter painter(this);
    QFont font;
    if(this->getFont()==false)
    {
        font=QFont("Arial");
    }
    else
    {
        font=QFont("Times");
    }
    font.setBold(true);
    painter.setFont(font);
    QRect rect=QRect(10,60,500,100);
    QString tempString=this->region()->ccgName()
            +this->region()->ccgCode()+"  "
            +QString::number(this->region()->poplation())+"  ";

    if(this->getLookAhead()==true)
    {
        rectlist=drawSqTreeMap2(10,100,500,500,0,this->region()->healthData(),&painter);
    }
    else
    {
        if(this->getMapDifference()==false)
        {
            if(this->getCgroup()==false)
            {
                rectlist=drawSqTreeMap(10,100,500,500,0,this->region()->healthData(),&painter,2);
            }
            else
            {
               QList<double> * dataTemp=new QList<double>;
               double temp=0;
               for(int k=0;k<3;k++)
               {
                   temp+=this->region()->healthData()->at(k);
               }
               dataTemp->append(temp);
               for(int k=3;k<this->region()->healthData()->size();k++)
               {
                   dataTemp->append(this->region()->healthData()->at(k));
               }
               rectlist=drawSqTreeMap(10,
                           100,
                           500,
                           500,0,
                           dataTemp,
                           &painter,2);
            }
        }
        else
        {
            QList <double>* dataTemp=new QList<double>;
            for(int k=0;k<this->region()->healthData()->size();k++)
            {
                double tempdata=double(this->region()->healthData()->at(k)-
                        this->getAveragePrevlance()->at(k));
                if(fabs(tempdata)>0.005)
                {
                    dataTemp->append(this->region()->healthData()->at(k)-
                                     this->getAveragePrevlance()->at(k));
                }
                else
                {
                    if(tempdata>0)
                        dataTemp->append(0.005);
                    else
                        dataTemp->append(-0.005);
                }
            }
            rectlist=drawSqTreeMap(10,100,500,500,0,dataTemp,&painter,2);
        }
    }
    this->setTotalAsp(0);
    qreal tempAsp;
    for(int i=0;i<rectlist->size();i++)
    {
        //cout<<rectlist->at(i)->W()<<" "<<rectlist->at(i)->L()<<endl;
        tempAsp=rectlist->at(i)->W()/rectlist->at(i)->L();

        if(tempAsp<1)
        {
            tempAsp=1/tempAsp;
        }
        this->setTotalAsp(this->getTotalAsp()+tempAsp);
    }
    tempString+="Average aspect ratio "+QString::number(this->getTotalAsp()/this->region()->healthData()->size());
    if(this->getCgroup()==true)
    {
        QList <double>* dataTemp=new QList<double>;
        QList<QColor>  *tempColor= new QList<QColor>;
        for(int k=0;k<3;k++)
        {
            dataTemp->append(this->region()->healthData()->at(k));
            tempColor->append(QColor::fromHsvF(dataColor0.at(0).hueF(),
                                               1,0.5+k*0.15));
        }
       this->dataColor0=*tempColor;
        drawSqTreeMap(rectlist->at(0)->X(),
                      rectlist->at(0)->Y(),
                      rectlist->at(0)->W(),
                      rectlist->at(0)->L(),0,
                      dataTemp,&painter,1);
    }
    painter.setPen(Qt::black);
    painter.drawText(rect,tempString);
    if(this->getMouseOver()==true)
    {
        painter.drawText(QRect(300,60,200,40),
                         m_HealthName.at(this->getMouseIndex())+" "+
                         QString::number(this->region()->healthData()->at(this->getMouseIndex())));
    }


}
Region *treeMap::region() const
{
    return m_region;
}

void treeMap::setRegion(Region *region)
{
    m_region = region;
}
QList <rectHolder *> *  treeMap::drawSqTreeMap(qreal x, qreal y, qreal width, qreal length, int pos, QList<double> *data, QPainter *p, int layer)
{

    if(pos>=data->size())
    {
        return NULL;
    }
    QList<rectHolder *> *rectList=new QList<rectHolder *>;
    qreal total=0;
    qreal ratio=10000;
    qreal temp;
    qreal value=0;
    int number;
    for(int i=pos;i<data->size();i++)
    {
        total+=fabs(data->at(i));
    }
    for(number=0;number<data->size()-pos;number++)
    {
        temp=calRatio(width,length,pos,number,data);
        if(temp<this->getAspectRatio())
        {
            number++;
            break;
        }
        if(temp<ratio)
        {
            ratio=temp;
        }
        else
        {
            break;
        }
    }
    if(true)//if(length>=width)
    {
        qreal tempx=x;
        for(int i=pos;i<pos+number;i++)
        {
            value+=fabs(data->at(i));
        }
        for(int i=pos;i<pos+number;i++)
        {
            QRectF rect=QRectF(tempx,y,fabs(data->at(i))*width/value,value*length/total);
            //cout<<"new length"<<value*length/total<<endl;
            rectList->append(new rectHolder(tempx,y,fabs(data->at(i))*width/value,value*length/total));
            if(layer==2)
            {
                if(this->getGradient()==false)
                {
                    QLinearGradient grad(tempx,y,
                                         tempx+fabs(data->at(i))*width/value,
                                         y+value*length/total);
                    grad.setColorAt(0,
                                    QColor::fromHsvF(dataColor0.at(i).hueF(),
                                                     1,0.5));
                    grad.setColorAt(1,
                                    QColor::fromHsvF(dataColor0.at(i).hueF(),
                                                     0.5,1));
                    p->fillRect(rect,grad);
                }
                else
                {
                    QRadialGradient grad(tempx+fabs(data->at(i))*width/value/2,
                                         y+value*length/total/2,
                                         fabs(data->at(i))*width/value/2+
                                         value*length/total/2);
                    grad.setColorAt(0,
                                    QColor::fromHsvF(dataColor0.at(i).hueF(),
                                                     0.3,1));
                    grad.setColorAt(1,
                                    QColor::fromHsvF(dataColor0.at(i).hueF(),
                                                     1,0.7));
                    p->fillRect(rect,grad);
                }
                if(this->getMapDifference()==false)
                {
                    if(fabs(data->at(i))>this->getAveragePrevlance()->at(i))
                    {
                        //QPen pen(QColor::fromRgb(255,0,0,100));
                        QPen pen(Qt::white);
                        pen.setWidth(this->getBorder());
                        p->setPen(pen);
                        if(this->getFilter()==2)
                        {
                            p->fillRect(rect,QColor::fromHsvF(0,
                                                          0,0.97));
                        }

                    }
                    else
                    {
                        //QPen pen(QColor::fromRgb(0,255,0,100));
                        QPen pen(Qt::white);
                        pen.setWidth(this->getBorder());
                        p->setPen(pen);
                        if(this->getFilter()==1)
                        {
                            p->fillRect(rect,QColor::fromHsvF(0,
                                                          0,0.97));
                        }
                    }
                }
                else
                {
                    if(data->at(i)>0)
                    {
                        //QPen pen(QColor::fromRgb(255,0,0,100));
                        QPen pen(Qt::white);
                        pen.setWidth(this->getBorder());
                        p->setPen(pen);
                        if(this->getFilter()==2)
                        {
                            p->fillRect(rect,QColor::fromHsvF(0,
                                                          0,0.97));
                        }

                    }
                    else
                    {
                        //QPen pen(QColor::fromRgb(0,255,0,100));
                        QPen pen(Qt::white);
                        pen.setWidth(this->getBorder());
                        p->setPen(pen);
                        if(this->getFilter()==1)
                        {
                            p->fillRect(rect,QColor::fromHsvF(0,
                                                          0,0.97));
                        }
                    }
                }

            }
            else if(layer==1)
            {
                p->fillRect(rect,dataColor0.at(i));
                if(fabs(data->at(i))>this->getAveragePrevlance()->at(i))
                {
                    QPen pen(QColor::fromRgb(255,0,0,100));
                    pen.setWidth(this->getBorder());
                    p->setPen(pen);

                }
                else
                {
                    QPen pen(QColor::fromRgb(0,255,0,100));
                    pen.setWidth(this->getBorder());
                    p->setPen(pen);
                }
            }
            p->drawRect(rect);
            p->setPen(Qt::white);
            p->drawText(rect,QString::number(data->at(i)));
            tempx=tempx+fabs(data->at(i))*width/value;
        }
        y=y+value*length/total;
        length=length-value*length/total;
        pos=pos+number;
        if(drawSqTreeMap(x,y,width,length,pos,data,p,layer)!=NULL)
        {
            rectList->append(*drawSqTreeMap(x,y,width,length,pos,data,p,layer));
        }
        return rectList;
    }

}

QList <rectHolder *> *  treeMap::drawSqTreeMap2(qreal x, qreal y, qreal width, qreal length, int pos, QList<double> *data, QPainter *p)
{
    if(pos>=data->size())
    {
        return NULL;
    }
    QList<rectHolder *> *rectList=new QList<rectHolder *>;
    qreal total=0;
    qreal temp1;
    qreal temp2;
    qreal value=0;
    int number;
    for(int i=pos;i<data->size();i++)
    {
        total+=data->at(i);
    }
    for(number=0;number<data->size()-pos;number++)
    {
        temp1=calRatio(width,length,pos,number,data);
        temp2=calRatio2(width,length,pos,number,data);
        cout<<" pos "<<pos<<" number "<<number<<endl;
        //cout<<"ratio1 "<<temp1<<"  ratio2 "<<temp2<<endl;
        if(temp1>temp2)
        {
            break;
        }
    }
    if(true)//if(length>=width)
    {
        temp1=calRatio(width,length,pos,number-1,data);
        this->setTotalAsp(this->getTotalAsp()+this->getRatioTemp());
        qreal tempx=x;
        for(int i=pos;i<pos+number;i++)
        {
            value+=data->at(i);
        }
        for(int i=pos;i<pos+number;i++)
        {
            QRectF rect=QRectF(tempx,y,data->at(i)*width/value,value*length/total);
            rectList->append(new rectHolder(tempx,y,data->at(i)*width/value,value*length/total));

            if(data->at(i)>this->getAveragePrevlance()->at(i))
            {
                QLinearGradient grad(tempx,y,tempx+data->at(i)*width/value,y+value*length/total);
                QPen pen(Qt::red);
                p->setPen(pen);
                p->drawRect(rect);
                grad.setColorAt(0,
                                QColor::fromHsvF(dataColor0.at(i).hueF(),1,0.7));
                grad.setColorAt(1,
                                QColor::fromHsvF(dataColor0.at(i).hueF(),0.7,1));
                p->fillRect(rect,grad);
            }
            else
            {
                QPen pen(Qt::green);
                p->setPen(pen);
                p->drawRect(rect);
                p->fillRect(rect,dataColor0.at(i));

            }
            p->setPen(Qt::black);
            p->drawText(rect,QString::number(data->at(i)));
            tempx=tempx+data->at(i)*width/value;
        }
        y=y+value*length/total;
        length=length-value*length/total;
        pos=pos+number;
        if(drawSqTreeMap2(x,y,width,length,pos,data,p)!=NULL)
        {
            rectList->append(*drawSqTreeMap2(x,y,width,length,pos,data,p));
        }
        return rectList;
    }
}

qreal treeMap::calRatio(qreal w, qreal l, int pos, int number, QList<double> *data)
{
    qreal ratio=1;
    qreal temp;
    qreal total=0;
    qreal sum=0;
    for(int i=pos;i<data->size();i++)
    {
        total+=data->at(i);
    }
    qreal value=0;
    for(int i=pos;i<=pos+number;i++)
    {
        value+=data->at(i);
    }
    if(true)//if(l>=w)
    {
        for(int i=pos;i<=pos+number;i++)
        {
            temp=data->at(i)*total*w/(l*value*value);
            if(temp<1)
            {
                temp=1/temp;
            }
            sum=sum+temp;
        }
    }
    /*
    else
    {
        for(int i=pos;i<=pos+number;i++)
        {
            temp=data->at(i)*total*l/(w*value*value);
            if(temp<1)
            {
                temp=1/temp;
            }
            if(temp>ratio)
            {
                ratio=temp;
            }
        }

    }*/
    this->setRatioTemp(sum);
    ratio=sum/(number+1);
    //cout<<"number:" <<number+1<<" ratio: "<<ratio<<endl;
    return ratio;
}

qreal treeMap::calRatio2(qreal w, qreal l, int pos, int number, QList<double> *data)
{
    qreal ratio=1;
    qreal temp;
    qreal total=0;
    qreal sum=0;
    int i;
    for(i=pos;i<data->size();i++)
    {
        total+=data->at(i);
    }
    qreal value=0;
    for(int i=pos;i<=pos+number-1;i++)
    {
        value+=data->at(i);
    }
    if(true)//if(l>=w)
    {
        for(i=pos;i<=pos+number-1;i++)
        {
            temp=data->at(i)*total*w/(l*value*value);
            if(temp<1)
            {
                temp=1/temp;
            }
            sum=sum+temp;
        }
    }
    sum+=w*total/(data->at(pos+number)*l);
    this->setRatioTemp(sum);
    ratio=sum/(number+1);
    return ratio;


}

int treeMap::getAspectRatio() const
{
    return m_aspectRatio;
}

void treeMap::setAspectRatio(int aspectRatio)
{
    m_aspectRatio = aspectRatio;
}
QList<QString> treeMap::getHealthName() const
{
    return m_HealthName;
}

void treeMap::setHealthName(const QList<QString> &HealthName)
{
    m_HealthName = HealthName;
}


int treeMap::getMouseIndex() const
{
    return m_mouseIndex;
}

void treeMap::setMouseIndex(int mouseIndex)
{
    m_mouseIndex = mouseIndex;
}

qreal treeMap::getMouseY() const
{
    return m_mouseY;
}

void treeMap::setMouseY(const qreal &mouseY)
{
    m_mouseY = mouseY;
}

qreal treeMap::getMouseX() const
{
    return m_mouseX;
}

void treeMap::setMouseX(const qreal &mouseX)
{
    m_mouseX = mouseX;
}

bool treeMap::getMouseOver() const
{
    return m_mouseOver;
}

void treeMap::setMouseOver(bool mouseOver)
{
    m_mouseOver = mouseOver;
}

int treeMap::getFilter() const
{
    return m_Filter;
}

void treeMap::setFilter(int Filter)
{
    m_Filter = Filter;
}
bool treeMap::getCgroup() const
{
    return m_Cgroup;
}

void treeMap::setCgroup(bool Cgroup)
{
    m_Cgroup = Cgroup;
}


void treeMap::mouseMoveEvent(QMouseEvent *e)
{
    int x=e->pos().x();
    int y=e->pos().y();
    int i;
    for(i=0;i<rectlist->size();i++)
    {
        if(rectlist->at(i)->X()<x&&
           rectlist->at(i)->X()+rectlist->at(i)->W()>x&&
           rectlist->at(i)->Y()<y&&
           rectlist->at(i)->Y()+rectlist->at(i)->L()>y)
        {
            //cout<<"tracking"<<endl;
            this->setMouseOver(true);
            this->setMouseIndex(i);
            update();
            break;
        }

    }
    if(i==rectlist->size())
    {
        //cout<<"out bonder"<<endl;
        this->setMouseOver(false);
        update();
    }
}


bool treeMap::getFont() const
{
    return m_Font;
}

void treeMap::setFont(bool Font)
{
    m_Font = Font;
}

bool treeMap::getGradient() const
{
    return m_gradient;
}

void treeMap::setGradient(bool gradient)
{
    m_gradient = gradient;
}

int treeMap::getColor() const
{
    return m_Color;
}

void treeMap::setColor(int Color)
{
    m_Color = Color;
}

bool treeMap::getMapDifference() const
{
    return m_MapDifference;
}

void treeMap::setMapDifference(bool MapDifference)
{
    m_MapDifference = MapDifference;
}

int treeMap::getBorder() const
{
    return m_border;
}

void treeMap::setBorder(int border)
{
    m_border = border;
}

QList<double> *treeMap::getAveragePrevlance() const
{
    return m_AveragePrevlance;
}

void treeMap::setAveragePrevlance(QList<double> *AveragePrevlance)
{
    m_AveragePrevlance = AveragePrevlance;
}


qreal treeMap::getTotalAsp() const
{
    return m_totalAsp;
}

void treeMap::setTotalAsp(const qreal &totalAsp)
{
    m_totalAsp = totalAsp;
}

qreal treeMap::getRatioTemp() const
{
    return m_ratioTemp;
}

void treeMap::setRatioTemp(const qreal &ratioTemp)
{
    m_ratioTemp = ratioTemp;
}

bool treeMap::getLookAhead() const
{
    return m_lookAhead;
}

void treeMap::setLookAhead(bool lookAhead)
{
    m_lookAhead = lookAhead;
}



