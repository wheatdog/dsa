#include <cstring>
#include <iostream>

using namespace std;

int HashCode(char *s)
{
    int Result;
    Result = (7 * strlen(s) + 2 * s[0] + 0 * s[strlen(s) - 1])  % 32;
    return Result;
}

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
    char *Keyword[] = {"auto",
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

    int TotalNum = sizeof(Keyword) / sizeof(*Keyword);
    int HashCodeArray[TotalNum];

    cout << "Total Num = " << TotalNum << endl;
    for (int i = 0; i < TotalNum; i++)
    {
        HashCodeArray[i] = HashCode(Keyword[i]);
        cout << Keyword[i] << ": " <<  HashCodeArray[i] << endl;
    }

    int Count = CheckUnique(HashCodeArray);
    if (Count == 0)
    {
        cout << "Nice HashCode!" << endl;
    }
    else
    {
        cout << ":( " << Count << endl;
    }

    return 0;
}
