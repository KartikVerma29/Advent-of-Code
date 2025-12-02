#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

bool check(long long a){
    // --------PART 1---------------
    string s = to_string(a);
    int n=s.size();
    string s1=s.substr(0,n/2);
    string s2=s.substr(n/2);

    return s1==s2;
}

bool check2(long long a){
    //-----------PART 2------------

    string s = to_string(a);
    int n=s.size();

    for(int i=1; i<=n/2; i++){
        if(n%i!=0)continue;

        string s1=s.substr(0,i);
        string s2="";        

        int cnt = n/i;
        for (int j = 0; j < cnt; j++)
        {
            s2+=s1;
        }
        if(s2==s)return true;
    }
    return false;
}


long long solve(vector<vector<long long>> &range){
    long long sum=0;

    for(auto ID:range){
        long long a=ID[0];
        long long b=ID[1];

        for(long long i=a; i<=b; i++){
            if(check2(i)) sum+=i;
        }
    }

    return sum;
}


int main(){

    ifstream inputFile("input.txt");

    vector<string> input;
    string line;
    while(getline(inputFile, line)) input.push_back(line);
    inputFile.close();
    
    vector<vector<long long>> range;
    for(int i=0; i<input.size(); i++){
        string t=input[i];
        int pos=t.find("-");
        long long a=stoll(t.substr(0,pos));
        long long b=stoll(t.substr(pos+1));
        range.push_back({a,b});
    }
    
    long long ans=solve(range);
    
    cout<<ans;
    return 0;
}
