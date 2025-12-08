#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

struct D3{
    int x, y, z;
    bool connet=false;
};

long long Distance_3D(D3 a, D3 b){
    long long x = (long long)a.x - b.x;
    long long y = (long long)a.y - b.y;
    long long z = (long long)a.z - b.z;
    return x*x + y*y + z*z;
}

class DSU{
    vector<int> parent, size;
public:
    DSU(int n){
        parent.resize(n);
        size.resize(n);
        for(int i=0; i<n; i++){
            parent[i]=i;
            size[i]=1;
        }
    }

    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }

    void unite(int x, int y) {
        int s1 = find(x);
        int s2 = find(y);
        
        if (s1 != s2) {
            if (size[s1] < size[s2]) {
                parent[s1] = s2;
                size[s2] += size[s1]; 
            } else {
                parent[s2] = s1;
                size[s1] += size[s2]; 
            }
        }
    }

    int getSize(int x) {
        return size[find(x)];
    }

    bool isRoot(int x) {
        return parent[x] == x;
    }
};
bool cmpr(vector<long long> &a,vector<long long> &b){
    return a[2] < b[2]; 
}

int main(){

    ifstream inputFile("input.txt");

    vector<string> input;
    string line;
    while(getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    vector<D3> Coord;
    for(auto it:input){
        int pos1 = it.find(',');
        int pos2 = it.find(',', pos1+1);
        D3 t;
        t.x = stoi(it.substr(0, pos1));
        t.y = stoi(it.substr(pos1+1, pos2-1-pos1));
        t.z = stoi(it.substr(pos2+1));
        Coord.push_back(t);
    }
    
    vector<vector<long long>> edges;
    int n=Coord.size();
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            edges.push_back({i,j, Distance_3D(Coord[i], Coord[j])});
        }
    }

    sort(edges.begin(), edges.end(), cmpr);
    
    DSU dsu(n);
    int limit = min((int)edges.size(), 1000);

    for (int i = 0; i < limit; i++) {
        dsu.unite((int)edges[i][0], (int)edges[i][1]);
    }

    vector<long long> circuitSizes;
    for (int i = 0; i < n; i++) {
        if (dsu.isRoot(i)) {
            circuitSizes.push_back(dsu.getSize(i));
        }
    }

    DSU dsu1(n);
    int cnt = n;
    for(auto edge:edges){
        int u = edge[0];
        int v = edge[1];
        if(dsu1.find(u)!=dsu1.find(v)){
            dsu1.unite(u,v);
            cnt--;
        }

        if(cnt==1){
            long long x1 = Coord[u].x;
            long long x2 = Coord[v].x;
            cout<<x1*x2<<endl;
            break;
        }

    }

    sort(circuitSizes.rbegin(), circuitSizes.rend());

    long long ans = 1;
    for(int i=0; i<min((int)circuitSizes.size(), 3); i++) {
        cout << circuitSizes[i] << " ";
        ans *= circuitSizes[i];
    }
    cout <<ans << endl;

    return 0;
}