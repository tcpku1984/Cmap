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
    HH=-400,
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
    EASTBOUND=1650,
    HALFSIZE=105,
    HALFSIZEA=13,
    TEXTX=1760,
    SIGNX=1680,
    DELAY=500,
    STEP=50
};

bool verticalOrder(Region * r1, Region * r2)
{
    return r1->Longti()>r2->Longti();
}

bool horizontalOrder(Region * r1, Region * r2)
{
    return r1->Lati()>r2->Lati();
}


bool XOrder(Region *r1, Region * r2)
{
    return r1->X()>=r2->X();
}


bool YOrder(Region *r1, Region * r2)
{
    return r1->Y()>=r2->Y();
}
bool XAOrder(AreaTeam *r1, AreaTeam * r2)
{
    return r1->X()>=r2->X();
}


bool YAOrder(AreaTeam *r1, AreaTeam * r2)
{
    return r1->Y()>=r2->Y();
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
    m_regionListSave= new QList<Region *>;
    m_Currentregion= new QList<Region *>;
    m_Lastregion= new QList<Region *>;
    m_CurrentYregion= new QList<Region *>;
    m_LastYregion= new QList<Region *>;
    m_CurrentregionA=new QList<AreaTeam *>;
    m_LastregionA=new QList<AreaTeam *>;
    m_CurrentYregionA=new QList<AreaTeam *>;
    m_LastYregionA=new QList<AreaTeam *>;
    m_FileList=new QList<QList<Region *>*>;
    m_dataCheck=new QList<int>;
    m_polygonList=new QList<QPolygonF *>;
    m_River=new QList<QString>;
    m_crossCount=0;
    //m_RiverPolygon=new QPolygonF();
    for(int i=0;i<14;i++)
    {
        m_dataCheck->append(1);
    }
    this->setTrend(0);
    this->setAspectRatio(1);
    this->setBottomStair(false);
    this->setGap(0);
    this->setShowDifference(false);
    this->setLineChart(false);

    index=0;
    index3=0;
    m_increaseSize=1;
    m_regionMaxsize=110;
    m_searchRange=209;
    m_population=0;
    m_dataYear=2013;
    this->setLoopCount(1);
    m_border=1;
    this->setColor(6);
    this->setFilter(0);
    finished=false;
    m_samesize=true;
    m_algorithm=true;
    m_lookAhead=false;
    this->setMapDifference(false);
    this->setGradient(false);
    this->setBorderColor(Qt::white);
    this->setFont(false);
    this->setCgroup(false);
    this->setMouseOver(false);
    this->setConer(false);
    m_Windowsnumber=0;
    m_AreaGroup=new QList<AreaTeam *>;
    this->setGroup(false);
    this->setColorFilter(false);
    this->setMouseTracking(true);
    this->setPercent(0);
    this->setScreen(false);
    this->setCenterLines(false);
    this->setCenterPoints(false);
    this->setError(0);
    this->setLocalError(0);
    this->setYError(0);
    this->setLocalYError(0);
    this->setStep(false);
    this->setXcross(true);
    this->setYcross(true);
    this->setLocalPercentage(20);
    this->setBColor(true);
    this->setOpacity(100);
    this->setRiverBoundary(false);
    refreshColor();
    regionFile* polyfile=new regionFile();
    polyfile->readPolygon();
    m_polygonList=polyfile->PolygonList();
    polyfile->readRiver();
    m_River=polyfile->River();
    for(int i=0;i<m_River->size();i++)
    {
        cout<<m_River->at(i).toStdString();
    }

    for(int i=0;i<3;i++)
    {
        regionFile* file=new regionFile();
        file->readfile(2011+i);
        QList<Region *> * temp=new QList<Region *>;
        temp=file->regionList();
        qSort(temp->begin(),temp->end(),
                                     verticalOrder);
        this->getFileList()->append(temp);


    }
    for(int i=0;i<this->getFileList()->at(0)->size();i++)
    {
        index2.append(0);
    }
    sta=new TC_statistics();
    sta->setWindowFlags(Qt::WindowStaysOnTopHint);
    sta->setGeometry(QRect(10,600,400,200));
    m_AveragePrevlance=new QList<double>;
    for(int i=0;i<14;i++)
    {
        this->getAveragePrevlance()->append(0);
    }

    ui->setupUi(this);
    regionFile* file=new regionFile();
    file->readfile(2013);
    this->setRegionListV(file->regionList());
    this->setPopulation(file->populiation());
    this->setAreaGroup(file->AreaGroup());
    this->setAveragePrevlance(file->AveragePrevlance());
    for(int i=0;i<this->regionListV()->size();i++)
    {
       this->regionListH()->append(this->regionListV()->at(i));

    }
    for(int i=0;i<this->searchRange();i++)
    {
        this->getLastregion()->append(this->regionListV()->at(i));
        this->getCurrentregion()->append(this->regionListV()->at(i));
        this->getLastYregion()->append(this->regionListV()->at(i));
        this->getCurrentYregion()->append(this->regionListV()->at(i));
    }

    cout<<"ccg size:"<<this->regionListH()->size()<<endl;
    cout<<"area number :"<<this->getAreaGroup()->size()<<endl;
    for(int i=0; i<this->getAreaGroup()->size();i++)
    {
        this->getAreaGroup()->at(i)->initi();
        this->getLastregionA()->append(this->getAreaGroup()->at(i));
        this->getCurrentregionA()->append(this->getAreaGroup()->at(i));
        this->getLastYregionA()->append(this->getAreaGroup()->at(i));
        this->getCurrentYregionA()->append(this->getAreaGroup()->at(i));
    }
    qSort(this->regionListH()->begin(),this->regionListH()->end(),
          horizontalOrder);
    qSort(this->regionListV()->begin(),this->regionListV()->end(),
                                 verticalOrder);
    for(int i=0;i<this->regionListH()->size();i++)
    {
        this->regionListH()->at(i)->setHOrder(i);
    }

    for(int i=0;i<this->regionListV()->size();i++)
    {
        this->regionListV()->at(i)->setVOrder(i);
    }
    qSort(this->getCurrentregion()->begin(),this->getCurrentregion()->end(),
          XOrder);
    qSort(this->getLastregion()->begin(),this->getLastregion()->end(),
          XOrder);
    errorCount(this->getLastregion(),this->getCurrentregion());
    qSort(this->getCurrentYregion()->begin(),this->getCurrentYregion()->end(),
          YOrder);
    qSort(this->getLastYregion()->begin(),this->getLastYregion()->end(),
          YOrder);
    errorYCount(this->getLastYregion(),this->getCurrentYregion());

    qSort(this->getCurrentregionA()->begin(),this->getCurrentregionA()->end(),
          XAOrder);
    qSort(this->getLastregionA()->begin(),this->getLastregionA()->end(),
          XAOrder);
    qSort(this->getCurrentYregionA()->begin(),this->getCurrentYregionA()->end(),
          YAOrder);
    qSort(this->getLastYregionA()->begin(),this->getLastYregionA()->end(),
          YAOrder);

    m_Datacolor=new dataColor();
    this->regionColor=m_Datacolor->getRegionColor();
    m_HealthName<<"Coronary-heart-disease"<<"Heart Failure"<<"Stroke"
               <<"Chronic-kidney-disease"<<"Diabetes"<<"Hypertension"
              <<"COPD"<<"Mental-Health"<<"Osteoporosis"<<"Rheumatoid-Arthritis"
             <<"Cancer"<<"Epilepsy"<<"Hypothyroidism"<<"Asthma";
    count=0;
    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(animate()));
    timer2=new QTimer();
    connect(timer2,SIGNAL(timeout()),this,SLOT(animation()));
    timer3=new QTimer();
   connect(timer3,SIGNAL(timeout()),this,SLOT(animationRiver()));



       riverPoly=new QPolygonF();
       for(int i=m_River->size()-1;i>0;i=i-2)
       {
           int i1=-1;
           int i2=-1;
           for(int z=0;z<this->regionListV()->size();z++)
           {
               //cout<<this->regionListV()->at(z)->ccgCode().toStdString()<<endl;
               if(this->regionListV()->at(z)->ccgCode()==m_River->at(i))
               {
                   i1=z;
               }
               if(this->regionListV()->at(z)->ccgCode()==m_River->at(i-1))
               {
                   i2=z;
               }
           }
           if(i1==i2)
           {
               //painter->drawPoint(this->regionListV()->at(i1)->X()+this->regionListV()->at(i1)->getSize()/2,
                 //                 this->regionListV()->at(i1)->Y()+this->regionListV()->at(i1)->getSize()/2);
               riverPoly->append(QPointF(this->regionListV()->at(i1)->X()+this->regionListV()->at(i1)->getSize()/2,
                                         this->regionListV()->at(i1)->Y()+this->regionListV()->at(i1)->getSize()/2));
           }
           else
           {
               //painter->drawLine(QPointF(this->regionListV()->at(i1)->X()+this->regionListV()->at(i1)->getSize()/2,
                 //                        this->regionListV()->at(i1)->Y()+this->regionListV()->at(i1)->getSize()/2),
                   //              QPointF(this->regionListV()->at(i2)->X()+this->regionListV()->at(i2)->getSize()/2,
                     //                                                  this->regionListV()->at(i2)->Y()+this->regionListV()->at(i2)->getSize()/2));
               //painter->drawPoint(QPointF(this->regionListV()->at(i1)->X()/2+this->regionListV()->at(i1)->getSize()/4
                 //                         +this->regionListV()->at(i2)->X()/2+this->regionListV()->at(i2)->getSize()/4,
                   //                       this->regionListV()->at(i1)->Y()/2+this->regionListV()->at(i1)->getSize()/4
                     //                     +this->regionListV()->at(i2)->Y()/2+this->regionListV()->at(i2)->getSize()/4));
               riverPoly->append(QPointF(this->regionListV()->at(i1)->X()/2+this->regionListV()->at(i1)->getSize()/4
                                         +this->regionListV()->at(i2)->X()/2+this->regionListV()->at(i2)->getSize()/4,
                                         this->regionListV()->at(i1)->Y()/2+this->regionListV()->at(i1)->getSize()/4
                                         +this->regionListV()->at(i2)->Y()/2+this->regionListV()->at(i2)->getSize()/4));

           }
       }
       int y;
       for(int z=0;z<this->regionListV()->size();z++)
       {
           for(y=0;y<this->riverPoly->size();y++)
           {
               if(this->regionListV()->at(z)->X()+this->regionListV()->at(z)->getSize()/2>
                       this->riverPoly->at(y).x())
               {
                   break;
               }
           }
           cout<<"test y:"<<y<<endl;
           if(y==0)
           {
               if(this->regionListV()->at(z)->Y()+this->regionListV()->at(z)->getSize()/2-
                       this->riverPoly->at(y).y()>0)
               {
                   this->regionListV()->at(z)->setRiverSide(-1);
               }
               else if(this->regionListV()->at(z)->Y()+this->regionListV()->at(z)->getSize()/2-
                       this->riverPoly->at(y).y()<0)
               {
                   this->regionListV()->at(z)->setRiverSide(1);
               }
               else
               {
                   this->regionListV()->at(z)->setRiverSide(0);
               }
           }
           else if(y==this->riverPoly->size())
           {
               if(this->regionListV()->at(z)->Y()+this->regionListV()->at(z)->getSize()/2-
                       this->riverPoly->at(y-1).y()>0)
               {
                   this->regionListV()->at(z)->setRiverSide(-1);
               }
               else if(this->regionListV()->at(z)->Y()+this->regionListV()->at(z)->getSize()/2-
                       this->riverPoly->at(y-1).y()<0)
               {
                   this->regionListV()->at(z)->setRiverSide(1);
               }
               else
               {
                   this->regionListV()->at(z)->setRiverSide(0);
               }
           }
           else
           {
               //cout<<"test"<<endl;
               double dx=this->riverPoly->at(y-1).x()-this->riverPoly->at(y).x();
               double dy=this->riverPoly->at(y-1).y()-this->riverPoly->at(y).y();
               double tmpx=this->regionListV()->at(z)->X()+this->regionListV()->at(z)->getSize()/2-this->riverPoly->at(y).x();
               double tmpy=this->riverPoly->at(y).y()+tmpx*dy/dx;
               double tmp=this->regionListV()->at(z)->Y()+this->regionListV()->at(z)->getSize()/2-tmpy;
               /*
               double tmp=(this->riverPoly->at(y-1).y()-this->riverPoly->at(y).y())*
                       this->regionListV()->at(z)->X()+
                       (this->riverPoly->at(y).x()-this->riverPoly->at(y-1).x())*
                                              this->regionListV()->at(z)->Y()+
                       this->riverPoly->at(y-1).x()*this->riverPoly->at(y).y()-
                       this->riverPoly->at(y).x()*this->riverPoly->at(y-1).y();*/
               if(tmp>0)
                   this->regionListV()->at(z)->setRiverSide(-1);
               else if(tmp<0)
                   this->regionListV()->at(z)->setRiverSide(1);
               else
                   this->regionListV()->at(z)->setRiverSide(0);

           }


       }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    this->dataColor0=m_Datacolor->getColor(this->getColor());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for(int i=0;i<m_polygonList->size();i++)
    {
        //cout<<"testing::"<<m_polygonList->at(i)->at(0).x()<<"  :   "<<m_polygonList->at(i)->at(0).y()<<endl;
        painter.drawPolyline(*m_polygonList->at(i));
    }
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


    //cout<<"size :"<<this->regionListV()->at(0)->getSize()<<endl;
    painter->setPen(Qt::white);
    //m_crossCount=0;
    for(int i=0;i<this->regionListV()->size();i++)
    {
        painter->setBrush(regionColor.at(this->regionListV()->at(i)->getColorIndex()));
        if(this->regionListV()->at(i)->getCrossRiver()==true)
            painter->setBrush(Qt::black);
        if(this->getScreen()==false)
        {
            painter->drawRect(
                        QRectF(this->regionListV()->at(i)->X(),
                               this->regionListV()->at(i)->Y(),
                               this->regionListV()->at(i)->getSize(),
                               this->regionListV()->at(i)->getSize()));

           painter->drawText(QRectF(this->regionListV()->at(i)->X(),
                                     this->regionListV()->at(i)->Y(),
                                     this->regionListV()->at(i)->getSize(),
                                     this->regionListV()->at(i)->getSize()), QString::number(
                                  this->regionListV()->at(i)->getRiverSide()));
            /*
            painter->drawText(QRectF(this->regionListV()->at(i)->X(),
                                      this->regionListV()->at(i)->Y(),
                                      this->regionListV()->at(i)->getSize(),
                                      this->regionListV()->at(i)->getSize()),
                                   this->regionListV()->at(i)->ccgCode());*/

        }
        else
        {
            painter->drawRect(
                        QRectF(this->regionListV()->at(i)->X(),
                               this->regionListV()->at(i)->Y(),
                               this->regionListV()->at(i)->getSize(),
                               this->regionListV()->at(i)->getSize()*9/16));
        }
        double size=0;
        for(int i=0;i<this->regionListV()->size();i++)
        {
            if(this->getScreen()==false)
            {
                size+=this->regionListV()->at(i)->getSize()*
                        this->regionListV()->at(i)->getSize();
            }
            else
            {
                size+=this->regionListV()->at(i)->getSize()*
                        this->regionListV()->at(i)->getSize()*9/16;
            }
        }
        size=size*100/(SOUTHBOUND-NORTHBOUND)/(EASTBOUND-WESTBOUND);
        sta->setSize(QString::number(size));
        sta->setLocalError(QString::number(this->getLocalError()));
        sta->setLocalYError(QString::number(this->getLocalYError()));
        sta->setGlobelError(QString::number(this->getError()));
        sta->setGlobelYError(QString::number(this->getYError()));
        sta->setLocalErrorP(QString::number(double(100*this->getLocalError())
                                            /this->regionListV()->size()/this->regionListV()->size()));
        sta->setLocalYErrorP(QString::number(double(100*this->getLocalYError())
                                            /this->regionListV()->size()/this->regionListV()->size()));
        sta->setGlobelErrorP(QString::number(double(100*this->getError())/this->regionListV()->size()
                                             /this->regionListV()->size()));
        sta->setGlobelYErrorP(QString::number(double(100*this->getYError())/this->regionListV()->size()
                                             /this->regionListV()->size()));
        sta->setLocalTError(QString::number(double(100*this->getLocalError())
                                            /this->regionListV()->size()/this->regionListV()->size()
                                            +double(100*this->getLocalYError())
                                            /this->regionListV()->size()/this->regionListV()->size()));
        sta->setGlobelTError(QString::number(double(100*this->getError())
                                            /this->regionListV()->size()/this->regionListV()->size()
                                            +double(100*this->getYError())
                                            /this->regionListV()->size()/this->regionListV()->size()));

        sta->update();

    }
    //overlapRemove();


        QPen riverPen;
        riverPen.setWidth(5);
        riverPen.setColor(Qt::green);
        painter->setPen(riverPen);
        painter->drawPolyline(*riverPoly);



    if(this->getFinished())
    {
        painter->setBrush(Qt::NoBrush);
        /*
        if(this->getLineChart()==true)
        {
            for(int i=0;i<this->regionListV()->size();i++)
            {

               // drawLineChart(this->regionListV()->at(i)->X(),
                    //          this->regionListV()->at(i)->Y(),
                         //     this->regionListV()->at(i)->getSize(),
                        //      i,painter);
                drawGlyphChart(this->regionListV()->at(i)->X(),
                              this->regionListV()->at(i)->Y(),
                              this->regionListV()->at(i)->getSize(),
                              i,painter);
            }

        }
        else
        {
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
                                            painter,2,i);
                            }
                            else
                            {
                                drawSqTreeMap(this->regionListV()->at(i)->X(),
                                            this->regionListV()->at(i)->Y(),
                                            this->regionListV()->at(i)->getSize(),
                                            this->regionListV()->at(i)->getSize()*9/16,0,
                                            this->regionListV()->at(i)->healthData(),
                                            painter,2,i);

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
                                       painter,2,i);
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
                                     painter,2,i);


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

        }*/

        for(int i=0;i<this->regionListV()->size();i++)
        {
            QPen pen;
            if(this->getBColor()==true)
            {
                pen.setBrush(regionColor.at(this->regionListV()->at(i)->getColorIndex()));
            }
            else
            {
                pen.setBrush(Qt::white);
            }

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
        double size=0;
        for(int i=0;i<this->regionListV()->size();i++)
        {
            if(this->getScreen()==false)
            {
                size+=this->regionListV()->at(i)->getSize()*
                        this->regionListV()->at(i)->getSize();
            }
            else
            {
                size+=this->regionListV()->at(i)->getSize()*
                        this->regionListV()->at(i)->getSize()*9/16;
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
        /*
        if(this->getFont()==false)
        {
            cout<<index3<<endl;
            QPen riverPen;
            riverPen.setWidth(5);
            riverPen.setColor(Qt::blue);
            painter->setPen(riverPen);
            if(m_RiverPolygon!=NULL)
            {
                //cout<<"here 1"<<endl;
                for(int z=0;z<m_RiverPolygon->size();z++)
                {
                    painter->drawPoint(m_RiverPolygon->at(z));
                }
                painter->drawPolygon(*m_RiverPolygon);
            }
            int i1=-1,i2=-2;
            if(index3*2+1<m_River->size())
            {
                //cout<<"here 2"<<endl;
                for(int z=0;z<this->regionListV()->size();z++)
                {
                    //cout<<this->regionListV()->at(z)->ccgCode().toStdString()<<endl;
                    if(this->regionListV()->at(z)->ccgCode()==m_River->at(index3*2))
                    {
                        i1=z;
                    }
                    if(this->regionListV()->at(z)->ccgCode()==m_River->at(index3*2+1))
                    {
                        i2=z;
                    }
                }
                if(i1>0&&i2>0)
                {
                    painter->fillRect(QRectF(this->regionListV()->at(i1)->X(),this->regionListV()->at(i1)->Y(),
                                  this->regionListV()->at(i1)->getSize(),this->regionListV()->at(i1)->getSize()),Qt::red);
                    painter->fillRect(QRectF(this->regionListV()->at(i2)->X(),this->regionListV()->at(i2)->Y(),
                                  this->regionListV()->at(i2)->getSize(),this->regionListV()->at(i2)->getSize()),Qt::red);
                    m_RiverPolygon->append(QPointF(this->regionListV()->at(i1)->X()/2+this->regionListV()->at(i1)->getSize()/4
                                               +this->regionListV()->at(i2)->X()/2+this->regionListV()->at(i2)->getSize()/4,
                                               this->regionListV()->at(i1)->Y()/2+this->regionListV()->at(i1)->getSize()/4
                                               +this->regionListV()->at(i2)->Y()/2+this->regionListV()->at(i2)->getSize()/4));
                    painter->drawPoint(QPointF(this->regionListV()->at(i1)->X()/2+this->regionListV()->at(i1)->getSize()/4
                                               +this->regionListV()->at(i2)->X()/2+this->regionListV()->at(i2)->getSize()/4,
                                               this->regionListV()->at(i1)->Y()/2+this->regionListV()->at(i1)->getSize()/4
                                               +this->regionListV()->at(i2)->Y()/2+this->regionListV()->at(i2)->getSize()/4));
                }
            }
            else
            {
                timer3->stop();

            }
        }
*/
    }
    painter->setPen(Qt::green);
    painter->drawLine(QPointF(10,this->regionListV()->at(z)->Y()+
                             this->regionListV()->at(z)->getSize()/2),
                     QPoint(1600,this->regionListV()->at(z)->Y()
                            +this->regionListV()->at(z)->getSize()/2));
    painter->drawLine(QPointF(this->regionListH()->at(z)->X()+
                             this->regionListH()->at(z)->getSize()/2,0),
                     QPointF(this->regionListH()->at(z)->X()+
                            this->regionListH()->at(z)->getSize()/2,1920));
    if(this->getCenterLines()==true)
    {
        for(int i=0;i<this->regionListH()->size();i++)
        {
            painter->setPen(regionColor.at(this->regionListH()->at(i)->getColorIndex()));
            painter->drawLine(QPointF(this->regionListH()->at(i)->X()+
                                     this->regionListH()->at(i)->getSize()/2,0),
                             QPointF(this->regionListH()->at(i)->X()+
                                    this->regionListH()->at(i)->getSize()/2,1080));
        }
    }
    if(this->getCenterPoints()==true)
    {
        for(int i=0;i<this->searchRange();i++)
        {
            if(this->regionListV()->at(i)->getCrossing()->size()>0)
            {
                for(int z=0;z<this->regionListV()->at(i)->getCrossing()->size();z++)
                {
                    //if(true)
                    if(this->regionListV()->at(i)->X()<this->regionListV()->at(i)->getCrossing()->at(z)->X())
                    {
                        painter->setPen(regionColor.at(this->regionListV()->at(i)->getColorIndex()));
                        QLineF line=QLineF(QPointF(this->regionListV()->at(i)->X()+
                                                   this->regionListV()->at(i)->getSize()/2,
                                                   this->regionListV()->at(i)->Y()+
                                                   this->regionListV()->at(i)->getSize()/2),
                                           QPointF(this->regionListV()->at(i)->getCrossing()->at(z)->X()+
                                                   this->regionListV()->at(i)->getCrossing()->at(z)->getSize()/2,
                                                   this->regionListV()->at(i)->getCrossing()->at(z)->Y()+
                                                   this->regionListV()->at(i)->getCrossing()->at(z)->getSize()/2));
                        if(line.length()<double(this->getLocalPercentage())*(SOUTHBOUND-NORTHBOUND)/100)
                        {
                            painter->setPen(Qt::gray);
                        }

                        else
                        {
                            QLinearGradient grad;
                            grad.setStart(QPointF(this->regionListV()->at(i)->X()+
                                                  this->regionListV()->at(i)->getSize()/2,
                                                  this->regionListV()->at(i)->Y()+
                                                  this->regionListV()->at(i)->getSize()/2));
                            grad.setFinalStop(QPointF(this->regionListV()->at(i)->getCrossing()->at(z)->X()+
                                                      this->regionListV()->at(i)->getCrossing()->at(z)->getSize()/2,
                                                      this->regionListV()->at(i)->getCrossing()->at(z)->Y()+
                                                      this->regionListV()->at(i)->getCrossing()->at(z)->getSize()/2));
                            grad.setColorAt(0,Qt::gray);
                            grad.setColorAt(double(this->getLocalPercentage())*(SOUTHBOUND-NORTHBOUND)/100/line.length()
                                            ,Qt::gray);
                            //cout<<double(this->getLocalPercentage())*(SOUTHBOUND-NORTHBOUND)/100/line.length()<<endl;
                            grad.setColorAt(double(this->getLocalPercentage())*(SOUTHBOUND-NORTHBOUND)/100/line.length()+0.000001
                                            ,regionColor.at(this->regionListV()->at(i)->getColorIndex()));
                            grad.setColorAt(1,regionColor.at(this->regionListV()->at(i)->getColorIndex()));
                            QPen pen;
                            pen.setWidth(0);
                            pen.setBrush(grad);
                            painter->setPen(pen);
                        }
                        painter->drawLine(line);
                    }
                }
            }
        }
    }
    painter->setPen(Qt::black);
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
    double size=0;
    for(int i=0;i<this->getAreaGroup()->size();i++)
    {
        size+=this->getAreaGroup()->at(i)->Size()
                *this->getAreaGroup()->at(i)->Size();
    }
    size=size*100/(SOUTHBOUND-NORTHBOUND)/(EASTBOUND-WESTBOUND);
    sta->setSize(QString::number(size));
    sta->setGlobelError(QString::number(this->getError()));
    sta->setGlobelYError(QString::number(this->getYError()));
    sta->setGlobelErrorP(QString::number(double(100*this->getError())/this->getAreaGroup()->size()
                                         /this->getAreaGroup()->size()));
    sta->setGlobelYErrorP(QString::number(double(100*this->getYError())/this->getAreaGroup()->size()
                                         /this->getAreaGroup()->size()));
    sta->setGlobelTError(QString::number(double(100*this->getError())
                                        /this->getAreaGroup()->size()/this->getAreaGroup()->size()
                                        +double(100*this->getYError())
                                        /this->getAreaGroup()->size()/this->getAreaGroup()->size()));


    sta->update();
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
                          painter,1,i);
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
                             this->getAreaGroup()->at(i)->RegionList()->at(j)->healthData(),painter,2,i);
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
                                    painter,2,i);
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
                                 painter,2,i);


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
            if(this->getBColor()==true)
            {
                pen.setBrush(regionColor.at(i%13));
            }
            else
            {
                pen.setBrush(Qt::white);
            }
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

