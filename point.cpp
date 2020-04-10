#include <iostream>
#define MAX_N 5001
using namespace std;
typedef long long int llt;
typedef pair<int, int> pii;

int n, m;
pii pos[MAX_N];

void swap_int(int& a, int& b) { int tmp = a; a = b; b = tmp; }

int ccw(pii a, pii b, pii c) {
	llt tmp = a.first * b.second + b.first * c.second + c.first * a.second - a.second * b.first - b.second * c.first - c.second * a.first;
	return tmp == 0 ? 0 : tmp > 0 ? 1 : -1;
}

bool between(pii a, pii b, pii c) {
	if (ccw(a, b, c)) return 0;
	if (a.first != b.first) {
		if (a.first > b.first) swap_int(a.first, b.first);
		return a.first <= c.first && c.first <= b.first;
	}
	else {
		if (a.second > b.second) swap_int(a.second, b.second);
		return a.second <= c.second && c.second <= b.second;
	}
}

bool isInside(pii q) {
	int cross = 0;
	for (int i = 0;i < n;++i) {
		int j = (i + 1) % n;
		if (between(pos[i], pos[j], q)) return 1;
		if (pos[i].second > q.second != pos[j].second > q.second) {
			double atX = (double)((pos[j].first - pos[i].first) * (q.second - pos[i].second)) / (pos[j].second - pos[i].second) + pos[i].first;
			if (q.first < atX) cross++;
		}
	}
	return cross % 2;
}

bool solve() {
	pii tmp;
	cin >> tmp.first >> tmp.second;
	return isInside(tmp) ? 1 : 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("point.inp", "r", stdin);
	freopen("point.out", "w", stdout);

	cin >> n;
	for (int i = 0;i < n;++i) cin >> pos[i].first >> pos[i].second;
	cin >> m;
	while (m--) cout << (solve() ? "1\n" : "0\n");
	return 0;
}