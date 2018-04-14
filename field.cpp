#include "field.h"

Field::Field()
{

}
Field::~Field()
{

}


double Field::getAnualBudget(){
    return AnualBudget;

}
QList<Invoice> Field::getInvoiceByID(unsigned int ID){
    return InvoiceList;
}
QList<Invoice> Field::getInvoiceByDay(QDate Date){
    return InvoiceList;
}
QList<Invoice> Field::getInvoiceByMonth(QDate Date){
    return InvoiceList;
}
QList<Invoice> Field::getInvoiceByYear(QDate Date){
    return InvoiceList;
}