void Widget::animation()
{
    for(int i=0;i<this->getFileList()->at(0)->size();i++)
    {
        index2.replace(i,index2.at(i)+1);
    }

    update();
}

void Widget::animationRiver()
{
    index3++;
    update();
}

void Widget::regionIncrease()
{
    this->setLoopCount(this->getLoopCount()+1);
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
    cout<<"index::"<<index<<endl;
    cout<<"m cross:"<<m_crossCount<<endl;
        if(index%2==0)
        {
            if(m_crossCount==0)
            {
                this->setLoopCount(this->getLoopCount()+1);
                for(int i=0;i<this->searchRange();i++)
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
                for(int i=0;i<this->regionListV()->size();i++)
                {
                    this->regionListV()->at(i)->setLastX(this->regionListV()->at(i)->X());
                    this->regionListV()->at(i)->setLastY(this->regionListV()->at(i)->Y());

                }
                //overlapRemove();
            }
            overlapRemove();
        }
        else
        {
            m_crossCount=0;
            for(int i=0;i<this->regionListV()->size();i++)
            {
                this->regionListV()->at(i)->setCrossRiver(false);

                double tmp=0;
                 int y;
                 int currentriverside=0;
                     for(y=0;y<this->riverPoly->size();y++)
                     {
                         if(this->regionListV()->at(i)->X()+this->regionListV()->at(i)->getSize()/2>
                                 this->riverPoly->at(y).x())
                         {
                             break;
                         }
                     }
                     if(y==0)
                     {
                         if(this->regionListV()->at(i)->Y()+this->regionListV()->at(i)->getSize()/2-
                                 this->riverPoly->at(y).y()>0)
                         {
                             currentriverside=-1;
                         }
                         else if(this->regionListV()->at(i)->Y()+this->regionListV()->at(i)->getSize()/2-
                                 this->riverPoly->at(y).y()<0)
                         {
                            currentriverside=1;
                         }
                     }
                     else if(y==this->riverPoly->size())
                     {
                         if(this->regionListV()->at(i)->Y()+this->regionListV()->at(i)->getSize()/2-
                                 this->riverPoly->at(y-1).y()>0)
                         {
                             currentriverside=-1;
                         }
                         else if(this->regionListV()->at(i)->Y()+this->regionListV()->at(i)->getSize()/2-
                                 this->riverPoly->at(y-1).y()<0)
                         {
                            currentriverside=1;
                         }

                     }
                     else
                     {
                         double dx=this->riverPoly->at(y-1).x()-this->riverPoly->at(y).x();
                         double dy=this->riverPoly->at(y-1).y()-this->riverPoly->at(y).y();
                         double tmpx=this->regionListV()->at(i)->X()+this->regionListV()->at(i)->getSize()/2-this->riverPoly->at(y).x();
                         double tmpy=this->riverPoly->at(y).y()+tmpx*dy/dx;
                         tmp=this->regionListV()->at(i)->Y()+this->regionListV()->at(i)->getSize()/2-tmpy;
                         if(tmp>0)
                             currentriverside=-1;
                         else if(tmp<0)
                             currentriverside=1;


                     }
                     //cout<<"temp:"<<tmp<<endl;
                     if(abs(currentriverside-this->regionListV()->at(i)->getRiverSide())>1)
                     {
                        // cout<<"temp:"<<tmp<<endl;
                         this->regionListV()->at(i)->setCrossRiver(true);
                         m_crossCount++;
                         if(this->getRiverBoundary()==true)
                         {
                                 this->regionListV()->at(i)->setX(this->regionListV()->at(i)->getLastX());
                                 this->regionListV()->at(i)->setY(this->regionListV()->at(i)->getLastY());
                             //this->regionListV()->at(i)->setY(this->regionListV()->at(i)->Y()-tmp);
                                 //cout<<"move: "<<tmp<<endl;

                         }

                     }

            }
            cout<<"test: "<<m_crossCount<<endl;

        }


    for(int i=0;i<this->regionListV()->size();i++)
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

        if(this->regionListV()->at(i)->X()<WESTBOUND)
        {
            if(this->getConer()==false)
            {
                overlapRemove();
                timer->stop();
                this->setFinished(true);
            }
            else
            {
                if(this->regionListV()->at(i)->Y()<this->regionListV()->at(HALFSIZE)->Y())
                {
                    if(this->regionListV()->at(i)->Y()<=NORTHBOUND)
                    {
                        overlapRemove();
                        timer->stop();
                        this->setFinished(true);
                    }
                    else
                    {
                        qreal temp=this->regionListV()->at(i)->X()-WESTBOUND;
                        this->regionListV()->at(i)->setY(this->regionListV()->at(i)->Y()+temp);
                        this->regionListV()->at(i)->setX(WESTBOUND);
                    }
                }
                else
                {
                    if(this->regionListV()->at(i)->Y()>=SOUTHBOUND)
                    {
                        overlapRemove();
                        timer->stop();
                        this->setFinished(true);
                    }
                    else
                    {
                        qreal temp=this->regionListV()->at(i)->X()-WESTBOUND;
                        this->regionListV()->at(i)->setY(this->regionListV()->at(i)->Y()-temp);
                        this->regionListV()->at(i)->setX(WESTBOUND);
                    }
                }

            }
        }
        if(this->regionListV()->at(i)->X()>EASTBOUND)
        {
            if(this->getConer()==false)
            {
                overlapRemove();
                timer->stop();
                this->setFinished(true);
            }
            else
            {
                if(this->regionListV()->at(i)->Y()<this->regionListV()->at(HALFSIZE)->Y())
                {
                    if(this->regionListV()->at(i)->Y()<=NORTHBOUND)
                    {
                        overlapRemove();
                        timer->stop();
                        this->setFinished(true);
                    }
                    else
                    {
                        qreal temp=this->regionListV()->at(i)->X()-EASTBOUND;
                        this->regionListV()->at(i)->setY(this->regionListV()->at(i)->Y()-temp);
                        this->regionListV()->at(i)->setX(EASTBOUND);
                    }
                }
                else
                {
                    if(this->regionListV()->at(i)->Y()>=SOUTHBOUND)
                    {
                        overlapRemove();
                        timer->stop();
                        this->setFinished(true);
                    }
                    else
                    {
                        qreal temp=this->regionListV()->at(i)->X()-EASTBOUND;
                        this->regionListV()->at(i)->setY(this->regionListV()->at(i)->Y()+temp);
                        this->regionListV()->at(i)->setX(EASTBOUND);
                    }
                }

            }

        }
    }
    overlapRemove();
    if(this->getXcross()==true)
    {
        qSort(this->getCurrentregion()->begin(),this->getCurrentregion()->end(),
              XOrder);
        this->setError(this->getError()+
                       errorCount(this->getLastregion(),this->getCurrentregion()));
        this->getLastregion()->clear();
        for(int i=0;i<this->getCurrentregion()->size();i++)
        {
            this->getLastregion()->append(
                        this->getCurrentregion()->at(i));
        }
    }
    if(this->getYcross()==true)
    {
        qSort(this->getCurrentYregion()->begin(),this->getCurrentYregion()->end(),
              YOrder);

        this->setYError(this->getYError()+
                       errorYCount(this->getLastYregion(),this->getCurrentYregion()));
        this->getLastYregion()->clear();
        for(int i=0;i<this->getCurrentregion()->size();i++)
        {
            this->getLastYregion()->append(
                        this->getCurrentYregion()->at(i));
        }
    }

    if(count>=this->searchRange())
    {
        timer->stop();
        this->setFinished(true);
    }
    if(this->getStep()==true)
    {
        timer->stop();
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
    for(int i=0;i<this->getAreaGroup()->size();i++)
    {
        if(this->getAreaGroup()->at(i)->Y()<NORTHBOUND
                &this->getAreaGroup()->at(i)->X()<this->getAreaGroup()->at(HALFSIZEA)->X())
        {
            qreal temp=NORTHBOUND-this->getAreaGroup()->at(i)->Y();
            this->getAreaGroup()->at(i)->setX(this->getAreaGroup()->at(i)->X()-temp);
            this->getAreaGroup()->at(i)->setY(NORTHBOUND);
        }
        if(this->getAreaGroup()->at(i)->Y()<NORTHBOUND
                &this->getAreaGroup()->at(i)->X()>=this->getAreaGroup()->at(HALFSIZEA)->X())
        {
            qreal temp=NORTHBOUND-this->regionListV()->at(i)->Y();
            this->getAreaGroup()->at(i)->setX(this->getAreaGroup()->at(i)->X()+temp);
            this->getAreaGroup()->at(i)->setY(NORTHBOUND);

        }
        if(this->getAreaGroup()->at(i)->Y()>SOUTHBOUND
                &this->getAreaGroup()->at(i)->X()<this->getAreaGroup()->at(HALFSIZEA)->X())
        {
            qreal temp=this->getAreaGroup()->at(i)->Y()-SOUTHBOUND;
            this->getAreaGroup()->at(i)->setX(this->getAreaGroup()->at(i)->X()-temp);
            this->getAreaGroup()->at(i)->setY(SOUTHBOUND);

        }
        if(this->getAreaGroup()->at(i)->Y()>SOUTHBOUND
                &this->getAreaGroup()->at(i)->X()>=this->getAreaGroup()->at(HALFSIZEA)->X())
        {
            qreal temp=this->getAreaGroup()->at(i)->Y()-SOUTHBOUND;
            this->getAreaGroup()->at(i)->setX(this->getAreaGroup()->at(i)->X()+temp);
            this->getAreaGroup()->at(i)->setY(SOUTHBOUND);
        }

        if(this->getAreaGroup()->at(i)->X()<WESTBOUND)
        {
                overlapRemoveArea();
                timer->stop();
                this->setFinished(true);
         }
        if(this->getAreaGroup()->at(i)->X()>EASTBOUND)
        {
                overlapRemoveArea();
                timer->stop();
                this->setFinished(true);
         }
    }
    overlapRemoveArea();
    if(this->getXcross()==true)
    {
        qSort(this->getCurrentregionA()->begin(),this->getCurrentregionA()->end(),
              XAOrder);
        errorCountA(this->getLastregionA(),this->getCurrentregionA());
        this->getLastregionA()->clear();
        for(int i=0;i<this->getCurrentregionA()->size();i++)
        {
            this->getLastregionA()->append(
                        this->getCurrentregionA()->at(i));
        }
    }
    if(this->getYcross()==true)
    {
        qSort(this->getCurrentYregionA()->begin(),this->getCurrentYregionA()->end(),
              YAOrder);
        errorYCountA(this->getLastYregionA(),this->getCurrentYregionA());
        this->getLastYregionA()->clear();
        for(int i=0;i<this->getCurrentregionA()->size();i++)
        {
            this->getLastYregionA()->append(
                        this->getCurrentYregionA()->at(i));
        }
    }
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
              QList<Region *> * listTemp=new QList<Region *>;
              for(int z=0;z<3;z++)
              {
                  listTemp->append(this->getFileList()->at(z)->at(i));
              }
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
              t->setAspectRatio(this->getAspectRatio());
              t->setAttribute(Qt::WA_DeleteOnClose);
              t->setWindowFlags(Qt::WindowStaysOnTopHint);
              t->setRegionList(listTemp);
              t->setTrend(this->getTrend());
              t->setBottomStair(this->getBottomStair());
              t->setSingleYear(this->getSingleYear());
              t->setGap(this->getGap());
              t->setShowDifference(this->getShowDifference());
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
        if(x>1680&&x<1750&&y>440&&y<440+40*13)
        {
            int i=(y-440)/40;
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


QList<rectHolder *> *Widget::drawSqTreeMap(qreal x, qreal y, qreal width, qreal length, int pos, QList<double> *data, QPainter *p, int layer,int j)
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
            if(fabs(data->at(i))<0.01)
            {

            }
            else
            {
            QRectF rect=QRectF(tempx,y,fabs(data->at(i))*width/value,value*length/total);
            //cout<<"new length"<<value*length/total<<endl;
            rectList->append(new rectHolder(tempx,y,fabs(data->at(i))*width/value,value*length/total));
            if(layer==2)
            {
                p->fillRect(rect,Qt::white);
                QList <QRectF> * rectListTemp=new QList<QRectF>;
                double max=-1;
                double min=100;
                int trend;
                if(this->getSingleYear()==false)
                {
                    if(this->getFileList()->at(0)->at(j)->healthData()->at(i)>=this->getFileList()->at(1)->at(j)->healthData()->at(i)&
                            this->getFileList()->at(1)->at(j)->healthData()->at(i)>=this->getFileList()->at(2)->at(j)->healthData()->at(i))
                    {
                        trend=2;
                    }
                    else if(this->getFileList()->at(0)->at(j)->healthData()->at(i)<=this->getFileList()->at(1)->at(j)->healthData()->at(i)&
                            this->getFileList()->at(1)->at(j)->healthData()->at(i)<=this->getFileList()->at(2)->at(j)->healthData()->at(i))
                    {
                        trend=1;
                    }
                    else
                    {
                        trend=0;
                    }
                    for(int z=0;z<3;z++)
                    {
                        if(max<this->getFileList()->at(z)->at(j)->healthData()->at(i))
                        {
                            max=this->getFileList()->at(z)->at(j)->healthData()->at(i);
                        }
                        if(min>this->getFileList()->at(z)->at(j)->healthData()->at(i))
                        {
                            min=this->getFileList()->at(z)->at(j)->healthData()->at(i);
                        }
                    }
                    for(int z=0;z<3;z++)
                    {
                        double smally;
                        double smallw;
                        if(this->getShowDifference()==true)
                        {
                            if(max==min)
                            {
                                smally=y+value*length/total;
                                smallw=0;
                            }
                            else
                            {
                                if(this->getBottomStair()==false)
                                {
                                    smally=y+value*length/total*(1-(this->getFileList()->at(z)->at(j)->healthData()->at(i)-min)/(max-min));
                                    smallw=value*length/total*(this->getFileList()->at(z)->at(j)->healthData()->at(i)-min)/(max-min);
                                    if(this->getFileList()->at(z)->at(j)->healthData()->at(i)==min)
                                    {
                                        smally=y+value*length/total*0.95;
                                        smallw=value*length/total*0.05;
                                    }
                                }
                                else
                                {
                                    smally=y+value*length/total*(0.5-(this->getFileList()->at(z)->at(j)->healthData()->at(i)-min)/(max-min)/2);
                                    smallw=value*length/total*(this->getFileList()->at(z)->at(j)->healthData()->at(i)-min)/(max-min);
                                    if(this->getFileList()->at(z)->at(j)->healthData()->at(i)==min)
                                    {
                                        smally=y+value*length/total*0.475;
                                        smallw=value*length/total*0.05;
                                    }
                                }
                            }
                        }
                        else
                        {
                            if(this->getBottomStair()==false)
                            {
                                smally=y+value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max)
                                        +this->getGap()*value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max);
                                smallw=value*length/total*this->getFileList()->at(z)->at(j)->healthData()->at(i)/max-
                                        this->getGap()*value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max);
                                while(smally>y+length/2||smallw<0)
                                {
                                    smally=smally-value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max);
                                    smallw=smallw+value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max);
                                }
                            }
                            else
                            {
                                smally=y+value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max)+
                                        this->getGap()*value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max);
                                smallw=value*length/total*this->getFileList()->at(z)->at(j)->healthData()->at(i)/max-
                                        value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max)-
                                        2*this->getGap()*value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max);
                                while(smally>y+length/2||smallw<0)
                                {
                                    smally=smally-value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max);
                                    smallw=smallw+2*value*length/total*(1-this->getFileList()->at(z)->at(j)->healthData()->at(i)/max);
                                }
                            }
                        }
                            double x;
                            if(trend==1)
                            {
                                x=tempx+z*double(fabs(data->at(i))*width/value)/3+index2.at(j)*double(fabs(data->at(i))*width/value)/STEP;
                            }
                            else if(trend==2)
                            {
                                x=tempx+z*double(fabs(data->at(i))*width/value)/3-index2.at(j)*double(fabs(data->at(i))*width/value)/STEP;
                            }
                            else
                            {
                                x=tempx+z*double(fabs(data->at(i))*width/value)/3;
                            }
                            //

                            if(x>tempx+double(fabs(data->at(i))*width/value))
                            {
                                double w=double(fabs(data->at(i))*width/value)/3;

                                if(x>=tempx+6*w)
                                {
                                    index2.replace(j,0);
                                }
                                x=x-double(fabs(data->at(i))*width/value)-w;

                                if(x+w>tempx+double(fabs(data->at(i))*width/value))
                                {
                                    w=tempx+double(fabs(data->at(i))*width/value)-x;

                                    QRectF rectTemp=QRectF(x,
                                                        smally,
                                                        w,
                                                        smallw);
                                    rectListTemp->append(rectTemp);
                                }
                                else if(x<tempx)
                                {
                                    w=x+w-tempx;
                                    QRectF rectTemp=QRectF(tempx,
                                                        smally,
                                                        w,
                                                        smallw);
                                    rectListTemp->append(rectTemp);

                                }
                                else
                                {
                                    QRectF rectTemp=QRectF(x,
                                                        smally,
                                                        w,
                                                        smallw);
                                    rectListTemp->append(rectTemp);
                                }
                            }
                            else if(x<tempx)
                            {
                                double w=double(fabs(data->at(i))*width/value)/3;
                                if(x<tempx-4*w)
                                {
                                    index2.replace(j,0);
                                }
                                if(x>tempx-w)
                                {
                                    w=x+w-tempx;
                                    QRectF rectTemp=QRectF(tempx,
                                                        smally,
                                                        w,
                                                        smallw);
                                    rectListTemp->append(rectTemp);

                                }
                                else
                                {

                                    x=x+double(fabs(data->at(i))*width/value)+w;
                                    if(x>tempx+2*w)
                                    {
                                        w=tempx+3*w-x;
                                    }

                                    QRectF rectTemp=QRectF(x,
                                                        smally,
                                                        w,
                                                        smallw);
                                    rectListTemp->append(rectTemp);

                                }




                           }
                            else
                            {
                                double w=double(fabs(data->at(i))*width/value)/3;
                                if(x+w>tempx+double(fabs(data->at(i))*width/value))
                                {
                                    w=tempx+double(fabs(data->at(i))*width/value)-x;
                                }
                                QRectF rectTemp=QRectF(x,
                                                    smally,
                                                    w,
                                                    smallw);
                                rectListTemp->append(rectTemp);
                            }

                    }
                }

                if(this->getGradient()==false)
                {
                    QLinearGradient grad(tempx,y,
                                         tempx+fabs(data->at(i))*width/value,
                                         y+value*length/total);
                    grad.setColorAt(0,
                                    dataColor0.at(i));
                    grad.setColorAt(1,
                                    dataColor0.at(i));
                    /*
                    grad.setColorAt(0,
                                    QColor::fromHsvF(dataColor0.at(i).hueF(),
                                                     1,0.5));
                    grad.setColorAt(1,
                                    QColor::fromHsvF(dataColor0.at(i).hueF(),
                                                     0.5,1));*/

                    if(this->getSingleYear()==true)
                    {
                        p->fillRect(rect,grad);
                    }
                    else
                    {
                        for(int z=0;z<3;z++)
                        {
                            if(this->getTrend()==0)
                            {
                                p->fillRect(rectListTemp->at(z),grad);
                            }
                            else
                            {
                                if(trend==this->getTrend())
                                    p->fillRect(rectListTemp->at(z),grad);
                                else
                                    p->fillRect(rectListTemp->at(z),QColor::fromHsvF(0,
                                                    0,0.97,double(this->getOpacity())/100));
                            }
                         }
                    }
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
                    if(this->getSingleYear()==true)
                    {
                        p->fillRect(rect,grad);
                    }
                    else
                    {
                        for(int z=0;z<3;z++)
                        {
                            if(this->getTrend()==0)
                            {
                                p->fillRect(rectListTemp->at(z),grad);
                            }
                            else
                            {
                                if(trend==this->getTrend())
                                    p->fillRect(rectListTemp->at(z),grad);
                                else
                                    p->fillRect(rectListTemp->at(z),QColor::fromHsvF(0,
                                                    0,0.97,double(this->getOpacity())/100));
                            }
                         }
                    }
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
                            if(this->getSingleYear()==true)
                            {
                                p->fillRect(rect,QColor::fromHsvF(0,
                                                          0,0.97,double(this->getOpacity())/100));
                            }
                            else
                            {
                                for(int z=0;z<3;z++)
                                {
                                    p->fillRect(rectListTemp->at(z),QColor::fromHsvF(0,
                                                    0,0.97,double(this->getOpacity())/100));
                                }
                            }
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
                            if(this->getSingleYear()==true)
                            {
                                p->fillRect(rect,QColor::fromHsvF(0,
                                                          0,0.97,double(this->getOpacity())/100));
                            }
                            else
                            {
                                for(int z=0;z<3;z++)
                                {
                                    p->fillRect(rectListTemp->at(z),QColor::fromHsvF(0,
                                                    0,0.97,double(this->getOpacity())/100));
                                }
                            }
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
                            if(this->getSingleYear()==true)
                            {
                                p->fillRect(rect,QColor::fromHsvF(0,
                                                          0,0.97,double(this->getOpacity())/100));
                            }
                            else
                            {
                                for(int z=0;z<3;z++)
                                {
                                    p->fillRect(rectListTemp->at(z),QColor::fromHsvF(0,
                                                    0,0.97,double(this->getOpacity())/100));
                                }
                            }
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
                            if(this->getSingleYear()==true)
                            {
                                p->fillRect(rect,QColor::fromHsvF(0,
                                                          0,0.97,double(this->getOpacity())/100));
                            }
                            else
                            {
                                for(int z=0;z<3;z++)
                                {
                                    p->fillRect(rectListTemp->at(z),QColor::fromHsvF(0,
                                                    0,0.97,double(this->getOpacity())/100));
                                }
                            }
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
        }
        y=y+value*length/total;
        length=length-value*length/total;
        pos=pos+number;
        if(drawSqTreeMap(x,y,width,length,pos,data,p,layer,j)!=NULL)
        {
            rectList->append(*drawSqTreeMap(x,y,width,length,pos,data,p,layer,j));
        }
        return rectList;
    }

}

