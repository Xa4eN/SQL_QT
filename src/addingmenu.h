#ifndef ADDINGMENU_H
#define ADDINGMENU_H

#include <QWidget>
#include <QMessageBox>
#include <QDateTime>

namespace Ui {
class AddingMenu;
}

class AddingMenu : public QWidget
{
    Q_OBJECT

public:
    explicit AddingMenu(QWidget *parent = nullptr);
    ~AddingMenu();

private:
    Ui::AddingMenu *ui;

signals:
    void databaseWindow();
    void databaseAdder(QVariantList);

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();
};

#endif // ADDINGMENU_H
