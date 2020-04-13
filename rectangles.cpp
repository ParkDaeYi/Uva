#include <iostream>
#include <algorithm>
#include <cmath>
#define MAX_N 10001
#define MAX_Y 20001
#pragma warning(disable:4996)
using namespace std;
typedef long long int llt;

class point {
public:
	int x, y1, y2, op;
	point(int x = 0, int y1 = 0, int y2 = 0, int op = 0) :x(x), y1(y1), y2(y2), op(op) {}
}pos[MAX_N + MAX_N];
llt seg[MAX_Y * 4], cnt[MAX_Y * 4], ans;
int n;

void update(int node, int s, int e, int l, int r, int val) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) cnt[node] += val;
	else {
		int mid = (s + e) >> 1;
		update(node * 2, s, mid, l, r, val);
		update(node * 2 + 1, mid + 1, e, l, r, val);
	}
	if (cnt[node]) seg[node] = e - s + 1;
	else seg[node] = s == e ? 0 : seg[node * 2] + seg[node * 2 + 1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("rectangles.inp", "r", stdin);
	freopen("rectangles.out", "w", stdout);

	cin >> n;
	for (int i = 0, a, b, c, d;i < n;++i) {
		cin >> a >> b >> c >> d;
		a += 1e4, b += 1e4, c += 1e4, d += 1e4;
		pos[i] = point(a, b, d - 1, 1);
		pos[i + n] = point(c, b, d - 1, -1);
	}
	sort(pos, pos + n + n, [](point& p1, point& p2) {
		return p1.x < p2.x;
	});
	const int sz = pow(2, (int)log2(MAX_Y - 1) + 1);
	for (int i = 0, prev = 0;i < n + n;++i) {
		if (i) ans += (pos[i].x - prev) * seg[1];
		update(1, 0, sz - 1, pos[i].y1, pos[i].y2, pos[i].op);
		prev = pos[i].x;
	}
	cout << ans;
	return 0;
}