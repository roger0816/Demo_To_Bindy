#ifndef CCLASSA_H
#define CCLASSA_H

#include <QObject>
#include <QDebug>

enum _COLOR
{
    _SPADE = 0x400,
    _HEART = 0x300,
    _DIAMOND = 0x100,
    _CLUB = 0x200
    
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
};

enum _REPORT
{
    Grade = 1,              //皇家同花順
    Straight_Flush,      //同花順
	Four_of_a_Kind,      //金鋼 ? 應該跟鐵支一樣意思
    Full_house,          //葫蘆
    Flush,               //同花
    Straight,            //順子
    Three,
    Tow,
    One,
    High
 
};


class CClassA : public QObject
{
    Q_OBJECT
public:
    explicit CClassA(QObject *parent = nullptr);

    void test1();

    QString test2(QStringList list);

    bool theSameColor(QList<int> list);

    bool minDiffMaxIn5();

    int theSameNum();

signals:

};

#endif // CCLASSA_H
