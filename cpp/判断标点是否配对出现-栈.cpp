#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main(void)
{
    bool judge = false;
    stack <int> SqStack;
    string str;
    char tempCh;
    cout<<"请输入表达式："<<endl;
    getline(cin,str);
    int n =str.size();

    for(int i=0;i<n;i++){
        if(str[i]=='{'||str[i]=='['||str[i]=='('){
            SqStack.push(str[i]);
        }

        else if(str[i]=='}'){
            if(SqStack.empty()){
                judge = false;
            }
            else if(tempCh=SqStack.top(),tempCh=='{'){
                SqStack.pop();
                judge = true;
            }
            else{
                judge = false;
            }
        }

        else if(str[i]==']'){
            if(SqStack.empty()){
                judge = false;
            }
            else if(tempCh=SqStack.top(),tempCh=='['){
                SqStack.pop();
                judge = true;
            }
            else{
                judge = false;
            }
        }

        else if(str[i]==')'){
            if(SqStack.empty()){
                judge = false;
            }
            else if(tempCh=SqStack.top(),tempCh=='('){
                SqStack.pop();
                judge = true;
            }
            else{
                judge = false;
            }
        }
    }
    if(SqStack.empty()){
        judge = true;
    }
    else{
        judge = false;
    } 

    if(judge){
        cout<<"表达式中括号配对出现";
    }
    else{
        cout<<"表达式中括号不匹配";
    }

    return 0;
}