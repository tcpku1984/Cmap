#include "rectholder.h"

rectHolder::rectHolder()
{

}

rectHolder::rectHolder(qreal x, qreal y, qreal w, qreal l)
{
    this->setX(x);
    this->setY(y);
    this->setW(w);
    this->setL(l);
}

qreal rectHolder::X() const
{
    return m_X;
}

void rectHolder::setX(const qreal &X)
{
    m_X = X;
}

qreal rectHolder::Y() const
{
    return m_Y;
}

void rectHolder::setY(const qreal &Y)
{
    m_Y = Y;
}

qreal rectHolder::W() const
{
    return m_W;
}

void rectHolder::setW(const qreal &W)
{
    m_W = W;
}

qreal rectHolder::L() const
{
    return m_L;
}

void rectHolder::setL(const qreal &L)
{
    m_L = L;
}

