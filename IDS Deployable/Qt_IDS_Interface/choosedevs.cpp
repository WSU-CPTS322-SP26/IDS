#include "choosedevs.h"
#include "mainwindow.h"
#include "ui_choosedevs.h"
#include "FindAllDevs.h"
#include "QIcon"
void DisplayInterfaces(Ui::ChooseDevs *ui);

ChooseDevs::ChooseDevs(QWidget *parent)
    : QDialog(parent)
    ,ui(new Ui::ChooseDevs)
{
    ui->setupUi(this);
    setWindowTitle("Interface List");
    ui->home->verticalHeader()->setVisible(false);
    ui->home->setColumnWidth(0,50);
    ui->home->setColumnWidth(1,200);
    ui->home->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    DisplayInterfaces(ui);
    setWindowIcon(QIcon(":/icons/cougar.png"));
    ui->home->setColumnHidden(2,true); // Hide this row. It is just used to store backend data.
}

ChooseDevs::~ChooseDevs()
{
    delete ui;
}


// Used ChatGPT for help with Syntax
void ChooseDevs::DisplayInterfaces(Ui::ChooseDevs *ui){
    pcap_if_t* alldevs = FindAllDevs();
    if(alldevs != NULL){
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
            ui->home->setItem(row, 2, new QTableWidgetItem(QString::fromLocal8Bit(d->name)));
            row++;

        }
        pcap_freealldevs(alldevs);
    }
    else{
        qDebug() << "No devices found.\n";
    }
}

void ChooseDevs::on_home_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    QTableWidgetItem *column2 = ui->home->item(row,2);
    MainWindow *w = new MainWindow(column2->text());
    w->showMaximized();
    this->close();
}

