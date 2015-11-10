#include "treemap.h"
#include "ui_treemap.h"

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
    dataColor1<<QColor("#86a6af")<<QColor("#a6cee3")<<QColor("#1f78b4")
             <<QColor("#b2df8a")<<QColor("#33a02c")
             <<QColor("#fb9a99")<<QColor("#e31a1c")
             <<QColor("#fdbf6f")<<QColor("#ff7f00")
             <<QColor("#cab2d6")<<QColor("#6a3d9a")
             <<QColor("#ffff99")<<QColor("#b15928")
             <<QColor("#000");
    for(int i=0;i<4;i++)
    {
        this->dataColor2.append(QColor::fromHsvF(qreal(i)*90/qreal(4)/qreal(360),1,1));

    }
    for(int i=4;i<6;i++)
    {
        this->dataColor2.append(QColor::fromHsvF((qreal(90)+qreal(i-4)*90/qreal(2))/qreal(360),1,1));
        //cout<<(qreal(90)+qreal(i)*90/qreal(2))<<endl;
    }
    for(int i=6;i<10;i++)
    {
        this->dataColor2.append(QColor::fromHsvF((qreal(180)+qreal(i-6)*90/qreal(4))/qreal(360),1,1));
        //cout<<(qreal(180)+qreal(i)*90/qreal(4))<<endl;
    }
    for(int i=10;i<14;i++)
    {
        this->dataColor2.append(QColor::fromHsvF((qreal(270)+qreal(i-10)*90/qreal(4))/qreal(360),1,1));
        //cout<<(qreal(270)+qreal(i)*90/qreal(4))<<endl;

    }
    dataColor3<<QColor("#2acae6")<<QColor("#deb274")<<QColor("#518adb")
             <<QColor("#c240d6")<<QColor("#2ecc16")
             <<QColor("#afef5a")<<QColor("#9163cd")
             <<QColor("#d26685")<<QColor("#72e6c5")
             <<QColor("#cf1f9d")<<QColor("#53d179")
             <<QColor("#e02e0e")<<QColor("#5c5ce6")
             <<QColor("#000");
}


treeMap::~treeMap()
{
    delete ui;
}

void treeMap::paintEvent(QPaintEvent *event)
{
    switch(this->getColor())
    {
    case 1:
        this->dataColor=this->dataColor1;
        break;
    case 2:
        this->dataColor=this->dataColor2;
        break;
    case 3:
       this->dataColor=this->dataColor3;
       break;

    }

    QPainter painter(this);
    QFont font("font:Arial");
    painter.setFont(font);
    QRect rect=QRect(0,0,500,100);
    QString tempString=this->region()->ccgName()
            +this->region()->ccgCode()+"  "
            +QString::number(this->region()->poplation())+"  ";
    QList <rectHolder *> * rectlist;
    if(this->getLookAhead()==true)
    {
        //cout<<"looking aheadddddddddddddddddddddddddddddddddddddddddddd"<<endl;
        rectlist=drawSqTreeMap2(10,100,500,500,0,this->region()->healthData(),&painter);
    }
    else
    {
        if(this->getMapDifference()==false)
        {
            rectlist=drawSqTreeMap(10,100,500,500,0,this->region()->healthData(),&painter,2);
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
        cout<<rectlist->at(i)->W()<<" "<<rectlist->at(i)->L()<<endl;
        tempAsp=rectlist->at(i)->W()/rectlist->at(i)->L();

        if(tempAsp<1)
        {
            tempAsp=1/tempAsp;
        }
        this->setTotalAsp(this->getTotalAsp()+tempAsp);
    }
    tempString+="Average aspect ratio "+QString::number(this->getTotalAsp()/this->region()->healthData()->size());
    painter.drawText(rect,tempString);


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
                if(this->getMapDifference()==false)
                {
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
                else
                {
                    if(data->at(i)>0)
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
                if(this->getGradient()==false)
                {
                    QLinearGradient grad(tempx,y,
                                         tempx+fabs(data->at(i))*width/value,
                                         y+value*length/total);
                    grad.setColorAt(0,
                                    QColor::fromHsvF(dataColor.at(i).hueF(),
                                                     1,0.5));
                    grad.setColorAt(1,
                                    QColor::fromHsvF(dataColor.at(i).hueF(),
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
                                    QColor::fromHsvF(dataColor.at(i).hueF(),
                                                     0.3,1));
                    grad.setColorAt(1,
                                    QColor::fromHsvF(dataColor.at(i).hueF(),
                                                     1,0.7));
                    p->fillRect(rect,grad);
                }
            }
            else
            {
                QPen pen(Qt::black);
                pen.setWidth(this->getBorder());
                p->setPen(pen);
            }
            p->drawRect(rect);
            p->setPen(Qt::black);
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
                                QColor::fromHsvF(dataColor.at(i).hueF(),1,0.7));
                grad.setColorAt(1,
                                QColor::fromHsvF(dataColor.at(i).hueF(),0.7,1));
                p->fillRect(rect,grad);
            }
            else
            {
                QPen pen(Qt::green);
                p->setPen(pen);
                p->drawRect(rect);
                p->fillRect(rect,dataColor.at(i));

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


QList<QColor> treeMap::getDataColor2() const
{
    return dataColor2;
}

void treeMap::setDataColor2(const QList<QColor> &value)
{
    dataColor2 = value;
}

QList<QColor> treeMap::getDataColor1() const
{
    return dataColor1;
}

void treeMap::setDataColor1(const QList<QColor> &value)
{
    dataColor1 = value;
}



