#include "databasemenu.h"
#include "ui_databasemenu.h"

//конструктор виджета
DatabaseMenu::DatabaseMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseMenu)
{
    ui->setupUi(this);

    this->setWindowTitle("База данных");

    //инициализация базы данных с помощью переменной
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../db/countries.db");

    //контроль ошибок при загрузке базы данных
    if (db.open())
    {
        ui->statusLabel->
            setText("База данных успешно загружена");

        //инициализация и настройка таблицы для вывода базы данных
        model = new QSqlTableModel(this, db);
        model->setTable("Страны");
        model->select();

        ui->databaseViewer->setModel(model);

        ui->databaseViewer->horizontalHeader()->
            setSectionResizeMode(QHeaderView::Stretch);

        //инициализация и обработка сигнала вызова окна добавления элемента в базу данных
        addWindow = new AddingMenu();
        connect(addWindow, &AddingMenu::databaseWindow, this, &DatabaseMenu::show);
        connect(addWindow, &AddingMenu::databaseAdder, this, &DatabaseMenu::databaseAdderSlot);
    }
    else ui->statusLabel->
            setText("Ошибка загрузки базы данных: " + db.lastError().databaseText());
}

DatabaseMenu::~DatabaseMenu()
{
    delete ui;
}

//функция кнопки возврата в главное меню
void DatabaseMenu::on_backBtn_clicked()
{
    this->close();
    emit firstWindow();
}

//функция кнопки добавления элемента в базу данных
void DatabaseMenu::on_addButton_clicked()
{
    addWindow->show();
}

//слот, отрабатываемый при вызове сигнала открытия окна добавления нового элемента в базу данных
void DatabaseMenu::databaseAdderSlot(QVariantList data)
{
    model->insertRow(model->rowCount());

    //добавление в базу данных нового элемента, информация о котором получена в окне добавления
    for (int i = 0; i < 7; i++)
        model->setData(model->index(model->rowCount() - 1, i), data[i]);

    model->submit();
}

//функция кнопки удаления элемента из базы данных
void DatabaseMenu::on_removeButton_clicked()
{
    model->removeRow(rowNumber);
    model->select();
}

//функция нажатия на таблицу с базой данных (выбор строки)
void DatabaseMenu::on_databaseViewer_clicked(const QModelIndex &index)
{
    rowNumber = index.row();
}

//функция нажатия на раскрывающийся список методов сортировки базы данных
void DatabaseMenu::on_sortBox_activated(int index)
{
    //установка метода сортировки в зависимости от выбора пользователя
    switch (index)
    {
    case 0:
        model->sort(6, Qt::AscendingOrder);
        break;
    case 1:
        model->sort(6, Qt::DescendingOrder);
        break;
    case 2:
        model->sort(0, Qt::AscendingOrder);
        break;
    case 3:
        model->sort(0, Qt::DescendingOrder);
        break;
    case 4:
        model->sort(1, Qt::AscendingOrder);
        break;
    case 5:
        model->sort(1, Qt::DescendingOrder);
        break;
    case 6:
        model->sort(2, Qt::AscendingOrder);
        break;
    case 7:
        model->sort(2, Qt::DescendingOrder);
        break;
    case 8:
        model->sort(3, Qt::AscendingOrder);
        break;
    case 9:
        model->sort(3, Qt::DescendingOrder);
        break;
    case 10:
        model->sort(4, Qt::AscendingOrder);
        break;
    case 11:
        model->sort(4, Qt::DescendingOrder);
        break;
    case 12:
        model->sort(5, Qt::AscendingOrder);
        break;
    case 13:
        model->sort(5, Qt::DescendingOrder);
        break;
    }
}

//функция кнопки очистки базы данных (удаления всех полей)
void DatabaseMenu::on_clearButton_clicked()
{
    //открытие окна с предупреждением
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Подтвердите действие",
        "Внимание! Очистка базы данных приведёт к удалению всех имеющихся полей. "
        "Отменить действие будет невозможно. Вы уверены, что желаете продолжить?", QMessageBox::Yes | QMessageBox::No);

    //очистка базы данных
    if (reply == QMessageBox::Yes)
    {
        for (int i = 0; i < model->rowCount(); ++i)
                model->removeRow(i);
        model->select();
    }
}

