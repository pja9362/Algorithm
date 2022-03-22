#include <iostream>
#include <string>
#include <stack>
using namespace std;


// 연산자 우선순위
// 1. )
// 2. */
// 3. +-
// 4. ( 시작괄호의 경우, 가장낮은 우선순위지만 대소상관없이 무조건 스택에 삽입. (예외적)
enum OPERAND { PLUS=1, MINUS=1, PRODUCT=2, DIVIDE=2, LEFT_BRAKET=0, RIGHT_BRAKET=3};

/*-----메인 함수들-----*/
void NumFormulaChange(string& s);
void ChangePostFix(string& inputStr, string& outputStr, stack<string>& opStack);
int Calculator(string& outputStr, stack<int> calcStack);
/*-----부가적인 함수들-----*/
string CharToString(char c);
int GetOperand(char s);
int GetOperand(string s);
int Calc(string& inputStr, string& outputStr, stack<string> opStack, stack<int> calcStack);

int main()
{
    
    string inputStr;
    string outputStr;
    stack<string> opStack;
    stack<int> calcStack;
    int answer = 0;

    cout << "수식을 입력해주세요." << endl;
    cin >> inputStr;

    answer = Calc(inputStr, outputStr, opStack, calcStack);
    
    cout<< answer <<endl;
    
    
}
// 입력받은 수식으로 계산을 시작합니다.
int Calc(string& inputStr, string& outputStr, stack<string> opStack, stack<int> calcStack)
{
    NumFormulaChange(inputStr);
    ChangePostFix(inputStr, outputStr, opStack);

    return Calculator(outputStr, calcStack);
}

// 단일문자형을 스트링으로 변환.
string CharToString(char c)
{
    string str(1, c);
    return str;
}
// char to Operand
int GetOperand(char s)
{
    int op = s;
    switch (op)
    {
    case 40:
        op = LEFT_BRAKET;
        break;
    case 41:
        op = RIGHT_BRAKET;
        break;
    case 42:
        op = PRODUCT;
        break;
    case 43:
        op = PLUS;
        break;
    case 45:
        op = MINUS;
        break;
    case 47:
        op = DIVIDE;
        break;
    }
    return op;
}
//string to Operand
int GetOperand(string s)
{
    int op = s[0];
    switch (op)
    {
    case 40:
        op = LEFT_BRAKET;
        break;
    case 41:
        op = RIGHT_BRAKET;
        break;
    case 42:
        op = PRODUCT;
        break;
    case 43:
        op = PLUS;
        break;
    case 45:
        op = MINUS;
        break;
    case 47:
        op = DIVIDE;
        break;
    }
    return op;
}
// 입력받은 수식을 계산하여 int형 값으로 돌려줍니다.
int Calculator(string& outputStr, stack<int> calcStack)
{
    int tot = 0;
    int idx = 0;
    while (outputStr[idx] != '\0')
    {
        if ((outputStr[idx] == '+') ||
            (outputStr[idx] == '-') ||
            (outputStr[idx] == '*') ||
            (outputStr[idx] == '/')
            )
        {
            switch (outputStr[idx])
            {
            case 42: // * 곱하기.
                if (calcStack.size() >= 2)
                {
                    int num2 = calcStack.top();
                    calcStack.pop();
                    int num1 = calcStack.top();
                    calcStack.pop();

                    calcStack.push(num1 * num2);
                }
                break;
            case 43: // + 더하기.
                if (calcStack.size() >= 2)
                {
                    int num2 = calcStack.top();
                    calcStack.pop();
                    int num1 = calcStack.top();
                    calcStack.pop();

                    calcStack.push(num1 + num2);
                }
                break;
            case 45: // - 빼기.
                if (calcStack.size() >= 2)
                {
                    int num2 = calcStack.top();
                    calcStack.pop();
                    int num1 = calcStack.top();
                    calcStack.pop();

                    calcStack.push(num1 - num2);
                }
                break;
            case 47: // / 나누기.
                if (calcStack.size() >= 2)
                {
                    int num2 = calcStack.top();
                    calcStack.pop();
                    int num1 = calcStack.top();
                    calcStack.pop();

                    calcStack.push(num1 / num2);
                }
                break;
            }
            idx++;
        }
        else
        {
            int cnt = idx;
            while (outputStr[cnt] != '.')
            {
                cnt++;
            }
            string tmp = outputStr.substr(idx, cnt - idx);
            calcStack.push(stoi(tmp));
            idx += cnt - idx + 1;
        }
    }

    // 수식 계산이 완료 되었다.
    tot = calcStack.top();
    calcStack.pop();

    return tot;
}

