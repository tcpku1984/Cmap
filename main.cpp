#include "TC_widget.h"
#include <QApplication>
#include<QScrollArea>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget * w=new Widget;
    /*
    QWidget * top=0;
    QScrollArea * scroller=new QScrollArea;
    scroller->setWidget(w);
    top=scroller;
    top->show();
    top->raise();
*/
    w->show();
    return a.exec();
}
