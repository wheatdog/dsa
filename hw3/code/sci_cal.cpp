#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <stack>

int main()
{
    string Express;
    vector<string> PostfixExpress;

    while (getline(cin, Express))
    {
        ToPostfix(Express, PostfixExpress);
       
        int Result = Calulate(PostfixExpress);

        ShowPostfix(PostfixExpress, "Postfix Exp:");
        cout << "Result: " << Result << endl;

        PostfixExpress.clear();
    }

    return 0;
}
