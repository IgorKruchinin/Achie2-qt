#include "mainwindow.h"

#include <QApplication>
#include "Achie2API/Achies.cpp"
#include "firststart.h"
#include "Achie2API/props.h"
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    Achies_info achinfo = Storage::get_all_profiles();
    if (achinfo.names.size() == 0) {
        printf("Warning: No default profile found!");
        FirstStart fs(nullptr);
        fs.show();
    } else {
        Achies achies = Achies(achinfo.names[achinfo.default_index], true);
        MainWindow w(nullptr, &achies);
        w.show();
    }*/

    Achies achies("default", true);
    MainWindow w(nullptr, &achies);
    w.show();
    return a.exec();
}
