/**
  * @file datacolor.cpp
  * @author Chao Tong
  * @date 10 Feb 2016
  * @see datacolor.h
  */
#include "datacolor.h"

dataColor::dataColor()
{
    regionColor<<QColor("#2acae6")<<QColor("#deb274")<<QColor("#518adb")
             <<QColor("#c240d6")<<QColor("#2ecc16")
             <<QColor("#afef5a")<<QColor("#9163cd")
             <<QColor("#d26685")<<QColor("#72e6c5")
             <<QColor("#cf1f9d")<<QColor("#53d179")
             <<QColor("#e02e0e")<<QColor("#5c5ce6")
             <<QColor("#000");
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
    dataColor4<<QColor("#0000ff")<<QColor("#ffc0cb")<<QColor("#800080")
             <<QColor("#32cd32")<<QColor("#ff0000")
             <<QColor("#808080")<<QColor("#008080")
             <<QColor("#ffa500")<<QColor("#ee82ee")
             <<QColor("#40e0d0")<<QColor("#ff00ff")
             <<QColor("#90ee90")<<QColor("#ffff00")
             <<QColor("#000");

}
QList<QColor> dataColor::getDataColor0() const
{
    return dataColor0;
}

void dataColor::setDataColor0(const QList<QColor> &value)
{
    dataColor0 = value;
}
QList<QColor> dataColor::getDataColor1() const
{
    return dataColor1;
}

void dataColor::setDataColor1(const QList<QColor> &value)
{
    dataColor1 = value;
}
QList<QColor> dataColor::getDataColor2() const
{
    return dataColor2;
}

void dataColor::setDataColor2(const QList<QColor> &value)
{
    dataColor2 = value;
}
QList<QColor> dataColor::getDataColor3() const
{
    return dataColor3;
}

void dataColor::setDataColor3(const QList<QColor> &value)
{
    dataColor3 = value;
}
QList<QColor> dataColor::getDataColor4() const
{
    return dataColor4;
}

void dataColor::setDataColor4(const QList<QColor> &value)
{
    dataColor4 = value;
}


QList<QColor> dataColor::getRegionColor() const
{
    return regionColor;
}

void dataColor::setRegionColor(const QList<QColor> &value)
{
    regionColor = value;
}

QList<QColor> dataColor::getColor(int number)
{
    switch(number)
    {
    case 0:
        return this->getDataColor0();
        break;
    case 1:
        return this->getDataColor1();
        break;
    case 2:
        return this->getDataColor2();
        break;
    case 3:
       return this->getDataColor3();
       break;
    case 4:
        return this->getDataColor4();
        break;

    }
}







