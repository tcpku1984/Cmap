#include "areatreemap.h"
#include "ui_areatreemap.h"



areaTreemap::areaTreemap(QWidget *parent, bool color, AreaTeam * area,QList <float>* aver) :
    QWidget(parent),
    ui(new Ui::areaTreemap)
{
    m_AveragePrevlance=new QList<float>;
    m_RectList=new QList <rectHolder *>;
    this->setWindowsnumber(0);
    ui->setupUi(this);
    this->setOtherColor(color);
    this->setArea(area);
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
}

areaTreemap::~areaTreemap()
{
    delete ui;
}

void areaTreemap::paintEvent(QPaintEvent *event)
{
    if(this->getOtherColor()==true)
    {
        this->dataColor=this->dataColor1;
    }
    else
    {
        this->dataColor=this->dataColor2;
    }
    QPainter painter(this);
    QFont font("font:Arial");
    painter.setFont(font);
    QRect rect=QRect(0,0,600,100);
    QString tempString=this->Area()->AreaName()+"  "
            +this->Area()->AreaCode()+" \nCCG list :";
    for(int i=0;i<this->Area()->RegionList()->size();i++)
    {
        tempString+=this->Area()->RegionList()->at(i)->ccgName()
                +"; ";
    }


    this->setRectList(drawSqTreeMap(10,100,600,600,
                           0,this->Area()->PopulationList(),&painter));
    for(int j=0;j<this->getRectList()->size();j++)
    {
        qreal x=this->getRectList()->at(j)->X();
        qreal y=this->getRectList()->at(j)->Y();
        qreal w=this->getRectList()->at(j)->W();
        qreal l=this->getRectList()->at(j)->L();
        drawSqTreeMap(x,y,w,l,0,
                      this->Area()->RegionList()->at(j)->healthData(),
                      &painter);
    }
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
bool areaTreemap::getOtherColor() const
{
    return m_otherColor;
}

void areaTreemap::setOtherColor(bool otherColor)
{
    m_otherColor = otherColor;
}

QList<rectHolder *> *areaTreemap::drawSqTreeMap(qreal x, qreal y, qreal width, qreal length, int pos, QList<float> *data, QPainter *p)
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
        total+=data->at(i);
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
            value+=data->at(i);
        }
        for(int i=pos;i<pos+number;i++)
        {
            QRectF rect=QRectF(tempx,y,data->at(i)*width/value,value*length/total);
            //cout<<"new length"<<value*length/total<<endl;
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
            tempx=tempx+data->at(i)*width/value;
        }
        y=y+value*length/total;
        length=length-value*length/total;
        pos=pos+number;
        if(drawSqTreeMap(x,y,width,length,pos,data,p)!=NULL)
        {
            rectList->append(*drawSqTreeMap(x,y,width,length,pos,data,p));
        }
        return rectList;
    }
}

qreal areaTreemap::calRatio(qreal w, qreal l, int pos, int number, QList<float> *data)
{
    qreal ratio=1;
    qreal temp=1;
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
            //cout<<temp<<endl;
            sum=sum+temp;
            if(temp>ratio)
            {
                ratio=temp;
            }
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
    //cout<<sum<<endl;
    sum=sum/(number+1);
    ratio=sum;
    //cout<<sum<<endl;
    //ratio=sumRatio/(number+1);
    return ratio;
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

QList<float> *areaTreemap::getAveragePrevlance() const
{
    return m_AveragePrevlance;
}

void areaTreemap::setAveragePrevlance(QList<float> *AveragePrevlance)
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
                                  this->getOtherColor(),
                                  this->Area()->RegionList()->at(i),
                                  this->getAveragePrevlance());
          t->setGeometry(10+530*this->getWindowsnumber(),730,520,620);
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







