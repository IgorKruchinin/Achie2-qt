#include "adddialog.h"
#include "ui_adddialog.h"
#include "Achie2API/Achies.cpp"

AddDialog::AddDialog(QWidget *parent, Achies *achies, QListWidget *list) :
    QDialog(parent),
    achies(achies),
    list(list),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    ui->dateFld->setDate(QDate::QDate::currentDate());
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_OKBtn_clicked()
{
    auto dateTime = ui->dateFld->dateTime();
    long time = dateTime.toMSecsSinceEpoch();
    std::string name = ui->nameFld->text().toStdString();
    std::string description = ui->descriptionFld->text().toStdString();
    long count = ui->countFld->value();
    achies->add(time, name.c_str(), description.c_str(),count);
    /*
    prof->geti("date").add(time);
    prof->gets("object").add(object);
    prof->gets("type").add(type);
    prof->gets("measure").add(measure);
    prof->geti("count").add(count);
    prof->gets("photo").add("");
    prof->to_file();
    */
    list->addItem(dateTime.date().toString(Qt::DateFormat::ISODate) + "    " + QString(name.c_str()));
    this->close();
}

