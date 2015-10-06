#include "widget.h"
#include "ui_widget.h"


enum{
    RATHH=400,
    RATHV=600,
    HH=-200,
    VV=1000,
    MAXSIZE=65,
    HALF=2,
    TEXT=10,
    TEXTL=150,
    TEXTW=80,
    RECTSIZE=500,
    FONTSIZEA=15,
    FONTSIZEB=14
};

bool verticalOrder(Region * r1, Region * r2)
{
    return r1->Longti()>r2->Longti();
}

bool horizontalOrder(Region * r1, Region * r2)
{
    return r1->Lati()<r2->Lati();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    m_regionListV= new QList<Region *>;
    m_regionListH= new QList<Region *>;
    index=0;
    m_increaseSize=1;
    m_regionMaxsize=10;
    m_searchRange=212;
    m_population=0;
    finished=false;
    m_samesize=false;
    m_algorithm=false;
    m_lookAhead=false;
    m_otherColor=false;
    m_Windowsnumber=0;
    m_AreaGroup=new QList<AreaTeam *>;
    this->setGroup(false);



    ui->setupUi(this);
    fileRead();
    cout<<"ccg size:"<<this->regionListH()->size()<<endl;
    cout<<"area number :"<<this->getAreaGroup()->size()<<endl;
    for(int i=0; i<this->getAreaGroup()->size();i++)
    {
        this->getAreaGroup()->at(i)->initi();
        /*
        cout<<"area Code : "<<this->getAreaGroup()->at(i)->AreaCode().toStdString()<<endl;
        cout<<"ccg number :"<<this->getAreaGroup()->at(i)->RegionList()->size()<<endl;
        for(int j=0;j<this->getAreaGroup()->at(i)->RegionList()->size();j++)
        {
            cout<<"ccg code :"<<this->getAreaGroup()->at(i)->RegionList()->at(j)->ccgCode().toStdString()<<endl;
        }*/
    }
    qSort(this->regionListH()->begin(),this->regionListH()->end(),
          horizontalOrder);
    qSort(this->regionListV()->begin(),this->regionListV()->end(),
          verticalOrder);
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
    if(this->getOtherColor()==false)
    {
        this->dataColor=this->dataColor2;
    }
    else
    {
        this->dataColor=this->dataColor1;
    }
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
    QFont font("font:Arial");
    font.setPixelSize(FONTSIZEA);
    painter->setFont(font);

    int z=this->regionListV()->size()/HALF;
    painter->setPen(Qt::green);
    painter->drawLine(QPoint(300,this->regionListV()->at(z)->Y()),
                     QPoint(1720,this->regionListV()->at(z)->Y()));
    painter->drawLine(QPoint(this->regionListH()->at(z)->X(),0),
                     QPoint(this->regionListH()->at(z)->X(),1920));
    painter->setPen(Qt::black);
    for(int i=0;i<this->regionListV()->size();i++)
    {
        if(this->regionListV()->at(i)->color()==1)
        {
            painter->setBrush(Qt::red);
        }
        else if(this->regionListV()->at(i)->color()==2)
        {
            painter->setBrush(Qt::green);
        }
        else
        {
            painter->setBrush(Qt::blue);
        }


        painter->drawRect(
                    QRectF(this->regionListV()->at(i)->X(),
                           this->regionListV()->at(i)->Y(),
                           this->regionListV()->at(i)->getSize(),
                           this->regionListV()->at(i)->getSize()));
    }

    if(this->getFinished())
    {
        if(this->getLookAhead()==false)
        {
            for(int i=0;i<this->regionListV()->size();i++)
            {

                drawSqTreeMap(this->regionListV()->at(i)->X(),
                            this->regionListV()->at(i)->Y(),
                            this->regionListV()->at(i)->getSize(),
                            this->regionListV()->at(i)->getSize(),0,
                            this->regionListV()->at(i)->healthData(),
                            painter);
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
        drawSign(painter);
    }
}

void Widget::paintArea(QPainter *painter)
{
    for(int i=0;i<this->getAreaGroup()->size();i++)
    {
        painter->drawRect(
                    QRectF(this->getAreaGroup()->at(i)->X(),
                           this->getAreaGroup()->at(i)->Y(),
                           this->getAreaGroup()->at(i)->Size(),
                           this->getAreaGroup()->at(i)->Size()));
    }
    if(this->getFinished()==true)
    {
        for(int i=0;i<this->getAreaGroup()->size();i++)
        {
            cout<<"draw Treemap: "<<i<<endl;
            drawSqTreeMap(this->getAreaGroup()->at(i)->X(),
                          this->getAreaGroup()->at(i)->Y(),
                          this->getAreaGroup()->at(i)->Size(),
                          this->getAreaGroup()->at(i)->Size(),0,
                          this->getAreaGroup()->at(i)->PopulationList(),
                          painter);
        }
        drawSign(painter);
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
    //cout<<e->pos().x()<<" : "<<e->pos().y()<<endl;
    //egion * temp;
    int x=e->pos().x();
    int y=e->pos().y();
    this->setPressed(true);
    for(int i=0;i<this->regionListV()->size();i++)
    {
      if(this->regionListV()->at(i)->X()<x&&
         this->regionListV()->at(i)->X()+this->regionListV()->at(i)->getSize()>x&&
         this->regionListV()->at(i)->Y()<y&&
         this->regionListV()->at(i)->Y()+this->regionListV()->at(i)->getSize()>y)
      {

          treeMap * t=new treeMap(0,this->getLookAhead(),this->getOtherColor(),this->regionListV()->at(i));
          t->setGeometry(10+510*this->Windowsnumber(),30,500,600);
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

          break;
      }
    }
    update();

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
          break;
      }
    }
    update();


}

/*void Widget::drawTreeMap(qreal x, qreal y, qreal width, qreal length, QList<float> *data, QPainter *p)
{

   qreal total=0;
   for(int i=0;i<data->size();i++)
   {
       total+=data->at(i);
   }
   for(int i=0;i<data->size();i++)
   {
       if(length>=width)
       {
           qreal temp=length*data->at(i)/total;

           QRectF rect=QRectF(x,y,width,temp);
           p->fillRect(rect,dataColor.at(i));

           if(data->at(i)>1)
           {
               p->fillRect(rect,Qt::BDiagPattern);
           }
           y=y+temp;
           length=length-temp;
           total=total-data->at(i);
       }
       else
       {
           qreal temp=width*data->at(i)/total;
           QRectF rect=QRectF(x,y,temp,length);
           p->fillRect(rect,dataColor.at(i));
           x=x+temp;
           width=width-temp;
           total=total-data->at(i);
       }
   }
}
*/


void Widget::drawSqTreeMap(qreal x, qreal y, qreal width, qreal length, int pos, QList<float> *data, QPainter *p)
{
   // cout<<" draw sq treemap called"<<endl;
    if(pos>=data->size())
    {
        return;
    }
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
            //p->fillRect(rect,dataColor.at(i));
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
            tempy=tempy+data->at(i)*length/value;
        }
        x=x+value*width/total;
        width=width-value*width/total;
        pos=pos+number;
        drawSqTreeMap(x,y,width,length,pos,data,p);
    }*/

}

