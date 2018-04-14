#ifndef FIELD_H
#define FIELD_H

#include "invoice.h"

class Field
{
public:
    Field();
    ~Field();

    double getAnualBudget();
    QList<Invoice> getInvoiceByID(unsigned int ID);
    QList<Invoice> getInvoiceByDay(QDate Date);
    QList<Invoice> getInvoiceByMonth(QDate Date);
    QList<Invoice> getInvoiceByYear(QDate Date);

private:
    double AnualBudget;
    QList<Invoice> InvoiceList;
};

#endif // FIELD_H
