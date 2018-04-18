/********************************************************************************
** Form generated from reading UI file 'adddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDIALOG_H
#define UI_ADDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_AddDialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *Pessoa;
    QLabel *label_2;
    QDoubleSpinBox *Valor;
    QLabel *label_3;
    QComboBox *Area;
    QLineEdit *E_Fatura;
    QLabel *label_5;
    QPlainTextEdit *Descricao;
    QLabel *label_6;
    QLabel *label_4;
    QDateEdit *Data;

    void setupUi(QDialog *AddDialog)
    {
        if (AddDialog->objectName().isEmpty())
            AddDialog->setObjectName(QStringLiteral("AddDialog"));
        AddDialog->setWindowModality(Qt::ApplicationModal);
        AddDialog->resize(400, 300);
        gridLayout = new QGridLayout(AddDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonBox = new QDialogButtonBox(AddDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(AddDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        Pessoa = new QComboBox(AddDialog);
        Pessoa->setObjectName(QStringLiteral("Pessoa"));

        formLayout->setWidget(1, QFormLayout::FieldRole, Pessoa);

        label_2 = new QLabel(AddDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        Valor = new QDoubleSpinBox(AddDialog);
        Valor->setObjectName(QStringLiteral("Valor"));
        Valor->setMaximum(1e+6);

        formLayout->setWidget(2, QFormLayout::FieldRole, Valor);

        label_3 = new QLabel(AddDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        Area = new QComboBox(AddDialog);
        Area->setObjectName(QStringLiteral("Area"));

        formLayout->setWidget(3, QFormLayout::FieldRole, Area);

        E_Fatura = new QLineEdit(AddDialog);
        E_Fatura->setObjectName(QStringLiteral("E_Fatura"));

        formLayout->setWidget(5, QFormLayout::FieldRole, E_Fatura);

        label_5 = new QLabel(AddDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_5);

        Descricao = new QPlainTextEdit(AddDialog);
        Descricao->setObjectName(QStringLiteral("Descricao"));

        formLayout->setWidget(6, QFormLayout::FieldRole, Descricao);

        label_6 = new QLabel(AddDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        label_4 = new QLabel(AddDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        Data = new QDateEdit(AddDialog);
        Data->setObjectName(QStringLiteral("Data"));
        Data->setCalendarPopup(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, Data);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);


        retranslateUi(AddDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddDialog);
    } // setupUi

    void retranslateUi(QDialog *AddDialog)
    {
        AddDialog->setWindowTitle(QApplication::translate("AddDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("AddDialog", "Data", nullptr));
        label_2->setText(QApplication::translate("AddDialog", "Pessoa", nullptr));
        label_3->setText(QApplication::translate("AddDialog", "Valor", nullptr));
        label_5->setText(QApplication::translate("AddDialog", "E-Fatura", nullptr));
        label_6->setText(QApplication::translate("AddDialog", "Descri\303\247\303\243o", nullptr));
        label_4->setText(QApplication::translate("AddDialog", "Area", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddDialog: public Ui_AddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDIALOG_H
