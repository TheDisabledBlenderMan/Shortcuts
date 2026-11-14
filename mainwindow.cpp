#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include<QStandardPaths>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setup instruct label
    ui->inLabel->setStyleSheet("color: grey;");
    ui->inLabel->setAlignment(Qt::AlignHCenter);

    //checking if main text files are populated
    connect(ui->nameText, &QLineEdit::textChanged, this, &MainWindow::updateMakeBtn);
    connect(ui->programText, &QLineEdit::textChanged, this, &MainWindow::updateMakeBtn);

    //if  not disable the make button
    updateMakeBtn();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_findBtn_clicked()
{
    //find file
    QString file = QFileDialog::getOpenFileName(
        this,
        "Select Program",
        "/usr/bin",
        "All Files (*)"
        );
    if (file.isEmpty())
        return; // user cancelled

    //Put file name in txtBox
    ui->programText->setText(file);

    //Get the file path
    programPath = file;
}
void MainWindow::on_makeBtn_clicked()
{


    //Stream to .desktop file
    /*
     * testing
    std::cout << "[Desktop Entry]" << std::endl;
    std::cout << "Name=" << name.toStdString() << std::endl;
    std::cout << "Exac=" << programPath.toStdString() << std::endl;
    std::cout << "Type=Application" << std::endl;
    */

    QString name = ui->nameText->text();

    //getting path for new .desktop file
    QString dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = dir + "/" + name + ".desktop";

    QFile f(filePath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not write " + filePath);
        return;
    }

    QTextStream out(&f);

    //writing new desktop file
    out << "[Desktop Entry]\n"
        << "Type=Application\n"
        << "Name=" << name << "\n"
        << "Icon=" << iconPath << "\n"
        << "Exec=" << programPath << "\n"
        << "Terminal=" << (ui->checkBox->isChecked() ? "true" : "false") << "\n";

    f.close();

    f.setPermissions(f.permissions() | QFileDevice::ExeOwner);

    //message about new file
    QMessageBox::information(this, "Done", "Created " + filePath);

    //clear text boxes
    ui->nameText->clear();
    ui->programText->clear();
    ui->checkBox->setChecked(false);
    updateMakeBtn();
}

void MainWindow::updateMakeBtn()
{
    bool nameEmpty = ui->nameText->text().trimmed().isEmpty();
    bool programEmpty = ui->programText->text().trimmed().isEmpty();

    ui->makeBtn->setEnabled(!nameEmpty && !programEmpty);
}
void MainWindow::on_iconBtn_clicked()
{
    //find file
    QString file = QFileDialog::getOpenFileName(
        this,
        "Select a Icon",
        "/home/",
        "Images (*.png *.svg *.xpm)"
        );
    if (file.isEmpty())
        return; // user cancelled



    //Get the icon path
    iconPath = file;

    // show the icon on the button
    ui->iconBtn->setIcon(QIcon(file));
    ui->iconBtn->setIconSize(QSize(24, 24));
    //ui->iconBtn->setText(QFileInfo(file).fileName());
    ui->iconBtn->setToolTip(file);
}

