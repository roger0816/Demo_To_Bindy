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

#if 0  //只求結果
    qSort(list.begin(), list.end());
#else // 手寫泡沫


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

#endif

    return list.join(" ");
}

int  CClassA::test3(QList<int> listPoker)
{


    m_listData = listPoker;

    m_iKingCount = 0;

    if(m_listData.indexOf(0x50f) >=0 )
        m_iKingCount++;

    if(m_listData.indexOf(0x610) >=0 )
        m_iKingCount++;

    int iRe = High;

    int iMinCount,iMaxCount;  //對子 的數量

    bool bHasPairt = theSameNum(iMinCount,iMaxCount);


    if(iMaxCount==5)
    {
        iRe = Five;
    }

    else if(isRoyal())
    {
        iRe = Royal_Straight_Flush;
    }
    else if(isFlush() && isStraight())
    {
        iRe = Straight_Flush;
    }
    else if(iMaxCount==4)
    {
        iRe = Four_of_a_Kind;
    }
    else if(iMaxCount==3 && iMinCount ==2)
    {
        iRe = Full_house;
    }
    else if(isFlush())
    {
        iRe = Flush;
    }

    else if(isStraight())
    {
        iRe = Straight;
    }

    else if(iMaxCount == 3)
    {
        iRe = Three;
    }

    else if(iMaxCount == 2 && iMinCount ==2)
    {
        iRe = Two;
    }
    else if(iMaxCount == 2)
    {
        iRe = One;
    }
    else {}


    qDebug()<<"status : "<<iRe;

    QString sTmp;
    foreach(int i , m_listData)
    {
        sTmp+=" 0x"+QString::number(i,16);

    }

    qDebug()<<sTmp;

    return iRe;
}

QList<int> CClassA::randomCard(int iIdx, bool bHasKing)
{
    int iKingCount = 0;

    if(bHasKing)
    {
        iKingCount = 2;
    }


    if(iIdx == -1)
    {
        m_listData.clear();

        while(m_listData.length()< 5)
        {
            m_listData.append(-1);
        }

    }
    else
    {
        while(m_listData.length()<=iIdx)
        {
            m_listData.append(-1);
        }

        m_listData[qBound(0,iIdx,4)] = -1;
    }


    for(int i=0;i<m_listData.length();i++)
    {

        if(m_listData.at(i)!=-1)
            continue;

        int iCard = -1;

        while(iCard == -1)
        {

            int iRand = QRandomGenerator::global()->bounded(0, 51+iKingCount);

            int iColor = (iRand/13+1)*0x100;

            int iNum = iRand%13+0x02;

            int iTmp = iColor+iNum ;

            if(iRand == 52)
            {
                iTmp = 0x50f;
            }
            else if(iRand == 53)
            {
                iTmp = 0x610;
            }

            if(m_listData.indexOf(iTmp) < 0 )
            {
                iCard = iTmp;
            }

        }


        m_listData[i] = iCard;


    }

    return m_listData;
}

QList<int> CClassA::setCardNum(int iIdx, int iValue)
{
    m_listData[qBound(0,iIdx,m_listData.length()-1)] = iValue;

    return m_listData;
}

bool CClassA::isRoyal()
{
    bool bRe = false;

    if(!isStraight() || !isFlush())
        return bRe;


    if(m_listData.first()%0x100 > _Poker(_10))
    {
        bRe = true;
    }

    return bRe;
}

bool CClassA::isFlush()
{

    bool b = true;

    //補救的機會，大小王任意牌
    int iChance = m_iKingCount;

    int iColor = m_listData.at(0) / 0x100;

    foreach(int iNum,m_listData)
    {

        if(iNum / 0x100 != iColor)
        {

            iChance--;

            if(iChance< 0)
            {
                b = false;

                break;
            }
        }
    }

    return b;

}

bool CClassA::isStraight()
{
    bool bRe = false;

    if(theSameNum())
        return bRe;


    int iDiff = 4 ;  //最大最小落差


    QList<int > listTmp ;

    foreach(int iNum, m_listData)
    {
        if(iNum < 0x500 )  //大小王類不必計算
            listTmp.append(iNum%0x100);
    }

    qSort(listTmp.begin(),listTmp.end());

    if(qAbs(listTmp.last()-listTmp.first()) <= iDiff)
    {
        bRe = true;
    }

    //特殊規則  A 2 3 4 5 6  小順
    if(listTmp.last()==_A && listTmp.at(listTmp.length()-2) == _5)
        bRe = true ;

    return bRe;
}

bool CClassA::theSameNum(int &iMinCout,int &iMaxCout)
{
    bool b = false;

    QMap<int , int > outData;

    for(int i=0;i<m_listData.length();i++)
    {
        outData[m_listData[i]%0x100]++;
    }

    // key 是牌號， value 是數量

    QList<int> listValue  = outData.values();

    qSort(listValue.begin(),listValue.end());


    iMinCout = listValue[qBound(0,listValue.length()-2,listValue.length()-1)];

    iMaxCout = listValue.last() + m_iKingCount;


    return outData.count() < m_listData.length();

}

bool CClassA::theSameNum()
{
    int i,j;

    return theSameNum(i,j);
}
