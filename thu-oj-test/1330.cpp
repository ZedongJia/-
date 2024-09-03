#include <cstring>
#include <iostream>
#include <map>
#include <stack>
#include <string>

#define isChar(c) ('a' <= c && c <= 'z')
#define isMul(c) (c == '*')
#define isDiv(c) (c == '/')
#define isPlus(c) (c == '+')
#define isMinus(c) (c == '-')
#define isDot(c) (c == '.')
#define isLB(c) (c == '(')
#define isRB(c) (c == ')')
#define isComma(c) (c == ',')

using namespace std;
typedef struct Terminator
{
    char character;
    int position;
} Terminator;

typedef struct Constant
{
    string lexical;
    int position;
} Constant;

map<char, int> priority;
stack<Terminator> operations;
stack<Constant> constants;
string expression;
int expressionIndex = 0;
int outputLine = 1;

void calculate()
{
    Constant rp = constants.top();
    constants.pop();
    Constant lp = constants.top();
    constants.pop();
    char op = operations.top().character;
    operations.pop();
    printf("%c %s %s\n", op, lp.lexical.c_str(), rp.lexical.c_str());
    constants.push({to_string(outputLine), rp.position});
    outputLine++;
}

void parse()
{
    while (expressionIndex < expression.length())
    {
        char ch = expression[expressionIndex];
        if (isChar(ch))
        {
            constants.push({{ch}, expressionIndex});
        }
        else if (isMul(ch) | isDiv(ch) | isPlus(ch) | isMinus(ch))
        {
            while (!operations.empty() && !isLB(operations.top().character) &&
                   priority[operations.top().character] >= priority[ch])
            {
                calculate();
            }
            operations.push({ch, expressionIndex});
        }
        else if (isLB(ch))
        {
            operations.push({ch, expressionIndex});
        }
        else if (isRB(ch))
        {
            while (!operations.empty() && !isLB(operations.top().character) && !isComma(operations.top().character))
            {
                calculate();
            }
            stack<Constant> subExpressions;
            Constant lastSubExpression = constants.top();
            subExpressions.push(constants.top());
            constants.pop();
            while (!isLB(operations.top().character))
            {
                subExpressions.push(constants.top());
                constants.pop();
                operations.pop();
            }
            int lbPosition = operations.top().position;
            operations.pop();
            if (!constants.empty() && lbPosition == constants.top().position + 1)
            {
                // function
                if (!operations.empty() && isDot(operations.top().character))
                {
                    // get function name
                    Constant funName = constants.top();
                    constants.pop();
                    // push instance param
                    subExpressions.push(constants.top());
                    constants.pop();

                    // push instance
                    constants.push(funName);

                    // pop '.'
                    operations.pop();
                }
                printf("%s", constants.top().lexical.c_str());
                constants.pop();
                while (!subExpressions.empty())
                {
                    printf(" %s", subExpressions.top().lexical.c_str());
                    subExpressions.pop();
                }
                printf("\n");
                constants.push({to_string(outputLine), lastSubExpression.position});
                outputLine++;
            }
            else
            {
                constants.push(subExpressions.top());
            }
        }
        else if (isDot(ch))
        {
            operations.push({ch, expressionIndex});
        }
        else if (isComma(ch))
        {
            while (!operations.empty() && !isLB(operations.top().character) && !isComma(operations.top().character))
            {
                calculate();
            }
            operations.push({ch, expressionIndex});
        }
        expressionIndex++;
    }
    while (!operations.empty())
    {
        calculate();
    }
}
int main()
{
    priority['*'] = 2;
    priority['/'] = 2;
    priority['+'] = 1;
    priority['-'] = 1;
    cin >> expression;
    parse();
}