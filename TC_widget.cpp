/**
  * @file widget.cpp
  * @author Chao Tong
  * @date 10 Feb 2016
  * @see widget.h
  */
#include "TC_widget.h"
#include "ui_widget.h"


enum{
    RATHH=400,
    RATHV=600,
    HH=-200,
    VV=1050,
    MAXSIZE=65,
    HALF=2,
    TEXT=10,
    TEXTL=150,
    TEXTW=80,
    RECTSIZE=500,
    FONTSIZEA=15,
    FONTSIZEB=14,
    GRAY=85,
    NORTHBOUND=1,
    SOUTHBOUND=950,
    WESTBOUND=10,
    EASTBOUND=1600,
    HALFSIZE=105
};

bool verticalOrder(Region * r1, Region * r2)
{
    return r1->Longti()>r2->Longti();
}

bool horizontalOrder(Region * r1, Region * r2)
{
    return r1->Lati()>r2->Lati();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::white);
    this->setPalette(pal);
    m_regionListV= new QList<Region *>;
    m_regionListH= new QList<Region *>;
    index=0;
    m_increaseSize=1;
    m_regionMaxsize=110;
    m_searchRange=212;
    m_population=0;
    m_border=1;
    this->setColor(0);
    this->setFilter(0);
    finished=false;
    m_samesize=false;
    m_algorithm=true;
    m_lookAhead=false;
    this->setMapDifference(false);
    this->setGradient(false);
    this->setBorderColor(Qt::white);
    this->setFont(false);
    this->setCgroup(false);
    this->setMouseOver(false);
    m_Windowsnumber=0;
    m_AreaGroup=new QList<AreaTeam *>;
    this->setGroup(false);
    this->setColorFilter(false);
    this->setMouseTracking(true);
    this->setPercent(0);
    this->setScreen(false);
    refreshColor();
    m_AveragePrevlance=new QList<double>;
    for(int i=0;i<14;i++)
    {
        this->getAveragePrevlance()->append(0);
    }

    ui->setupUi(this);
    regionFile* file=new regionFile();
    file->readfile();
    this->setRegionListH(file->regionList());
    this->setRegionListV(file->regionList());
    this->setPopulation(file->populiation());
    this->setAreaGroup(file->AreaGroup());
    this->setAveragePrevlance(file->AveragePrevlance());
    cout<<"ccg size:"<<this->regionListH()->size()<<endl;
    cout<<"area number :"<<this->getAreaGroup()->size()<<endl;
    for(int i=0; i<this->getAreaGroup()->size();i++)
    {
        this->getAreaGroup()->at(i)->initi();
    }
    qSort(this->regionListH()->begin(),this->regionListH()->end(),
          horizontalOrder);
    for(int i=0;i<this->regionListH()->size();i++)
    {
        this->regionListH()->at(i)->setHOrder(i);
    }
    qSort(this->regionListV()->begin(),this->regionListV()->end(),
          verticalOrder);
    for(int i=0;i<this->regionListV()->size();i++)
    {
        this->regionListV()->at(i)->setVOrder(i);
    }
    /*
    for(int i=0;i<this->regionListV()->size();i++)
    {
        cout<<this->regionListV()->at(i)->getVOrder()<<" Horder : "<<
        this->regionListV()->at(i)->getHOrder()<<endl;
    }*/
    m_Datacolor=new dataColor();
    this->regionColor=m_Datacolor->getRegionColor();
    m_HealthName<<"Coronary-heart-disease"<<"Heart Failure"<<"Stroke"
               <<"Chronic-kidney-disease"<<"Diabetes"<<"Hypertension"
              <<"COPD"<<"Mental-Health"<<"Osteoporosis"<<"Rheumatoid-Arthritis"
             <<"Cancer"<<"Epilepsy"<<"Hypothyroidism"<<"Asthma";
    count=0;
    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(animate()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    this->dataColor0=m_Datacolor->getColor(this->getColor());
    QPainter painter(this);
    if(this->getGroup()==false)
    {
       paintCCg(&painter);
    }
    else
    {
        paintArea(&painter);
    }


}

