#ifndef DATABASEMENU_H
#define DATABASEMENU_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QMessageBox>
#include "addingmenu.h"

namespace Ui {
class DatabaseMenu;
}

class DatabaseMenu : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseMenu(QWidget *parent = nullptr);
    ~DatabaseMenu();

private slots:
    void on_backBtn_clicked();

    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_databaseViewer_clicked(const QModelIndex &index);

    void on_sortBox_activated(int index);

    void on_clearButton_clicked();

public slots:
    void databaseAdderSlot(QVariantList data);

private:
    Ui::DatabaseMenu *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    AddingMenu *addWindow;
    int rowNumber;

signals:
    void firstWindow();
};


#endif // DATABASEMENU_H
