/**
  *@file datacolor.h
  * @author Chao Tong
  * @date 10 Jan 2016
 * @brief dataColor class
 * This class includes kinds of color representing health care data
  */
#ifndef DATACOLOR_H
#define DATACOLOR_H


#include<QColor>
#include<QList>


class dataColor
{
public:
    dataColor();
    QList<QColor> getDataColor0() const;
    void setDataColor0(const QList<QColor> &value);

    QList<QColor> getDataColor1() const;
    void setDataColor1(const QList<QColor> &value);

    QList<QColor> getDataColor2() const;
    void setDataColor2(const QList<QColor> &value);

    QList<QColor> getDataColor3() const;
    void setDataColor3(const QList<QColor> &value);

    QList<QColor> getDataColor4() const;
    void setDataColor4(const QList<QColor> &value);

    QList<QColor> getRegionColor() const;

    void setRegionColor(const QList<QColor> &value);

    QList<QColor> getColor(int number);

private:
    QList<QColor> dataColor0;
    QList<QColor> dataColor1;
    QList<QColor> dataColor2;
    QList<QColor> dataColor3;
    QList<QColor> dataColor4;
    QList<QColor> regionColor;
};

#endif // DATACOLOR_H