void Widget::paintCCg(QPainter *painter)
{
    QFont font("Arial");
    font.setPixelSize(FONTSIZEA);
    painter->setFont(font);

    int z=this->regionListV()->size()/HALF;
    painter->setPen(Qt::green);
    painter->drawLine(QPoint(300,this->regionListV()->at(z)->Y()),
                     QPoint(1520,this->regionListV()->at(z)->Y()));
    painter->drawLine(QPoint(this->regionListH()->at(z)->X(),0),
                     QPoint(this->regionListH()->at(z)->X(),1920));
    painter->setPen(Qt::white);
    for(int i=0;i<this->regionListV()->size();i++)
    {
        painter->setBrush(regionColor.at(this->regionListV()->at(i)->getColorIndex()));
        if(this->getScreen()==false)
        {
            painter->drawRect(
                        QRectF(this->regionListV()->at(i)->X(),
                               this->regionListV()->at(i)->Y(),
                               this->regionListV()->at(i)->getSize(),
                               this->regionListV()->at(i)->getSize()));
        }
        else
        {
            painter->drawRect(
                        QRectF(this->regionListV()->at(i)->X(),
                               this->regionListV()->at(i)->Y(),
                               this->regionListV()->at(i)->getSize(),
                               this->regionListV()->at(i)->getSize()*9/16));
        }
    }

    if(this->getFinished())
    {
        painter->setBrush(Qt::NoBrush);
        if(this->getLookAhead()==false)
        {
            for(int i=0;i<this->regionListV()->size();i++)
            {
                if(this->getMapDifference()==false)
                {
                    if(this->getCgroup()==false)
                    {
                        if(this->getScreen()==false)
                        {
                            drawSqTreeMap(this->regionListV()->at(i)->X(),
                                        this->regionListV()->at(i)->Y(),
                                        this->regionListV()->at(i)->getSize(),
                                        this->regionListV()->at(i)->getSize(),0,
                                        this->regionListV()->at(i)->healthData(),
                                        painter,2);
                        }
                        else
                        {
                            drawSqTreeMap(this->regionListV()->at(i)->X(),
                                        this->regionListV()->at(i)->Y(),
                                        this->regionListV()->at(i)->getSize(),
                                        this->regionListV()->at(i)->getSize()*9/16,0,
                                        this->regionListV()->at(i)->healthData(),
                                        painter,2);

                        }
                    }
                    else
                    {
                       QList<double> * dataTemp=new QList<double>;
                       double temp=0;
                       for(int k=0;k<3;k++)
                       {
                           temp+=this->regionListV()->at(i)->healthData()->at(k);
                       }
                       dataTemp->append(temp);
                       for(int k=3;k<this->regionListV()->at(i)->healthData()->size();k++)
                       {
                           dataTemp->append(this->regionListV()->at(i)->healthData()->at(k));
                       }
                       drawSqTreeMap(this->regionListV()->at(i)->X(),
                                   this->regionListV()->at(i)->Y(),
                                   this->regionListV()->at(i)->getSize(),
                                   this->regionListV()->at(i)->getSize(),0,
                                   dataTemp,
                                   painter,2);
                    }
                }
                else
                {
                    QList <double>* dataTemp=new QList<double>;
                    for(int k=0;k<this->regionListV()->at(i)->healthData()->size();k++)
                    {
                        double tempdata=double(this->regionListV()->at(i)->healthData()->at(k)-
                                this->getAveragePrevlance()->at(k));
                        if(fabs(tempdata)>0.005)
                        {
                            dataTemp->append(this->regionListV()->at(i)->healthData()->at(k)-
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

                    drawSqTreeMap(this->regionListV()->at(i)->X(),
                                 this->regionListV()->at(i)->Y(),
                                 this->regionListV()->at(i)->getSize(),
                                 this->regionListV()->at(i)->getSize(),0,
                                 dataTemp,
                                 painter,2);


                }
            }
        }
        else
        {
            for(int i=0;i<this->regionListV()->size();i++)
            {

                drawSqTreeMap2(this->regionListV()->at(i)->X(),
                            this->regionListV()->at(i)->Y(),
                            this->regionListV()->at(i)->getSize(),
                            this->regionListV()->at(i)->getSize(),0,
                            this->regionListV()->at(i)->healthData(),
                            painter);
            }

        }
        for(int i=0;i<this->regionListV()->size();i++)
        {
            QPen pen;
            pen.setBrush(Qt::white);
            pen.setWidth(this->getBorder()+2);
            painter->setPen(pen);
            if(this->getScreen()==false)
            {
                painter->drawRect(this->regionListV()->at(i)->X(),
                                  this->regionListV()->at(i)->Y(),
                                  this->regionListV()->at(i)->getSize(),
                                  this->regionListV()->at(i)->getSize());
            }
            else
            {
                painter->drawRect(this->regionListV()->at(i)->X(),
                                  this->regionListV()->at(i)->Y(),
                                  this->regionListV()->at(i)->getSize(),
                                  this->regionListV()->at(i)->getSize()*9/16);
            }
        }
        drawSign(painter);
        if(this->getMouseOver()==true)
        {
            QFont font("Arial");
            font.setPixelSize(16);
            painter->setFont(font);
            QString output;
            output+=this->regionListV()->at(
                        this->getMouseOverIndex())->ccgName()+"\n";
            output+="population "+
                    QString::number(this->regionListV()->at(
                        this->getMouseOverIndex())->poplation())+"\n";
            for(int i=0;i<14;i++)
            {
                output+=m_HealthName.at(i)+" "+
                        QString::number(this->regionListV()->at(
                                                this->getMouseOverIndex())
                        ->healthData()->at(i))+" \n";

            }
            painter->drawText(QRect(50,50,300,500),
                              output);
        }
    }
}

void Widget::paintArea(QPainter *painter)
{
    //cout<<"paintArea"<<endl;
    for(int i=0;i<this->getAreaGroup()->size();i++)
    {
        painter->setBrush(regionColor.at(i%13));
        painter->drawRect(
                    QRectF(this->getAreaGroup()->at(i)->X(),
                           this->getAreaGroup()->at(i)->Y(),
                           this->getAreaGroup()->at(i)->Size(),
                           this->getAreaGroup()->at(i)->Size()));
    }
    if(this->getFinished()==true)
    {
        painter->setBrush(Qt::NoBrush);
        //cout<<"drawing"<<endl;
        for(int i=0;i<this->getAreaGroup()->size();i++)
        {
            //cout<<"draw Treemap: "<<i<<endl;
           QList<rectHolder *> *rectList;
            rectList=drawSqTreeMap(this->getAreaGroup()->at(i)->X(),
                          this->getAreaGroup()->at(i)->Y(),
                          this->getAreaGroup()->at(i)->Size(),
                          this->getAreaGroup()->at(i)->Size(),0,
                          this->getAreaGroup()->at(i)->PopulationList(),
                          painter,1);
            cout<<"i: "<<i<<" popluationlist "
               <<this->getAreaGroup()->at(i)->PopulationList()->size()
              <<" size "<<rectList->size()<<endl;
            cout<<"region list "<<this->getAreaGroup()->at(i)->RegionList()->size()<<endl;

            for(int j=0;j<rectList->size();j++)
            {
                //cout<<j<<endl;
                qreal x=rectList->at(j)->X();
                qreal y=rectList->at(j)->Y();
                qreal w=rectList->at(j)->W();
                qreal l=rectList->at(j)->L();
                if(this->getMapDifference()==false)
                {
                    if(this->getCgroup()==false)
                    {
                        drawSqTreeMap(x,y,w,l,0,
                             this->getAreaGroup()->at(i)->RegionList()->at(j)->healthData(),painter,2);
                    }
                    else
                    {
                        QList<double> * dataTemp=new QList<double>;
                        double temp=0;
                        for(int k=0;k<3;k++)
                        {
                            temp+=this->getAreaGroup()->at(i)->RegionList()->at(j)->healthData()->at(k);
                        }
                        dataTemp->append(temp);
                        for(int k=3;k<this->getAreaGroup()->at(i)->RegionList()->at(j)->healthData()->size();k++)
                        {
                            dataTemp->append(
                                        this->getAreaGroup()->at(i)->RegionList()->at(j)->healthData()->at(k));
                        }
                        drawSqTreeMap(x,y,w,l,0,
                                    dataTemp,
                                    painter,2);
                     }

                }
                else
                {
                    QList <double>* dataTemp=new QList<double>;
                    for(int k=0;k<this->regionListV()->at(i)->healthData()->size();k++)
                    {
                        double tempdata=double(this->getAreaGroup()->at(i)->RegionList()
                                               ->at(j)->healthData()->at(k)-
                                this->getAveragePrevlance()->at(k));
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
                                 painter,2);


                }
            }

            QPen pen(Qt::gray);
            painter->setBrush(Qt::NoBrush);
            for(int j=0;j<rectList->size();j++)
            {
                QLinearGradient grad(rectList->at(j)->X(),rectList->at(j)->Y(),
                                     rectList->at(j)->X()+
                                     rectList->at(j)->W(),
                                     rectList->at(j)->Y()+
                                     rectList->at(j)->L());
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
                painter->setPen(pen);
                painter->drawRect(rectList->at(j)->X(),
                                 rectList->at(j)->Y(),
                                 rectList->at(j)->W(),
                                 rectList->at(j)->L());

            }
            pen.setBrush(Qt::white);
            pen.setWidth(this->getBorder()+4);
            painter->setPen(pen);
            painter->drawRect(this->getAreaGroup()->at(i)->X(),
                              this->getAreaGroup()->at(i)->Y(),
                              this->getAreaGroup()->at(i)->Size(),
                              this->getAreaGroup()->at(i)->Size());
        }
        drawSign(painter);
        if(this->getMouseOver()==true)
        {
            QFont font("Arial");
            painter->setFont(font);
            painter->drawText(QRect(50,50,200,100),
                              this->getAreaGroup()->at(this->getMouseOverIndex())->AreaName());
        }
    }

}

void Widget::animate()
{
    if(this->getGroup()==false)
    {
        if(this->getAlgorithm()==false)
        {
            regionIncrease();
        }
        else
        {
            regionIncrease2();
        }
        index++;
        update();
    }
    else
    {
        areaIncrease();
        update();
    }
}

void Widget::regionIncrease()
{
    int k=index%this->regionListV()->size();
    if(k==0)
    {
        cout<<"loop :"<<index/this->regionListV()->size()<<endl;
        tCount.restart();
    }
    if(k==this->regionListV()->size()-1)
    {
        cout<<"Time:"<<tCount.elapsed()<<"ms"<<endl;
    }

    for(int i=0;i<this->increaseSize();i++)
    {
        double max;
        if(this->samesize()==false)
        {
            max=MAXSIZE*this->regionMaxsize()*double(
                    this->regionListV()->at(k)->poplation()
                    /double(this->population()));
        }
        else
        {
            max=this->regionMaxsize();
        }
        if(this->regionListV()->at(k)->stopIncrease()==false)
        {
           this->regionListV()->at(k)->increase();
            if(this->regionListV()->at(k)->getSize()
                    >max)
            {
                this->regionListV()->at(k)->stop();
                count++;
            }
        }
        if(overlap(k)->isEmpty()==false
                &&k>=this->regionListV()->size()/HALF)
        {
            if(this->testNorthOverlap(k))
            {
                moveSouth(this->regionListV()->size()/HALF);
            }
        }
         else if(overlap(k)->isEmpty()==false
                 &&k<this->regionListV()->size()/HALF)
         {
             if(this->testSouthOverlap(k))
             {
                 moveNorth(this->regionListV()->size()/HALF-1);
             }

         }

     }



    if(count>=this->regionListV()->size())
    {
        timer->stop();
        this->setFinished(true);
    }
}

void Widget::regionIncrease2()
{
    for(int i=0;i<this->regionListV()->size();i++)
    {
        double max;
        if(this->samesize()==false)
        {
            max=MAXSIZE*this->regionMaxsize()*double(
                    this->regionListV()->at(i)->poplation()
                    /double(this->population()));
        }
        else
        {
            max=this->regionMaxsize();
        }
        for(int k=0;k<this->increaseSize();k++)
        {
            if(this->regionListV()->at(i)->Y()<NORTHBOUND
                    &this->regionListV()->at(i)->X()<this->regionListH()->at(HALFSIZE)->X())
            {
                qreal temp=NORTHBOUND-this->regionListV()->at(i)->Y();
                this->regionListV()->at(i)->setX(this->regionListV()->at(i)->X()-temp);
                this->regionListV()->at(i)->setY(NORTHBOUND);
            }
            if(this->regionListV()->at(i)->Y()<NORTHBOUND
                    &this->regionListV()->at(i)->X()>=this->regionListH()->at(HALFSIZE)->X())
            {
                qreal temp=NORTHBOUND-this->regionListV()->at(i)->Y();
                this->regionListV()->at(i)->setX(this->regionListV()->at(i)->X()+temp);
                this->regionListV()->at(i)->setY(NORTHBOUND);

            }
            if(this->regionListV()->at(i)->Y()>SOUTHBOUND
                    &this->regionListV()->at(i)->X()<this->regionListH()->at(HALFSIZE)->X())
            {
                qreal temp=this->regionListV()->at(i)->Y()-SOUTHBOUND;
                this->regionListV()->at(i)->setX(this->regionListV()->at(i)->X()-temp);
                this->regionListV()->at(i)->setY(SOUTHBOUND);

            }
            if(this->regionListV()->at(i)->Y()>SOUTHBOUND
                    &this->regionListV()->at(i)->X()>=this->regionListH()->at(HALFSIZE)->X())
            {
                qreal temp=this->regionListV()->at(i)->Y()-SOUTHBOUND;
                this->regionListV()->at(i)->setX(this->regionListV()->at(i)->X()+temp);
                this->regionListV()->at(i)->setY(SOUTHBOUND);
            }
            /*
            if(this->regionListV()->at(i)->X()<WESTBOUND)
            {
                overlapRemove();
                timer->stop();
                this->setFinished(true);
            }
            if(this->regionListV()->at(i)->X()+this->regionListV()->at(i)->getSize()>EASTBOUND)
            {
                overlapRemove();
                timer->stop();
                this->setFinished(true);
            }*/

            if(this->regionListV()->at(i)->stopIncrease()==false)
            {
               this->regionListV()->at(i)->increase();
                if(this->regionListV()->at(i)->getSize()
                        >max)
                {
                    this->regionListV()->at(i)->stop();
                    count++;
                }
            }
        }
     }
    overlapRemove();
    if(count>=this->regionListV()->size())
    {
        timer->stop();
        this->setFinished(true);
    }
}

void Widget::areaIncrease()
{
    for(int i=0;i<this->getAreaGroup()->size();i++)
    {
        double max;
        if(this->samesize()==false)
        {
            max=MAXSIZE*this->regionMaxsize()*double(
                    this->getAreaGroup()->at(i)->Population()
                    /double(this->population()));
        }
        else
        {
            max=this->regionMaxsize();
        }

        if(this->getAreaGroup()->at(i)->stopIncrease()==false)
        {
           this->getAreaGroup()->at(i)->increase();
            if(this->getAreaGroup()->at(i)->Size()
                    >max)
            {
                this->getAreaGroup()->at(i)->setStopIncrease(true);
                count++;
            }
        }
     }
    overlapRemoveArea();
    if(count>=this->getAreaGroup()->size())
    {
        timer->stop();
        this->setFinished(true);
    }
}

bool Widget::getFinished() const
{
    return finished;
}

void Widget::setFinished(bool value)
{
    finished = value;
}

int Widget::searchRange() const
{
    return m_searchRange;
}

void Widget::setSearchRange(int searchRange)
{
    m_searchRange = searchRange;
}

bool Widget::getPressed() const
{
    return pressed;
}

void Widget::setPressed(bool value)
{
    pressed = value;
}




void Widget::mousePressEvent(QMouseEvent *e)
{
    int x=e->pos().x();
    int y=e->pos().y();
    this->setPressed(true);
    if(this->getGroup()==false)
    {
        for(int i=0;i<this->regionListV()->size();i++)
        {
          if(this->regionListV()->at(i)->X()<x&&
             this->regionListV()->at(i)->X()+this->regionListV()->at(i)->getSize()>x&&
             this->regionListV()->at(i)->Y()<y&&
             this->regionListV()->at(i)->Y()+this->regionListV()->at(i)->getSize()>y)
          {
              treeMap * t=new treeMap(0,this->getLookAhead(),
                                      this->getColor(),this->regionListV()->at(i),
                                      this->getAveragePrevlance());
              t->setBorder(this->getBorder());
              t->setMapDifference(this->getMapDifference());
              t->setGradient(this->getGradient());
              t->setGeometry(10+530*this->Windowsnumber(),30,520,620);
              t->setFont(this->getFont());
              t->setCgroup(this->getCgroup());
              t->setFilter(this->getFilter());
              t->setAttribute(Qt::WA_DeleteOnClose);
              t->setWindowFlags(Qt::WindowStaysOnTopHint);
              connect(t,SIGNAL(destroyed(QObject*)),this,SLOT(windowClose()));
              t->show();
              this->setWindowsnumber(this->Windowsnumber()+1);
              this->regionListV()->at(i)->setColor(2);
              this->regionListV()->at(i)->setDetail(true);
              QList <Region *> * temp=this->overlap(i);
              for(int j=0;j<temp->size();j++)
              {
                  temp->at(j)->setColor(0);
              }
              update();
              break;

          }
        }
    }
    else
    {
        for(int i=0;i<this->getAreaGroup()->size();i++)
        {
          if(this->getAreaGroup()->at(i)->X()<x&&
             this->getAreaGroup()->at(i)->X()+this->getAreaGroup()->at(i)->Size()>x&&
             this->getAreaGroup()->at(i)->Y()<y&&
             this->getAreaGroup()->at(i)->Y()+this->getAreaGroup()->at(i)->Size()>y)
          {
              areaTreemap * t=new areaTreemap(0,this->getColor(),this->getAreaGroup()->at(i),this->getAveragePrevlance());
              t->setBorder(this->getBorder());
              t->setMapDifference(this->getMapDifference());
              t->setGradient(this->getGradient());
              t->setGeometry(10+630*this->Windowsnumber(),30,620,720);
              t->setBorderColor(this->getBorderColor());
              t->setFont(this->getFont());
              t->setCgroup(this->getCgroup());
              t->setFilter(this->getFilter());
              t->setAttribute(Qt::WA_DeleteOnClose);
              t->setWindowFlags(Qt::WindowStaysOnTopHint);
              connect(t,SIGNAL(destroyed(QObject*)),this,SLOT(windowClose()));
              t->show();
              this->setWindowsnumber(this->Windowsnumber()+1);
              this->regionListV()->at(i)->setColor(2);
              this->regionListV()->at(i)->setDetail(true);
              QList <Region *> * temp=this->overlap(i);
              for(int j=0;j<temp->size();j++)
              {
                  temp->at(j)->setColor(0);
              }
              update();
              break;
          }
        }
    }
    if(this->getColorFilter()==true)
    {
        if(x>1610&&x<1750&&y>400&&y<400+400*13)
        {
            int i=(y-400)/40;
            if(this->colorlegend->at(i)==true)
            {
                this->colorlegend->replace(i, false);
            }
            else
            {
                this->colorlegend->replace(i,true);
            }
        }
    }


}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    this->setPressed(false);
    int x=e->pos().x();
    int y=e->pos().y();
    for(int i=0;i<this->regionListV()->size();i++)
    {
      if(this->regionListV()->at(i)->X()<x&&
         this->regionListV()->at(i)->X()+this->regionListV()->at(i)->getSize()>x&&
         this->regionListV()->at(i)->Y()<y&&
         this->regionListV()->at(i)->Y()+this->regionListV()->at(i)->getSize()>y)
      {
          this->regionListV()->at(i)->setColor(1);
          this->regionListV()->at(i)->setDetail(false);
          QList <Region *> * temp=this->overlap(i);
          for(int j=0;j<temp->size();j++)
          {
              temp->at(j)->setColor(1);
          }
          update();
          break;

      }
    }
    update();



}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    int x=e->pos().x();
    int y=e->pos().y();
    if(this->getGroup()==false)
    {
        int i=0;
        for(i;i<this->regionListV()->size();i++)
        {
          if(this->regionListV()->at(i)->X()<x&&
             this->regionListV()->at(i)->X()+this->regionListV()->at(i)->getSize()>x&&
             this->regionListV()->at(i)->Y()<y&&
             this->regionListV()->at(i)->Y()+this->regionListV()->at(i)->getSize()>y)
          {
              this->setMouseOver(true);
              this->setMouseOverIndex(i);
              update();
              break;
          }
        }
        if(i>=this->regionListV()->size())
        {
            this->setMouseOver(false);
            this->setMouseOverIndex(0);
            update();
        }
    }
    else
    {
        int i=0;
        for(i=0;i<this->getAreaGroup()->size();i++)
        {
          if(this->getAreaGroup()->at(i)->X()<x&&
             this->getAreaGroup()->at(i)->X()+this->getAreaGroup()->at(i)->Size()>x&&
             this->getAreaGroup()->at(i)->Y()<y&&
             this->getAreaGroup()->at(i)->Y()+this->getAreaGroup()->at(i)->Size()>y)
          {
              this->setMouseOver(true);
              this->setMouseOverIndex(i);
              update();
              break;
          }
        }
        if(i>=this->getAreaGroup()->size())
        {
            this->setMouseOver(false);
            this->setMouseOverIndex(0);
            update();
        }
    }
}


QList<rectHolder *> *Widget::drawSqTreeMap(qreal x, qreal y, qreal width, qreal length, int pos, QList<double> *data, QPainter *p, int layer)
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
                if(this->getColorFilter()==true)
                {

                    if(this->colorlegend->at(i)==false)
                    {
                        QPen pen(Qt::white);
                        pen.setWidth(this->getBorder());
                        p->setPen(pen);
                        p->fillRect(rect,QColor::fromHsvF(0,0,0.9));
                    }
                }

            }
            else
            {
                QPen pen(Qt::white);
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

qreal Widget::calRatio(qreal w, qreal l, int pos, int number, QList<double> *data)
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

QList <rectHolder *> * Widget::drawSqTreeMap2(qreal x, qreal y, qreal width, qreal length, int pos, QList<double> *data, QPainter *p)
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
        total+=fabs(data->at(i));
    }
    for(number=0;number<data->size()-pos;number++)
    {
        temp1=calRatio(width,length,pos,number,data);
        temp2=calRatio2(width,length,pos,number,data);
        //cout<<"ratio1 "<<temp1<<"  ratio2 "<<temp2<<endl;
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
            value+=fabs(data->at(i));
        }
        for(int i=pos;i<pos+number;i++)
        {
            QRectF rect=QRectF(tempx,y,fabs(data->at(i))*width/value,value*length/total);
            rectList->append(new rectHolder(tempx,y,fabs(data->at(i))*width/value,value*length/total));

            p->fillRect(rect,dataColor0.at(i));
            tempx=tempx+fabs(data->at(i))*width/value;
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

qreal Widget::calRatio2(qreal w, qreal l, int pos, int number, QList<double> *data)
{
    qreal ratio=1;
    qreal temp;
    qreal total=0;
    qreal sum=0;
    int i;
    for(i=pos;i<data->size();i++)
    {
        total+=fabs(data->at(i));
    }
    qreal value=0;
    for(int i=pos;i<=pos+number-1;i++)
    {
        value+=fabs(data->at(i));
    }
    if(true)//if(l>=w)
    {
        for(i=pos;i<=pos+number-1;i++)
        {
            temp=fabs(data->at(i))*total*w/(l*value*value);
            if(temp<1)
            {
                temp=1/temp;
            }
            sum=sum+temp;
        }
    }
    sum+=w*total/(fabs(data->at(pos+number))*l);
    ratio=sum/(number+1);
    return ratio;


}

void Widget::on_start_pressed()
{
    if(this->getGroup()==false)
    {

        for(int i=0;i<this->regionListV()->size();i++)
        {
            this->regionListV()->at(i)->setSize(1);
            this->regionListV()->at(i)->setX(
                        this->regionListV()->at(i)->Lati()/RATHH+HH);
            this->regionListV()->at(i)->setY(-
                        this->regionListV()->at(i)->Longti()/RATHV+VV);
            this->regionListV()->at(i)->setColor(0);
            this->regionListV()->at(i)->setStopIncrease(false);
        }
            this->setFinished(false);


        count=0;
        index=0;
        if(this->getAlgorithm()==false)
        {
            timer->start();
        }
        else
        {
            timer->start(100);
        }
    }
    else
    {
        for(int i=0;i<this->getAreaGroup()->size();i++)
        {
            this->getAreaGroup()->at(i)->initi();
        }
        this->setFinished(false);
        count=0;
        timer->start(20);
    }
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    this->setIncreaseSize(value);
}

void Widget::on_horizontalSlider_2_valueChanged(int value)
{
    this->setRegionMaxsize(value);
}



void Widget::on_horizontalSlider_3_valueChanged(int value)
{
    this->setSearchRange(value);
}


void Widget::addPopulation(int population)
{
    this->setPopulation(this->population()+population);

}


int Widget::population() const
{
    return m_population;
}

void Widget::setPopulation(int population)
{
    m_population = population;
}

int Widget::regionMaxsize() const
{
    return m_regionMaxsize;
}

void Widget::setRegionMaxsize(int regionMaxsize)
{
    m_regionMaxsize = regionMaxsize;
}

int Widget::increaseSize() const
{
    return m_increaseSize;
}

void Widget::setIncreaseSize(int increaseSize)
{
    m_increaseSize = increaseSize;
}

QList<Region *> *Widget::regionListH() const
{
    return m_regionListH;
}

void Widget::setRegionListH(QList<Region *> *regionListH)
{
    m_regionListH = regionListH;
}

QList<Region *> *Widget::regionListV() const
{
    return m_regionListV;
}

void Widget::setRegionListV(QList<Region *> *regionListV)
{
    m_regionListV = regionListV;
}

void Widget::drawSign(QPainter *p)
{ 
    QFont font("Arial",12,QFont::Bold);
    p->setFont(font);
    p->setPen(Qt::white);
    if(this->getCgroup()==false)
    {
        for(int i=0;i<14;i++)
        {
            if(this->getGradient()==false)
            {
                QLinearGradient temp(1610,400+i*40,1750,440+40*i);
                //QRadialGradient temp(QPoint(1830,420+40*i),60);
                temp.setColorAt(0,
                                QColor::fromHsvF(dataColor0[i].hueF(),
                                                 1,0.6));
                temp.setColorAt(1,
                                QColor::fromHsvF(dataColor0[i].hueF(),
                                                 0.6,1));
                p->fillRect(1610,400+i*40,140,40,temp);
            }
            else
            {
                QRadialGradient temp(QPoint(1680,420+40*i),80);
                temp.setColorAt(0,
                                QColor::fromHsvF(dataColor0[i].hueF(),
                                                 0.3,1));
                temp.setColorAt(1,
                                QColor::fromHsvF(dataColor0[i].hueF(),
                                                 1,0.7));
                p->fillRect(1610,400+i*40,140,40,temp);

            }
        }
    }
    else
    {
        for(int i=0;i<3;i++)
        {
            p->fillRect(1610,400+i*40,140,40,QColor::fromHsvF(dataColor0.at(0).hueF(),
                                                              1,0.3+i*0.15));
        }
        for(int i=3;i<14;i++)
        {
            if(this->getGradient()==false)
            {
                QLinearGradient temp(1610,400+i*40,1750,440+40*i);
                //QRadialGradient temp(QPoint(1830,420+40*i),60);
                temp.setColorAt(0,
                                QColor::fromHsvF(dataColor0[i-2].hueF(),
                                                 1,0.6));
                temp.setColorAt(1,
                                QColor::fromHsvF(dataColor0[i-2].hueF(),
                                                 0.6,1));
                p->fillRect(1610,400+i*40,140,40,temp);
            }
            else
            {
                QRadialGradient temp(QPoint(1680,420+40*i),80);
                temp.setColorAt(0,
                                QColor::fromHsvF(dataColor0[i-2].hueF(),
                                                 0.3,1));
                temp.setColorAt(1,
                                QColor::fromHsvF(dataColor0[i-2].hueF(),
                                                 1,0.7));
                p->fillRect(1610,400+i*40,140,40,temp);

            }
        }
    }
    if(this->getFilter()==0)
    {

    }
    else
    {
        p->setPen(Qt::black);
        p->drawText(QRect(1640,380,120,20),"Focus");
        p->drawText(QRect(1750,380,120,20),"Context");
        for(int i=0;i<14;i++)
        {
            p->fillRect(1750,400+i*40,70,40,QColor::fromHsvF(0,
                                                              0,0.97));
        }
    }
    p->setPen(Qt::white);
    p->drawText(QRect(1610,400,140,40),"Coronary-heart-disease");
    p->drawText(QRect(1610,440,140,40),"Heart Failure");
    p->drawText(QRect(1610,480,140,40),"Stroke");
    p->drawText(QRect(1610,520,140,40),"Chronic-kidney-disease");
    p->drawText(QRect(1610,560,140,40),"Diabetes");
    p->drawText(QRect(1610,600,140,40),"Hypertension");
    p->drawText(QRect(1610,640,140,40),"COPD");
    p->drawText(QRect(1610,680,140,40),"Mental-Health");
    p->drawText(QRect(1610,720,140,40),"Osteoporosis");
    p->drawText(QRect(1610,760,140,40),"Rheumatoid-Arthritis");
    p->drawText(QRect(1610,800,140,40),"Cancer");
    p->drawText(QRect(1610,840,140,40),"Epilepsy");
    p->drawText(QRect(1610,880,140,40),"Hypothyroidism");
    p->drawText(QRect(1610,920,140,40),"Asthma");
    if(this->getColorFilter()==true)
    {
        for(int i=0;i<14;i++)
        {
            if(this->colorlegend->at(i)==true)
            {
                QPen pen(Qt::black);
                pen.setWidth(4);
                p->setPen(pen);
                p->drawRect(1610,400+40*i,140,40);
            }
        }
    }
    font.setPixelSize(FONTSIZEA);
    font.setBold(false);
    p->setFont(font);
    p->setPen(Qt::black);



}

void Widget::overlapRemove()
{
    vpsc::Rectangle ** nodeRect = new vpsc::Rectangle * [this->regionListV()->size()];
    for(int i=0;i<this->regionListV()->size();i++)
    {
        int minX=this->regionListV()->at(i)->X();
        int maxX=minX+this->regionListV()->at(i)->getSize();
        int minY=this->regionListV()->at(i)->Y();
        int maxY;
        if(this->getScreen()==false)
        {
            maxY=minY+this->regionListV()->at(i)->getSize();
        }
        else
        {
            maxY=minY+this->regionListV()->at(i)->getSize()*9/16;
        }
        nodeRect[i]=new vpsc::Rectangle(minX,maxX,minY,maxY);
    }
    removeRectangleOverlap(this->regionListV()->size(),nodeRect,1e-3,1e-3);
    for(int i=0;i<this->regionListV()->size();i++)
    {
        this->regionListV()->at(i)->setX(nodeRect[i]->getMinX());
        this->regionListV()->at(i)->setY(nodeRect[i]->getMinY());
    }
}

void Widget::overlapRemoveArea()
{
    vpsc::Rectangle ** nodeRect = new vpsc::Rectangle * [this->getAreaGroup()->size()];
    for(int i=0;i<this->getAreaGroup()->size();i++)
    {
        int minX=this->getAreaGroup()->at(i)->X();
        int maxX=minX+this->getAreaGroup()->at(i)->Size();
        int minY=this->getAreaGroup()->at(i)->Y();
        int maxY=minY+this->getAreaGroup()->at(i)->Size();
        nodeRect[i]=new vpsc::Rectangle(minX,maxX,minY,maxY);
    }
    removeRectangleOverlap(this->getAreaGroup()->size(),nodeRect,1e-3,1e-3);
    for(int i=0;i<this->getAreaGroup()->size();i++)
    {
        this->getAreaGroup()->at(i)->setX(nodeRect[i]->getMinX());
        this->getAreaGroup()->at(i)->setY(nodeRect[i]->getMinY());
    }

}


void Widget::refreshColor()
{
    colorlegend=new QList<bool>;
    for(int i=0;i<14;i++)
    {
        colorlegend->append(false);
    }
}

bool Widget::getScreen() const
{
    return m_Screen;
}

void Widget::setScreen(bool Screen)
{
    m_Screen = Screen;
}
int Widget::getPercent() const
{
    return m_Percent;
}

void Widget::setPercent(int Percent)
{
    m_Percent = Percent;
}

int Widget::getMouseOverIndex() const
{
    return m_MouseOverIndex;
}

void Widget::setMouseOverIndex(int MouseOverIndex)
{
    m_MouseOverIndex = MouseOverIndex;
}

bool Widget::getMouseOver() const
{
    return m_MouseOver;
}

void Widget::setMouseOver(bool MouseOver)
{
    m_MouseOver = MouseOver;
}


bool Widget::getColorFilter() const
{
    return m_ColorFilter;
}

void Widget::setColorFilter(bool ColorFilter)
{
    m_ColorFilter = ColorFilter;
}

int Widget::getFilter() const
{
    return m_Filter;
}

void Widget::setFilter(int Filter)
{
    m_Filter = Filter;
}
bool Widget::getCgroup() const
{
    return m_Cgroup;
}

void Widget::setCgroup(bool Cgroup)
{
    m_Cgroup = Cgroup;
}


bool Widget::getFont() const
{
    return m_Font;
}

void Widget::setFont(bool Font)
{
    m_Font = Font;
}

QList<QColor> Widget::getDataColor0() const
{
    return dataColor0;
}

void Widget::setDataColor0(const QList<QColor> &value)
{
    dataColor0 = value;
}

QColor Widget::getBorderColor() const
{
    return m_BorderColor;
}

void Widget::setBorderColor(const QColor &BorderColor)
{
    m_BorderColor = BorderColor;
}
bool Widget::getGradient() const
{
    return m_gradient;
}

void Widget::setGradient(bool gradient)
{
    m_gradient = gradient;
}

int Widget::getColor() const
{
    return m_Color;
}

void Widget::setColor(int Color)
{
    m_Color = Color;
}

bool Widget::getMapDifference() const
{
    return m_mapDifference;
}

void Widget::setMapDifference(bool mapDifference)
{
    m_mapDifference = mapDifference;
}


int Widget::getBorder() const
{
    return m_border;
}

void Widget::setBorder(int border)
{
    m_border = border;
}
QList<double> *Widget::getAveragePrevlance() const
{
    return m_AveragePrevlance;
}

void Widget::setAveragePrevlance(QList<double> *AveragePrevlance)
{
    m_AveragePrevlance = AveragePrevlance;
}




bool Widget::getGroup() const
{
    return m_group;
}

void Widget::setGroup(bool group)
{
    m_group = group;
}

QList<AreaTeam *> *Widget::getAreaGroup() const
{
    return m_AreaGroup;
}

void Widget::setAreaGroup(QList<AreaTeam *> *AreaGroup)
{
    m_AreaGroup = AreaGroup;
}


bool Widget::getLookAhead() const
{
    return m_lookAhead;
}

void Widget::setLookAhead(bool lookAhead)
{
    m_lookAhead = lookAhead;
}

bool Widget::getAlgorithm() const
{
    return m_algorithm;
}

void Widget::setAlgorithm(bool algorithm)
{
    m_algorithm = algorithm;
}

int Widget::Windowsnumber() const
{
    return m_Windowsnumber;
}

void Widget::setWindowsnumber(int Windowsnumber)
{
    m_Windowsnumber = Windowsnumber;
}

bool Widget::samesize() const
{
    return m_samesize;
}

void Widget::setSamesize(bool samesize)
{
    m_samesize = samesize;
}


void Widget::on_checkBox_toggled(bool checked)
{
    if(checked==true)
    {
        this->setSamesize(true);
        this->setRegionMaxsize(37);
    }
    else
    {
        this->setSamesize(false);
        this->setRegionMaxsize(110);
    }
}

void Widget::windowClose()
{
    this->setWindowsnumber(this->Windowsnumber()-1);
}

void Widget::on_checkBox_2_toggled(bool checked)
{
    if(checked==true)
    {
        this->setAlgorithm(true);
    }
    else
    {
        this->setAlgorithm(false);
    }
}

void Widget::on_checkBox_3_toggled(bool checked)
{
    if(checked==true)
    {
        this->setLookAhead(true);
    }
    else
    {
        this->setLookAhead(false);
    }

}


void Widget::on_checkBox_5_toggled(bool checked)
{
    if(checked==true)
    {
        this->setGroup(true);
        this->setRegionMaxsize(48);
    }
    else
    {
        this->setGroup(false);
        this->setRegionMaxsize(110);
    }

}


void Widget::on_horizontalSlider_4_valueChanged(int value)
{
    this->setBorder(value);
}

void Widget::on_checkBox_6_toggled(bool checked)
{
    if(checked==true)
    {
        this->setMapDifference(true);
    }
    else
    {
        this->setMapDifference(false);
    }
}
QList<Region *> *Widget::overlap(int k)
{
    Region * r=this->regionListV()->at(k);
    QList <Region *> * temp= new QList<Region *>;
    QRect rect(r->X(),r->Y(),r->getSize(),r->getSize());
    int i=0;
    int max=this->regionListV()->size();
    if(k-this->searchRange()>0)
    {
        i=k-this->searchRange();
    }
    if(k+this->searchRange()<max)
    {
        max=k+this->searchRange();
    }
    for(i;i<max;i++)
    {
        Region * r1=this->regionListV()->at(i);
        QRect rect1(r1->X(),r1->Y(),r1->getSize(),r1->getSize());
        if(r->X()==r1->X()&&r->Y()==r1->Y())
        {

        }
        else
        {
            if(rect.contains(r1->X(),r1->Y(),false)||
               rect.contains(r1->X(),r1->Y()+r1->getSize(),false)||
               rect.contains(r1->X()+r1->getSize(),r1->Y(),false)||
               rect.contains(r1->X()+r1->getSize(),r1->Y()+r1->getSize(),false))
            {
                 temp->append(this->regionListV()->at(i));
            }
            else if(rect1.contains(r->X(),r->Y(),false)||
                    rect1.contains(r->X(),r->Y()+r->getSize(),false)||
                    rect1.contains(r->X()+r->getSize(),r->Y(),false)||
                    rect1.contains(r->X()+r->getSize(),r->Y()+r->getSize(),false))
            {
                temp->append(this->regionListV()->at(i));
            }

        }
    }
    return temp;
}


bool Widget::testSouthOverlap(int k)
{
    Region * r=this->regionListV()->at(k);
    QList <Region *> * temp=this->overlap(k);
    if(temp->isEmpty()==true)
    {
      return false;
    }
    else
    {
       for(int i=0;i<temp->size();i++)
       {
           if(temp->at(i)->Y()>=r->Y())
           {
               return true;
           }
       }
       return false;
    }
}

void Widget::moveNorth(int vOrder)
{
    if(vOrder<0)
    {
        return;
    }
    if(testSouthOverlap(vOrder)==true)
    {
        this->regionListV()->at(vOrder)->moveNorth();
        if(testWestOverlap(vOrder)==true)
            this->regionListV()->at(vOrder)->moveWest();
        moveNorth(vOrder-1);
    }
    else
    {
        if(testWestOverlap(vOrder)==true)
            this->regionListV()->at(vOrder)->moveWest();
        moveNorth(vOrder-1);
    }


}

bool Widget::testNorthOverlap(int k)
{
    Region * r=this->regionListV()->at(k);
    QList <Region *> * temp=this->overlap(k);
    if(temp->isEmpty()==true)
    {
      return false;
    }
    else
    {
       for(int i=0;i<temp->size();i++)
       {
           if(temp->at(i)->Y()<r->Y())
           {
               return true;
           }
       }
       return false;
    }
}

void Widget::moveSouth(int vOrder)
{
    if(vOrder>=this->regionListV()->size())
    {
        return;
    }
    if(testNorthOverlap(vOrder)==true)
    {
        this->regionListV()->at(vOrder)->moveSouth();
        if(testEastOverlap(vOrder)==true)
            this->regionListV()->at(vOrder)->moveEast();
        moveSouth(vOrder+1);
    }
    else
    {
        if(testEastOverlap(vOrder)==true)
            this->regionListV()->at(vOrder)->moveEast();
        moveSouth(vOrder+1);
    }


}

bool Widget::testWestOverlap(int k)
{
    Region * r=this->regionListV()->at(k);
    QList <Region *> * temp=this->overlap(k);
    if(temp->isEmpty()==true)
    {
      return false;
    }
    else
    {
       for(int i=0;i<temp->size();i++)
       {
           if(temp->at(i)->X()>r->X())
           {
               return true;
           }
       }
       return false;
    }
}

bool Widget::testEastOverlap(int k)
{
    Region * r=this->regionListV()->at(k);
    QList <Region *> * temp=this->overlap(k);
    if(temp->isEmpty()==true)
    {
      return false;
    }
    else
    {
       for(int i=0;i<temp->size();i++)
       {
           if(temp->at(i)->X()<r->X())
           {
               return true;
           }
       }
       return false;
    }


}

void Widget::on_checkBox_4_toggled(bool checked)
{
    if(checked==true)
    {
        this->setGradient(true);
    }
    else
    {
        this->setGradient(false);
    }
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    this->setColor(index);
}

void Widget::on_pushButton_clicked()
{

    this->setBorderColor(QColorDialog::getColor(Qt::white,this));
}

void Widget::on_checkBox_7_toggled(bool checked)
{
    if(checked==true)
    {
        this->setFont(true);
    }
    else
    {
        this->setFont(false);
    }
}

void Widget::on_checkBox_9_toggled(bool checked)
{
    if(checked==true)
    {
        this->setCgroup(true);
    }
    else
    {
        this->setCgroup(false);
    }
}

void Widget::on_comboBox_2_currentIndexChanged(int index)
{
    this->setFilter(index);
}

void Widget::on_checkBox_8_toggled(bool checked)
{
    if(checked==true)
    {
        refreshColor();
        this->setColorFilter(true);
    }
    else
    {
        refreshColor();
        this->setColorFilter(false);
    }
}


void Widget::on_checkBox_10_toggled(bool checked)
{
    if(checked==true)
    {
        this->setScreen(true);
    }
    else
    {
        this->setScreen(false);
    }
}
