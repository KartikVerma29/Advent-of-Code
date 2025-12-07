#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

long long solve(const vector<string>& input){
    
    int n = input.size();
    int m = input[0].size();
    vector<vector<long long>> dp(n, vector<long long>(m, 0));

    int sx = 0, sy = 0;
    for (int j = 0; j < m; j++)
        if (input[0][j] == 'S') sy = j;

    dp[0][sy] = 1;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            long long v = dp[i][j];
            if (!v) continue;

            if (input[i][j] == '.' || input[i][j] == '|' || input[i][j] == 'S') {
                dp[i+1][j] += v;
            }

            if (input[i][j] == '^') {
                if (j-1 >= 0) dp[i+1][j-1] += v;
                if (j+1 < m) dp[i+1][j+1] += v;
            }
        }
    }

    long long ans = 0;
    for (int j = 0; j < m; j++) ans += dp[n-1][j];
    return ans;
}


int main(){

    ifstream inputFile("input.txt");

    vector<string> input;
    string line;
    while(getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    int n=input.size(), m=input[0].size();
    int Sx, Sy;
    vector<pair<int,int>> spliter;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            char c = input[i][j];
            if(c=='S'){Sx=i; Sy=j; }
            if(c=='^') spliter.push_back(make_pair(i,j));
       }
    }

    input[1][Sy]='|';

    for(int i=2; i<n; i++){
        for (int j = 0; j < m; j++){
            char point = input[i][j];
            char above = input[i-1][j];
            if(point == '^'){
                if(above=='|'){
                    if(input[i][j-1]=='.') input[i][j-1]='|';
                    if(input[i][j+1]=='.') input[i][j+1]='|';
                }
            }
            if(above=='|'){
                if(point=='.') input[i][j]='|';
            }
        }
    }
    
    long ans=0;

    for(auto split:spliter){
        int x=split.first;
        int y=split.second;

        if(input[x-1][y]=='|') ans++;

    }
    
    cout<<ans<<endl;
    cout<<solve(input);
    return 0;
}
