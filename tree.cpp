#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 10001
#pragma warning(disable:4996)
using namespace std;

class point {
public:
	int idx, cost, max;
	point(int idx = 0, int c = 0, int m = 0) :idx(idx), cost(c), max(m) {}
};
int t, n, ans;
vector<point> graph[MAX_N];

int dfs(int idx,int cost) {
	int ret = cost;
	for (point& p : graph[idx]) {
		p.max = dfs(p.idx, p.cost);
		ret = max(ret, p.max + cost);
	}
	return ret;
}

int solve(int max, int idx) {
	if (!max) return 0;
	int ret = 0;
	for (point p : graph[idx]) {
		int diff = max - p.max;
		ret += diff + solve(max - p.cost - diff, p.idx);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("tree.inp", "r", stdin);
	freopen("tree.out", "w", stdout);

	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1, a, b;i < n;++i) {
			cin >> a >> b;
			graph[a].push_back(point(i, b));
		}
		dfs(0, 0);
		int max_v = 0;
		for (point p : graph[0]) max_v = max(max_v, p.max);
		cout << solve(max_v, 0) << '\n';
		for (int i = 0;i <= n;++i) graph[i].clear();
	}
	return 0;
}