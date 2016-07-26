#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>


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
    void on_action_Load_triggered();

    void on_action_History_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *historyTableModel = nullptr;

};

#endif // MAINWINDOW_H
