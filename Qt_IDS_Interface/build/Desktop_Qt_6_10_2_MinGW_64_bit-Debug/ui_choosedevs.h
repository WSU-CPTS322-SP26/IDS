/********************************************************************************
** Form generated from reading UI file 'choosedevs.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEDEVS_H
#define UI_CHOOSEDEVS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChooseDevs
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *home;

    void setupUi(QDialog *ChooseDevs)
    {
        if (ChooseDevs->objectName().isEmpty())
            ChooseDevs->setObjectName("ChooseDevs");
        ChooseDevs->resize(899, 687);
        verticalLayout = new QVBoxLayout(ChooseDevs);
        verticalLayout->setObjectName("verticalLayout");
        home = new QTableWidget(ChooseDevs);
        if (home->columnCount() < 3)
            home->setColumnCount(3);
        QFont font;
        font.setPointSize(14);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        home->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        home->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        home->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        home->setObjectName("home");
        home->setFont(font);
        home->setRowCount(0);
        home->setColumnCount(3);
        home->horizontalHeader()->setDefaultSectionSize(50);
        home->horizontalHeader()->setHighlightSections(true);

        verticalLayout->addWidget(home);


        retranslateUi(ChooseDevs);

        QMetaObject::connectSlotsByName(ChooseDevs);
    } // setupUi

    void retranslateUi(QDialog *ChooseDevs)
    {
        ChooseDevs->setWindowTitle(QCoreApplication::translate("ChooseDevs", "Dialog", nullptr));
        QTableWidgetItem *___qtablewidgetitem = home->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ChooseDevs", "No.", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = home->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ChooseDevs", "Interface", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = home->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ChooseDevs", "GhostColumn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseDevs: public Ui_ChooseDevs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEDEVS_H
