#include "linechart.h"
#include "ui_linechart.h"

Linechart::Linechart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Linechart)
{
    ui->setupUi(this);
    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::white);
    this->setPalette(pal);
    m_Datacolor=new dataColor();
    regionList=new QList<Region *>;
    m_HealthName<<"Coronary-heart-disease"<<"Heart Failure"<<"Stroke"
               <<"Chronic-kidney-disease"<<"Diabetes"<<"Hypertension"
              <<"COPD"<<"Mental-Health"<<"Osteoporosis"<<"Rheumatoid-Arthritis"
             <<"Cancer"<<"Epilepsy"<<"Hypothyroidism"<<"Asthma";
    this->setShowDifference(false);
    this->setTrend(0);
}

Linechart::~Linechart()
{
    delete ui;
}

void Linechart::paintEvent(QPaintEvent *event)
{
    QFont font("Arial");
    font.setPixelSize(10);
    this->dataColor0=m_Datacolor->getColor(this->Color());
    QPainter painter(this);
    painter.setFont(font);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.drawLine(QPointF(45,0),QPointF(45,510));
    painter.drawLine(QPointF(45,510),QPointF(790,510));
    painter.drawText(QRect(45,510,50,20),"2011");
    painter.drawText(QRect(395,510,50,20),"2012");
    painter.drawText(QRect(745,510,50,20),"2013");
    if(this->getShowDifference()==false)
    {
        painter.drawText(QRect(25,10,20,20),"20");
        painter.drawText(QRect(25,260,20,20),"10");
    }
    else
    {
        painter.drawText(QRect(25,10,20,20),"Max");
    }
    for(int i=0;i<this->getRegionList()->at(0)->healthData()->size();i++)
    {

            QPen pen;
            pen.setColor(this->dataColor0.at(i));
            pen.setWidth(2);
            painter.setPen(pen);
            QPointF a,b,c;
            if(this->getShowDifference()==false)
            {
                a=QPointF(50,500-this->getRegionList()->at(0)->healthData()->at(i)*25);
                b=QPointF(400,500-this->getRegionList()->at(1)->healthData()->at(i)*25);
                c=QPointF(750,500-this->getRegionList()->at(2)->healthData()->at(i)*25);

            }
            else
            {
                double max=-1;
                double min=100;
                for(int z=0;z<3;z++)
                {
                    if(max<this->getRegionList()->at(z)->healthData()->at(i))
                    {
                        max=this->getRegionList()->at(z)->healthData()->at(i);
                    }
                    if(min>this->getRegionList()->at(z)->healthData()->at(i))
                    {
                        min=this->getRegionList()->at(z)->healthData()->at(i);
                    }
                }

                if(max==min)
                {
                    a=QPointF(50,500);
                    b=QPointF(400,500);
                    c=QPointF(750,500);
                }
                else
                {
                    a=QPointF(50,500-(this->getRegionList()->at(0)->healthData()->at(i)-min)/(max-min)*480);
                    b=QPointF(400,500-(this->getRegionList()->at(1)->healthData()->at(i)-min)/(max-min)*480);
                    c=QPointF(750,500-(this->getRegionList()->at(2)->healthData()->at(i)-min)/(max-min)*480);
                }
            }
            pen.setWidth(10);
            painter.setPen(pen);


            painter.drawPoint(a);
            painter.drawPoint(b);
            painter.drawPoint(c);
            //painter.drawText(QRectF(),2011);

            painter.drawText(QRectF(770,c.ry()-10
                                    ,50,20),m_HealthName.at(i));
            if(this->getTrend()==2)
            {
                if((a.ry()<=b.ry())&&(b.ry()<=c.ry()))
                {  }
                else
                {
                    pen.setColor(Qt::white);
                }
            }
            else if(this->getTrend()==1)
            {
                if((a.ry()>=b.ry())&&(b.ry()>=c.ry()))
                {  }
                else
                {
                    pen.setColor(Qt::white);
                }
            }
            pen.setWidth(2);
            painter.setPen(pen);
            painter.drawLine(a,b);
            painter.drawLine(b,c);




    }
}

int Linechart::Color() const
{
    return m_Color;
}

void Linechart::setColor(int Color)
{
    m_Color = Color;
}

dataColor *Linechart::Datacolor() const
{
    return m_Datacolor;
}

void Linechart::setDatacolor(dataColor *Datacolor)
{
    m_Datacolor = Datacolor;
}

QList<Region *> *Linechart::getRegionList() const
{
    return regionList;
}

void Linechart::setRegionList(QList<Region *> *value)
{
    regionList = value;
}

bool Linechart::getShowDifference() const
{
    return m_showDifference;
}

void Linechart::setShowDifference(bool showDifference)
{
    m_showDifference = showDifference;
}
int Linechart::getTrend() const
{
    return m_Trend;
}

void Linechart::setTrend(int Trend)
{
    m_Trend = Trend;
}

