#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)
#define MAX_N 10001
#define INF 1e9
using namespace std;

int n, c[MAX_N][MAX_N], f[MAX_N][MAX_N], ans;
vector<int> adj[MAX_N];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("flow.inp", "r", stdin);
	freopen("flow.out", "w", stdout);

	cin >> n;
	while (1) {
		int i, j, w;
		cin >> i >> j >> w;
		if (i == -1 && j == -1 && w == -1) break;
		c[i][j] = c[j][i] += w;
		adj[i].push_back(j);
		adj[j].push_back(i);
	}
	int s = 0, e = n - 1;
	while (1) {
		int prev[MAX_N];
		fill(prev, prev + n, -1);
		queue<int> q;
		q.push(s);
		while (!q.empty() && prev[e] == -1) {
			int cur = q.front();
			q.pop();
			for (int nxt : adj[cur]) {
				if (c[cur][nxt] > f[cur][nxt] && prev[nxt] == -1) {
					q.push(nxt);
					prev[nxt] = cur;
					if (nxt == e) break;
				}
			}
		}
		if (prev[e] == -1) break;

		int flow = INF;
		for (int i = e;i != s;i = prev[i])
			flow = min(flow, c[prev[i]][i] - f[prev[i]][i]);
		for (int i = e;i != s;i = prev[i]) {
			f[prev[i]][i] += flow;
			f[i][prev[i]] -= flow;
		}
		ans += flow;
	}
	cout << ans;
	return 0;
}