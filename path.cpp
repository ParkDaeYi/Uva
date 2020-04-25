#include <iostream>
#include <cstdio>
#include <algorithm>
#pragma warning(disable:4996)
#define MAX_N 100001
#define MIN -1e9-1
using namespace std;

int pre_order[MAX_N], n, t, in_cost[MAX_N], idx, ans;

int solve(int s, int e) {
	if (s == e) {
		ans = max(ans, in_cost[s]);
		idx++;
		return in_cost[s];
	}
	if (s > e || idx == n) return 0;

	int i = s;
	for (;i <= e;++i)
		if (pre_order[idx] == i) break;
	idx++;

	int l = MIN, r = MIN, ret = MIN;

	if (i == e) {
		l = solve(s, i - 1);
		return l + in_cost[i];
	}
	else if (i == s) {
		r = solve(i + 1, e);
		return r + in_cost[i];
	}
	else {
		l = solve(s, i - 1);
		r = solve(i + 1, e);
		ans = max(ans, l + r + in_cost[i]);
		return max(l + in_cost[i], r + in_cost[i]);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("path.inp", "r", stdin);
	freopen("path.out", "w", stdout);

	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 0;i < n;++i) cin >> in_cost[i];
		for (int i = 0;i < n;++i) cin >> pre_order[i];
		ans = MIN;
		idx = 0;
		solve(0, n - 1);
		cout << ans << '\n';
	}

	return 0;
}