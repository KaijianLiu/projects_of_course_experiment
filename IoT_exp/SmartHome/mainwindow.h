#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_humidityButton_clicked();

    void on_temperatureButton_clicked();

    void on_lampButton_clicked();

    void on_toiletButton_clicked();

    void on_gateButton_clicked();

    void on_settingButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