//입력받은 수식을 후위표현식으로 바꾼다.
void ChangePostFix(string& inputStr, string& outputStr, stack<string>& opStack)
{
    int idx = 0;
    while (inputStr[idx] != '\0')
    {   
        //현재 inputStr 에서 읽어들인 연산자 (※ 연산자 비교시에만 쓰입니다. )
        int curOperand = 0;
        
        // 연산자 또는 괄호인 경우. (※ string 에서 첨자로 데이터접근시, char type으로 된다.)
        if ((inputStr[idx] == '+') ||
            (inputStr[idx] == '-') ||
            (inputStr[idx] == '*') ||
            (inputStr[idx] == '/') ||
            (inputStr[idx] == '(') ||
            (inputStr[idx] == ')'))
        {
            curOperand = GetOperand(inputStr[idx]);
                
            if (curOperand == LEFT_BRAKET) 
            {
                //예외적으로 '(' 연산자는, 스택에 바로 push() 한다.
                opStack.push(CharToString(inputStr[idx]));
            }
            else if (curOperand == RIGHT_BRAKET)
            {
                // 닫는 중괄호')'를 발견하면, 
                // 현재 스택에서 시작 괄호'('를 만날때까지 pop() 한다.
                // 시작, 닫는 괄호는 전부 버리고, 다른 연산자의 경우 outputStr에 저장.
                while ((opStack.size() > 0) && (opStack.top() != CharToString('(')))
                {
                    // +, -, *, / 연산자의 경우 outputStr에 저장.
                    outputStr += opStack.top();
                    opStack.pop();
                }
                // while 종료후, 닫는괄호')' 도 버린다.
                if (opStack.size() > 0)
                    opStack.pop();
            }
            else if (opStack.empty())
            {
                opStack.push(CharToString(inputStr[idx]));
            }
            else if (curOperand > GetOperand(opStack.top()))
            {
                opStack.push(CharToString(inputStr[idx]));
            }
            else if (curOperand <= GetOperand(opStack.top()))
            {
                do
                {
                    outputStr += opStack.top();
                    opStack.pop();
                    if (opStack.empty())
                        break;
                } while ((curOperand <= GetOperand(opStack.top())) != true);
                
                opStack.push(CharToString(inputStr[idx]));
            }
            idx++;    
        }
        else // 숫자인 경우, outputStr에 저장.
        {
            /*
             숫자의 경우, 자릿수별로 토큰을 나누어야한다.
             현재 첨자에서 숫자가 발견됬으니, 연산자를 만나기전까지 계속 읽어들여
             증가한 cnt 값을 idx 에서 빼주면, 숫자의 자릿수 크기를 구할 수 있다.
             이 값으로 subString 하여 outputStr에 저장한다. 그리고 숫자별 구분점 '.' 을
             추가해준다.
            */
            int cnt = idx;
            while ((inputStr[cnt] != '+') &&
                (inputStr[cnt] != '-') &&
                (inputStr[cnt] != '*') &&
                (inputStr[cnt] != '/') &&
                (inputStr[cnt] != '(') &&
                (inputStr[cnt] != ')') &&
                inputStr[cnt] != '\0')
            {
                cnt++;
            }
            outputStr += inputStr.substr(idx, cnt - idx);
            outputStr += CharToString('.');
            idx += cnt - idx;
        }
        
    }

    //모든 토큰화가 끝나고나서 스택에 남아있는 연산자를 전부 넣는다.
    while (opStack.size() > 0)
    {
        outputStr += opStack.top();
        opStack.pop();
    }
}

//입력받은 수식에서 음수 -N 꼴을 (0-N) 꼴로 바꾼다.
void NumFormulaChange(string& s)
{
    int idx = 0;
    while (s[idx] != '\0')
    {
        // 입력받은 string의 첫 원소가 '-' 인가?
        if (s[0] == '-')
        {
            s.insert(0, "(0");
            // 삽입 후, 내부 idx 에 밀려난 만큼 더해준다.
            int j = 0 + 4;
            while ((s[j] != '\0') &&
                (s[j] != '*') &&
                (s[j] != '/') &&
                (s[j] != '+') &&
                (s[j] != '-') &&
                (s[j] != '(') &&
                (s[j] != ')'))
            { 
                j++;
            }
            s.insert(j, ")"); // 종료괄호를 삽입.
        }
        else if ((s[idx] == '*') ||
            (s[idx] == '/') ||
            (s[idx] == '+') ||
            (s[idx] == '('))
        {
            // 연산자 발견후, 다음 위치에 '-'가 발견되면 -N 의 음수를 (0-N) 형태로 바꾸어준다.
            if (s[idx + 1] == '-')
            {   // minus 가 발견된 지점에 "(0" 삽입.
                s.insert(idx + 1, "(0");
                // 삽입 후, 내부 idx 에 밀려난 만큼 더해준다.
                int j = idx + 4;
                while ((s[j] != '\0') &&
                    (s[j] != '*') &&
                    (s[j] != '/') &&
                    (s[j] != '+') &&
                    (s[j] != '-') &&
                    (s[j] != '(') &&
                    (s[j] != ')'))
                { // 위에 언급된 연산자중에 하나라도 일치하는게 있다면 break;
                    j++;
                }
                s.insert(j, ")"); // 종료괄호를 삽입.
            }
        }
        idx++;
    }
}