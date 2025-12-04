#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;


long solve(vector<vector<char>> &input, int n, int m){
    long ans=0;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            char point = input[i][j];
            if(point!='@') continue;
            
            int val=0;
            for(int r=i-1; r<=i+1; r++){
                for(int c=j-1; c<=j+1; c++){

                    if(r<0 || c<0 || r>=n || c>=m) continue;
                    if(r == i && c == j) continue;
                    char towel=input[r][c];
                    if(towel=='@' || towel=='x') val++;
                }
            }
            if(val<4){
                ans++;
                input[i][j]='x';
            }
        }
    }
    if(ans==0) return -1;
    return ans;
}


int main(){

    ifstream inputFile("input.txt");

    vector<string> input;
    string line;
    while(getline(inputFile, line)) input.push_back(line);
    inputFile.close();

    int n=input.size();
    int m=input[0].size();

    vector<vector<char>> input2D(n, vector<char>(m,'.'));
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            input2D[i][j]=input[i][j];

        }
    }

    // cout<<solve(input2D, n, m); for Part 1, use without Loop, only one iteration
    long ans=0, iter=0;
    while(iter!=-1){
        iter=solve(input2D, n, m);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(input2D[i][j]=='x')input2D[i][j]='.';
            }
        }
        ans+=iter;
    }
    
    cout<<ans;
    return 0;
}