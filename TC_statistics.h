/**
  *@file TC_statistics.h
  * @author Chao Tong
  * @date 10 June 2016
 * @brief The statistics class
 * This class is to create a new window
 * to show the statistics information of cartographic treemap.
 * It includes space filling percentage , local and global errors.
  */
#ifndef TC_STATISTICS_H
#define TC_STATISTICS_H

#include <QWidget>
#include <QPainter>
#include<QString>

namespace Ui {
class TC_statistics;
}

class TC_statistics : public QWidget
{
    Q_OBJECT

public:
    explicit TC_statistics(QWidget *parent = 0);
    ~TC_statistics();
    void paintEvent(QPaintEvent * event);

    QString getSize() const;
    void setSize(const QString &value);

    QString getLocalError() const;
    void setLocalError(const QString &value);

    QString getGlobelError() const;
    void setGlobelError(const QString &value);

    QString getLocalYError() const;
    void setLocalYError(const QString &value);

    QString getGlobelYError() const;
    void setGlobelYError(const QString &value);

    QString getLocalErrorP() const;
    void setLocalErrorP(const QString &value);

    QString getGlobelErrorP() const;
    void setGlobelErrorP(const QString &value);

    QString getLocalYErrorP() const;
    void setLocalYErrorP(const QString &value);

    QString getGlobelYErrorP() const;
    void setGlobelYErrorP(const QString &value);

    QString getGlobelTError() const;
    void setGlobelTError(const QString &value);

    QString getLocalTError() const;
    void setLocalTError(const QString &value);

private:
    Ui::TC_statistics *ui;
    QString size;
    QString localError;
    QString globelError;
    QString localYError;
    QString globelYError;
    QString localErrorP;
    QString globelErrorP;
    QString localYErrorP;
    QString globelYErrorP;
    QString globelTError;
    QString localTError;

};

#endif // TC_STATISTICS_H
