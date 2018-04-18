#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

private slots:
    void on_buttonBox_accepted();

signals:

    void gastoAccepted(QDialog*);

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
