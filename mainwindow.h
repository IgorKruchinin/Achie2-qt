#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "adddialog.h"
#include "Achie2API/Achies.cpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Achies *achies;

public:
    MainWindow(QWidget *parent = nullptr, Achies *achies = nullptr);
    void OpenAddDialog();
    ~MainWindow();

private slots:
    void on_addAchie_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