void Widget::drawLineChart(qreal x, qreal y, qreal s,int j, QPainter *p)
{
    //p->setBrush(Qt::white);
    p->fillRect(QRectF(x,y,s,s),Qt::white);
    for(int i=0;i<this->getFileList()->at(0)->at(j)->healthData()->size();i++)
    {

            QPen pen;
            pen.setColor(this->dataColor0.at(i));
            if(this->getColorFilter()==true)
            {
                if(this->colorlegend->at(i)==false)
                {
                    pen.setColor(Qt::white);
                }
            }
            pen.setWidth(2);
            p->setPen(pen);
            QPointF a,b,c;
            if(this->getShowDifference()==false)
            {
                a=QPointF(x+0.1*s,y+0.9*s-this->getFileList()->at(0)->at(j)->healthData()->at(i)*0.9*s/20);
                b=QPointF(x+0.5*s,y+0.9*s-this->getFileList()->at(1)->at(j)->healthData()->at(i)*0.9*s/20);
                c=QPointF(x+0.9*s,y+0.9*s-this->getFileList()->at(2)->at(j)->healthData()->at(i)*0.9*s/20);

            }
            else
            {
                double max=-1;
                double min=100;
                for(int z=0;z<3;z++)
                {
                    if(max<this->getFileList()->at(z)->at(j)->healthData()->at(i))
                    {
                        max=this->getFileList()->at(z)->at(j)->healthData()->at(i);
                    }
                    if(min>this->getFileList()->at(z)->at(j)->healthData()->at(i))
                    {
                        min=this->getFileList()->at(z)->at(j)->healthData()->at(i);
                    }
                }

                if(max==min)
                {
                    a=QPointF(x+0.1*s,y+0.9*s);
                    b=QPointF(x+0.1*s,y+0.9*s);
                    c=QPointF(x+0.1*s,y+0.9*s);
                }
                else
                {
                    a=QPointF(x+0.1*s,y+0.9*s-(this->getFileList()->at(0)->at(j)->healthData()->at(i)-min)/(max-min)*0.8*s);
                    b=QPointF(x+0.5*s,y+0.9*s-(this->getFileList()->at(1)->at(j)->healthData()->at(i)-min)/(max-min)*0.8*s);
                    c=QPointF(x+0.9*s,y+0.9*s-(this->getFileList()->at(2)->at(j)->healthData()->at(i)-min)/(max-min)*0.8*s);
                }
            }
            pen.setWidth(3);
            p->setPen(pen);
            p->drawPoint(a);
            p->drawPoint(b);
            p->drawPoint(c);
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
            p->setPen(pen);
            p->drawLine(a,b);
            p->drawLine(b,c);


    }

}

