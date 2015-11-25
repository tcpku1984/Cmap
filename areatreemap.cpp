#include "areatreemap.h"
#include "ui_areatreemap.h"



areaTreemap::areaTreemap(QWidget *parent, int color, AreaTeam * area,QList <double>* aver) :
    QWidget(parent),
    ui(new Ui::areaTreemap)
{
    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::white);
    this->setPalette(pal);
    m_AveragePrevlance=new QList<double>;
    m_RectList=new QList <rectHolder *>;
    this->setWindowsnumber(0);
    ui->setupUi(this);
    this->setColor(color);
    this->setArea(area);
    this->setAveragePrevlance(aver);
    this->setMapDifference(true);
    this->setBorder(3);
    this->setBorderColor(Qt::gray);
    this->setCgroup(false);
    dataColor0<<QColor("#7373FF")<<QColor("#FF7272")<<QColor("#70FF70")
             <<QColor("#00F3F3")<<QColor("#F400F4")
             <<QColor("#F7F700")<<QColor("#000")<<QColor("#8181DB")
             <<QColor("#DE8383")<<QColor("#7BD17B")
             <<QColor("#6DB9B9")<<QColor("#BE70BE")
             <<QColor("#BCBC6E")<<QColor("#989898");

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

areaTreemap::~areaTreemap()
{
    delete ui;
}

