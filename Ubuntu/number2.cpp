#include<cstdio>
#include<stack>
#include<string.h>
#include <string>
#include <cstring>

using namespace std;

// Evaluate Postfix expression using Stack
double EvalPostfix(char* postExp)
{
	stack<double> dstack;

    char *p = postExp;
    int len =strlen(p);

    double result;  // value to contain the results of operations
	double op1,op2; 

	while(*p)
	{
        // 1) 숫자인 경우 (number)
		if(isdigit(*p))
		{   
            result = atof(p); // convert type (char* to int)
            dstack.push(result);
            for(;isdigit(*p);p++) {;};
		} 
        // 2) 연산자인 경우 (+ - * /)
        else {
            if((*p=='+')||(*p=='-')||(*p=='*')||(*p=='/'))
            {
                // 피연산자(number) stack에서 number 차례로 pop
                op2 = dstack.top(); dstack.pop();
                op1 = dstack.top(); dstack.pop();

                // Using switch statement to calculate each case according to *p value
                // switch문을 활용하여 연산자에 따라 각각의 연산 수행
                switch(*p)
                {
                    case '+' :
                        dstack.push(op1+op2);
                        p++;
                        break;
                    case '-' :
                        dstack.push(op1-op2);
                        p++;
                        break;
                    case '*' :
                        dstack.push(op1*op2);
                        p++;
                        break;
                    case '/' :
                        dstack.push(op1/op2);
                        p++;
                        break;
                }	
            }
            // 3) 기타 (etc ex. ' '(space))
            else  
                p++;
        }
	}
    // Repeat pop until the stack is empty, and update the result
    if(!dstack.empty()) {
        result = dstack.top(); dstack.pop();
    }
    
	return result;
}

// 연산자간 우선순위 비교
// Compare Priority using operator precedence
int GetPriority(char op)
{
    if (op == '*' || op =='/')
        return 3;
    else if (op == '+' || op =='-')
        return 2;
	else if(op=='(')
		return 1;
    else
        return 0;
}
int ComPriority(char op1, char op2)
{
    int op1_pr = GetPriority(op1);
    int op2_pr = GetPriority(op2);

    if(op1_pr >= op2_pr)
        return 1;
    else    
        return 0;
}

// Convert InfixExp to PostExp
void InfixToPostfix(char *arr, char *convArr) {	
	stack<char> stack;
    
    char *infix = arr; // arr: infix 입력 수식(중위표기식)
    char *postfix = convArr; // convArr: postfix 중위표기식 -> 후위표기식으로 변환
	
    while(*infix) {
        // 1) 숫자인 경우 (number)
        if(isdigit(*infix)) {
            while((isdigit(*infix))) {
                *postfix++ = *infix++;
            } 
            *postfix++ =' '; // 마지막 자리에 공백 추가, 숫자 구분 목적 
        }
        // 2) 연산자인 경우 (operator)
        else if((*infix=='*')||(*infix=='/')||(*infix=='+')||(*infix=='-')) {
            // Compare Priority between top (operator) and *infix (operator)
            while((!stack.empty()) && ComPriority(stack.top(),*infix)) {
                *postfix++ = stack.top(); stack.pop(); // 연산자 우선순위 비교 : 기존 top값이 더 크면 top값 pop 
            }
            stack.push(*infix++); // 연산자 우선순위 비교 : 기존 top값이 더 작으면 바로 push
        }
        // 3) 괄호인 경우 (parenthesis)
        else if (*infix =='(')
            stack.push(*infix++);
        // if *infix value is ')', repeat "pop" until the '(' appears.
        // * 닫는 괄호일 때, 여는 괄호가 나올 때까지 계속 pop
        else if (*infix == ')') {
            while(stack.top()!='('){
                *postfix++ = stack.top(); stack.pop();
			}
			stack.pop(); // just pop '(' 
            *infix++; 
        }
        // 4) 기타 (etc ex. ' '(space))
        else {
            *infix++; // just increase infix value
        }
    }
    // 스택이 빌 때까지 .top()/.pop() 반복 
    // repeat .top()/.pop() until stack is empty
    while(!stack.empty()){
		*postfix++ = stack.top(); stack.pop();
	} 
	*postfix = 0; 
}

int main(int argc, char** argv)
{
    FILE *inputFile = fopen(argv[1], "r");
    if(inputFile == NULL)
        printf("ERROR\n");
	
	char input[100]; // Input : infix expression
	char convExp[100]={0,}; // to contain converted expression (Infix to Postfix)

	double total;   // to contain the results of operations

    fscanf(inputFile, "%s", input);
    fclose(inputFile);
	InfixToPostfix(input, convExp); // call function to convert expression(infix to postfix)

    total = EvalPostfix(convExp);   // call function to evaluate the postfix expression

    FILE *outputFile = fopen(argv[2], "w");
    fprintf(outputFile, "%.2lf", total);    // "%.2lf" to provide result to the second decimal place by rounding off
    fclose(outputFile);

	return 0;
	
}