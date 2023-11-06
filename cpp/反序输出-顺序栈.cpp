#include <iostream>
#include <stack>//堆栈的头文件

using namespace std;

int main()
{
    stack <int> SqStack;//声明一个栈
    int n,m;
    cout<<"请输入一个整数n："<<endl;
    cin>>n;

    while(n<=0){
        cout<<"整数不能为负或为0，请重新输入n:"<<endl;
        cin>>n;
    }

    cout<<"请输入"<<n<<"个整数:"<<endl;
    for(int i=0;i<n;i++){
        cin>>m;
        SqStack.push(m);
    }

    cout<<"按相反顺序输出："<<endl;
    while(!SqStack.empty())
    {
        m=SqStack.top();
        cout<<m<<" ";
        SqStack.pop();
        
    }
}