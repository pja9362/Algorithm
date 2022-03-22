// global array based stack implementation
#include<iostream>
#include<string>
#define MAX 20
using namespace std;

char stk[20];
int top = -1;

bool isEmpty(){
    return top == -1;
}
bool isFull(){
    return top == MAX - 1;
}

char peek(){
    return stk[top];
}
// Push function here, inserts value in stack and increments stack top by 1
void push(char oper){
    if(isFull())
        cout << "Stack Full!!!!";
   
    else{
        top++;
        stk[top] = oper;
    }
}
// Function to remove an item from stack. It decreases top by 1
char pop(){
    if(isEmpty())
        cout << "Stack Empty!!!!"; 
    else{ 
        char ch = stk[top]; 
        top--; return(ch); 
    } 
    return 0; 
} 
int priority (char alpha)
{ 
    if(alpha == '+' || alpha =='-') 
        return 1; 
    if(alpha == '*' || alpha =='/') 
        return 2; 
    if(alpha == '^') 
        return 3; 

    return 0; 
} 

string convert(string infix) 
{ 
    int i=0; 
    string postfix = ""; 

    while(infix[i]!='\0') 
    { 

        // if operand add to the postfix expression 
        if(infix[i]>='a' && infix[i]<='z'|| infix[i]>='A'&& infix[i]<='Z')          
        {
            postfix += infix[i];
            i++;
        }
        // if opening bracket then push the stack
        else if(infix[i]=='(')
        {
            push(infix[i]);
            i++;
        }
        // if closing bracket encounted then keep popping from stack until 
        // closing a pair opening bracket is not encountered
        else if(infix[i]==')')
        {
            while(stk[top]!='(')
                postfix += pop();
                
            pop();
            i++;
        }
        else            
        {
            while (!isEmpty() && priority(infix[i]) <= priority(peek())){
                postfix += pop();
            }
            push(infix[i]);
            i++;
        }
    }
    while(!isEmpty()){
        postfix += pop();
    }


    cout << "Postfix is : " << postfix; //it will print postfix conversion  
    return postfix;
}
// Note can also use std::string::insert to add to string
// check here - https://www.cplusplus.com/reference/string/string/insert/
// the expression : postfix += infix[i] can also be written as
// postfix.insert(postfix.end(),infix[i]);

int main()
{
    string infix = "((a+(b*c))-d)"; 
    string postfix;
    postfix = convert(infix);
    
    return 0;
}