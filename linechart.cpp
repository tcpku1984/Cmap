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
}

Linechart::~Linechart()
{
    delete ui;
}

void Linechart::paintEvent(QPaintEvent *event)
{
    this->dataColor0=m_Datacolor->getColor(this->Color());
    QPainter painter(this);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.drawLine(QPointF(10,10),QPointF(10,210));
    painter.drawLine(QPointF(310,210),QPointF(10,210));
    for(int i=0;i<this->getRegionList()->at(0)->healthData()->size();i++)
    {

            QPen pen;
            pen.setColor(this->dataColor0.at(i));
            painter.setPen(pen);
            painter.drawLine(QPointF(10,210-this->getRegionList()->at(0)->healthData()->at(i)*10),
                             QPointF(160,210-this->getRegionList()->at(1)->healthData()->at(i)*10));
            painter.drawLine(QPointF(160,210-this->getRegionList()->at(1)->healthData()->at(i)*10),
                             QPointF(310,210-this->getRegionList()->at(2)->healthData()->at(i)*10));

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
