#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <stack>

using namespace std;

int GetPrecedence(string& a)
{
    if (a.compare("+") == 0)
        return 0;
    else if (a.compare("-") == 0)
        return 0;
    else if (a.compare("*") == 0)
        return 1;
    else if (a.compare("/") == 0)
        return 1;
    else if (a.compare("U+") == 0)
        return 2;
    else if (a.compare("U-") == 0)
        return 2;
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
        a.compare("sin") == 0 || 
        a.compare("cos") == 0 || 
        a.compare("exp") == 0 || 
        a.compare("log") == 0 || 
        a.compare("sqrt") == 0 || 
        a.compare("pow") == 0 || 
        a.compare("fabs") == 0)
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
        else if (isdigit((*i).at(0)))
            printf("%.6f", atof(i->c_str()));
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
        if (isspace(*It) || *It == ',')
            continue;

        if (isdigit(*It) || *It == '.')
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

                if (isalpha(*It))
                {
                    while (*(++It) != '(')
                        Buf.push_back(*It);
                    --It;
                }

                if (WasOperator)
                {
                    if (*It == '+') 
                        Buf = "U+";
                    else if (*It == '-')
                        Buf = "U-";
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
                    cout << "flush the stack to output until meeting '(' " ;
                    while (Operators.top().compare("(") != 0)
                    {
                        PostfixExpress.push_back(Operators.top());
                        Operators.pop();
                    }
                    Operators.pop();

                    if (isalpha(Operators.top().at(0)))
                    {
                        cout << "and pop function '" << Operators.top() << "' to output";
                        PostfixExpress.push_back(Operators.top());
                        Operators.pop();
                    }
                    cout << endl;

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

void DetermineOperands(stack<double>& NumStack, double& First, double& Second)
{
    Second = NumStack.top();
    NumStack.pop();
    First = NumStack.top();
    NumStack.pop();
    return;
}

double Calulate(vector<string>& PostfixExpress)
{
    stack<double> NumStack;
    for (vector<string>::iterator Pit = PostfixExpress.begin();
            Pit != PostfixExpress.end();
            ++Pit)
    {
        if (isdigit(Pit->front()))
        {
            NumStack.push(atof(Pit->c_str()));
        }
        else
        {
            double First, Second;

            if (Pit->compare("+") == 0)
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
            else if (Pit->compare("pow") == 0)
            {
                DetermineOperands(NumStack, First, Second);
                NumStack.push(pow(First, Second));
            }
            else if (Pit->compare("sin") == 0)
            {
                First = NumStack.top();
                NumStack.pop();
                NumStack.push(sin(First));
            }
            else if (Pit->compare("cos") == 0)
            {
                First = NumStack.top();
                NumStack.pop();
                NumStack.push(cos(First));
            }
            else if (Pit->compare("exp") == 0)
            {
                First = NumStack.top();
                NumStack.pop();
                NumStack.push(exp(First));

            }
            else if (Pit->compare("log") == 0)
            {
                First = NumStack.top();
                NumStack.pop();
                NumStack.push(log(First));
            }
            else if (Pit->compare("sqrt") == 0)
            {
                First = NumStack.top();
                NumStack.pop();
                NumStack.push(sqrt(First));
            }
            else if (Pit->compare("fabs") == 0)
            {
                First = NumStack.top();
                NumStack.pop();
                NumStack.push(fabs(First));
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
       
        double Result = Calulate(PostfixExpress);

        ShowPostfix(PostfixExpress, "Postfix Exp:");
        printf("RESULT: %.6f\n", Result);

        PostfixExpress.clear();
    }

    return 0;
}
