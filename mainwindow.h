#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_findBtn_clicked();
    void updateMakeBtn();


    void on_makeBtn_clicked();

    void on_iconBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString iconPath;
    QString programPath;

};
#endif // MAINWINDOW_H
