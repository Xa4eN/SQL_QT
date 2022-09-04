#include "addingmenu.h"
#include "ui_addingmenu.h"
#include <QMessageBox>

//конструктор виджета
AddingMenu::AddingMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddingMenu)
{
    ui->setupUi(this);

    this->setWindowTitle("Добавление элемента...");  //установка наименования окна

    ui->formRadio_1->setChecked(true);
    ui->regimeRadio_1->setChecked(true);
    ui->admRadio_1->setChecked(true);
}

AddingMenu::~AddingMenu()
{
    delete ui;
}

//функция нажатия на кнопку отмены
void AddingMenu::on_cancelButton_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    ui->formRadio_1->setChecked(true);
    ui->regimeRadio_1->setChecked(true);
    ui->admRadio_1->setChecked(true);


    this->close();
    emit databaseWindow();
}

//функция нажатия на кнопку "Ок"
void AddingMenu::on_okButton_clicked()
{
    //контроль входных данных
    QString warning_1 = "", warning_2 = "", warning_3 = "";

    if (ui->lineEdit->text() == "") warning_1 = "*Поле <Название страны> не должно быть пустым. ";
    if (ui->lineEdit_2->text() == "") warning_2 = "*Поле <Название столицы> не должно быть пустым. ";
    if ((ui->lineEdit_3->text().toInt() == false) || (ui->lineEdit_3->text().toInt() <= 0))
        warning_3 = "*Поле <Численность населения> должно содержать положительное целочисленное значение. ";

    //заполнение переменной data для последующего добавления объекта в БД при отсутствии ошибок ввода
    if ((warning_1 == warning_2) && (warning_2 == warning_3))
    {
        QVariantList data;

        data.append(ui->lineEdit->text());
        data.append(ui->lineEdit_2->text());
        data.append(ui->lineEdit_3->text());

        if (ui->formRadio_1->isChecked()) data.append("республика");
        if (ui->formRadio_2->isChecked()) data.append("монархия");

        if (ui->admRadio_1->isChecked()) data.append("унитарное");
        if (ui->admRadio_2->isChecked()) data.append("федеративное");
        if (ui->admRadio_3->isChecked()) data.append("конфедеративное");

        if (ui->regimeRadio_1->isChecked()) data.append("демократический");
        if (ui->regimeRadio_2->isChecked()) data.append("авторитарный");
        if (ui->regimeRadio_3->isChecked()) data.append("тоталитарный");

        data.append(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"));

        emit databaseAdder(data);

        //очистка окна после ввода данных
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();

        ui->formRadio_1->setChecked(true);
        ui->regimeRadio_1->setChecked(true);
        ui->admRadio_1->setChecked(true);


        this->close();
        emit databaseWindow();
    }

    //вывод сообщения об ошибках ввода
    else QMessageBox::warning(this, "Ошибка ввода", "При вводе информации об объекте допущены следующие ошибки: "
                              + warning_1 + warning_2 + warning_3 + "Пожалуйста, исправьте неточности и повторите ввод.");
}

