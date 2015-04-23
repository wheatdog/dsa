#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <stack>

using namespace std;

int GetPrecedence(string& a)
{
    if (a.compare("||") == 0)
        return 0;
    else if (a.compare("&&") == 0)
        return 1;
    else if (a.compare("|") == 0)
        return 2;
    else if (a.compare("^") == 0)
        return 2;
    else if (a.compare("&") == 0)
        return 2;
    else if (a.compare("<<") == 0)
        return 3;
    else if (a.compare(">>") == 0)
        return 3;
    else if (a.compare("+") == 0)
        return 4;
    else if (a.compare("-") == 0)
        return 4;
    else if (a.compare("*") == 0)
        return 5;
    else if (a.compare("/") == 0)
        return 5;
    else if (a.compare("%") == 0)
        return 5;
    else if (a.compare("!") == 0)
        return 6;
    else if (a.compare("~") == 0)
        return 6;
    else if (a.compare("U+") == 0)
        return 6;
    else if (a.compare("U-") == 0)
        return 6;
    else if (a.compare("(") == 0)
        return -1;
    else
        exit(-1);
}

bool LeqPrecedence(string& a, string& b)
{
    if (a.compare("(") == 0 || 
        a.compare("U+") == 0 || 
        a.compare("U-") == 0 || 
        a.compare("!") == 0 || 
        a.compare("~") == 0)
        return 0;
    return (GetPrecedence(a) <= GetPrecedence(b));
}

void ShowPostfix(vector<string>& PostfixExpress, const string& Message)
{
    cout << Message;
    for (vector<string>::iterator i = PostfixExpress.begin();
            i != PostfixExpress.end();
            ++i)
    {
        cout << " ";
        if ((*i).at(0) == 'U')
            cout << (*i).at(1);
        else
            cout << *i;
    }
    cout << endl;

    return;
}

void ShowOprStack(stack<string> Operators)
{
    if (Operators.empty())
        return;

    stack<string> Output;

    while (!Operators.empty())
    {
        Output.push(Operators.top());
        Operators.pop();
    }
    cout << "\tcurrent stack: ";
    while (!Output.empty())
    {
        cout << " ";
        if (Output.top().at(0) == 'U')
            cout << Output.top().at(1);
        else
            cout << Output.top();
       
        Output.pop();
    }
    cout << endl;

    return;
}

void ToPostfix(string& Express, vector<string>& PostfixExpress)
{
    string Buf;
    stack<string> Operators;
    int WasOperator = 1;

    // NOTE: The end of express
    Express.push_back('@');

    cout << "--- postfix expression transforming ---" << endl;
    for (string::iterator It = Express.begin(); It != Express.end(); ++It)
    {
        if (isspace(*It))
            continue;

        if (isdigit(*It))
        {
            Buf.push_back(*It);
            WasOperator = 0;
        }
        else 
        {
            if (Buf.size())
            {
                cout << "encounter " << Buf << ": " << "push to output" << endl;

                PostfixExpress.push_back(Buf);

                ShowPostfix(PostfixExpress, "\tcurrent output:");
                ShowOprStack(Operators);
            }

            Buf = *It;

            if (Buf.compare("@") != 0)
            {
                if (WasOperator)
                {
                    if (*It == '+') 
                        Buf = "U+";
                    else if (*It == '-')
                        Buf = "U-";
                }

                if(*It == '<')
                {
                    Buf = "<<";
                    It++;
                }

                if(*It == '>')
                {
                    Buf = ">>";
                    It++;
                }

                string::iterator PeepNext = It;
                ++PeepNext;
                if ((*It == '&' && *PeepNext == '&') ||
                        (*It == '|' && *PeepNext == '|'))
                {
                    Buf.push_back(*(++It));
                }

                cout << "encounter " << Buf << ": ";

                bool MessageFlag = false;
                if (!Operators.empty() && Buf.compare(")") != 0)
                {
                    while (!Operators.empty() && LeqPrecedence(Buf, Operators.top()))
                    {
                        MessageFlag = true;
                        PostfixExpress.push_back(Operators.top());
                        Operators.pop();
                    }
                    if (MessageFlag)
                    {
                        cout << "stack.top() has greater or the same precdence, after pop something out to output, then push to the stack" << endl;
                    }
                }

                if (Buf.compare(")") != 0)
                {
                    if (!MessageFlag)
                        cout << "push to the stack directly" << endl;

                    Operators.push(Buf);

                    ShowPostfix(PostfixExpress, "\tcurrent output:");
                    ShowOprStack(Operators);
                }
                else
                {
                    cout << "flush the stack to output until meeting '('" << endl;
                    while (Operators.top().compare("(") != 0)
                    {
                        PostfixExpress.push_back(Operators.top());
                        Operators.pop();
                    }
                    Operators.pop();

                    ShowPostfix(PostfixExpress, "\tcurrent output:");
                    ShowOprStack(Operators);
                }

            }

            if (Buf.compare(")") != 0)
                WasOperator = 1;

            Buf.clear();

        }
    }

    cout << "encounter NOTHING: flush the stack to output" << endl;
    while (!Operators.empty())
    {
        PostfixExpress.push_back(Operators.top());
        Operators.pop();
    }

    ShowPostfix(PostfixExpress, "\tcurrent output:");
    cout << "--- postfix expression transforming complete :) ---" << endl;
}

void DetermineOperands(stack<int>& NumStack, int& First, int& Second)
{
    Second = NumStack.top();
    NumStack.pop();
    First = NumStack.top();
    NumStack.pop();
    return;
}

int Calulate(vector<string>& PostfixExpress)
{
    stack<int> NumStack;
    for (vector<string>::iterator Pit = PostfixExpress.begin();
            Pit != PostfixExpress.end();
            ++Pit)
    {
        if (isdigit(Pit->front()))
        {
            NumStack.push(atoi(Pit->c_str()));
        }
        else
        {
            int First, Second;

            if (Pit->compare("||") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First || Second);
            }
            else if (Pit->compare("&&") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First && Second);
            }
            else if (Pit->compare("|") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First | Second);
            }
            else if (Pit->compare("&") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First & Second);
            }
            else if (Pit->compare("<<") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First << Second);
            }
            else if (Pit->compare(">>") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First >> Second);
            }
            else if (Pit->compare("+") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First + Second);
            }
            else if (Pit->compare("-") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First - Second);
            }
            else if (Pit->compare("*") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First * Second);
            }
            else if (Pit->compare("/") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First / Second);
            }
            else if (Pit->compare("%") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(First % Second);
            }
            else if (Pit->compare("!") == 0)
            {
                First = NumStack.top();
                NumStack.pop();
                NumStack.push(!First);
            }
            else if (Pit->compare("~") == 0)
            {
                First = NumStack.top();
                NumStack.pop();
                NumStack.push(~First);
            }
            else if (Pit->compare("U+") == 0)
            {
                // Note: Just do nothing
            }
            else if (Pit->compare("U-") == 0)
            {
                First = NumStack.top();
                NumStack.pop();
                NumStack.push(-First);
            }
        }
    }
    return NumStack.top();
}

int main()
{
    string Express;
    vector<string> PostfixExpress;

    while (getline(cin, Express))
    {
        ToPostfix(Express, PostfixExpress);
       
        int Result = Calulate(PostfixExpress);

        ShowPostfix(PostfixExpress, "Postfix Exp:");
        cout << "RESULT: " << Result << endl;

        PostfixExpress.clear();
    }

    return 0;
}
