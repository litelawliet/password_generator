#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nbPassword = 0;
    lengthPassword = 0;

    QObject::connect(ui->pushButton_generate, SIGNAL(clicked()), this, SLOT(generateListOfPasswords()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
* @brief Generate a password based on a model with a given size.
*
* @param[in] MODEL The list of usable characters.
* @param[in] length The size of the password.
*
* @return The generated password.
*
* @author Thibaut PONCHON
* @version 1.1
* @date 2018 June 12
*/
std::string MainWindow::generate_password(const std::string MODEL, const int length) {
    std::string password = "";

    std::uniform_int_distribution<int> dist(0, MODEL.size()-1);

    for(int i = 0; i < length; i++) {
        password += MODEL[dist(rd)];
    }

    return password;
}

void MainWindow::generateListOfPasswords() {
    listOfPassword.clear();
    for(int i = 0; i < ui->spinBox_nbPassword->value(); i++) {
        listOfPassword.push_back(generate_password(CHARACTERS_MODEL, ui->spinBox_lengthPassword->value()));
    }
    showListPasswords(listOfPassword);
}

void MainWindow::showListPasswords(const std::vector<std::string> listPasswords) {
    model = new QStringListModel(this);
    for(unsigned int i = 0; i < listPasswords.size(); i++) {
        qDebug() << listPasswords[i].c_str();
        // model.listPasswords[i]);
    }
    ui->listView_listPasswords->setModel(model);
}
