
#include <iostream>
#include <string>

#include "biginteger_for_euclid.h"

using namespace std;

void BigInteger::initStatus()
{
    for (int i = 0; i < 256; i++)
        number[i] = 0;
    digit = 0;
}

BigInteger::BigInteger()
{
    initStatus();
}

BigInteger::BigInteger(const int& n)
{
    initStatus();

    int input = n;
    while (input != 0)
    {
        number[digit++] = input % 10;
        input /= 10;
    }
    return;
}

BigInteger::BigInteger(const string& s)
{
    initStatus();

    digit = s.length();

    if ((digit == 1) && (s.at(0) == '0'))
    {
        digit = 0;
        return;
    }

    for (int i = 0; i < digit; i++)
    {
        number[digit - i - 1] = s.at(i) - '0';
    }

}

BigInteger::BigInteger(const BigInteger& bi)
{
    digit = bi.digit;
    for (int i = 0; i < 256; i++)
        number[i] = bi.number[i];
}

ostream& operator<<(ostream& os, const BigInteger& bigInt)
{
    if (!bigInt.digit)
    {
        os << 0;
        return os;
    }

    for (int i = bigInt.digit - 1; i >= 0; i--)
        os << bigInt.number[i];

    return os;
}

bool BigInteger::iszero() const { return (digit == 0); }

bool BigInteger::operator<(const BigInteger& bi) const
{
    if (bi.iszero() && this->iszero()) return false;
    else if (digit > bi.digit) return false;
    else if (digit < bi.digit) return true;
    else
    {
        for (int i = digit - 1; i >= 0; i--)
        {
            if (number[i] > bi.number[i]) break;
            else if (number[i] < bi.number[i]) return true;
        }
        return false;
    }
}

BigInteger BigInteger::Lshift(int shift) 
{
    BigInteger newbi;
    newbi.digit = this->digit + shift;

    for (int i = 0; i < this->digit; i++)
        newbi.number[i + shift] = this->number[i];

    return newbi;
}

const BigInteger BigInteger::operator%(const BigInteger& bi) const
{
    BigInteger target(*this);
    BigInteger modBy(bi);

    while (!(target < modBy))
    {
        int shift = (target.digit - modBy.digit);
        BigInteger minusBy =  modBy.Lshift(shift);
        if (target < minusBy)
            minusBy =  modBy.Lshift(shift - 1);
        target = target - minusBy;
    }
    return target;
}

const BigInteger BigInteger::operator-(const BigInteger& bi) const
{
    BigInteger newbi;
    
    int BorrowOut = 0, BorrowIn = 0;
    for (int i = 0; i < max(digit, bi.digit); i++)
    {
        BorrowOut = BorrowIn;
        int ToCheck = number[i] - BorrowOut - bi.number[i];
        if (ToCheck < 0)
        {
            BorrowIn = 1;
            newbi.number[i] = ToCheck + 10;
            continue;
        }
        BorrowIn = 0;
        newbi.number[i] = ToCheck;
    }

    for (int i = max(digit, bi.digit) - 1; i >= 0; i--)
    {
        if (newbi.number[i] != 0)
        {
            newbi.digit = i + 1;
            break;
        }
    }
    return newbi;
}

BigInteger& BigInteger::operator=(const BigInteger& bi)
{
    this->digit = bi.digit;
    for (int i = 0; i < 256; i++)
        this->number[i] = bi.number[i];
    return *this;
}