void Widget::drawGlyphChart(qreal x, qreal y, qreal s, int j, QPainter *p)
{
    QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidth(1);
    p->setPen(pen);
    p->fillRect(QRectF(x,y,s,s),Qt::white);
    p->drawLine(QPointF(x,y+s/2),QPointF(x+s,y+s/2));
    for(int i=1;i<6;i++)
    {
        p->drawLine(QPointF(x+i*s/6,y),QPointF(x+i*s/6,y+s));
    }
    for(int i=0;i<6;i++)
    {
        QPen pen;
        pen.setColor(this->dataColor0.at(i));
        pen.setWidth(8);
        p->setPen(pen);
        p->drawLine(QPointF(x+i*s/6,y+this->getFileList()->at(0)->at(j)->healthData()->at(i)*s/2/15),
                    QPointF(x+(i+1)*s/6,y+this->getFileList()->at(0)->at(j)->healthData()->at(i+1)*s/2/15));
    }
    for(int i=7;i<13;i++)
    {
        QPen pen;
        pen.setColor(this->dataColor0.at(i));
        pen.setWidth(4);
        p->setPen(pen);
        p->drawLine(QPointF(x+(i-7)*s/6,y+s/2+this->getFileList()->at(0)->at(j)->healthData()->at(i)*s/2/15),
                    QPointF(x+(i-6)*s/6,y+s/2+this->getFileList()->at(0)->at(j)->healthData()->at(i+1)*s/2/15));
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
            if(fabs(data->at(i))<0.01)
            {

            }
            else
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
    timer2->stop();
    for(int i=0;i<this->getFileList()->at(0)->size();i++)
    {
        index2.replace(i,0);
    }
    this->setStep(false);
    if(this->getFinished()==true)
    {
        this->setLoopCount(1);
        this->setError(0);
        this->setLocalError(0);
        this->setYError(0);
        this->setLocalYError(0);
        this->getCurrentregion()->clear();
        this->getLastregion()->clear();
        this->getCurrentYregion()->clear();
        this->getLastYregion()->clear();

        this->regionListV()->clear();
        this->regionListH()->clear();
        this->getRegionListSave()->clear();
        this->getAreaGroup()->clear();
        regionFile* file=new regionFile();
        file->readfile(this->getDataYear());
        this->setRegionListV(file->regionList());
        this->setPopulation(file->populiation());
        this->setAreaGroup(file->AreaGroup());
        /*
        for(int i=0;i<this->regionListV()->size();i++)
        {
            for(int j=0;j<14;j++)
            {
                if(this->getDataCheck()->at(j)==1)
                {
                    this->regionListV()->at(i)->healthData()->replace(j,0.01);
                }
            }
        }
        */
        for(int i=0;i<this->regionListV()->size();i++)
        {
           this->regionListH()->append(this->regionListV()->at(i));
            Region * regionTemp=new Region();
            QList<double> * healthTemp= new QList<double>;
            for(int j=0;j<14;j++)
            {
                healthTemp->append(0);
                healthTemp->replace(j,
                                    this->regionListV()->at(i)->healthData()->at(j));
            }
            regionTemp->setHealthData(healthTemp);
           this->getRegionListSave()->append(regionTemp);
        }
        qSort(this->regionListH()->begin(),this->regionListH()->end(),
              horizontalOrder);
        qSort(this->regionListV()->begin(),this->regionListV()->end(),
                                     verticalOrder);
        qSort(this->getRegionListSave()->begin(),this->getRegionListSave()->end(),
              verticalOrder);
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
                this->regionListV()->at(i)->setError(0);
                this->regionListV()->at(i)->getCrossing()->clear();
                this->regionListV()->at(i)->setStopIncrease(false);
            }
            for(int i=0;i<this->searchRange();i++)
            {
                this->getCurrentregion()->append(this->regionListV()->at(i));
                this->getLastregion()->append(this->regionListV()->at(i));
                this->getCurrentYregion()->append(this->regionListV()->at(i));
                this->getLastYregion()->append(this->regionListV()->at(i));
            }
            qSort(this->getCurrentregion()->begin(),this->getCurrentregion()->end(),
                  XOrder);
            qSort(this->getLastregion()->begin(),this->getLastregion()->end(),
                  XOrder);
            qSort(this->getCurrentYregion()->begin(),this->getCurrentYregion()->end(),
                  YOrder);
            qSort(this->getLastYregion()->begin(),this->getLastYregion()->end(),
                  YOrder);
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
            qSort(this->getCurrentregionA()->begin(),this->getCurrentregionA()->end(),
                  XAOrder);
            qSort(this->getLastregionA()->begin(),this->getLastregionA()->end(),
                  XAOrder);
            qSort(this->getCurrentYregionA()->begin(),this->getCurrentYregionA()->end(),
                  YAOrder);
            qSort(this->getLastYregionA()->begin(),this->getLastYregionA()->end(),
                  YAOrder);
            this->setFinished(false);
            count=0;
            timer->start(20);
        }
    }
    else
    {
        timer->start(100);
    }
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    this->setIncreaseSize(value);
}

