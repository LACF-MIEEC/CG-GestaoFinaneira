#include "mainwindow.h"
#include <QApplication>

#include "freeglut.h"

#include <QDebug>
#include <QDir>
#include <QSurfaceFormat>


#include <dbmanager.h>

QDir DBdir("test.db");
static const QString path = "example.db";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    glutInit(&argc, argv);

    //    QSurfaceFormat format;
    //    format.setDepthBufferSize(24);
    //    format.setStencilBufferSize(10);
    //    format.setVersion(3, 7);
    //    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    //    QSurfaceFormat::setDefaultFormat(format);


    MainWindow w;
    DB_Manager db(DBdir.absolutePath());
    if (db.isOpen())
    {
        //---------------------------------------------------------------
        //CREATE TABLES
        //---------------------------------------------------------------

        //db.createTables();


        //---------------------------------------------------------------
        //ADD'S
        //---------------------------------------------------------------

        int Area =3;
        int Ano = 2019;
        float Valor=150.6;
        int ID_Pessoa =1;
        int ID_Gasto = 1;
        int E_Fatura = 123;
        int flag=0;
        QString Pessoa="Pedro";
        QString Grau = "Pai";
        QString Data_String;

        Data_String = "2019-05-08";
        QDate data1(QDate::fromString(Data_String,Qt::ISODate));

        //db.addPessoa(Pessoa,Grau);

        //db.addOrcamento(Area,Valor,data1);

        //db.addGasto(data1,Area,Valor,"Manteiga",ID_Pessoa,E_Fatura);

        //---------------------------------------------------------------
        //GET GASTOS
        //---------------------------------------------------------------


        //função que retorna gastos totais (somatório) por anos,mês ou dia por pesseoa ou por area (todas se podem conjugar)
        //flag-> 0 - não procura por data, 1- procura por ano, 2-procura por mês, 3- procura por dia (sendo que a data pode ser
        //sempre a mesma mas consoante a flag considera ou não o ano, mês ou dia.

        //ID_Pessoa=0;
        //Area =0;
        //flag = 0;
        //qDebug() << db.getTotalBy(ID_Pessoa,Area,data1,flag);




        //funciona da mesma forma que a anterior, mas em vez de retornar os totais retorna tabelas
        /* QVector<GASTO*>* rcv;
                rcv=db.getBy(ID_Pessoa,Area,data1,flag);

                for (int i=0;i<rcv->size();i++){
                    qDebug() << "ID_Gasto: " << rcv->at(i)->ID_Gasto
                             << "   Valor: " << rcv->at(i)->Valor
                             << "   Area: " << rcv->at(i)->Area
                             << "   Pessoa: " << rcv->at(i)->ID_Pessoa
                             << "   Descrição: " << rcv->at(i)->Descricao
                             << "   Data: " << rcv->at(i)->Data_Gasto
                             <<"    E_Fatura: "<< rcv->at(i)->E_Fatura;
                    qDebug();
                }
                */

        //rcv=db.getGastosBetweenData(data1,data2);

        //rcv=db.getGastosByAreaBetweenData(1,data1,data2);


        //---------------------------------------------------------------
        //GET PESSOAS
        //---------------------------------------------------------------
        /*
            QVector<PESSOA*>* rcv1;
            rcv1=db.getPessoas();

            for (int i=0;i<rcv1->size();i++){
                qDebug() << "ID_Pessoa: " << rcv1->at(i)->ID_Pessoa
                         << "   Nome: " << rcv1->at(i)->Nome
                         << "   Grau: " << rcv1->at(i)->Grau;
                qDebug();
            }
            */


        //---------------------------------------------------------------
        //GET ORCAMENTOS
        //---------------------------------------------------------------

        /*
            QVector<ORCAMENTO*>* rcv2;
            rcv2=db.getOrcamentos();

            for (int i=0;i<rcv2->size();i++){
                qDebug() << "Ano: " << rcv2->at(i)->Ano
                         << "   Area: " << rcv2->at(i)->Area
                         << "   Valor: " << rcv2->at(i)->Valor;
                qDebug();
            }
            */

        //---------------------------------------------------------------
        //UPDATE'S
        //---------------------------------------------------------------


        //db.updateGasto(ID_Gasto,data1,Area,Valor,"Almoço de ressada da PDA",ID_Pessoa,E_Fatura);

        //db.updateOrcamento(Area,800,data1);


        //---------------------------------------------------------------
        //DELETE'S
        //---------------------------------------------------------------


        //db.deletePessoa(4);

        //db.deleteGasto(2);

        //db.deleteOrcamento(data1,Area);



        //---------------------------------------------------------------
        //OUTROS
        //---------------------------------------------------------------

        //db.removeAll();
        //db.clearAll();

        qDebug() << "End";
    }
    else
    {
        qDebug() << "Database is not open!";
    }
    w.show();
    return a.exec();
}
