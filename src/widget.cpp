#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    m_listBtn.addButton(ui->btnCh0,0);

    m_listBtn.addButton(ui->btnCh1,1);

    m_listBtn.addButton(ui->btnCh2,2);

    m_listBtn.addButton(ui->btnCh3,3);

    m_listBtn.addButton(ui->btnCh4,4);

    m_listBtn.addButton(ui->btnSet0,10);

    m_listBtn.addButton(ui->btnSet1,11);

    m_listBtn.addButton(ui->btnSet2,12);

    m_listBtn.addButton(ui->btnSet3,13);

    m_listBtn.addButton(ui->btnSet4,14);

    foreach(QAbstractButton *btn,m_listBtn.buttons())
        btn->hide();

    connect(&m_listBtn,&QButtonGroup::idPressed,this,&Widget::btnChangeCard);


    m_listLb<<ui->lbPk0<<ui->lbPk1<<ui->lbPk2<<ui->lbPk3<<ui->lbPk4;

    foreach(QLabel *lb ,m_listLb)
        lb->hide();


    m_showOutput<<"題目沒提\n暫叫五條";

    m_showOutput<<"皇家\n同花順";

    m_showOutput<<"同花順";

    m_showOutput<<"金剛";

    m_showOutput<<"葫蘆";

    m_showOutput<<"同花";

    m_showOutput<<"順子";

    m_showOutput<<"三條";

    m_showOutput<<"兩對";

    m_showOutput<<"一對";

    m_showOutput<<"高牌";




}

Widget::~Widget()
{
    delete ui;
}


void Widget::refreshPoker()
{


    foreach(QAbstractButton *btn,m_listBtn.buttons())
        btn->setVisible(m_listData.length()==5);

    for(int i=0;i<m_listLb.length();i++)
    {
        if(i<m_listData.length())
        {
            QString sColor="";

            int iCode = m_listData[i];

            m_listLb[i]->setStyleSheet("color:red");

            if(iCode >= _SP_L)
            {
                sColor ="♛";

                m_listLb[i]->setStyleSheet("color:#DAA520");

            }

            else if(iCode >= _SP_S)
            {
                sColor ="♚";

                m_listLb[i]->setStyleSheet("color:#DAA520");

            }

            else if(iCode>= _SPADE )
            {
                sColor ="♠";

                m_listLb[i]->setStyleSheet("color:black");

            }
            else if(iCode >= _HEART)
            {
                sColor ="♥";

            }

            else if(iCode >= _CLUB)
            {
                sColor ="♣";

                m_listLb[i]->setStyleSheet("color:black");

            }

            else// (iCode >= _DIAMOND)
            {
                sColor ="♦";

            }



            int iNum = iCode % 0x100;


            QString sTmpNum = QString::number(iNum);

            if(iNum>10)
            {
                if(iNum == _J)
                {
                    sTmpNum ="J";
                }
                else if (iNum == _Q)
                {
                    sTmpNum ="Q";
                }

                else if (iNum == _K)
                {
                    sTmpNum ="K";
                }

                else if (iNum == _A)
                {
                    sTmpNum ="A";
                }

                else if (iNum == _S_KING)
                {
                    sTmpNum ="\n小王";
                }

                else if (iNum == _L_KING)
                {
                    sTmpNum ="\n大王";
                }


            }


            m_listLb[i]->setText(sColor+sTmpNum);



            m_listLb[i]->show();
        }
        else
        {
            m_listLb[i]->hide();
        }

    }

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
    ui->lbMsg->clear();

    ui->lbOutput->clear();

    int iColor = 0x100 * (ui->cbColor->currentIndex()+1);

    int iNum = ui->cbNum->currentIndex()+2;

    //

    if(ui->cbColor->currentIndex()==4)
    {
        iNum = 0x00f;
    }

    else if(ui->cbColor->currentIndex() == 5)
    {
        iNum = 0x010;
    }
    else {}




    if(m_listData.length()<5)
    {

        if(m_listData.indexOf(iColor+iNum)>=0)
            return ui->lbMsg->setText("牌卡已存在");

        m_listData.append(iColor+iNum);

    }

    if(m_listData.length()>=5)
    {
        QString sOutput =    m_showOutput.at(m_func.test3(m_listData));

        ui->lbOutput->setText(sOutput);

    }

    refreshPoker();

}

void Widget::on_btnPkClear_clicked()
{
    m_listData.clear();

    ui->lbOutput->clear();

    refreshPoker();
}

void Widget::on_btnAny_clicked()
{

    m_listData = m_func.randomCard(-1,ui->cbKing->isChecked());

    QString sOutput = m_showOutput.at(m_func.test3(m_listData));

    ui->lbOutput->setText(sOutput);

    refreshPoker();

}

void Widget::btnChangeCard(int iId)
{
    if(iId<10)
        m_listData = m_func.randomCard(iId,ui->cbKing->isChecked());
    else
    {

        ui->lbMsg->clear();


        int iColor = 0x100 * (ui->cbColor->currentIndex()+1);

        int iNum = ui->cbNum->currentIndex()+2;

        if(ui->cbColor->currentIndex()==4)
        {
            iNum = 0x00f;
        }

        else if(ui->cbColor->currentIndex() == 5)
        {
            iNum = 0x010;
        }
        else {}

        if(m_listData.indexOf(iColor+iNum)>=0)
            return ui->lbMsg->setText("牌卡已存在");

        ui->lbOutput->clear();

        qDebug()<<"change : "<<QString::number(iColor+iNum,16);
        m_listData = m_func.setCardNum(iId%10, iColor+iNum);

    }
    QString sOutput = m_showOutput.at(m_func.test3(m_listData));

    ui->lbOutput->setText(sOutput);

    refreshPoker();
}

void Widget::on_cbColor_currentIndexChanged(int index)
{
    ui->cbNum->setHidden(index==4 || index ==5);
}