void Widget::on_horizontalSlider_2_valueChanged(int value)
{
    this->setRegionMaxsize(value);
    //on_start_pressed();
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
            p->fillRect(1680,440+i*40,70,40,dataColor0[i]);
            /*
            if(this->getGradient()==false)
            {
                QLinearGradient temp(1680,440+i*40,1750,480+40*i);
                //QRadialGradient temp(QPoint(1830,420+40*i),60);
                temp.setColorAt(0,
                                QColor::fromHsvF(dataColor0[i].hueF(),
                                                 1,0.6));
                temp.setColorAt(1,
                                QColor::fromHsvF(dataColor0[i].hueF(),
                                                 0.6,1));
                p->fillRect(1680,440+i*40,70,40,temp);
            }
            else
            {
                QRadialGradient temp(QPoint(1715,460+40*i),40);
                temp.setColorAt(0,
                                QColor::fromHsvF(dataColor0[i].hueF(),
                                                 0.3,1));
                temp.setColorAt(1,
                                QColor::fromHsvF(dataColor0[i].hueF(),
                                                 1,0.7));
                p->fillRect(1680,440+i*40,70,40,temp);

            }*/
        }
    }
    else
    {
        for(int i=0;i<3;i++)
        {
            p->fillRect(1680,440+i*40,140,40,QColor::fromHsvF(dataColor0.at(0).hueF(),
                                                              1,0.3+i*0.15));
        }
        for(int i=3;i<14;i++)
        {
            if(this->getGradient()==false)
            {
                QLinearGradient temp(1680,440+i*40,1750,480+40*i);
                //QRadialGradient temp(QPoint(1830,420+40*i),60);
                temp.setColorAt(0,
                                QColor::fromHsvF(dataColor0[i-2].hueF(),
                                                 1,0.6));
                temp.setColorAt(1,
                                QColor::fromHsvF(dataColor0[i-2].hueF(),
                                                 0.6,1));
                p->fillRect(1610,440+i*40,70,40,temp);
            }
            else
            {
                QRadialGradient temp(QPoint(1715,460+40*i),40);
                temp.setColorAt(0,
                                QColor::fromHsvF(dataColor0[i-2].hueF(),
                                                 0.3,1));
                temp.setColorAt(1,
                                QColor::fromHsvF(dataColor0[i-2].hueF(),
                                                 1,0.7));
                p->fillRect(1680,440+i*40,70,40,temp);

            }
        }
    }
    if(this->getFilter()==0)
    {

    }
    else
    {
        p->setPen(Qt::black);
        p->drawText(QRect(1640,420,120,20),"Focus");
        p->drawText(QRect(1750,420,120,20),"Context");
        for(int i=0;i<14;i++)
        {
            p->fillRect(1750,440+i*40,70,40,QColor::fromHsvF(0,
                                                              0,0.97));
        }
    }
    p->setPen(Qt::black);
    p->drawText(QRect(TEXTX,440,140,40),"Coronary-heart-disease");
    p->drawText(QRect(TEXTX,480,140,40),"Heart Failure");
    p->drawText(QRect(TEXTX,520,140,40),"Stroke");
    p->drawText(QRect(TEXTX,560,140,40),"Chronic-kidney-disease");
    p->drawText(QRect(TEXTX,600,140,40),"Diabetes");
    p->drawText(QRect(TEXTX,640,140,40),"Hypertension");
    p->drawText(QRect(TEXTX,680,140,40),"COPD");
    p->drawText(QRect(TEXTX,720,140,40),"Mental-Health");
    p->drawText(QRect(TEXTX,760,140,40),"Osteoporosis");
    p->drawText(QRect(TEXTX,800,140,40),"Rheumatoid-Arthritis");
    p->drawText(QRect(TEXTX,840,140,40),"Cancer");
    p->drawText(QRect(TEXTX,880,140,40),"Epilepsy");
    p->drawText(QRect(TEXTX,920,140,40),"Hypothyroidism");
    p->drawText(QRect(TEXTX,960,140,40),"Asthma");
    if(this->getColorFilter()==true)
    {
        for(int i=0;i<14;i++)
        {
            if(this->colorlegend->at(i)==true)
            {
                QPen pen(Qt::black);
                pen.setWidth(4);
                p->setPen(pen);
                p->drawRect(1680,440+40*i,70,40);
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

int Widget::errorCount(QList<Region *> *r1, QList<Region *> *r2)
{
    int error=0;
    for(int i=0;i<r1->size();i++)
    {
        if(r1->at(i)->ccgCode()==r2->at(i)->ccgCode())
        {}
        else
        {
            if(abs(r1->at(i)->X()-r2->at(i)->X())>1)
            {
                r1->at(i)->setError(r1->at(i)->getError()+1);
                r1->at(i)->addCrossingRegion(r2->at(i));
            //r2->at(i)->setError(r2->at(i)->getError()+1);
                error=error+1;
                if(abs(r1->at(i)->Y()-r2->at(i)->Y())<
                        this->getLocalPercentage()*
                        (SOUTHBOUND-NORTHBOUND)/100)
                {
                    this->setLocalError(this->getLocalError()+1);
                }
            }
        }
    }
    if(error==0)
    {
        cout<<error<<endl;
        return 0;
    }
    else
    {
        cout<<error<<endl;
        return error;
    }
}

int Widget::errorYCount(QList<Region *> *r1, QList<Region *> *r2)
{
    int error=0;
    for(int i=0;i<r1->size();i++)
    {
        if(r1->at(i)->ccgCode()==r2->at(i)->ccgCode())
        {}
        else
        {
            if(abs(r1->at(i)->Y()-r2->at(i)->Y())>1)
            {
                r1->at(i)->setError(r1->at(i)->getError()+1);
                r1->at(i)->addCrossingRegion(r2->at(i));
            //r2->at(i)->setError(r2->at(i)->getError()+1);
                error=error+1;
                if(abs(r1->at(i)->X()-r2->at(i)->X())<
                        this->getLocalPercentage()*
                        (SOUTHBOUND-NORTHBOUND)/100)
                {
                    this->setLocalYError(this->getLocalYError()+1);
                }
            }
        }
    }
    if(error==0)
    {
        cout<<error<<endl;
        return 0;
    }
    else
    {
        cout<<error<<endl;
        return error;
    }
}

int Widget::errorCountA(QList<AreaTeam *> *r1, QList<AreaTeam *> *r2)
{
    int error=0;
    for(int i=0;i<r1->size();i++)
    {
        if(r1->at(i)->AreaCode()==r2->at(i)->AreaCode())
        {}
        else
        {
            if(abs(r1->at(i)->X()-r2->at(i)->X())>1)
            {
                error=error+1;
            }
        }
    }
    this->setError(this->getError()+error);
}

int Widget::errorYCountA(QList<AreaTeam *> *r1, QList<AreaTeam *> *r2)
{
    int error=0;
    for(int i=0;i<r1->size();i++)
    {
        if(r1->at(i)->AreaCode()==r2->at(i)->AreaCode())
        {}
        else
        {
            if(abs(r1->at(i)->Y()-r2->at(i)->Y())>1)
            {
                error=error+1;
            }
        }
    }
    this->setYError(this->getYError()+error);
}
bool Widget::getRiverBoundary() const
{
    return m_riverBoundary;
}

void Widget::setRiverBoundary(bool riverBoundary)
{
    m_riverBoundary = riverBoundary;
}

QList<Region *> *Widget::getRegionListSave() const
{
    return m_regionListSave;
}

void Widget::setRegionListSave(QList<Region *> *regionListSave)
{
    m_regionListSave = regionListSave;
}

QList<int> *Widget::getDataCheck() const
{
    return m_dataCheck;
}

void Widget::setDataCheck(QList<int> *dataCheck)
{
    m_dataCheck = dataCheck;
}


bool Widget::getLineChart() const
{
    return m_LineChart;
}

void Widget::setLineChart(bool LineChart)
{
    m_LineChart = LineChart;
}

bool Widget::getShowDifference() const
{
    return m_showDifference;
}

void Widget::setShowDifference(bool showDifference)
{
    m_showDifference = showDifference;
}

int Widget::getGap() const
{
    return m_Gap;
}

void Widget::setGap(int Gap)
{
    m_Gap = Gap;
}

bool Widget::getSingleYear() const
{
    return m_singleYear;
}

void Widget::setSingleYear(bool singleYear)
{
    m_singleYear = singleYear;
}

bool Widget::getBottomStair() const
{
    return m_bottomStair;
}

void Widget::setBottomStair(bool bottomStair)
{
    m_bottomStair = bottomStair;
}

int Widget::getTrend() const
{
    return m_Trend;
}

void Widget::setTrend(int Trend)
{
    m_Trend = Trend;
}
QList<QList<Region *> *> *Widget::getFileList() const
{
    return m_FileList;
}

void Widget::setFileList(QList<QList<Region *> *> *FileList)
{
    m_FileList = FileList;
}



int Widget::getAspectRatio() const
{
    return m_aspectRatio;
}

void Widget::setAspectRatio(int aspectRatio)
{
    m_aspectRatio = aspectRatio;
}

int Widget::getDataYear() const
{
    return m_dataYear;
}

void Widget::setDataYear(int dataYear)
{
    m_dataYear = dataYear;
}
int Widget::getOpacity() const
{
    return m_Opacity;
}

void Widget::setOpacity(int Opacity)
{
    m_Opacity = Opacity;
}

bool Widget::getBColor() const
{
    return m_BColor;
}

void Widget::setBColor(bool BColor)
{
    m_BColor = BColor;
}

QList<AreaTeam *> *Widget::getCurrentYregionA() const
{
    return m_CurrentYregionA;
}

void Widget::setCurrentYregionA(QList<AreaTeam *> *CurrentYregionA)
{
    m_CurrentYregionA = CurrentYregionA;
}

QList<AreaTeam *> *Widget::getLastYregionA() const
{
    return m_LastYregionA;
}

void Widget::setLastYregionA(QList<AreaTeam *> *LastYregionA)
{
    m_LastYregionA = LastYregionA;
}

QList<AreaTeam *> *Widget::getCurrentregionA() const
{
    return m_CurrentregionA;
}

void Widget::setCurrentregionA(QList<AreaTeam *> *CurrentregionA)
{
    m_CurrentregionA = CurrentregionA;
}

QList<AreaTeam *> *Widget::getLastregionA() const
{
    return m_LastregionA;
}

void Widget::setLastregionA(QList<AreaTeam *> *LastregionA)
{
    m_LastregionA = LastregionA;
}


bool Widget::getYcross() const
{
    return m_Ycross;
}

void Widget::setYcross(bool Ycross)
{
    m_Ycross = Ycross;
}

bool Widget::getXcross() const
{
    return m_Xcross;
}

void Widget::setXcross(bool Xcross)
{
    m_Xcross = Xcross;
}

int Widget::getYError() const
{
    return m_YError;
}

void Widget::setYError(int YError)
{
    m_YError = YError;
}

int Widget::getLocalYError() const
{
    return m_LocalYError;
}

void Widget::setLocalYError(int LocalYError)
{
    m_LocalYError = LocalYError;
}

QList<Region *> *Widget::getCurrentYregion() const
{
    return m_CurrentYregion;
}

void Widget::setCurrentYregion(QList<Region *> *CurrentYregion)
{
    m_CurrentYregion = CurrentYregion;
}

QList<Region *> *Widget::getLastYregion() const
{
    return m_LastYregion;
}

void Widget::setLastYregion(QList<Region *> *LastYregion)
{
    m_LastYregion = LastYregion;
}

int Widget::getLocalError() const
{
    return m_LocalError;
}

void Widget::setLocalError(int LocalError)
{
    m_LocalError = LocalError;
}

int Widget::getLocalPercentage() const
{
    return m_LocalPercentage;
}

void Widget::setLocalPercentage(int LocalPercentage)
{
    m_LocalPercentage = LocalPercentage;
}

bool Widget::getStep() const
{
    return m_Step;
}

void Widget::setStep(bool Step)
{
    m_Step = Step;
}
bool Widget::getCenterPoints() const
{
    return m_CenterPoints;
}

void Widget::setCenterPoints(bool CenterPoints)
{
    m_CenterPoints = CenterPoints;
}

int Widget::getLoopCount() const
{
    return m_LoopCount;
}

void Widget::setLoopCount(int LoopCount)
{
    m_LoopCount = LoopCount;
}


QList<Region *> *Widget::getCurrentregion() const
{
    return m_Currentregion;
}

void Widget::setCurrentregion(QList<Region *> *Currentregion)
{
    m_Currentregion = Currentregion;
}

QList<Region *> *Widget::getLastregion() const
{
    return m_Lastregion;
}

void Widget::setLastregion(QList<Region *> *Lastregion)
{
    m_Lastregion = Lastregion;
}

int Widget::getError() const
{
    return m_Error;
}

void Widget::setError(int Error)
{
    m_Error = Error;
}

bool Widget::getCenterLines() const
{
    return m_CenterLines;
}

void Widget::setCenterLines(bool CenterLines)
{
    m_CenterLines = CenterLines;
}
bool Widget::getConer() const
{
    return m_Coner;
}

void Widget::setConer(bool Coner)
{
    m_Coner = Coner;
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

void Widget::on_checkBox_11_toggled(bool checked)
{
    if(checked==true)
    {
        this->setConer(true);
    }
    else
    {
        this->setConer(false);
    }
}

void Widget::on_checkBox_12_toggled(bool checked)
{
    if(checked==true)
    {
        this->setCenterLines(true);
    }
    else
    {
        this->setCenterLines(false);
    }
}

void Widget::on_checkBox_13_toggled(bool checked)
{
    if(checked==true)
    {
        this->setCenterPoints(true);
    }
    else
    {
        this->setCenterPoints(false);
    }
}

void Widget::on_start_2_pressed()
{
    this->setStep(true);
    if(this->getFinished()==true)
    {
        this->setLoopCount(1);
        this->setError(0);
        this->setLocalError(0);
        this->setYError(0);
        this->setLocalYError(0);
        this->getCurrentregion()->clear();
        this->getLastregion()->clear();
        this->getCurrentYregion()->clear();
        this->getLastYregion()->clear();
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
                this->regionListV()->at(i)->setError(0);
                this->regionListV()->at(i)->getCrossing()->clear();
                this->regionListV()->at(i)->setStopIncrease(false);
            }
            for(int i=0;i<this->searchRange();i++)
            {
                this->getCurrentregion()->append(this->regionListV()->at(i));
                this->getLastregion()->append(this->regionListV()->at(i));
                this->getCurrentYregion()->append(this->regionListV()->at(i));
                this->getLastYregion()->append(this->regionListV()->at(i));
            }
            qSort(this->getCurrentregion()->begin(),this->getCurrentregion()->end(),
                  XOrder);
            qSort(this->getLastregion()->begin(),this->getLastregion()->end(),
                  XOrder);
            qSort(this->getCurrentYregion()->begin(),this->getCurrentYregion()->end(),
                  YOrder);
            qSort(this->getLastYregion()->begin(),this->getLastYregion()->end(),
                  YOrder);
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
    else
    {
        timer->start(100);
    }
}

void Widget::on_horizontalSlider_5_valueChanged(int value)
{
    this->setLocalPercentage(value);
}

void Widget::on_start_3_clicked()
{
    sta->show();
}

void Widget::on_checkBox_14_toggled(bool checked)
{
    if(checked==true)
    {
        this->setXcross(true);
    }
    else
    {
        this->setXcross(false);
    }
}

void Widget::on_checkBox_15_toggled(bool checked)
{
    if(checked==true)
    {
        this->setYcross(true);
    }
    else
    {
        this->setYcross(false);
    }

}

void Widget::on_checkBox_16_toggled(bool checked)
{
    if(checked==true)
    {
        this->setBColor(true);
    }
    else
    {
        this->setBColor(false);
    }

}

void Widget::on_horizontalSlider_6_valueChanged(int value)
{
    this->setOpacity(100-value);
}

void Widget::on_comboBox_3_currentIndexChanged(int index)
{
    this->setDataYear(2011+index);
}

void Widget::on_horizontalSlider_7_valueChanged(int value)
{
    this->setAspectRatio(value);
    update();
}

void Widget::on_comboBox_4_currentIndexChanged(int index)
{
    this->setTrend(index);
}

void Widget::on_checkBox_17_toggled(bool checked)
{
    if(checked==true)
    {
        this->setBottomStair(true);
    }
    else
    {
        this->setBottomStair(false);
    }

}

void Widget::on_start_4_clicked()
{
    /*
    if(timer2->isActive()==true)
    {

       timer2->stop();
       update();
    }
    else
    {
        timer2->start(DELAY);
    }*/


        index3=0;
        //m_RiverPolygon->clear();
        timer3->start(DELAY);


}

void Widget::on_checkBox_35_toggled(bool checked)
{
    if(checked==true)
    {
        this->setSingleYear(true);
    }
    else
    {
        this->setSingleYear(false);
    }
}

void Widget::on_horizontalSlider_8_valueChanged(int value)
{
    this->setGap(value);
}

void Widget::on_checkBox_18_toggled(bool checked)
{
    if(checked==true)
    {
        this->setShowDifference(true);
    }
    else
    {
        this->setShowDifference(false);
    }
}

void Widget::on_checkBox_36_toggled(bool checked)
{
    if(checked==true)
    {
        this->setLineChart(true);
    }
    else
    {
        this->setLineChart(false);
    }
}


void Widget::on_checkBox_19_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(0,1);
    }
    else
    {
        this->getDataCheck()->replace(0,0);
    }
}

void Widget::on_checkBox_20_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(1,1);
    }
    else
    {
        this->getDataCheck()->replace(1,0);
    }

}

