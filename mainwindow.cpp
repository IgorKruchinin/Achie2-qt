#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "firststart.h"
#include <QDate>
#include "Achie2API/Achies.cpp"

MainWindow::MainWindow(QWidget *parent, Achies *achies)
    : QMainWindow(parent),
      achies(achies),
      ui(new Ui::MainWindow)
{
    if (achies != NULL) {
        ui->setupUi(this);
        //std::vector<long> dates = prof->geti("date").get_objects();
        //std::vector<std::string> objects = prof->gets("object").get_objects();
        for (int i = 0; i < achies->size(); ++i) {
            QDateTime *date = new QDateTime();
            date->setMSecsSinceEpoch(achies->get_achie(i)->get_unixtime());
            ui->achiesList->addItem(date->date().toString(Qt::DateFormat::ISODate) + "    " + QString(achies->get_achie(i)->get_name()));
            delete date;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenAddDialog() {
    AddDialog *addDialog = new AddDialog(nullptr, achies, ui->achiesList);
    addDialog->show();
}


void MainWindow::on_addAchie_clicked()
{
    OpenAddDialog();
}

