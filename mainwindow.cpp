#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dbmanager.h"
#include "adddialog.h"

#include "rgb.h"
Rgba Red={ 1.0, 0.0, 0.0, 0.0};
Rgba Green={ 0.0, 1.0, 0.0, 0.0};
Rgba Blue={ 0.0, 0.0, 1.0, 0.0};
Rgba White={ 1.0, 1.0, 1.0, 0.0};
Rgba Black={ 0.0, 0.0, 0.0, 0.0};
Rgba DarkGrey={ 0.2, 0.2, 0.2, 0.0};
Rgba LigthGrey={ 0.8, 0.8, 0.8, 0.0};
Rgba Yellow={ 1.0, 1.0, 0.0, 0.0};
Rgba Pink={ 1.0, 0.0, 1.0, 0.0};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db=new DB_Manager(DBdir.absolutePath());

    UpdateData();

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MainButton_clicked()
{
    ui->Stack->setCurrentIndex(0);

}


void MainWindow::on_MonthButton_clicked()
{
    ui->Stack->setCurrentIndex(1);
}

void MainWindow::on_AddGasto_clicked()
{
    AddDialog* dialog = new AddDialog(this);

    dialog->show();

    connect(dialog,SIGNAL(gastoAccepted(QDialog*)),this,SLOT(addGasto(QDialog*)));
}

void MainWindow::addGasto(QDialog *dialog){

    double Valor=dialog->findChild<QDoubleSpinBox*>("Valor")->value();
    int ID= dialog->findChild<QComboBox*>("Pessoa")->currentData().toInt();
    QDate data1 = dialog->findChild<QDateEdit*>("Data")->date();
    int Area =dialog->findChild<QComboBox*>("Area")->currentData().toInt();
    QString Descricao =dialog->findChild<QPlainTextEdit*>("Descricao")->toPlainText();
    int E_Fatura = dialog->findChild<QLineEdit*>("E_Fatura")->text().toInt();



   db->addGasto(data1,Area,Valor,Descricao,ID,E_Fatura);


    dialog->hide();
    dialog->deleteLater();

    UpdateData();
}

void MainWindow::UpdateData(){

    ui->AnualGraph->Lines.clear();

    QDate data1;
    data1.setDate(2017,1,1);
    float rcv;
    QVector<QPoint> TotaisMensais;
    QPoint ponto;
    for(int i=1;i<13;i++){
        rcv=db->getTotalBy(0,0,data1,2);
        qDebug() << "recebido: " << rcv;
        ponto.setX(i);
        ponto.setY(rcv);
        TotaisMensais.append(ponto);
        data1=data1.addMonths(1);
        qDebug() << data1;
    }
    LinePoints *Linha=new LinePoints;
    Linha->Points=TotaisMensais;
    ui->AnualGraph->LineColor.append(&Green);
    ui->AnualGraph->DotsColor.append(&Black);
    ui->AnualGraph->Lines.append(Linha);


//    ui->MainCheese->SectionColor.clear();
    data1.setDate(2017,1,1);
    //
    float section;
    float total=db->getOrcamentoTotalByAno(data1);
    qDebug() << "total: "<<total;
    for(int i=1; i<6;i++){

        section=db->getOrcamentoByAreaByAno(i,data1);
        qDebug() << "section: " << section << "percent: " << section/total;
        ui->MainCheese->SectionValue.append(section/total);

    }

    ui->MainCheese->SectionColor.append(&Red);
    ui->MainCheese->SectionColor.append(&Green);
    ui->MainCheese->SectionColor.append(&Blue);
    ui->MainCheese->SectionColor.append(&Yellow);
    ui->MainCheese->SectionColor.append(&Pink);

     ui->SpentCheese->SectionValue.clear();
    total=db->getTotalBy(0,0,data1,1);
    qDebug() << "total: "<<total;
    for(int i=1; i<6;i++){

        section=db->getTotalBy(0,i,data1,1);
        qDebug() << "section: " << section << "percent: " << section/total;
        ui->SpentCheese->SectionValue.append(section/total);

    }

    ui->SpentCheese->SectionColor.append(&Red);
    ui->SpentCheese->SectionColor.append(&Green);
    ui->SpentCheese->SectionColor.append(&Blue);
    ui->SpentCheese->SectionColor.append(&Yellow);
    ui->SpentCheese->SectionColor.append(&Pink);
}