void Widget::on_checkBox_21_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(2,1);
    }
    else
    {
        this->getDataCheck()->replace(2,0);
    }
}

void Widget::on_checkBox_22_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(3,1);
    }
    else
    {
        this->getDataCheck()->replace(3,0);
    }
}

void Widget::on_checkBox_23_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(4,1);
    }
    else
    {
        this->getDataCheck()->replace(4,0);
    }
}

void Widget::on_checkBox_24_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(5,1);
    }
    else
    {
        this->getDataCheck()->replace(5,0);
    }
}

void Widget::on_checkBox_25_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(6,1);
    }
    else
    {
        this->getDataCheck()->replace(6,0);
    }
}

void Widget::on_checkBox_26_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(7,1);
    }
    else
    {
        this->getDataCheck()->replace(7,0);
    }
}

void Widget::on_checkBox_27_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(8,1);
    }
    else
    {
        this->getDataCheck()->replace(8,0);
    }
}

void Widget::on_checkBox_28_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(9,1);
    }
    else
    {
        this->getDataCheck()->replace(9,0);
    }
}

void Widget::on_checkBox_29_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(10,1);
    }
    else
    {
        this->getDataCheck()->replace(10,0);
    }
}

void Widget::on_checkBox_30_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(11,1);
    }
    else
    {
        this->getDataCheck()->replace(11,0);
    }
}

void Widget::on_checkBox_31_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(12,1);
    }
    else
    {
        this->getDataCheck()->replace(12,0);
    }
}

void Widget::on_checkBox_32_toggled(bool checked)
{
    if(checked==true)
    {
        this->getDataCheck()->replace(13,1);
    }
    else
    {
        this->getDataCheck()->replace(13,0);
    }
}

void Widget::on_start_5_pressed()
{
    for(int i=0;i<this->regionListV()->size();i++)
    {
        for(int j=0;j<14;j++)
        {
            if(this->getDataCheck()->at(j)==0)
            {
                this->regionListV()->at(i)->healthData()->replace(j,0.009);
            }

            else
            {
                this->regionListV()->at(i)->healthData()->replace(j,
                 this->getRegionListSave()->at(i)->healthData()->at(j));
            }
        }
    }
    update();
}

void Widget::on_checkBox_37_toggled(bool checked)
{
    if(checked==true)
    {
       this->setRiverBoundary(true);
    }
    else
    {
        this->setRiverBoundary(false);
    }
}
