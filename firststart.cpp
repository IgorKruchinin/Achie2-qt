#include "firststart.h"
#include "ui_firststart.h"
#include "mainwindow.h"

FirstStart::FirstStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirstStart)
{
    ui->setupUi(this);
}

FirstStart::~FirstStart()
{
    delete ui;
}

void FirstStart::on_buttonBox_accepted()
{

    QString name = ui->profName->text();
    Achies *achies = new Achies(name.toStdString().c_str(), true);
    MainWindow w(nullptr, achies);
    w.show();
    /*auto prof = new USM(name.toStdString());
    prof->create_isec("count");
    prof->create_isec("date");
    prof->create_ssec("measure");
    prof->create_ssec("object");
    prof->create_ssec("type");
    prof->to_file();
    MainWindow *w = new MainWindow(nullptr, prof);
    w->show();
    */
    close();
}

