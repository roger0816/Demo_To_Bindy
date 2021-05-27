#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);




}

Widget::~Widget()
{
    delete ui;
}

void Widget::refreshPoker()
{
    //4♠	4♥	4♣	4♦	9♥
}


void Widget::on_btnAddSort_clicked()
{
    m_list.append(QString::number(ui->sbSort->value()));

    ui->lbSort->setText(m_func.test2(m_list));
}

void Widget::on_btnSortClear_clicked()
{
    m_list.clear();

    ui->lbSort->clear();
}

void Widget::on_btnPkAdd_clicked()
{

}
