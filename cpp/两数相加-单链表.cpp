#include <iostream>

struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x):val(x),next(nullptr){}
};

int main()
{
    using namespace std;
    
    ListNode*head1=nullptr;
    ListNode*tail1=nullptr;
    ListNode*head2=nullptr;
    ListNode*tail2=nullptr;

    int len1,len2;
    cout<<"请输入一个数表示第一个链表的长度：";
    cin>>len1;

    cout<<"请输入第一个链表中的元素:"<<endl;
    for(int i=0;i<len1;i++)
    {
        int value;
        cin>>value;
        if(head1){
            tail1->next=new ListNode(value);
            tail1=tail1->next;
        }else{
            head1=tail1=new ListNode(value);
        }
    }

    cout<<"请输入一个数表示第二个链表的长度：";
    cin>>len2;

    cout<<"请输入第二个链表中的元素:"<<endl;
    for(int i=0;i<len2;i++)
    {
        int value;
        cin>>value;
        if(head2){
            tail2->next=new ListNode(value);
            tail2=tail2->next;
        }else{
            head2=tail2=new ListNode(value);
        }
    }
    
    ListNode*head=nullptr;
    ListNode*tail=nullptr;
    ListNode*current1=head1;
    ListNode*current2=head2;

    int carry=0;
    //两数相加
    while(current1||current2){
        int n1=current1?current1->val:0;
        int n2=current2?current2->val:0;
        int sum=n1+n2+carry;
        if(head){
            tail->next=new ListNode(sum%10);
            tail=tail->next;
        }else{
            head=tail=new ListNode(sum%10);
        }
        carry=sum/10;
        if(current1){
            current1=current1->next;
        }
        if(current2){
            current2=current2->next;
        }
    }
    if(carry>0){
        tail->next=new ListNode(carry);
    }

    // 打印链表
    ListNode*current=head;
    while(current){
        cout<<current->val<<"->";
        current=current->next;
    }
    cout<<"nullptr";

}