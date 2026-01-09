#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <climits>

using namespace std;

struct Machine {
    int num_lights;
    vector<vector<int>> light_to_buttons;
    vector<long long> joltage;
};

long long min_presses;

void solve(int light_idx, const Machine& m, vector<long long>& counts, long long current_sum) {
    if (current_sum >= min_presses) return;

    if (light_idx == m.num_lights) {
        min_presses = min(min_presses, current_sum);
        return;
    }

    long long current_val = 0;
    vector<int> unset;
    
    for (int btn : m.light_to_buttons[light_idx]) {
        if (counts[btn] != -1) current_val += counts[btn];
        else unset.push_back(btn);
    }

    long long rem = m.joltage[light_idx] - current_val;
    if (rem < 0) return;

    if (unset.empty()) {
        if (rem == 0) solve(light_idx + 1, m, counts, current_sum);
        return;
    }

    int target_btn = unset[0];
    for (long long val = 0; val <= rem; ++val) {
        counts[target_btn] = val;
        solve(light_idx, m, counts, current_sum + val);
        counts[target_btn] = -1;
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) return 1;

    vector<string> lines;
    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    inputFile.close();

    long long total_result = 0;
    int n;
    int m;
    cin>>n>>m;
    int machinec_no=n;
    vector<Machine> Factory;
    for (int i=n; i<=m; i++) {
        string s = lines[i];
        Machine m;
        int p1 = s.find('[');
        int p2 = s.find(']');
        m.num_lights = p2 - p1 - 1;
        m.light_to_buttons.resize(m.num_lights);
        
        int p3 = s.find('{');
        int p4 = s.find('}');
        string joltStr = s.substr(p3 + 1, p4 - p3 - 1);
        stringstream ss(joltStr);
        string seg;
        while (getline(ss, seg, ',')) m.joltage.push_back(stoll(seg));
        
        string actStr = s.substr(p2 + 1, p3 - p2 - 1);
        int btn_idx = 0;
        for (int i = 0; i < actStr.length(); ++i) {
            if (actStr[i] == '(') {
                int end = actStr.find(')', i);
                string content = actStr.substr(i + 1, end - i - 1);
                stringstream ss2(content);
                string val;
                while (getline(ss2, val, ',')) {
                    if (!val.empty()) {
                        int l_idx = stoi(val);
                        if (l_idx < m.num_lights) {
                            m.light_to_buttons[l_idx].push_back(btn_idx);
                        }
                    }
                }
                btn_idx++;
                i = end;
            }
        }
        Factory.push_back(m);
    }
    
    for (const auto& mach : Factory) {
        min_presses = LLONG_MAX;
        cout<<"Done Machine: "<<machinec_no<<endl;
        machinec_no++;
        int btn_count = 0;
        for(const auto& vec : mach.light_to_buttons) {
             for(int b : vec) btn_count = max(btn_count, b + 1);
        }
        
        vector<long long> counts(btn_count, -1);
        
        solve(0, mach, counts, 0);

        if (min_presses != LLONG_MAX) total_result += min_presses;
    }


    cout << total_result << endl;
    cin>>n;
    return 0;
}