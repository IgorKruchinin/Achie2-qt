#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

#include <QListWidget>

#include "Achie2API/Achies.cpp"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT
    Achies *achies;
    QListWidget *list;

public:
    explicit AddDialog(QWidget *parent = nullptr, Achies *achies = nullptr, QListWidget *list = nullptr);
    ~AddDialog();

private slots:
    void on_OKBtn_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
