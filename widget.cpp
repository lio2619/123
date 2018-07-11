#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QTime>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("連播照片");
}

Widget::~Widget()
{
    delete ui;
}

void sleep(unsigned int msec){      //延遲時間 單位:毫秒
    QTime reachtime = QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime()<reachtime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

void Widget::on_close_clicked()
{
    close();
}

void Widget::on_load_clicked()
{
    filenames = QFileDialog::getOpenFileNames(this,tr("開啟檔案"),"/","Images(*.png *.jpeg *.jpg)");        //規定選擇的檔名
    many = filenames.size();
    for(int i = 0 ; i < 1 ; i++){
        Img.load(filenames[i]);
        ui->toolButton->setIconSize(QSize(Img.width(),Img.height()));
        ui->toolButton->setIcon(QPixmap::fromImage(Img));
    }

    QString m = QString::number(many,10);
    QMessageBox::information(this,tr("張數"),m);
}

void Widget::on_start_clicked()
{
    for(where = 0 ; where < many ; where++){
        Img.load(filenames[realwhere]);
        ui->toolButton->setIconSize(QSize(Img.width(),Img.height()));
        ui->toolButton->setIcon(QPixmap::fromImage(Img));
        sleep(frame);
        if(realwhere < many){
            realwhere = realwhere + 1;
        }
    }
}

void Widget::on_stop_clicked()
{
    sleep(999999);
}

void Widget::on_mul_clicked()       //兩倍速
{
    if(frame > 2){
        frame = frame / 2;
    }
}

void Widget::on_div_clicked()       //慢兩倍
{
    if(frame < 1001){
        frame = frame * 2;
    }
}

void Widget::on_first_clicked()
{
    for(int first = 0 ; first < many ; first++){
        Img.load(filenames[first]);
        ui->toolButton->setIconSize(QSize(Img.width(),Img.height()));
        ui->toolButton->setIcon(QPixmap::fromImage(Img));
        sleep(frame);
    }
}

void Widget::on_repeat_clicked()
{
    for(where = 0 ; where < many ; where++){
        Img.load(filenames[realwhere]);
        ui->toolButton->setIconSize(QSize(Img.width(),Img.height()));
        ui->toolButton->setIcon(QPixmap::fromImage(Img));
        sleep(frame);
        if(realwhere < filenames.size()){
            realwhere = realwhere + 1;
        }
        if(realwhere == many-1){
            realwhere = 0;
            where = 0;
        }
    }
}

void Widget::on_back_clicked()
{
    for(int back = many ; back >= 0 ; back--){
        Img.load(filenames[realwhere]);
        ui->toolButton->setIconSize(QSize(Img.width(),Img.height()));
        ui->toolButton->setIcon(QPixmap::fromImage(Img));
        sleep(frame);
        if(realwhere < many){
            realwhere = realwhere - 1;
        }
    }
}

void Widget::on_toolButton_2_clicked()
{
    watermarking = QFileDialog::getOpenFileName(this,tr("開啟檔案"),"/","Images(*.png *.jpeg *.jpg)");        //規定選擇的檔名
    wa =watermarking.size()*10;
    water.load(watermarking);
    ui->toolButton_2->setIconSize(QSize(water.width(),water.height()));
    ui->toolButton_2->setIcon(QPixmap::fromImage(water));

}

void Widget::LogicOperator(QImage *src1, QImage *src2, QImage *output)
{
    int i, j;
    int tmpPixel;
    unsigned char *src1Pixel, *src2Pixel;
    src1Pixel = new unsigned char[src1->height()*src1->width()];
    src2Pixel = new unsigned char[src2->height()*src2->width()];
    *output = *src1;

    for(j=0; j< src1->height(); j++)
           for(i=0; i< src1->width(); i++)
           {
           src1Pixel[i + j*src1->width()] =
                   (unsigned char)qGray(src1->pixel(i,j));
       }
       for(j=0; j< src2->height(); j++)
           for(i=0; i< src2->width(); i++)
           {
           src2Pixel[i + j*src2->width()] =
                   (unsigned char)qGray(src2->pixel(i,j));
       }
    for(j=0; j< src2->height(); j++)
                for(i=0; i< src2->width(); i++)
                {
                tmpPixel = ( src1Pixel[i + j*src1->width()]
                             & src2Pixel[i + j*src2->width()] );
                output->setPixel(i, j, qRgb(tmpPixel,tmpPixel,tmpPixel));
                }
                delete [] src1Pixel;
                delete [] src2Pixel;
}


void Widget::on_test_clicked()
{
   // water = water.scaled(QSize(Img.width(),Img.height()));
    LogicOperator(&Img,&water,&add);
    ui->toolButton->setIconSize(QSize(add.width(),add.height()));
    ui->toolButton->setIcon(QPixmap::fromImage(add));
}
