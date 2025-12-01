#include<iostream>
#include<vector>
#include<string>
#include<fstream>
// #include <bits/stdc++.h>

using namespace std;

int part1(vector<string> &input){
    int pointer = 50;
    int ans=0;
    for(int i=0; i<input.size(); i++){
        string s=input[i];
        char op=s[0];
        s.erase(0,1);
        int digit = stoi(s);

        if(op=='L'){
            pointer = (pointer-digit)%100;

        }else{
            pointer = (pointer+digit)%100;
        }
        if(pointer==0)ans++;
    }
    return ans;

}

int part2(vector<string>& input){
    int ans=0;
    int pointer=50;
    for(int i=0; i<input.size(); i++){
        string s=input[i];
        char op=s[0];
        s.erase(0,1);
        int digit = stoi(s);

        if(op=='L'){
            if(pointer-digit<0){
                ans+= abs(pointer-digit)/100;
            }
            pointer = (pointer-digit)%100;

        }else{
            if(pointer+digit>100){
                ans+= (pointer+digit)/100;
            }
            pointer = (pointer+digit)%100;
        }
        if(pointer==0)ans++;
    }

    return ans;
}


vector<long long> solve(vector<string> input){
    int pos = 50;
    long long p1 = 0;
    long long p2 = 0;
    for (int i=0; i<input.size(); i++) {
        string line=input[i];
        char d = line[0];
        int amt = stoi(line.substr(1));

        for (int i = 0; i < amt; i++) {
            if (d == 'L') pos = (pos - 1 + 100) % 100;
            else pos = (pos + 1) % 100;
            if (pos == 0) p2++;
        }
        if (pos == 0) p1++;
    }
    return {p1,p2};
}


int main(){

    ifstream inputFile("input.txt");

    vector<string> input;
    string line;
    while(getline(inputFile, line)) input.push_back(line);
    inputFile.close();

    vector<long long> ans = solve(input);
    cout<<ans[0]<<" "<<ans[1];

    return 0;
}

