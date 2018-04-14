#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <QDir>

#include <dbmanager.h>

QDir DBdir("test.db");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    DBManager db(DBdir.absolutePath());

    if (db.isOpen())
    {

        db.createTable();   // Creates a table if it doens't exist. Otherwise, it will use existing table.
        db.addPerson("A");

        db.printAllPersons();
    }
    //w.show();
    return a.exec();
}
