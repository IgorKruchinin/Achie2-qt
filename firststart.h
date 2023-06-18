#ifndef FIRSTSTART_H
#define FIRSTSTART_H

#include <QDialog>


namespace Ui {
class FirstStart;
}

class FirstStart : public QDialog
{
    Q_OBJECT

public:
    explicit FirstStart(QWidget *parent = nullptr);
    ~FirstStart();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FirstStart *ui;
};

#endif // FIRSTSTART_H
