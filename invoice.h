#ifndef INVOICE_H
#define INVOICE_H

#include "QString"
#include "QDate"

class Invoice
{
public:
    explicit Invoice(QDate date,float price,QString desc);
    ~Invoice();

    QDate getDate();
    float getPrice();
    QString getDesc();

private:
    QDate Date;
    float Price;
    QString Description;
    unsigned int IDNumber;
};

#endif // INVOICE_H
