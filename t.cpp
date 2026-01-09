#include<iostream>
#include<vector>
using namespace std;

int main(){

    vector<int> nums = {1,0,1,1};
    int k=1;
    int i=0, n=nums.size();
        while(i<n){
            int j=i;
            while(abs(i-j)<=k && j<n){
                if(i!=j && nums[i]==nums[j]) cout<<"True";
                j++;
            }
            i++;
        }
    cout<<"False";

    return 0;
}