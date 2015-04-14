#ifndef BIGINTEGER_FOR_BINARY

#define BIGINTEGER_FOR_BINARY

#include <string>
#include <iostream>

class BigInteger{

    int number[256];
    int digit;

    void initStatus();

    friend std::ostream& operator<<(std::ostream&, const BigInteger&);

    public:

    int getdigit() { return digit; }

    BigInteger();
    BigInteger(const int&);
    BigInteger(const std::string&);
    BigInteger(const BigInteger&);

    bool operator<(const BigInteger&) const;
    const BigInteger operator-(const BigInteger&) const;
    const BigInteger operator*(const BigInteger&) const;
    BigInteger& operator*=(int);
    BigInteger& operator/=(int);
    BigInteger& operator=(const BigInteger&);

    bool iseven() const;
    bool iszero() const;
};


#endif
