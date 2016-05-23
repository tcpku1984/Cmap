#include "TC_statistics.h"
#include "ui_TC_statistics.h"

TC_statistics::TC_statistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TC_statistics)
{
    ui->setupUi(this);
    this->setSize("0");
    this->setLocalError("0");
    this->setGlobelError("0");
    this->setLocalYError("0");
    this->setGlobelYError("0");
    this->setLocalErrorP("0");
    this->setGlobelErrorP("0");
    this->setLocalYErrorP("0");
    this->setGlobelYErrorP("0");
}

TC_statistics::~TC_statistics()
{
    delete ui;
}

void TC_statistics::paintEvent(QPaintEvent *event)
{
     QPainter * painter= new QPainter(this);
     painter->setPen(Qt::black);
     QFont font("Arial");
     font.setBold(true);
     font.setPixelSize(15);
     painter->setFont(font);
     painter->eraseRect(QRect(20,50,200,20));
     painter->drawText(QRect(20,50,200,20),"Original percentage : 18.5");
     painter->eraseRect(QRect(20,70,200,20));
     painter->drawText(QRect(20,70,200,20),"VErrorL :"
                       +this->getLocalError());
     painter->eraseRect(QRect(220,50,200,20));
     painter->drawText(QRect(220,50,200,20),"Percentage :"+this->getSize());
     painter->eraseRect(QRect(220,70,200,20));
     painter->drawText(QRect(220,70,200,20),"VErrorG :"+this->getGlobelError());
     painter->eraseRect(QRect(20,90,200,20));
     painter->drawText(QRect(20,90,200,20),"VErrorL :"
                       +this->getLocalErrorP());
     painter->eraseRect(QRect(220,90,200,20));
     painter->drawText(QRect(220,90,200,20),"VErrorG :"
                       +this->getGlobelErrorP());
     painter->eraseRect(QRect(20,110,200,20));
     painter->drawText(QRect(20,110,200,20),"HErrorL :"
                       +this->getLocalYError());
     painter->eraseRect(QRect(220,110,200,20));
     painter->drawText(QRect(220,110,200,20),"HErrorG :"
                       +this->getGlobelYError());
     painter->eraseRect(QRect(20,130,200,20));
     painter->drawText(QRect(20,130,200,20),"HErrorL :"
                       +this->getLocalYErrorP());
     painter->eraseRect(QRect(220,130,200,20));
     painter->drawText(QRect(220,130,200,20),"HErrorG :"
                       +this->getGlobelYErrorP());

}

QString TC_statistics::getSize() const
{
    return size;
}

void TC_statistics::setSize(const QString &value)
{
    size = value;
}

QString TC_statistics::getLocalError() const
{
    return localError;
}

void TC_statistics::setLocalError(const QString &value)
{
    localError = value;
}

QString TC_statistics::getGlobelError() const
{
    return globelError;
}

void TC_statistics::setGlobelError(const QString &value)
{
    globelError = value;
}

QString TC_statistics::getLocalYError() const
{
    return localYError;
}

void TC_statistics::setLocalYError(const QString &value)
{
    localYError = value;
}

QString TC_statistics::getGlobelYError() const
{
    return globelYError;
}

void TC_statistics::setGlobelYError(const QString &value)
{
    globelYError = value;
}

QString TC_statistics::getLocalErrorP() const
{
    return localErrorP;
}

void TC_statistics::setLocalErrorP(const QString &value)
{
    localErrorP = value;
}

QString TC_statistics::getGlobelErrorP() const
{
    return globelErrorP;
}

void TC_statistics::setGlobelErrorP(const QString &value)
{
    globelErrorP = value;
}

QString TC_statistics::getLocalYErrorP() const
{
    return localYErrorP;
}

void TC_statistics::setLocalYErrorP(const QString &value)
{
    localYErrorP = value;
}

QString TC_statistics::getGlobelYErrorP() const
{
    return globelYErrorP;
}

void TC_statistics::setGlobelYErrorP(const QString &value)
{
    globelYErrorP = value;
}
