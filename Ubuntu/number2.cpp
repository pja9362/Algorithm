#include<cstdio>
#include<stack>
#include<string.h>
#include <string>
#include <cstring>

using namespace std;

double EvalPostfix(char* postExp)
{
	stack<double> dstack;

    char *p = postExp;
    int len =strlen(p);

    double result;
	double op1,op2;

	while(*p)
	{
		if(isdigit(*p))
		{   
            result =atof(p);
            dstack.push(result);
            printf("result 값 출력 %f\n",  result);
            for(;isdigit(*p);p++) {;};
		} 

        else {
            if((*p=='+')||(*p=='-')||(*p=='*')||(*p=='/'))
            {
                // 피연산자
                op2 = dstack.top(); dstack.pop();
                op1 = dstack.top(); dstack.pop();

                switch(*p)
                {
                    case '+' :
                        // printf("덧셈 결과: %f + %f = %f\n", op1,op2,op1+op2);
                        dstack.push(op1+op2);
                        p++;
                        break;
                    case '-' :
                        // printf("뺄셈 결과: %f\n", op1-op2);
                        dstack.push(op1-op2);
                        p++;
                        break;
                    case '*' :
                        // printf("곱셈 결과: %f x %f = %f\n", op1,op2,op1*op2);
                        dstack.push(op1*op2);
                        p++;
                        break;
                    case '/' :
                        // printf("나눗셈 결과: %f\n", op1/op2);
                        dstack.push(op1/op2);
                        p++;
                        break;
                }	
            }
            else  
                p++;
        }
	}

    if(!dstack.empty()) {
        result = dstack.top(); dstack.pop();
    }
    
	return result;
}

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
        // if *infix value is ')', repeat "pop" until the '(' appears
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
	
	char input[100];
	char convExp[100]={0,};

	double total;

    fscanf(inputFile, "%s", input);
    fclose(inputFile);
	InfixToPostfix(input, convExp);

    total = EvalPostfix(convExp);

    FILE *outputFile = fopen(argv[2], "w");
    fprintf(outputFile, "%.2lf", total);
    fclose(outputFile);

	return 0;
	
}