#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStringList>
#include <vector>
#include <string>
#include <random>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    std::string generate_password(const std::string MODEL, const int length);
    void showListPasswords(const std::vector<std::string> listPasswords);
    void prepareModel();
    ~MainWindow();

private slots:
    void generateListOfPasswords();
    void resetUI();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;

    const std::string SPECIALS_MODEL = "~!@#$%^&*()-_=+[]{};:,.<>/?";
    const std::string NUMBER_MODEL = "0123456789";
    const std::string LOWERCASE_MODEL = "abcdefghijklmnopqrstuvwxyz";
    const std::string UPPERCASE_MODEL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string characters_model;

    std::vector<std::string> listOfPassword;
    int nbPassword;
    int lengthPassword;
    std::random_device rd;
};

#endif // MAINWINDOW_H
