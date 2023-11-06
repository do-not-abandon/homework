#include <iostream>
#include <vector>
#include <unordered_map>//��ϣ���ͷ�ļ�

int main(void)
{
    using namespace std;
    
    int size;
    cout<<"������һ������ʾ���������ĸ�����";
    cin>>size;

    vector<int> nums(size);
    for(int i=0;i<size;i++){
        cout<<"�������"<<i+1<<"�����֣�";
        cin>>nums[i];
    }

    int target;
    cout<<"����������Ҫ������֮�ͣ�";
    cin>>target;

    unordered_map<int,int>haxi_map;//����һ����ϣ��

    for(int j=0;j<size;j++){
        auto it=haxi_map.find(target-nums[j]);
        if(it != haxi_map.end()) {
            cout << "�ҵ�����������" << it->first << " �� " << nums[j] << " ���ǵ������ֱ���: " << it->second << " �� " << j << endl;
        }
        haxi_map[nums[j]]=j;
    }
    return 0;
}