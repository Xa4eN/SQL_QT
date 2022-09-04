#include "mainwindow.h"
#include "ui_mainwindow.h"

//конструктор виджета
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Главное меню");

    //инициализация окна работы с базой данных и подключение сигнала к слоту
    dbWindow = new DatabaseMenu();
    connect(dbWindow, &DatabaseMenu::firstWindow, this, &MainWindow::show);

    //инициализация окна работы с массивом и подключение сигнала к слоту
    arrWindow = new ArrayMenu();
    connect(arrWindow, &ArrayMenu::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//функция смены открытого окна программы при нажатии кнопки (открытие окна работы с базой данных)
void MainWindow::on_dbOpenBtn_clicked()
{
    dbWindow->show();
    this->close();
}

//функция смены открытого окна программы при нажатии кнопки (открытие окна работы с массивом)
void MainWindow::on_arrOpenBtn_clicked()
{
    arrWindow->show();
    this->close();
}

//функция кнопки завершения работы программы
void MainWindow::on_exitButton_clicked()
{
    qApp->exit();
}

