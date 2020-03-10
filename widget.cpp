#include "widget.h"
#include "ui_widget.h"
#include <QColorDialog>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton->setAutoFillBackground(true);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QColorDialog *dlg = new QColorDialog(this);
    QColor color = dlg->getColor();

    ui->widget_3->setWaterColor(color);
    ui->pushButton->setPalette(QPalette(color));
}

void Widget::on_horizontalSlider_3_sliderMoved(int position)
{

    ui->widget_3->updateValue(position);
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{
    //浪高

    ui->widget_3->setSinA(position*1.0/10);
}

void Widget::on_horizontalSlider_2_sliderMoved(int position)
{
    //频率
    ui->widget_3->setSinAlph(position*0.001);
}

void Widget::on_checkBox_clicked(bool checked)
{
    ui->widget_3->setMoreVision(checked);
}
