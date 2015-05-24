#include <cstring>
#include <iostream>
#include <vector>

#define Size(A) sizeof(A) / sizeof(*(A))

const int UP = 20;
const int SOMETHING = 6;

using namespace std;

int HashCode(char *s)
{
    int Result;
    Result = (strlen(s) + s[0] + s[strlen(s) - 1]);
    return Result;
}

#if 0
int Generate(int index, char *Keywords[], bool isUsed[],
             vector<int> &table)
{
    if (index == 26)
        return 1;

    for (int count = 0; count < UP; count++)
    {
        table[index] = count;
        int conflict = 0;
        for (int wordCount = 0; wordCount < 32 && !conflict; wordCount++)
        {
            HashValue = HashCode(Keywords[wordCount], table);
            if (HashValue < 0 || isUsed[HashValue])
                conflict = 1;
        }

        if (!conflict && Generate(index + 1, Keywords, isUsed, table))
            return 1;
    }
}
#endif

void Check(char *Keywords[], int TotalNum)
{
    int start_table[26] = {};
    for (int count = 0; count < TotalNum; count++)
        start_table[Keywords[count][0] - 'a']++;

    int end_table[26] = {};
    for (int count = 0; count < TotalNum; count++)
        end_table[Keywords[count][strlen(Keywords[count]) - 1] - 'a']++;

    for (int count = 0; count < 26; count++)
        cout << (char)('a' + count) << ": " << start_table[count] 
            << "\t" << end_table[count] 
            << "\t" << start_table[count] + end_table[count]<< endl;
    return;
}

int main()
{
    char *Keywords[] = {"else", "enum", "extern",
                       "short", "signed", "sizeof", "static", "struct", "switch",
                       "case", "char", "const", "continue",
                       "default", "do", "double",
                       "union", "unsigned",
                       "float", "for",
                       "register", "return",
                       "void", "volatile",
                       "if", "int",
                       "auto",
                       "break",
                       "goto",
                       "long", 
                       "typedef",
                       "while"};


#if 0

    vector<int> table(26, 0);
    bool isUsed[26] = {};

    cout << Size(Keywords) << endl;
    Check(Keywords, Size(Keywords));

    Generate(0, Keywords, isUsed, table);
    cout << "Generate Success!" << endl;

    for (int i = 0; i < 26; i++)
        cout << table[i] << endl;
#endif

    for (unsigned int i = 0; i < Size(Keywords); i++)
        cout << HashCode(Keywords[i]) << endl;
    return 0;
}
