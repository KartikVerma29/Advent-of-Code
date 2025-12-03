#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

long value(string &s){
    int n=s.size();
    int val=0;
    vector<int> suf(101, -1);

    for(int i=n-1; i>=0; i--){
        int d = s[i]-'0';
        suf[i]=(i==n-1)? d : max(d, suf[i+1]);
    }

    for(int i=0; i<n-1; i++){
        int d1=s[i]-'0';
        int d2=suf[i+1];
        val = max(val, d1*10+d2);
    }

    return val;
}

string value12(const string &s){
    int n=s.size();
    int k=12;
    int rem = n-k;
    vector<char> st;

    for(char c:s){
        while(!st.empty() && rem>0 && st.back() <c){
            st.pop_back();
            rem--;
        }
        st.push_back(c);
    }

    return string(st.begin(), st.begin()+k);

}

long long solve(vector<string>& input){
    long ans=0;

    for(string s:input){
        ans+=value(s);
    }

    long long ans1=0;

    for(string s:input){
        string t=value12(s);
        ans1+= stoll(t);
    }

    return ans1;
}

int main(){
    ifstream inputFile("input.txt");

    vector<string> input;
    string line;
    while(getline(inputFile, line)) input.push_back(line);
    inputFile.close();
    long long ans=solve(input);
    cout<<ans;
    return 0;
}