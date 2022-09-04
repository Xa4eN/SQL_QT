#include "arraymenu.h"
#include "ui_arraymenu.h"

//конструктор виджета
ArrayMenu::ArrayMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArrayMenu)
{
    ui->setupUi(this);

    this->setWindowTitle("Динамический массив");

    //установка диапазона ползунков
    ui->minSlider->setRange(-1000, 0);
    ui->maxSlider->setRange(1, 1000);

    ui->maxRB->setChecked(true);
}

ArrayMenu::~ArrayMenu()
{
    delete ui;
}

//функция нажатия на кнопку возврата в главное меню
void ArrayMenu::on_backBtn_clicked()
{
    this->close();
    emit firstWindow();
}

//функция перемещения ползунка с минимальным значением диапазона
void ArrayMenu::on_minSlider_valueChanged(int value)
{
    ui->minLcd->display(value);
}

//функция перемещения ползунка с максимальным значением диапазона
void ArrayMenu::on_maxSlider_valueChanged(int value)
{
    ui->maxLcd->display(value);
}

//функция кнопки "Задать"
void ArrayMenu::on_setButton_clicked()
{
    ui->startBrowser->clear();  //предварительная очистка окна вывода массива

    //инициализация переменной для хранения массива и начальные значения переменных для подсчета результата работы над массивом
    int *data = new int[10];
    this->average = 0;
    this->minimum = 1001;
    this->maximum = -1001;

    srand(time(NULL));

    //заполнение массива случайными числами, запись массива в окно для вывода и подсчёт результата каждого действия над массивом
    for (int i = 0; i < 10; i++)
    {
        QString value;

        data[i] = rand() % (ui->maxLcd->intValue() - ui->minLcd->intValue() + 1) + ui->minLcd->intValue();
        value.setNum(data[i]);
        ui->startBrowser->append(value);

        average += data[i];
        if (data[i] < minimum) minimum = data[i];
        if (data[i] > maximum) maximum = data[i];
    }

    average = average / 10;
}

//функция вывода в окно результата обработки массива
void ArrayMenu::on_resultButton_clicked()
{
    ui->resultBrowser->clear();

    //вывод наименьшего значения массива
    if (ui->minRB->isChecked())
    {
        QString result;
        result.setNum(minimum);
        ui->resultBrowser->append(result);
    }

    //вывод наибольшего значения массива
    if (ui->maxRB->isChecked())
    {
        QString result;
        result.setNum(maximum);
        ui->resultBrowser->append(result);
    }

    //вывод среднего арифметического всех значений массива
    if (ui->averageRB->isChecked())
    {
        QString result;
        result.setNum(average);
        ui->resultBrowser->append(result);
    }
}

//функция кнопки сброса (очистка всех окон для вывода, установка ползунков в начальное положение)
void ArrayMenu::on_resetButton_clicked()
{
    ui->startBrowser->clear();
    ui->resultBrowser->clear();
    ui->maxLcd->display(1);
    ui->minLcd->display(0);
    ui->minSlider->setSliderPosition(0);
    ui->maxSlider->setSliderPosition(1);
}

