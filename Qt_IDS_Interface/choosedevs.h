#ifndef CHOOSEDEVS_H
#define CHOOSEDEVS_H

#include "qtablewidget.h"
#include <QDialog>

namespace Ui {
class ChooseDevs;
}

class ChooseDevs : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDevs(QWidget *parent = nullptr);
    void DisplayInterfaces(Ui::ChooseDevs *ui);
    ~ChooseDevs();

private slots:
    void on_home_itemClicked(QTableWidgetItem *item);

private:
    Ui::ChooseDevs *ui;
};

#endif // CHOOSEDEVS_H
