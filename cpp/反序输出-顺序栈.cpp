#include <iostream>
#include <stack>//��ջ��ͷ�ļ�

using namespace std;

int main()
{
    stack <int> SqStack;//����һ��ջ
    int n,m;
    cout<<"������һ������n��"<<endl;
    cin>>n;

    while(n<=0){
        cout<<"��������Ϊ����Ϊ0������������n:"<<endl;
        cin>>n;
    }

    cout<<"������"<<n<<"������:"<<endl;
    for(int i=0;i<n;i++){
        cin>>m;
        SqStack.push(m);
    }

    cout<<"���෴˳�������"<<endl;
    while(!SqStack.empty())
    {
        m=SqStack.top();
        cout<<m<<" ";
        SqStack.pop();
        
    }
}