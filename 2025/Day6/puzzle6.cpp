#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<stack>
using namespace std;

long long part1(vector<string> &input){
    vector<long long> operand0;
    vector<long long> operand1;
    vector<long long> operand2;
    vector<long long> operand3;
    vector<char> action;
    
    string s0 = input[0];
    string s1 = input[1];
    string s2 = input[2];
    string s3 = input[3];
    string s4 = input[4];
    
    stringstream a(s0);
    long long temp;
    while(a >> temp) operand0.push_back(temp);
    
    stringstream b(s1);
    while(b >> temp) operand1.push_back(temp);
    
    stringstream ss(s2);
    while(ss >> temp) operand2.push_back(temp);
    
    stringstream d(s3);
    while(d >> temp) operand3.push_back(temp);
    
    stringstream e(s4);
    char c;
    while(e >> c) action.push_back(c);
    
    s0=""; s1=""; s2=""; s3=""; s4="";

    long long ans=0;
    for(int i=0; i<1000; i++){
        char op = action[i];
        long long n1,n2,n3,n0;
        n0=operand0[i];
        n1=operand1[i];
        n2=operand2[i];
        n3=operand3[i];
        long long sum=0;
        if(op=='+'){
            sum = n0+n1+n2+n3;
        }else{
            sum = n0*n1*n2*n3;
        }
        ans+=sum;
    }
    return ans;
}

long long part2(vector<string> &input){
    long long ans=0;

    string s0 = input[0];
    string s1 = input[1];
    string s2 = input[2];
    string s3 = input[3];
    string s4 = input[4];

    int n=s0.size();
    int j=0;
    stack<long long> oprand;
    for(int i=n-1; i>=0; i--){
        j++;
        char val0=s0[i];
        char val1=s1[i];
        char val2=s2[i];
        char val3=s3[i];
        char val4=s4[i];

        if(val0==' ' && val1==' ' && val2==' ' && val3==' ' && val4==' ') continue;

        string nums="";
        if(val0!=' ') nums.push_back(val0);
        if(val1!=' ') nums.push_back(val1);
        if(val2!=' ') nums.push_back(val2);
        if(val3!=' ') nums.push_back(val3);
        oprand.push(stoll(nums));

        if(val4!=' '){
            long long result;

            if(val4=='+')result=0;
            else result=1;

            while(!oprand.empty()){
                long long num=oprand.top(); oprand.pop();
                if(val4=='+'){
                    result+=num;
                }else{
                    result*=num;
                }
            }
            ans+=result;
        }

    }

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
    cout<<part1(input)<<endl;

    cout<<part2(input);
   
    return 0;
}