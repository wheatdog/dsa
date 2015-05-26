#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "1_6_perfect_hashfunction.cpp"

struct Pair {
    int code;
    int id;
};

bool compare (Pair i, Pair j) { return (i.code < j.code); }

int CheckUnique(int *array)
{
    int Count = 0;
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < i; j++)
            if (array[j] == array[i])
                Count++;
    return Count;
}

int main()
{
    string Keyword[] = {"auto",
                       "break",
                       "case", "char", "const", "continue",
                       "default", "do", "double",
                       "else", "enum", "extern",
                       "float", "for",
                       "goto",
                       "if", "int",
                       "long", 
                       "register", "return",
                       "short", "signed", "sizeof", "static", "struct", "switch",
                       "typedef",
                       "union", "unsigned",
                       "void", "volatile",
                       "while"};

    int TotalNum = 32;
    vector<Pair> HashCodeArray(TotalNum);

#if 0
    cout << "Total Num = " << TotalNum << endl;
#endif
    for (int i = 0; i < TotalNum; i++)
    {
        HashCodeArray[i].code = HashCode(Keyword[i]);
        HashCodeArray[i].id = i;
    }

    sort(HashCodeArray.begin(), HashCodeArray.end(), compare);

    for (int i = 0; i < TotalNum; i++)
    {
        cout << Keyword[HashCodeArray[i].id] << ": " <<  HashCodeArray[i].code << endl;
    }

#if 0
    int Count = CheckUnique(HashCodeArray);
    if (Count == 0)
    {
        cout << "Nice HashCode!" << endl;
    }
    else
    {
        cout << ":( " << Count << endl;
    }
#endif

    return 0;
}
