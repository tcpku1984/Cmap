#ifndef REGION_H
#define REGION_H
#include <QString>
#include <QList>

class Region
{
public:
    Region();
    ~Region();
    /**
     * accessing method for class member
     */


    float Lati() const;
    void setLati(float Lati);

    float Longti() const;
    void setLongti(float Longti);

    int poplation() const;
    void setPoplation(int poplation);

    int Y() const;
    void setY(int Y);

    bool stopIncrease() const;
    void setStopIncrease(bool stopIncrease);



    QString ccgCode() const;
    void setCcgCode(const QString &ccgCode);

    QString ccgName() const;
    void setCcgName(const QString &ccgName);

    int X() const;
    void setX(int X);

    int getSize() const;
    void setSize(int value);
    void increase();
    void stop();
    void moveNorth();
    void moveSouth();
    void moveWest();
    void moveEast();

    int color() const;
    void setColor(int color);

    bool detail() const;
    void setDetail(bool detail);

    QList<float> *healthData() const;
    void setHealthData(QList<float> *healthData);

private:
    /**
     * @brief m_ccgCode information of ccg code
     */
    QString m_ccgCode;
    QString m_ccgName;
    /**
     * @brief m_Lati information of latitude
     */

    float m_Lati;
    /**
     * @brief m_Longti information of longtitude
     */
    float m_Longti;
    /**
     * @brief m_poplation information of population
     */
    int m_poplation;
    /**
     * @brief m_X information of x position on map
     */

    QList <float> * m_healthData= new QList<float>;







    int m_X;
    /**
     * @brief m_Oy information of horizontal order
     */
    int m_Y;
    /**
     * @brief m_stopIncrease information of whether point
     * can do increment or not
     */
    bool m_stopIncrease=false;
    int size=1;
    int m_color=0;
    bool m_detail=false;
};

#endif // Region_H
