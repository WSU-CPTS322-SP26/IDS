#ifndef CHOOSEDEVS_H
#define CHOOSEDEVS_H

#include <QDialog>

namespace Ui {
class ChooseDevs;
}

class ChooseDevs : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDevs(QWidget *parent = nullptr);
    ~ChooseDevs();

private:
    Ui::ChooseDevs *ui;
};

#endif // CHOOSEDEVS_H
