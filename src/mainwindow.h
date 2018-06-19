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
    ~MainWindow();

private slots:
    void generateListOfPasswords();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;

    const std::string CHARACTERS_MODEL = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,?;.:/!*=}+])_|-[({#&";

    std::vector<std::string> listOfPassword;
    int nbPassword;
    int lengthPassword;
    std::random_device rd;
};

#endif // MAINWINDOW_H
