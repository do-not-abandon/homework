#include <iostream>
#include <vector>
#include <unordered_map>//哈希表的头文件

int main(void)
{
    using namespace std;
    
    int size;
    cout<<"请输入一个数表示数组中数的个数：";
    cin>>size;

    vector<int> nums(size);
    for(int i=0;i<size;i++){
        cout<<"请输入第"<<i+1<<"个数字：";
        cin>>nums[i];
    }

    int target;
    cout<<"请输入你想要的两数之和：";
    cin>>target;

    unordered_map<int,int>haxi_map;//声明一个哈希表

    for(int j=0;j<size;j++){
        auto it=haxi_map.find(target-nums[j]);
        if(it != haxi_map.end()) {
            cout << "找到了两个数：" << it->first << " 和 " << nums[j] << " 它们的索引分别是: " << it->second << " 和 " << j << endl;
        }
        haxi_map[nums[j]]=j;
    }
    return 0;
}