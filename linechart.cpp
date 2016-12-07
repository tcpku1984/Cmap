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
    //painter.drawLine(QPointF(10,10),QPointF(10,210));
    //painter.drawLine(QPointF(310,210),QPointF(10,210));
    for(int i=0;i<this->getRegionList()->at(0)->healthData()->size();i++)
    {

            QPen pen;
            pen.setColor(this->dataColor0.at(i));
            pen.setWidth(2);
            painter.setPen(pen);
            QPointF a,b,c;
            if(this->getShowDifference()==false)
            {
                a=QPointF(10,500-this->getRegionList()->at(0)->healthData()->at(i)*25);
                b=QPointF(360,500-this->getRegionList()->at(1)->healthData()->at(i)*25);
                c=QPointF(710,500-this->getRegionList()->at(2)->healthData()->at(i)*25);

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
                    a=QPointF(10,500);
                    b=QPointF(360,500);
                    c=QPointF(710,500);
                }
                else
                {
                    a=QPointF(10,500-(this->getRegionList()->at(0)->healthData()->at(i)-min)/max*500);
                    b=QPointF(360,500-(this->getRegionList()->at(1)->healthData()->at(i)-min)/max*500);
                    c=QPointF(710,500-(this->getRegionList()->at(2)->healthData()->at(i)-min)/max*500);
                }
            }
            painter.drawLine(a,b);
            painter.drawLine(b,c);
            pen.setWidth(10);
            painter.setPen(pen);
            painter.drawPoint(a);
            painter.drawPoint(b);
            painter.drawPoint(c);
            painter.drawText(QRectF(730,c.ry()-10
                                    ,50,20),m_HealthName.at(i));

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
