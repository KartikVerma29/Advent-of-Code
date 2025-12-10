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



bool IsInside(vector<double> p, const vector<vector<long long>>& poly) {
    bool inside = false;
    int n = poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        double xi = poly[i][0], yi = poly[i][1];
        double xj = poly[j][0], yj = poly[j][1];
        
        bool intersect = ((yi > p[1]) != (yj > p[1])) &&
                         (p[0] < (xj - xi) * (p[1] - yi) / (yj - yi) + xi);
        if (intersect) inside = !inside;
    }
    return inside;
}

bool edgeRect(vector<long long> p1, vector<long long> p2, long long minX, long long maxX, long long minY, long long maxY) {
    
    auto inRect = [&](vector<long long> pt) { 
        return pt[0] > minX && pt[0] < maxX && pt[1] > minY && pt[1] < maxY; 
    };
    if (inRect(p1) || inRect(p2)) return true;

    double r[4][2] = {{(double)minX, (double)minY}, {(double)maxX, (double)minY}, 
                      {(double)maxX, (double)maxY}, {(double)minX, (double)maxY}};
    
    for(int i=0; i<4; i++) {
        double x3 = r[i][0], y3 = r[i][1];
        double x4 = r[(i+1)%4][0], y4 = r[(i+1)%4][1];
        
        double den = (p1[0]-p2[0])*(y3-y4) - (p1[1]-p2[1])*(x3-x4);
        if(den == 0) continue;
        
        double t = ((p1[0]-x3)*(y3-y4) - (p1[1]-y3)*(x3-x4)) / den;
        double u = -((p1[0]-p2[0])*(p1[1]-y3) - (p1[1]-p2[1])*(p1[0]-x3)) / den;
        
        if (t > 0.0001 && t < 0.9999 && u > 0.0001 && u < 0.9999) return true;
    }
    return false;
}

long long solve(vector<vector<long long>>& Coords) {
    int n = Coords.size();
    long long max_valid_area = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long x1 = Coords[i][0], y1 = Coords[i][1];
            long long x2 = Coords[j][0], y2 = Coords[j][1];

            long long minX = min(x1, x2), maxX = max(x1, x2);
            long long minY = min(y1, y2), maxY = max(y1, y2);
            long long w = maxX - minX, h = maxY - minY;

            if (w == 0 || h == 0) continue;
            long long area = (w + 1) * (h + 1);
            if (area <= max_valid_area) continue;

            if (!IsInside({(minX + maxX) / 2.0, (minY + maxY) / 2.0}, Coords)) continue;

            bool bad = false;
            for (int k = 0; k < n; k++) {
                if (edgeRect(Coords[k], Coords[(k+1)%n], minX, maxX, minY, maxY)) {
                    bad = true; break;
                }
            }
            if (!bad) max_valid_area = area;
        }
    }
    return max_valid_area;
}

int main(){
    ifstream inputFile("input.txt");

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
    cout<<dist[0]<<endl;

   cout<<solve(Coords)<<endl;

    return 0;
}