#include<bits/stdc++.h>
using namespace std;

int main(){
    auto start = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");

    vector<string> input;
    string line;
    while(getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    vector<vector<long long>> range;
    vector<long long> ingredient;
    bool flag=false;

    for(string s:input){
        if(s=="@"){
            flag = true; continue;
        }

        if(flag){
            long long val = stoll(s);
            ingredient.push_back(val);
        }else{
            int pos = s.find('-',0);
            string s1 = s.substr(0,pos);
            string s2 = s.substr(pos+1);
            long long a = stoll(s1);
            long long b = stoll(s2);
            range.push_back({a, b});
        }

    }

    sort(ingredient.begin(), ingredient.end());

    // merge Range overlapping

    int n = range.size();
    vector<vector<long long>> temp;
    sort(range.begin(), range.end());

    for(int i=0; i<n; i++){
        if(temp.empty()){
            temp.push_back(range[i]);
            continue;
        }

        if(range[i][0] <= temp.back()[1]){
            temp.back()[1] = max(temp.back()[1], range[i][1]);
        }else temp.push_back(range[i]);
    }

    range = temp;
    temp.clear();

    int ans=0;
    int i=0, j=0;
    n=range.size();
    int m = ingredient.size();

    while(i<n && j<m){
        auto r = range[i];
        auto p = ingredient[j];

        if(r[0]<=p && p<=r[1]){
            ans++;
        }else if(r[1]<p){
            i++;
            continue;
        }
        j++;
    }

    long long ans1=0;

    for(auto r:range){
        ans1+=(r[1]-r[0]+1);
    }

    cout<<ans<<endl;
    cout<<ans1<<endl;
    auto end=chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end-start;
    cout<<1000*duration.count();
    return 0;
}