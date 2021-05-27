#include "CClassA.h"

CClassA::CClassA(QObject *parent) : QObject(parent)
{

}

void CClassA::test1()
{
    qDebug()<<"hello world";
}

QString CClassA::test2(QStringList list)
{

    int iN = list.length();

    for (int i=0; i<iN-1; i++)
    {
        for (int j=0; j<iN-i-1; j++)
        {
            if (list[j].toInt() > list[j+1].toInt())
            {
                QString sTmp = list[j];

                list[j] = list[j+1];

                list[j+1] = sTmp;
            }
        }
    }



    return list.join(" ");
}
