#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "CClassA.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    CClassA m_func;

    QStringList m_list;

    //poker
    QList<QLabel*> m_listLb;

    QList<int> m_listData;

    void refreshPoker();

private slots:
    void on_btnAddSort_clicked();

    void on_btnSortClear_clicked();



    void on_btnPkAdd_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
