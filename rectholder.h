/**
  *@file areateam.h
  * @author Chao Tong
  * @date 10 Jan 2016
 * @brief The rectHolder class
 * This class is a alternative class for defalut rectF class in QT
 * This class just record four parameter of rectF class
 * X position, Y position , W width and L length
  */
#ifndef RECTHOLDER_H
#define RECTHOLDER_H
#include<QtGlobal>

class rectHolder
{
public:
    rectHolder();
    rectHolder(qreal x,qreal y,qreal w,qreal l);

    qreal X() const;
    void setX(const qreal &X);

    qreal Y() const;
    void setY(const qreal &Y);

    qreal W() const;
    void setW(const qreal &W);

    qreal L() const;
    void setL(const qreal &L);

private:
    qreal m_X;
    qreal m_Y;
    qreal m_W;
    qreal m_L;

};

#endif // RECTHOLDER_H
