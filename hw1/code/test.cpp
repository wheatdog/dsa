#include "biginteger_for_binary.h"

#include <iostream>

using namespace std;

int main(void)
{
    string sa, sb, sc;
    cin >> sa >> sb >> sc;
    BigInteger a(sa), b(sb), c(sc);

    cout << a*b - c << endl;

    cout << b << endl;
    return 0;
}

