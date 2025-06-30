#include "createfood.h"
#include "ui_createfood.h"

CreateFood::CreateFood(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateFood)
{
    ui->setupUi(this);
}

CreateFood::~CreateFood()
{
    delete ui;
}
