#include "menuf.h"
#include "ui_menuf.h"

MenuF::MenuF(QWidget *parent): QWidget(parent), ui(new Ui::MenuF)
{
    ui->setupUi(this);
}

MenuF::~MenuF()
{
    delete ui;
}
