#include "messagedialog.h"
#include "ui_messagedialog.h"

messageDialog::messageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messageDialog)
{
    ui->setupUi(this);
}

messageDialog::~messageDialog()
{
    delete ui;
}

void messageDialog::on_pushButton_clicked()
{
    this->close();
}
