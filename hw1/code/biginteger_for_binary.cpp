#include <iostream>
#include <string>

#include "biginteger_for_binary.h"

using namespace std;

inline int max(int a, int b) { return (a > b)? a : b; }

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

bool BigInteger::iseven() const
{
    return ((number[0] % 2 == 0) ? 1 : 0);
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

const BigInteger BigInteger::operator*(const BigInteger& bi) const
{
    BigInteger newbi;
    
    if (bi.iszero() || this->iszero())
        return newbi;

    for (int i = 0; i < bi.digit; i++)
    {
        int CarryIn = 0, CarryOut = 0;
        for (int j = 0; j <= digit; j++)
        {
            CarryIn = CarryOut;
            int ans = newbi.number[i+j] + (number[j]*bi.number[i]) + CarryIn;
            newbi.number[i+j] = (ans % 10);
            CarryOut = ans / 10;
        }
    }
    int DigitToCheck = bi.digit + digit;
    newbi.digit = (newbi.number[DigitToCheck - 1] == 0) ? (DigitToCheck - 1) : (DigitToCheck); 
    
    return newbi;
}

BigInteger& BigInteger::operator*=(int a)
{

    if (a == 0)
    {
        initStatus();
        return *this;
    }
        
    BigInteger newbi;
    int i = 0;
    while (a > 0)
    {
        int ToMultiple = a % 10;

        int CarryIn = 0, CarryOut = 0;
        for (int j = 0; j <= digit; j++)
        {
            CarryIn = CarryOut;
            int ans = newbi.number[i+j] + (number[j]*ToMultiple) + CarryIn;
            newbi.number[i+j] = (ans % 10);
            CarryOut = ans / 10;
        }

        a /= 10;
        i++;
    }
    int DigitToCheck = i + digit;
    newbi.digit = (newbi.number[DigitToCheck - 1] == 0) ? (DigitToCheck - 1) : (DigitToCheck); 
    *this = newbi;

    return *this;
}

BigInteger& BigInteger::operator/=(int a)
{
    BigInteger newbi;

    int remain = 0;
    for (int i = digit - 1; i >= 0; i--)
    {
        newbi.number[i] = (remain*10 + number[i]) / a; 
        remain = (remain*10 + number[i]) % a;
    }

    newbi.digit = (newbi.number[digit - 1] == 0) ? (digit - 1) : (digit);
    *this = newbi;

    return *this;

}

BigInteger& BigInteger::operator=(const BigInteger& bi)
{
    this->digit = bi.digit;
    for (int i = 0; i < 256; i++)
        this->number[i] = bi.number[i];
    return *this;
}
