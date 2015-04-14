
#include "biginteger_for_euclid.h"

#include <iostream>

using namespace std;

int main(void)
{
    string sa, sb;
    cin >> sa >> sb;
    BigInteger a(sa), b(sb);
    BigInteger c = a%b;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    return 0;
}

