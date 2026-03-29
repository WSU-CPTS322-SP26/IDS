#include "choosedevs.h"
#include "ui_choosedevs.h"
#include "FindAllDevs.h"
void DisplayInterfaces(Ui::ChooseDevs *ui);

ChooseDevs::ChooseDevs(QWidget *parent)
    : QDialog(parent)
    ,ui(new Ui::ChooseDevs)
{
    ui->setupUi(this);
    ui->home->verticalHeader()->setVisible(false);
    ui->home->setColumnWidth(0,50);
    ui->home->setColumnWidth(1,200);
    ui->home->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    DisplayInterfaces(ui);
}

ChooseDevs::~ChooseDevs()
{
    delete ui;
}


// Used ChatGPT for help with Syntax
void DisplayInterfaces(Ui::ChooseDevs *ui){
    pcap_if_t* alldevs = FindAllDevs();
    pcap_if_t* d;
    int row = 0;
    for (d = alldevs; d != NULL; d = d->next)
    {
        QString text;
        if(d->description){
            text += QString(" ") + d->description;
        }
        else{
            text += QString(" Unknown");
        }

        ui->home->insertRow(row);
        ui->home->setItem(row, 0, new QTableWidgetItem(QString::number(row+1)));
        ui->home->item(row,0)->setTextAlignment(Qt::AlignCenter); // Center first column
        ui->home->setItem(row, 1, new QTableWidgetItem(text));

        row++;

    }
    pcap_freealldevs(alldevs);
}
