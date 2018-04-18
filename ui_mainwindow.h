/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "circulargraphic.h"
#include "glstatusbar.h"
#include "linesgraphic.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QStackedWidget *Stack;
    QWidget *MainView;
    QVBoxLayout *verticalLayout;
    QLabel *MainTitle;
    GLStatusBar *MainBar;
    QGridLayout *gridLayout_2;
    CircularGraphic *MainCheese;
    CircularGraphic *SpentCheese;
    LinesGraphic *MonthGraph;
    LinesGraphic *AnualGraph;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *MainButton;
    QPushButton *AddGasto;
    QPushButton *MonthButton;
    QMenuBar *menuBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(866, 617);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        Stack = new QStackedWidget(centralWidget);
        Stack->setObjectName(QStringLiteral("Stack"));
        MainView = new QWidget();
        MainView->setObjectName(QStringLiteral("MainView"));
        verticalLayout = new QVBoxLayout(MainView);
        verticalLayout->setSpacing(5);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        MainTitle = new QLabel(MainView);
        MainTitle->setObjectName(QStringLiteral("MainTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainTitle->sizePolicy().hasHeightForWidth());
        MainTitle->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Malgun Gothic"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        MainTitle->setFont(font);
        MainTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(MainTitle);

        MainBar = new GLStatusBar(MainView);
        MainBar->setObjectName(QStringLiteral("MainBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(MainBar->sizePolicy().hasHeightForWidth());
        MainBar->setSizePolicy(sizePolicy1);
        MainBar->setMinimumSize(QSize(0, 25));

        verticalLayout->addWidget(MainBar);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        MainCheese = new CircularGraphic(MainView);
        MainCheese->setObjectName(QStringLiteral("MainCheese"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(MainCheese->sizePolicy().hasHeightForWidth());
        MainCheese->setSizePolicy(sizePolicy2);
        MainCheese->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(MainCheese, 2, 0, 1, 1);

        SpentCheese = new CircularGraphic(MainView);
        SpentCheese->setObjectName(QStringLiteral("SpentCheese"));
        sizePolicy2.setHeightForWidth(SpentCheese->sizePolicy().hasHeightForWidth());
        SpentCheese->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(SpentCheese, 2, 1, 1, 1);

        MonthGraph = new LinesGraphic(MainView);
        MonthGraph->setObjectName(QStringLiteral("MonthGraph"));
        sizePolicy2.setHeightForWidth(MonthGraph->sizePolicy().hasHeightForWidth());
        MonthGraph->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(MonthGraph, 3, 1, 1, 1);

        AnualGraph = new LinesGraphic(MainView);
        AnualGraph->setObjectName(QStringLiteral("AnualGraph"));
        sizePolicy2.setHeightForWidth(AnualGraph->sizePolicy().hasHeightForWidth());
        AnualGraph->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(AnualGraph, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        Stack->addWidget(MainView);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        Stack->addWidget(page_2);

        gridLayout->addWidget(Stack, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        MainButton = new QPushButton(centralWidget);
        MainButton->setObjectName(QStringLiteral("MainButton"));

        horizontalLayout_3->addWidget(MainButton);

        AddGasto = new QPushButton(centralWidget);
        AddGasto->setObjectName(QStringLiteral("AddGasto"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(AddGasto->sizePolicy().hasHeightForWidth());
        AddGasto->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(AddGasto);

        MonthButton = new QPushButton(centralWidget);
        MonthButton->setObjectName(QStringLiteral("MonthButton"));

        horizontalLayout_3->addWidget(MonthButton);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 866, 26));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        MainTitle->setText(QApplication::translate("MainWindow", "Vista Geral", nullptr));
        MainButton->setText(QApplication::translate("MainWindow", "Vista Geral", nullptr));
        AddGasto->setText(QApplication::translate("MainWindow", "Adicionar Gasto", nullptr));
        MonthButton->setText(QApplication::translate("MainWindow", "Vista Mensal", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
