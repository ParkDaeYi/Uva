//Uva 제출하지마세요
//타임에러뜹니다~~ 과제용이에요
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#define MAX_N 50001
using namespace std;
ifstream fin;
ofstream fout;

int n, m, parent[MAX_N], color[MAX_N], e_cnt, c_cnt, used[MAX_N], used2[MAX_N];
unordered_map<int, int> mp;
bool flag = 0;

int getParent(int x) {
	if (x == 0 || used[x]) return x;
	used[x]++;
	return x = getParent(parent[x]);
}

int getParent2(int x) {
	if (x == 0 || used2[x]) return 0;
	if (used[x]) return x;
	used2[x]++;
	return x = getParent2(parent[x]);
}

int dist(int x, int v, int cnt = 0) {
	if (x == 0) return 0;
	if (x == v) return cnt;
	return dist(parent[x], v, cnt + 1);
}

int main() {
	fin.open("p11994.inp");
	fout.open("p11994.out");
	ios_base::sync_with_stdio(0);
	fin.tie(0); fout.tie(0);

	while ((fin >> n >> m)) {
		for (int i = 1;i < n + 1;++i) fin >> parent[i];
		for (int i = 1, x;i < n + 1;++i) {
			fin >> x;
			if (!parent[i]) continue;
			color[i] = x;
		}
		while (m--) {
			int op, x, y, z;
			fin >> op;
			if (op == 1) {
				fin >> x >> y >> z;
				if (x == y) continue;
				bool isParent = 0;
				int tmp_y = y;
				while (tmp_y) {
					if (x == parent[tmp_y]) {
						isParent = 1;
						break;
					}
					tmp_y = parent[tmp_y];
				}
				if (isParent) continue;
				parent[x] = y;
				color[x] = z;
			}
			else if (op == 2) {
				fin >> x >> y >> z;
				if (!parent[x] && !parent[y]) continue;		
				fill(used, used + MAX_N, 0);
				fill(used2, used2 + MAX_N, 0);
				int op1 = getParent(x);
				int op2 = getParent2(y);
				int tmp_x = x, tmp_y = y;
				if (!op2) continue;		
				while (x != op2) {
					color[x] = z;
					x = parent[x];
				}
				while (y != op2) {
					color[y] = z;
					y = parent[y];
				}
 			}
			else {	
				fin >> x >> y;
 				if (!parent[x] && !parent[y]) {
					fout << "0 0\n";
					continue;
				}
				fill(used, used + n + 1, 0);
				fill(used2, used2 + n + 1, 0);
				int op1 = getParent(x);
				int op2 = getParent2(y);
				if (!op2) {
					fout << "0 0\n";
					continue;
				}
				mp.clear();
				e_cnt = c_cnt = 0;
				while (x != op2) {
					e_cnt++;
					if (mp.find(color[x]) == mp.end()) mp[color[x]] = 1, c_cnt++;
					x = parent[x];
				}
				while (y != op2) {
					e_cnt++;
					if (mp.find(color[y]) == mp.end()) mp[color[y]] = 1, c_cnt++;
					y = parent[y];
				}
				fout << e_cnt << ' ' << c_cnt << '\n';
			}
		}
	}
	return 0;
}