#ifndef BIGINTEGER_FOR_EUCLID

#define BIGINTEGER_FOR_EUCLID

#include <string>
#include <iostream>

class BigInteger{

    int number[256];
    int digit;

    void initStatus();
    BigInteger Lshift(int);


    public:
    BigInteger();
    BigInteger(const int&);
    BigInteger(const std::string&);
    BigInteger(const BigInteger&);

    bool operator<(const BigInteger&) const;
    const BigInteger operator%(const BigInteger&) const;
    const BigInteger operator-(const BigInteger&) const;
    BigInteger& operator=(const BigInteger&);
    bool iszero() const;

    friend std::ostream& operator<<(std::ostream&, const BigInteger&);

};


#endif
