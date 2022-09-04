#ifndef ARRAYMENU_H
#define ARRAYMENU_H

#include <QWidget>
#include <ctime>

namespace Ui {
class ArrayMenu;
}

class ArrayMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayMenu(QWidget *parent = nullptr);
    ~ArrayMenu();

private slots:
    void on_backBtn_clicked();

    void on_minSlider_valueChanged(int value);

    void on_maxSlider_valueChanged(int value);

    void on_setButton_clicked();

    void on_resultButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::ArrayMenu *ui;
    float average;
    int minimum;
    int maximum;

signals:
    void firstWindow();
};

#endif // ARRAYMENU_H
