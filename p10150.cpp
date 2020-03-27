#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#define MAX 26000
using namespace std;

ifstream fin;
ofstream fout;

int parent[MAX];
vector<string> words[MAX];

bool doublets(string a, string b) {
    int d = 0;
    for (int i = 0; i < a.length(); i++) {
        d += (a[i] != b[i]);
        if (d > 1) return 0;
    }
    return d == 1;
}

void print(int s1, int s2, vector<string> ws) {
    if (s1 != s2) print(s1, parent[s2], ws);
    fout << ws[s2] << '\n';
}

int main() {
    fin.open("p10150.inp");
    fout.open("p10150.out");
    ios_base::sync_with_stdio(0);
    fin.tie(0); fout.tie(0);

    string str1, str2, word;
    while (getline(fin, word) && word.size()) {
        if (words[word.size()].empty()) words[word.size()].push_back("");
        words[word.size()].push_back(word);
    }
    bool first = 0;
    while ((fin >> str1 >> str2)) {
        if (first) fout << '\n';
        first = 1;
        vector<string> str = words[str1.size()];
        int s1 = str.size(), s2 = str.size();
        for (int i = 0;i < str.size();++i) {
            if (!str[i].compare(str1)) {
                s1 = i;
                break;
            }
        }
        for (int i = 0;i < str.size();++i) {
            if (!str[i].compare(str2)) {
                s2 = i;
                break;
            }
        }

        if (str1.size() != str2.size() || s1 == str.size()|| s2 == str.size())
            fout << "No solution." << '\n';
        else {
            fill(parent, parent + MAX, 0);
            parent[s1] = s1;
            queue<int> q;
            q.push(s1);
            while (q.size() && q.front() != s2) {
                int cur = q.front();
                q.pop();
                for (int nxt = 1; nxt < str.size(); nxt++) {
                    if (parent[nxt] || !doublets(str[cur], str[nxt])) continue;
                    parent[nxt] = cur;
                    q.push(nxt);
                }
            }
            if (!parent[s2]) fout << "No solution." << '\n';
            else print(s1, s2, str);
        }
    }
    return 0;
}