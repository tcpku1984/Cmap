#include "treemap.h"
#include "ui_treemap.h"

treeMap::treeMap(QWidget *parent,Region *region) :
    QWidget(parent),
    ui(new Ui::treeMap)
{
    ui->setupUi(this);
    this->setRegion(region);
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
        cout<<(qreal(90)+qreal(i)*90/qreal(2))<<endl;
    }
    for(int i=6;i<10;i++)
    {
        this->dataColor2.append(QColor::fromHsvF((qreal(180)+qreal(i-6)*90/qreal(4))/qreal(360),1,1));
        cout<<(qreal(180)+qreal(i)*90/qreal(4))<<endl;
    }
    for(int i=10;i<14;i++)
    {
        this->dataColor2.append(QColor::fromHsvF((qreal(270)+qreal(i-10)*90/qreal(4))/qreal(360),1,1));
        cout<<(qreal(270)+qreal(i)*90/qreal(4))<<endl;

    }
}


treeMap::~treeMap()
{
    delete ui;
}

void treeMap::paintEvent(QPaintEvent *event)
{
    this->dataColor=this->dataColor2;
    QPainter painter(this);
    QFont font("font:Arial");
    painter.setFont(font);
    QRect rect=QRect(0,0,500,100);
    QString temp=this->region()->ccgName()
            +this->region()->ccgCode()+"  "
            +QString::number(this->region()->poplation())+"  ";
    painter.drawText(rect,temp);
    drawSqTreeMap2(0,100,500,500,0,this->region()->healthData(),&painter);

}
Region *treeMap::region() const
{
    return m_region;
}

void treeMap::setRegion(Region *region)
{
    m_region = region;
}
void treeMap::drawSqTreeMap(qreal x, qreal y, qreal width, qreal length, int pos, QList<float> *data, QPainter *p)
{
    //p->setPen(Qt::white);
    if(pos>=data->size())
    {
        return;
    }
    qreal total=0;
    qreal ratio=INFINITY;
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
            p->fillRect(rect,dataColor.at(i));

            p->drawText(rect,QString::number(data->at(i)));
            tempx=tempx+data->at(i)*width/value;
        }
        y=y+value*length/total;
        length=length-value*length/total;
        pos=pos+number;
        drawSqTreeMap(x,y,width,length,pos,data,p);
    }
    /*
    else
    {
        qreal tempy=y;
        for(int i=pos;i<pos+number;i++)
        {
            value+=data->at(i);
        }
        for(int i=pos;i<pos+number;i++)
        {
            QRectF rect=QRectF(x,tempy,value*width/total,data->at(i)*length/value);
            p->fillRect(rect,dataColor.at(i));
            p->drawText(rect,QString::number(data->at(i)));
            tempy=tempy+data->at(i)*length/value;
        }
        x=x+value*width/total;
        width=width-value*width/total;
        pos=pos+number;
        drawSqTreeMap(x,y,width,length,pos,data,p);
    }*/
    //p->setPen(Qt::black);
}

void treeMap::drawSqTreeMap2(qreal x, qreal y, qreal width, qreal length, int pos, QList<float> *data, QPainter *p)
{
    if(pos>=data->size())
    {
        return;
    }
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
        cout<<"ratio1 "<<temp1<<"  ratio2 "<<temp2<<endl;
        if(temp1>temp2)
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
            p->fillRect(rect,dataColor.at(i));

            p->drawText(rect,QString::number(data->at(i)));
            tempx=tempx+data->at(i)*width/value;
        }
        y=y+value*length/total;
        length=length-value*length/total;
        pos=pos+number;
        drawSqTreeMap(x,y,width,length,pos,data,p);
    }
}

qreal treeMap::calRatio(qreal w, qreal l, int pos, int number, QList<float> *data)
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
    ratio=sum/(number+1);
    //cout<<"number:" <<number+1<<" ratio: "<<ratio<<endl;
    return ratio;
}

qreal treeMap::calRatio2(qreal w, qreal l, int pos, int number, QList<float> *data)
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
    ratio=sum/(number+1);
    return ratio;


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



