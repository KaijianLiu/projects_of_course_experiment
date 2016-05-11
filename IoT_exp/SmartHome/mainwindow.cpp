#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_humidityButton_clicked()
{
    QMessageBox::about(0, "Humidity Info", "Foo* foo;\nfoo->show();");
}

void MainWindow::on_temperatureButton_clicked()
{
    QMessageBox::about(0, "Temperature Info", "Foo* foo;\nfoo->show();");
}

void MainWindow::on_lampButton_clicked()
{
    QMessageBox::about(0, "Lamp Control", "Foo* foo;\nfoo->show();");
}

void MainWindow::on_toiletButton_clicked()
{
    QMessageBox::about(0, "Bathroom", "Foo* foo;\nfoo->show();");
}

void MainWindow::on_gateButton_clicked()
{
    QMessageBox::about(0, "Gate Record", "Foo* foo;\nfoo->show();");
}

void MainWindow::on_settingButton_clicked()
{
     QMessageBox::about(0, "Setting", "Foo* foo;\nfoo->show();");
}
