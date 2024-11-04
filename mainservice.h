#ifndef MAINSERVICE_H
#define MAINSERVICE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class mainservice;
}
QT_END_NAMESPACE

class mainservice : public QMainWindow
{
    Q_OBJECT

public:
    mainservice(QWidget *parent = nullptr);
    ~mainservice();

private slots:

    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();



    void on_pushButton_afficher_clicked();





    void on_pushButton_edit_clicked();

private:
    Ui::mainservice *ui;
};
#endif // MAINSERVICE_H
