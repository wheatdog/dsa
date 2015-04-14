#include <iostream>

using namespace std;

struct Gcd {
    int Gcd;
    int NumIteration;
};

inline int min(int a, int b) { return ((a < b) ? a : b); }
inline int max(int a, int b) { return ((a > b) ? a : b); }
inline bool isEven(int a) { return (a % 2 == 0); }
inline bool isOdd(int a) { return (a % 2 != 0); }

Gcd GcdByReverseSearch(int a, int b)
{
    Gcd Result = {};
    for (int i = min(a, b); i > 0; i--)
    {
        Result.NumIteration++;
        if ((a % i == 0) && (b % i == 0))
        {
            Result.Gcd = i;
            return Result;
        }
    }
    return Result;
}

Gcd GcdByFilter(int a, int b)
{
    Gcd Result = {};
    for (int i = 2; i <= min(a, b); i++)
    {
        Result.NumIteration++;
        if ((a % i == 0) && (b % i == 0))
        {
            Gcd FilteredGcd = GcdByFilter(a/i, b/i);
            Result.Gcd = i * FilteredGcd.Gcd;
            Result.NumIteration += FilteredGcd.NumIteration;
            return Result;
        }
    }
    Result.Gcd = 1;
    return Result;
}

Gcd GcdByFilterFasterInternal(int a, int b, int s)
{
    Gcd Result = {};
    for (int i = s; i <= min(a, b); i++)
    {
        Result.NumIteration++;
        if ((a % i == 0) && (b % i == 0))
        {
            Gcd FilteredGcd = GcdByFilterFasterInternal(a/i, b/i, i);
            Result.Gcd = i * FilteredGcd.Gcd;
            Result.NumIteration += FilteredGcd.NumIteration;
            return Result;
        }
    }
    Result.Gcd = 1;
    return Result;
}

Gcd GcdByFilterFaster(int a, int b) { return GcdByFilterFasterInternal(a, b, 2); }

void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
    return;
}

Gcd GcdByBinary(int a, int b)
{
    Gcd Result = {};
    int n = min(a, b);
    int m = max(a, b);
    int ans = 1;

    while ((n != 0) && (m != 0))
    {
        Result.NumIteration++;
        if (isEven(n) && isEven(m))
        {
            ans *= 2;
            n /= 2;
            m /= 2;
        }
        else if (isEven(n) && isOdd(m))
        {
            n /= 2;
        }
        else if (isOdd(n) && isEven(m))
        {
            m /= 2;
        }

        if (n > m)
        {
            swap(n, m);
        }
        m = m - n;
    }

    Result.Gcd = n * ans;
    return Result;
}

Gcd GcdByEuclid(int a, int b)
{
    Gcd Result = {};
    int n = min(a, b);
    int m = max(a, b);

    while (m % n != 0)
    {
        Result.NumIteration++;
        int tmp = n;
        n = m % n;
        m = tmp;
    }

    Result.Gcd = n;
    return Result;
}

int main(void)
{
    int a, b;
    cin >> a;
    while (a != 0)
    {
        cin >> b;

        Gcd GcdRS = GcdByReverseSearch(a, b);
        cout << "Case (" << a << ", " << b << "): GCD-By-Reverse-Search = " << GcdRS.Gcd << ", taking "<< GcdRS.NumIteration <<" iterations" << endl;

        Gcd GcdF = GcdByFilter(a, b);
        cout << "Case (" << a << ", " << b << "): GCD-By-Filter = " << GcdF.Gcd << ", taking " << GcdF.NumIteration << " iterations" << endl;

        Gcd GcdFF = GcdByFilterFaster(a, b);
        cout << "Case (" << a << ", " << b << "): GCD-By-Filter-Faster = " << GcdFF.Gcd << ", taking " << GcdFF.NumIteration << " iterations" << endl;

        Gcd GcdB = GcdByBinary(a, b);
        cout << "Case (" << a << ", " << b << "): GCD-By-Binary = " << GcdB.Gcd << ", taking " << GcdB.NumIteration << " iterations" << endl;

        Gcd GcdE = GcdByEuclid(a, b);
        cout << "Case (" << a << ", " << b << "): GCD-By-Enclid = " << GcdE.Gcd << ", taking " << GcdE.NumIteration << " iterations" << endl;
        cin >> a;
    }

    return 0;
}
