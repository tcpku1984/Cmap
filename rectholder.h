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
