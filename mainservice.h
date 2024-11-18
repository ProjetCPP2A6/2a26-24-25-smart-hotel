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
     void onLoginButtonClicked();
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();



    void on_pushButton_afficher_clicked();





    void on_pushButton_edit_clicked();

    void on_pushButton_afficher_tous_clicked();
    void on_lineEdit_id_ed_editingFinished();
    void onSendMessage();
    void on_pushButton_pdf_clicked();

private:
    Ui::mainservice *ui;
    void showAllEmployees();
    bool validateLogin(const QString &username, const QString &password);
};
#endif // MAINSERVICE_H
