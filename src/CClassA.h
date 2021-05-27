#ifndef CCLASSA_H
#define CCLASSA_H

#include <QObject>
#include <QDebug>
#include <QRandomGenerator>

enum _COLOR
{
    _SPADE = 0x400,
    _HEART = 0x300,
       _CLUB = 0x200,
    _DIAMOND = 0x100,
    _SP_S = 0x500,
    _SP_L = 0x600
};

enum _Poker
{
    _2 = 0x002,
    _3 = 0x003,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    _10,
    _J,
    _Q,
    _K,
    _A = 0x00e,
    _S_KING = 0x00f,
    _L_KING = 0x010
};

enum _REPORT
{
    Five =0,    //題目沒提到，暫叫五條
    Royal_Straight_Flush = 1,              //皇家同花順
    Straight_Flush,      //同花順
    Four_of_a_Kind,      //金鋼 ,應該跟鐵支一樣意思
    Full_house,          //葫蘆
    Flush,               //同花
    Straight,            //順子
    Three,
    Two,
    One,
    High
 
};


class CClassA : public QObject
{
    Q_OBJECT
public:
    explicit CClassA(QObject *parent = nullptr);
    //第一題 hello world
    void test1();
    //第二題 排序
    QString test2(QStringList list);
    //第三題、第四題 算牌型、赖子算牌型      規則一樣，差在給不當大小王，所以寫在同一題
    int test3(QList<int> listPoker);


    //隨機生成某張牌 ，-1 為全部
    QList<int> randomCard(int iIdx = -1 ,bool bHasKing = false);

    QList<int> setCardNum(int iIdx, int iValue);

private:

    bool isRoyal(); //大順

    bool isFlush(); //同花

    bool isStraight();//順子

    bool theSameNum(int &iMinCout, int &iMaxCout); //算pair

    bool theSameNum(); //同上，多形

    int m_iKingCount = 0;

    QList<int> m_listData;

signals:

};

#endif // CCLASSA_H
