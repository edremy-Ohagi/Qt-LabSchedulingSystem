#include "roomdialog.h"
#include "ui_roomdialog.h"

roomDialog::roomDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::roomDialog)
{
    ui->setupUi(this);
}

roomDialog::~roomDialog()
{
    delete ui;
}

int roomDialog::AreaChoice()
{
    return ui->comboBox->currentIndex();
}

QString roomDialog::getName()
{
    return ui->lineEdit_RoomName->text();
}

int roomDialog::getppl()
{
    return ui->spinBox->value();
}
