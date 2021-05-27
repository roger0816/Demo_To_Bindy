#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "CClassA.h"
#include <QTime>
#include <QLabel>
#include <QDebug>
#include <QRandomGenerator>
#include <QButtonGroup>
#include <QAbstractButton>
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

    QStringList m_showOutput;

    void refreshPoker();

    QButtonGroup m_listBtn;

private slots:
    void on_btnAddSort_clicked();

    void on_btnSortClear_clicked();

    void on_btnPkAdd_clicked();

    void on_btnPkClear_clicked();

    void on_btnAny_clicked();

    void btnChangeCard(int iId);


    void on_cbColor_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
