#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rgb.h"
Rgba Red={ 1.0, 0.0, 0.0, 0.0};
Rgba Green={ 0.0, 1.0, 0.0, 0.0};
Rgba Blue={ 0.0, 0.0, 1.0, 0.0};
Rgba White={ 1.0, 1.0, 1.0, 0.0};
Rgba Black={ 0.0, 0.0, 0.0, 0.0};
Rgba DarkGrey={ 0.2, 0.2, 0.2, 0.0};
Rgba LigthGrey={ 0.8, 0.8, 0.8, 0.0};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
