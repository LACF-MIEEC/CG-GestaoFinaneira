#include "invoice.h"

Invoice::Invoice(QDate date,float price,QString desc)
{
    Date=date;
    Price=price;
    Description=desc;
}
Invoice::~Invoice()
{

}

QDate Invoice::getDate(){
    return Date;
}
float Invoice::getPrice(){
    return Price;
}
QString Invoice::getDesc(){
    return Description;
}
