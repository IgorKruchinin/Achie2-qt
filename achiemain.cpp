#include "achiemain.h"
#include "./ui_achiemain.h"
#include "Achie2API/Achies.cpp"

AchieMain::AchieMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AchieMain)
{
    ui->setupUi(this);
}

AchieMain::~AchieMain()
{
    delete ui;
}

