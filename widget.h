#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    QImage Img,water,add;
    QStringList filenames;
    QString watermarking;
    int wa;
    int where,realwhere = 0;
    int frame = 1000,many;
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_close_clicked();

    void on_load_clicked();

    void on_start_clicked();

    void on_stop_clicked();

    void on_mul_clicked();

    void on_div_clicked();

    void on_first_clicked();

    void on_repeat_clicked();

    void on_back_clicked();

    void on_toolButton_2_clicked();

    void LogicOperator(QImage *srcImg_1, QImage *srcImg_2,
                           QImage *output);

    void on_test_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
