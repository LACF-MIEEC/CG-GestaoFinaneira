#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QLineEdit>

class DB_Manager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    DB_Manager* db;

private slots:
    void on_MainButton_clicked();


    void on_MonthButton_clicked();

    void addGasto(QDialog* dialog);

    void on_AddGasto_clicked();

    void UpdateData();

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
