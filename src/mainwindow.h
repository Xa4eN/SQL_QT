#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemenu.h"
#include "arraymenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dbOpenBtn_clicked();

    void on_arrOpenBtn_clicked();

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseMenu *dbWindow;
    ArrayMenu *arrWindow;
};
#endif // MAINWINDOW_H