void areaTreemap::paintEvent(QPaintEvent *event)
{
    switch(this->getColor())
    {
    case 0:
        this->dataColor=this->dataColor0;
        break;
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
    QRect rect=QRect(10,0,600,100);
    QString tempString=this->Area()->AreaName()+"  "
            +this->Area()->AreaCode()+" \nCCG list :";
    for(int i=0;i<this->Area()->RegionList()->size();i++)
    {
        tempString+=this->Area()->RegionList()->at(i)->ccgName()
                +"; ";
    }


    this->setRectList(drawSqTreeMap(10,100,600,600,
                           0,this->Area()->PopulationList(),&painter,1));
    for(int j=0;j<this->getRectList()->size();j++)
    {
        qreal x=this->getRectList()->at(j)->X();
        qreal y=this->getRectList()->at(j)->Y();
        qreal w=this->getRectList()->at(j)->W();
        qreal l=this->getRectList()->at(j)->L();

        if(this->getMapDifference()==false)
        {
            if(this->getCgroup()==false)
            {
                drawSqTreeMap(x,y,w,l,0,
                     this->Area()->RegionList()->at(j)->healthData(),&painter,2);
            }
            else
            {
                QList<double> * dataTemp=new QList<double>;
                double temp=0;
                for(int k=0;k<5;k++)
                {
                    temp+=this->Area()->RegionList()->at(j)->healthData()->at(k);
                }
                dataTemp->append(temp);
                for(int k=5;k<this->Area()->RegionList()->at(j)->healthData()->size();k++)
                {
                    dataTemp->append(this->Area()->RegionList()->at(j)->healthData()->at(k));
                }
                drawSqTreeMap(x,y,w,l,0,
                            dataTemp,
                            &painter,2);
            }
        }
        else
        {
            QList <double>* dataTemp=new QList<double>;
            for(int k=0;k<this->Area()->RegionList()->at(j)->healthData()->size();k++)
            {
                double tempdata=double(this->Area()->RegionList()
                                       ->at(j)->healthData()->at(k)-
                        this->getAveragePrevlance()->at(k));
                //cout<<"testing :"<<tempdata<<endl;
                if(fabs(tempdata)>0.005)
                {
                    dataTemp->append(tempdata);
                }
                else
                {
                    if(tempdata>0)
                        dataTemp->append(0.005);
                    else
                        dataTemp->append(-0.005);
                }
            }
            drawSqTreeMap(x,y,w,l,0,
                         dataTemp,
                         &painter,2);


        }

    }

    painter.setBrush(Qt::NoBrush);
    QPen pen(Qt::gray);
    for(int j=0;j<this->getRectList()->size();j++)
    {

        QLinearGradient grad(this->getRectList()->at(j)->X(),
                        this->getRectList()->at(j)->Y(),
                        this->getRectList()->at(j)->X()+
                        this->getRectList()->at(j)->W(),
                        this->getRectList()->at(j)->Y()+
                        this->getRectList()->at(j)->L());
        for(int z=0;z<6;z++)
        {
            if(z%2==0)
            {
                grad.setColorAt(z*0.2,this->getBorderColor());
            }
            else
            {
                grad.setColorAt(z*0.2,Qt::white);
            }
        }
        grad.setSpread(QGradient::RepeatSpread);
        pen.setBrush(grad);
        pen.setWidth(this->getBorder()+2);
        painter.setPen(pen);
        painter.drawRect(this->getRectList()->at(j)->X(),
                         this->getRectList()->at(j)->Y(),
                         this->getRectList()->at(j)->W(),
                         this->getRectList()->at(j)->L());

    }
    pen.setBrush(QColor::fromRgb(255,255,219));
    pen.setWidth(this->getBorder()+4);
    painter.setPen(pen);
    painter.drawRect(10,100,600,600);
    painter.setPen(Qt::black);
    painter.drawText(rect,tempString);
}





AreaTeam *areaTreemap::Area() const
{
    return m_Area;
}

void areaTreemap::setArea(AreaTeam *Area)
{
    m_Area = Area;
}
QList<QColor> areaTreemap::getDataColor() const
{
    return dataColor;
}

void areaTreemap::setDataColor(const QList<QColor> &value)
{
    dataColor = value;
}
QList<QColor> areaTreemap::getDataColor1() const
{
    return dataColor1;
}

void areaTreemap::setDataColor1(const QList<QColor> &value)
{
    dataColor1 = value;
}
QList<QColor> areaTreemap::getDataColor2() const
{
    return dataColor2;
}

void areaTreemap::setDataColor2(const QList<QColor> &value)
{
    dataColor2 = value;
}

QList<rectHolder *> *areaTreemap::drawSqTreeMap(qreal x, qreal y, qreal width, qreal length, int pos, QList<double> *data, QPainter *p, int layer)
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

qreal areaTreemap::calRatio(qreal w, qreal l, int pos, int number, QList<double> *data)
{
    qreal ratio=1;
    qreal temp=1;
    qreal total=0;
    qreal sum=0;
    for(int i=pos;i<data->size();i++)
    {
        total+=fabs(data->at(i));
    }
    qreal value=0;
    for(int i=pos;i<=pos+number;i++)
    {
        value+=fabs(data->at(i));
    }
    if(true)//if(l>=w)
    {
        for(int i=pos;i<=pos+number;i++)
        {
            temp=fabs(data->at(i))*total*w/(l*value*value);
            if(temp<1)
            {
                temp=1/temp;
            }
            //cout<<temp<<endl;
            sum=sum+temp;
            if(temp>ratio)
            {
                ratio=temp;
            }
        }
    }
    sum=sum/(number+1);
    ratio=sum;
    return ratio;
}
bool areaTreemap::getCgroup() const
{
    return m_Cgroup;
}

void areaTreemap::setCgroup(bool Cgroup)
{
    m_Cgroup = Cgroup;
}


bool areaTreemap::getFont() const
{
    return m_Font;
}

void areaTreemap::setFont(bool Font)
{
    m_Font = Font;
}

QColor areaTreemap::getBorderColor() const
{
    return m_BorderColor;
}

void areaTreemap::setBorderColor(const QColor &BorderColor)
{
    m_BorderColor = BorderColor;
}
bool areaTreemap::getGradient() const
{
    return m_gradient;
}

void areaTreemap::setGradient(bool gradient)
{
    m_gradient = gradient;
}

int areaTreemap::getColor() const
{
    return m_Color;
}

void areaTreemap::setColor(int Color)
{
    m_Color = Color;
}

int areaTreemap::getBorder() const
{
    return m_border;
}

void areaTreemap::setBorder(int border)
{
    m_border = border;
}

bool areaTreemap::getMapDifference() const
{
    return m_MapDifference;
}

void areaTreemap::setMapDifference(bool MapDifference)
{
    m_MapDifference = MapDifference;
}



void areaTreemap::windowClose()
{
    this->setWindowsnumber(this->getWindowsnumber()-1);
}
int areaTreemap::getWindowsnumber() const
{
    return m_Windowsnumber;
}

void areaTreemap::setWindowsnumber(int Windowsnumber)
{
    m_Windowsnumber = Windowsnumber;
}

QList<rectHolder *> *areaTreemap::getRectList() const
{
    return m_RectList;
}

void areaTreemap::setRectList(QList<rectHolder *> *RectList)
{
    m_RectList = RectList;
}

QList<double> *areaTreemap::getAveragePrevlance() const
{
    return m_AveragePrevlance;
}

void areaTreemap::setAveragePrevlance(QList<double> *AveragePrevlance)
{
    m_AveragePrevlance = AveragePrevlance;
}

void areaTreemap::mousePressEvent(QMouseEvent *e)
{
    int x=e->pos().x();
    int y=e->pos().y();
    for(int i=0;i<this->getRectList()->size();i++)
    {
      if(this->getRectList()->at(i)->X()<x&&
         this->getRectList()->at(i)->X()+this->getRectList()->at(i)->W()>x&&
         this->getRectList()->at(i)->Y()<y&&
         this->getRectList()->at(i)->Y()+this->getRectList()->at(i)->L()>y)
      {
          treeMap * t=new treeMap(0,false,
                                  this->getColor(),
                                  this->Area()->RegionList()->at(i),
                                  this->getAveragePrevlance());
          t->setGeometry(10+530*this->getWindowsnumber(),730,520,620);
          t->setBorder(this->getBorder());
          t->setMapDifference(this->getMapDifference());
          t->setGradient(this->getGradient());
          t->setFont(this->getFont());
          t->setCgroup(this->getCgroup());
          t->setAttribute(Qt::WA_DeleteOnClose);
          t->setWindowFlags(Qt::WindowStaysOnTopHint);
          connect(t,SIGNAL(destroyed(QObject*)),this,SLOT(windowClose()));
          t->show();
          this->setWindowsnumber(this->getWindowsnumber()+1);
          update();
          break;

      }
    }
}







