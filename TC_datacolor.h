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

    QList<QColor> getColorTest() const;
    void setColorTest(const QList<QColor> &value);

    QList<QColor> getColorTest1() const;
    void setColorTest1(const QList<QColor> &value);

    QList<QColor> getColorTest2() const;
    void setColorTest2(const QList<QColor> &value);

    QList<QColor> getColorTest3() const;
    void setColorTest3(const QList<QColor> &value);

    QList<QColor> getDataColor5() const;
    void setDataColor5(const QList<QColor> &value);

    QList<QColor> getDataColor6() const;
    void setDataColor6(const QList<QColor> &value);

    QList<QColor> getDataColor7() const;
    void setDataColor7(const QList<QColor> &value);

private:
    QList<QColor> dataColor0;
    QList<QColor> dataColor1;
    QList<QColor> dataColor2;
    QList<QColor> dataColor3;
    QList<QColor> dataColor4;
    QList<QColor> dataColor5;
    QList<QColor> regionColor;
    QList<QColor> colorTest;
    QList<QColor> colorTest1;
    QList<QColor> colorTest2;
    QList<QColor> colorTest3;
    QList<QColor> dataColor6;
    QList<QColor> dataColor7;
};

#endif // DATACOLOR_H
