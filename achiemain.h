#ifndef ACHIEMAIN_H
#define ACHIEMAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AchieMain; }
QT_END_NAMESPACE

class AchieMain : public QMainWindow
{
    Q_OBJECT

public:
    AchieMain(QWidget *parent = nullptr);
    ~AchieMain();

private:
    Ui::AchieMain *ui;
};
#endif // ACHIEMAIN_H
