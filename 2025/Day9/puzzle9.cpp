#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

vector<long long> areas(vector<vector<long long>>& Coords){
    int n=Coords.size();
    vector<long long> ans;
    for(int i=0; i<n; i++){
        long long x1 = Coords[i][0];
        long long y1 = Coords[i][1];
        for(int j=0; j<n; j++){
            if(i==j) continue;
            long long x2 = Coords[j][0];
            long long y2 = Coords[j][1];
            if(x1-x2==0 || y1-y2==0) continue;

            long long area = abs(x2-x1+1)*abs(y2-y1+1);

            ans.push_back(area);
        }
    }
    return ans;
}



int main(){
    ifstream inputFile("example.txt");

    vector<string> input;
    string line;
    while(getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    vector<vector<long long>> Coords;
    for(string it:input){
        int pos = it.find(',');
        string s1 = it.substr(0, pos);
        long long x = stoll(s1);
        s1 = it.substr(pos+1, it.size()-pos);
        long long y = stoll(s1);
        Coords.push_back({x,y});
    }

    vector<long long> dist = areas(Coords);
    sort(dist.begin(), dist.end(), greater<long long>());
    cout<<dist[0];

   

    return 0;
}