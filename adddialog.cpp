#include "adddialog.h"
#include "ui_adddialog.h"

#include "mainwindow.h"

#include "dbmanager.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);


    QVector<PESSOA*>*Pessoas;
    QVariant ID;

    MainWindow* MW=(MainWindow*)parent;
    Pessoas=MW->db->getPessoas();

    for(int i=0; i< Pessoas->size();i++)
        this->findChild<QComboBox*>("Pessoa")->addItem(Pessoas->at(i)->Nome,QVariant(Pessoas->at(i)->ID_Pessoa));


        this->findChild<QComboBox*>("Area")->addItem("Alimentação",QVariant(1));
        this->findChild<QComboBox*>("Area")->addItem("Lazer",QVariant(2));
        this->findChild<QComboBox*>("Area")->addItem("Vestuário",QVariant(3));
        this->findChild<QComboBox*>("Area")->addItem("Deslocações",QVariant(4));
        this->findChild<QComboBox*>("Area")->addItem("Outros",QVariant(5));


}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_buttonBox_accepted()
{
//    double valor=this->findChild<QDoubleSpinBox*>("Valor")->value();
//    int ID= this->findChild<QComboBox*>("Pessoa")->currentData().toInt();

   emit gastoAccepted(this);
}
