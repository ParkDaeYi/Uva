#include <iostream>
#include <algorithm>
#include <cmath>
#define MAX_N 10000
using namespace std;

// 세그먼트트리 (feat. 구간 합)
// 완전 이진트리, 무조건 재귀
int seg[MAX_N * 4], arr[MAX_N];

// arr는 이미 값이 초기화된 상태
void init(int seg[], int arr[], int node, int start, int end) {
	if (start == end) seg[node] = arr[start];
	else {
		int mid = (start + end) >> 1;
		init(seg, arr, node * 2, start, mid);
		init(seg, arr, node * 2 + 1, mid + 1, end);
		seg[node] = seg[node * 2] + seg[node * 2 + 1];
	}
}

// 공통
void update(int seg[], int node, int start, int end, int idx, int val) {
	if (idx < start || end < idx) return;
	if (start == end) {
		seg[node] = val;
		return;
	}
	int mid = (start + end) >> 1;
	update(seg, node * 2, start, mid, idx, val);
	update(seg, node * 2 + 1, mid + 1, end, idx, val);
	seg[node] = seg[node * 2] + seg[node * 2 + 1];
}

// 포화 이진트리, 재귀 없어도 됨, arr배열 따로 필요 없음
int seg[1 << 21];

void init(int seg[], int n) {
	const int sz = pow(2, (int)log2(n - 1) + 1); //사이즈를 최대한 줄이기 위해 n-1, sz 값으로 seg배열을 동적 생성해도 됨(ex. vector)
	for (int i = 0; i < n; ++i) cin >> seg[i + sz];
	for (int i = sz - 1; i > 0; --i) seg[i] = seg[i * 2] + seg[i * 2 + 1];
}

void update(int seg[], int sz, int idx, int val) {
	int node = sz + idx - 1;
	int diff = val - seg[node];
	for (; node > 0; node /= 2) seg[node] += diff;
}

// 공통
int query(int seg[], int node, int start, int end, int left, int right) {
	if (end < left || right < start) return 0;
	if (left <= start && end <= right) return seg[node];
	int mid = (start + end) >> 1;
	return query(seg, node * 2, start, mid, left, right) + query(seg, node * 2 + 1, mid + 1, end, left, right);
}

// 세그먼트 트리 기반 라인스위핑 (feat. 화성지도)
struct point {
	int x, y1, y2, v;
	point(int x = 0, int y1 = 0, int y2 = 0, int v = 0) :x(x), y1(y1), y2(y2), v(v) {}
	bool operator<(const point& p) const {
		return x == p.x ? v > p.v : x < p.x; // x 축으로 정렬(y로 해도 무방), 같을 경우 value가 높은 순으로 정렬
	}
};
point pos[MAX_N + MAX_N];
#define MAX_Y 30000
int n, seg[MAX_Y * 4], cnt[MAX_Y * 4];

void init(point pos[]) {
	cin >> n;
	for (int i = 0, a, b, c, d; i < n; ++i) {
		cin >> a >> b >> c >> d; // x1, y1, x2, y2
		pos[i] = point(a, b, d - 1, 1);
		pos[i + n] = point(c, b, d - 1, -1);
	}
	sort(pos, pos + n + n);
}

void update(int seg[], int cnt[], int node, int start, int end, int left, int right, int val) {
	if (end < left || right < start) return;
	if (left <= start && end <= right) cnt[node] += val;
	else {
		int mid = (start + end) >> 1;
		update(seg, cnt, node * 2, start, mid, left, right, val);
		update(seg, cnt, node * 2 + 1, mid + 1, end, left, right, val);
	}
	if (cnt[node]) seg[node] = end - start + 1;
	else seg[node] = start == end ? 0 : seg[node * 2] + seg[node * 2 + 1]; // cnt[node]가 0이고 start==end일 경우 seg[node]의 값을 0으로 초기화
}

int query(point pos[], int seg[],int cnt[]) {
	int ret = 0;
	for (int i = 0, prev; i < n + n; ++i) {
		if (i) ret += (pos[i].x - prev) * seg[1]; // pos[i].x-prev : 현재 x축 길이, seg[1] : 현재 y축 길이
		update(seg, cnt, 1, 0, MAX_Y, pos[i].y1, pos[i].y2, pos[i].v);
		prev = pos[i].x;
	}
	return ret;
}