qreal Widget::calRatio(qreal w, qreal l, int pos, int number, QList<float> *data)
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

void Widget::drawSqTreeMap2(qreal x, qreal y, qreal width, qreal length, int pos, QList<float> *data, QPainter *p)
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
            value+=data->at(i);
        }
        for(int i=pos;i<pos+number;i++)
        {
            QRectF rect=QRectF(tempx,y,data->at(i)*width/value,value*length/total);
            p->fillRect(rect,dataColor.at(i));
            tempx=tempx+data->at(i)*width/value;
        }
        y=y+value*length/total;
        length=length-value*length/total;
        pos=pos+number;
        drawSqTreeMap2(x,y,width,length,pos,data,p);
    }
}

qreal Widget::calRatio2(qreal w, qreal l, int pos, int number, QList<float> *data)
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
        timer->start(100);
    }
}


void Widget::fileRead()
{
    ifstream inFlow;
    inFlow.open("D:/Cmap/centerp3.csv");
    string input;
    int i = 0;

    if (!inFlow)
    {
        cout << "widegt::fileRead() inFlow ERRor"<<endl;
    }
    else
    {
    cout << "\n Reading" <<endl;


    /**
      using while to read each line of csv file
     */
    while (!inFlow.eof())
    {
        //cout<<i<<"region"<<endl;
        QList<float> *tempList=new QList<float>;
        Region * temp=new Region();
        AreaTeam * areaTemp;
        getline(inFlow,input, ',');
        temp->setCcgCode(QString::fromStdString(input));
        getline(inFlow,input, ',');
        temp->setCcgName(QString::fromStdString(input));
        getline(inFlow,input, ',');
        temp->setLati(atof(input.c_str()));
        getline(inFlow,input, ',');
        temp->setLongti(atof(input.c_str()));
        for(int j=0;j<14;j++)
        {
            getline(inFlow,input, ',');
            float b=atof(input.c_str());
            tempList->append(b);
        }
        temp->setHealthData(tempList);
        getline(inFlow,input, ',');
        QString areaCode=QString::fromStdString(input);
        int index=this->searchAreaCode(areaCode);
        if(index<0)
        {
            areaTemp=new AreaTeam();
            areaTemp->setAreaCode(areaCode);
            getline(inFlow,input, ',');
            areaTemp->setAreaName(QString::fromStdString(input));
            this->getAreaGroup()->append(areaTemp);
        }
        else
        {
            areaTemp=this->getAreaGroup()->at(index);
            getline(inFlow,input, ',');
        }

        int a;
        inFlow>>a;
        addPopulation(a);
        temp->setPoplation(a);
        temp->setX(temp->Lati()/RATHH+HH);
        temp->setY(-temp->Longti()/RATHV+VV);
        this->regionListH()->append(temp);
        this->regionListV()->append(temp);
        areaTemp->addRegion(temp);
        i++;

    }
    inFlow.close();
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
    QFont font("font:Arial");
    font.setPixelSize(FONTSIZEB);
    p->setFont(font);
    p->setPen(Qt::white);

    p->fillRect(QRect(1780,400,100,40),dataColor[0]);
    p->drawText(QRect(1780,400,100,40),"Coronary-heart-disease");
    p->fillRect(QRect(1780,440,100,40),dataColor[1]);
    p->drawText(QRect(1780,440,100,40),"Chronic-kidney-disease");
    p->fillRect(QRect(1780,480,100,40),dataColor[2]);
    p->drawText(QRect(1780,480,100,40),"diabetes");
    p->fillRect(QRect(1780,520,100,40),dataColor[3]);
    p->drawText(QRect(1780,520,100,40),"Heart Failure");
    p->fillRect(QRect(1780,560,100,40),dataColor[4]);
    p->drawText(QRect(1780,560,100,40),"Stroke");
    p->fillRect(QRect(1780,600,100,40),dataColor[5]);
    p->drawText(QRect(1780,600,100,40),"Hypertension");
    p->fillRect(QRect(1780,640,100,40),dataColor[6]);
    p->drawText(QRect(1780,640,100,40),"COPD");
    p->fillRect(QRect(1780,680,100,40),dataColor[7]);
    p->drawText(QRect(1780,680,100,40),"Mental-Health");
    p->fillRect(QRect(1780,720,100,40),dataColor[8]);
    p->drawText(QRect(1780,720,100,40),"Osteoporosis");
    p->fillRect(QRect(1780,760,100,40),dataColor[9]);
    p->drawText(QRect(1780,760,100,40),"Rheumatoid-Arthritis");
    p->fillRect(QRect(1780,800,100,40),dataColor[10]);
    p->drawText(QRect(1780,800,100,40),"Cancer");
    p->fillRect(QRect(1780,840,100,40),dataColor[11]);
    p->drawText(QRect(1780,840,100,40),"Epilepsy");
    p->fillRect(QRect(1780,880,100,40),dataColor[12]);
    p->drawText(QRect(1780,880,100,40),"Hypothyroidism");
    p->fillRect(QRect(1780,920,100,40),dataColor[13]);
    p->drawText(QRect(1780,920,100,40),"Palliative");
    font.setPixelSize(FONTSIZEA);
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
        int maxY=minY+this->regionListV()->at(i)->getSize();
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

int Widget::searchAreaCode(QString code)
{
    for(int i=0;i<this->getAreaGroup()->size();i++)
    {
        if(this->getAreaGroup()->at(i)->AreaCode()==code)
        {
            return i;
        }
    }
    return -1;
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

bool Widget::getOtherColor() const
{
    return m_otherColor;
}

void Widget::setOtherColor(bool otherColor)
{
    m_otherColor = otherColor;
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
QList<QColor> Widget::getDataColor1() const
{
    return dataColor1;
}

void Widget::setDataColor1(const QList<QColor> &value)
{
    dataColor1 = value;
}

QList<QColor> Widget::getDataColor2() const
{
    return dataColor2;
}

void Widget::setDataColor2(const QList<QColor> &value)
{
    dataColor2 = value;
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
    }
    else
    {
        this->setSamesize(false);
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

void Widget::on_checkBox_4_toggled(bool checked)
{
    if(checked==true)
    {
        this->setOtherColor(true);
    }
    else
    {
        this->setOtherColor(false);
    }
}

void Widget::on_checkBox_5_toggled(bool checked)
{
    if(checked==true)
    {
        this->setGroup(true);
    }
    else
    {
        this->setGroup(false);
    }

}
