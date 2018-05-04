/**
  * @file datacolor.cpp
  * @author Chao Tong
  * @date 10 Feb 2016
  * @see datacolor.h
  */
#include "TC_datacolor.h"

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
    dataColor5<<QColor(104,175,252)<<QColor(38,85,130)<<QColor(84,175,121)
                 <<QColor(48,106,60)<<QColor(173,230,79)
                 <<QColor(255,146,72)<<QColor(229,173,130)
                 <<QColor(159,33,8)<<QColor(247,96,21)
                 <<QColor(42,243,133)<<QColor(142,0,73)
                 <<QColor(241,119,151)<<QColor(255,0,135)
                 <<QColor(233,215,55);
    colorTest<<QColor("#40655e")<<QColor("#38b094")<<QColor("#a4beb8")
            <<QColor("#90ea66")<<QColor("#799d10")
            <<QColor("#d1dd68")<<QColor("#a33e12")
            <<QColor("#e5836a")<<QColor("#f73931")
            <<QColor("#20f53d")<<QColor("#19a71f")
            <<QColor("#38b5fc")<<QColor("#957206")
            <<QColor("#fbbd13");
    colorTest1<<QColor("#72e5ef")<<QColor("#b75d4e")<<QColor("#466366")
            <<QColor("#b1bf81")<<QColor("#e5ad82")
            <<QColor("#add51f")<<QColor("#79eb99")
            <<QColor("#fe5360")<<QColor("#06a56c")
            <<QColor("#f2c029")<<QColor("#957206")
            <<QColor("#73f02e")<<QColor("#096013")
            <<QColor("#fe8f06");
    colorTest2<<QColor("#a0e3b7")<<QColor("#a33e12")<<QColor("#1cf1a3")
            <<QColor("#d30c45")<<QColor("#56a06c")
            <<QColor("#de886a")<<QColor("#294d46")
            <<QColor("#c0e15c")<<QColor("#5ac4f8")
            <<QColor("#e6c352")<<QColor("#73f02e")
            <<QColor("#dcd4c2")<<QColor("#8f937f")
            <<QColor("#f79302");
    colorTest3<<QColor("#40655e")<<QColor("#b3dfc1")<<QColor("#c08080")
            <<QColor("#56eead")<<QColor("#b12941")
            <<QColor("#84ee15")<<QColor("#6f3631")
            <<QColor("#bed134")<<QColor("#5ac4f8")
            <<QColor("#ce7e2b")<<QColor("#f8cca6")
            <<QColor("#069668")<<QColor("#ff7074")
            <<QColor("#3aa609");
    dataColor6<<QColor("#d73027")<<QColor("#f46d43")<<QColor("#fdae61")
            <<QColor("#fee08b")<<QColor("#ffffbf")
            <<QColor("#d9ef8b")<<QColor("#a6d96a")
            <<QColor("#66bd63")<<QColor("#1a9850");
    dataColor7<<QColor("#f7fcfd")<<QColor("#e5f5f9")<<QColor("#ccece6")
            <<QColor("#99d8c9")<<QColor("#66c2a4")
            <<QColor("#41ae76")<<QColor("#238b45")
            <<QColor("#006d2c")<<QColor("#00441b");



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
    case 5:
        return this->getColorTest();
    case 6:
        return this->getDataColor5();
     case 7:
        return this->getDataColor6();
    case 8:
        return this->getDataColor7();
        break;

    }
}
QList<QColor> dataColor::getColorTest() const
{
    return colorTest;
}

void dataColor::setColorTest(const QList<QColor> &value)
{
    colorTest = value;
}
QList<QColor> dataColor::getColorTest1() const
{
    return colorTest1;
}

void dataColor::setColorTest1(const QList<QColor> &value)
{
    colorTest1 = value;
}
QList<QColor> dataColor::getColorTest2() const
{
    return colorTest2;
}

void dataColor::setColorTest2(const QList<QColor> &value)
{
    colorTest2 = value;
}
QList<QColor> dataColor::getColorTest3() const
{
    return colorTest3;
}

void dataColor::setColorTest3(const QList<QColor> &value)
{
    colorTest3 = value;
}
QList<QColor> dataColor::getDataColor5() const
{
    return dataColor5;
}

void dataColor::setDataColor5(const QList<QColor> &value)
{
    dataColor5 = value;
}
QList<QColor> dataColor::getDataColor6() const
{
    return dataColor6;
}

void dataColor::setDataColor6(const QList<QColor> &value)
{
    dataColor6 = value;
}
QList<QColor> dataColor::getDataColor7() const
{
    return dataColor7;
}

void dataColor::setDataColor7(const QList<QColor> &value)
{
    dataColor7 = value;
}














