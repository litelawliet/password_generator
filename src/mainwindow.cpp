#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create model
    model = new QStringListModel(this);

    characters_model = "";

    nbPassword = 0;
    lengthPassword = 0;

    QObject::connect(ui->pushButton_generate, SIGNAL(clicked()), this, SLOT(generateListOfPasswords()));
    QObject::connect(ui->pushButton_reset, SIGNAL(clicked()), this, SLOT(resetUI()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
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

/**
 * @brief MainWindow::generateListOfPasswords Generate a list of password into the model.
 *
 * @author Thibaut PONCHON
 * @version 1.0
 * @date 2018 June 19
 */
void MainWindow::generateListOfPasswords() {
    prepareModel();

    listOfPassword.clear();

    if(characters_model.size() > 0) {
        for(int i = 0; i < ui->spinBox_nbPassword->value(); i++) {
            listOfPassword.push_back(generate_password(characters_model, ui->spinBox_lengthPassword->value()));
        }
    }
    else {
        QPalette palette = ui->label_informations->palette();
        palette.setColor(QPalette::WindowText, Qt::red);
        ui->label_informations->setPalette(palette);
        ui->label_informations->setText("No characters model, can't generate a password.");
    }

    showListPasswords(listOfPassword);
}

/**
 * @brief MainWindow::resetUI Reset all the UI to the default settings.
 *
 * @author Thibaut PONCHON
 * @version 1.3
 * @date 2018 June 21
 */
void MainWindow::resetUI() {
    ui->checkBox_number->setCheckState(Qt::CheckState::Checked);
    ui->checkBox_lowercase->setCheckState(Qt::CheckState::Checked);
    ui->checkBox_uppercase->setCheckState(Qt::CheckState::Checked);
    ui->checkBox_specials->setCheckState(Qt::CheckState::Unchecked);

    ui->spinBox_lengthPassword->setValue(8);
    ui->spinBox_nbPassword->setValue(1);

    QPalette palette = ui->label_informations->palette();
    palette.setColor(QPalette::WindowText, Qt::black);
    ui->label_informations->setPalette(palette);
    ui->label_informations->setText("Set all the different parameters to your convenience then generate it !");

    model->setStringList(QStringList());
}

/**
 * @brief Show all the passwords generated by filling them into the ListView.
 *
 * @param[in] listPasswords The list of password.
 *
 * @author Thibaut PONCHON
 * @version 1.1
 * @date 2018 June 12
 *
 */

void MainWindow::showListPasswords(const std::vector<std::string> listPasswords) {
    QStringList listData;
    for(unsigned int i = 0; i < listPasswords.size(); i++) {
        listData << listPasswords[i].c_str();
    }

    model->setStringList(listData);

    ui->listView_listPasswords->setModel(model);
}

/**
 * @brief Prepare the characters model by adding every sub-model who has been checked.
 *
 * @author Thibaut PONCHON
 * @version 1.3
 * @date 2018 June 21
 */
void MainWindow::prepareModel() {
    // Color change
    QPalette palette = ui->label_informations->palette();
    palette.setColor(QPalette::WindowText, Qt::blue);
    ui->label_informations->setPalette(palette);

    // Data
    characters_model = "";
    ui->label_informations->setText("");

    // Tests
    if(ui->checkBox_number->isChecked()) {
        characters_model += NUMBER_MODEL;
        ui->label_informations->setText(" + Numbers added.\n");
    }

    if(ui->checkBox_lowercase->isChecked()) {
        characters_model += LOWERCASE_MODEL;
        ui->label_informations->setText(ui->label_informations->text() + " + Lowercase added\n");
    }

    if(ui->checkBox_uppercase->isChecked()) {
        characters_model += UPPERCASE_MODEL;
        ui->label_informations->setText(ui->label_informations->text() + " + Uppercase added\n");
    }

    if(ui->checkBox_specials->isChecked()) {
        characters_model += SPECIALS_MODEL;
        ui->label_informations->setText(ui->label_informations->text() + " + Specials added\n");
    }
}
