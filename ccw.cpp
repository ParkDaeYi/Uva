#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct point {
	int x, y, dx, dy;
	point(int x = 0, int y = 0) :x(x), y(y), dx(0), dy(0) {}
	bool operator<(const point& p) const {
		if (1LL * dy * p.dx != 1LL * dx * p.dy) return 1LL * dy * p.dx < 1LL * dx * p.dy;
		return y == p.y ? x < p.x : y < p.y;
	}
	point operator-(point& p) {
		return point(x - p.x, y - p.y);
	}
};

vector<point> a, b;

// 양수 : 반시계, 음수 : 시계, 0 : 일직선
int ccw(point a, point b, point c) {
	int tmp = a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
	return tmp == 0 ? 0 : tmp > 0 ? 1 : -1;
}

int _ccw(point a, point b) {
	return a.x * b.y - b.x * a.y;
}

int _ccw(point a, point b, point c) {
	return _ccw(point(b.x - a.x, b.y - a.y), point(c.x - a.x, c.y - a.y));
}
//

void convex_hull(int sz, vector<point>& v) {
	v.clear();
	point pos[100];
	for (int i = 0; i < sz; ++i) cin >> pos[i].x >> pos[i].y;
	sort(pos, pos + sz);
	for (int i = 1; i < sz; ++i) pos[i].dx = pos[i].x - pos[0].x, pos[i].dy = pos[i].y - pos[0].y;
	sort(pos + 1, pos + sz); // 반시계 방향으로 정렬

	//컨벡스헐 생성
	for (int i = 0; i < sz; ++i) {
		while (v.size() > 1 && ccw(v[v.size() - 2], v.back(), pos[i]) <= 0) v.pop_back(); // 시계방향이거나 일직선일 경우 뺀다.
		v.push_back(pos[i]);
	}
}

//ab 와 cd가 일직선 상에서 겹치지 않는 경우 True를 반환
bool disjoint(int a, int b, int c, int d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return b < c || d < a;
}

//두 선분이 서로 교차하는지 여부를 반환
bool sementIntersects(point a, point b, point c, point d) {
	//세 점 a, b, c의 회전 방향 검사에서
	//선분이 교차한다면 음수를 반환
	int ab = ccw(a, b, c) * ccw(a, b, d);
	int cd = ccw(c, d, a) * ccw(c, d, b);
	//두 선분이 일직선에 있는 경우, ab와 cd가 겹침 : True, 안겹침 : False
	if (!ab && !cd) return !(disjoint(a.x, b.x, c.x, d.x) || disjoint(a.y, b.y, c.y, d.y));
	//선분의 끝점이 교차점이 되는 경우를 포함
	return ab <= 0 && cd <= 0;
}

// 도형이 컨벡스헐로 되어 있지 않을 경우
//a와 b의 정점 중 다각형에 포함되는 경우를 판별
bool insidePolygon(point q, vector<point>& p) {
	//cross는 점 q와 다각형의 오른쪽 반직선과의 교점 개수
	int sz = p.size(), cross = 0;
	for (int i = 0; i < sz; ++i) {
		int j = (i + 1) % sz;
		//점 q가 선분 (p[i], p[j])의 y좌표 사이에 있을 경우
		if (p[i].y > q.y != p[j].y > q.y) {
			double atX = (double)((p[j].x - p[i].x) * (q.y - p[i].y)) / (p[j].y - p[i].y) + p[i].x;
			//atX가 q.x보다 클 경우 cross 증가
			//atx는 q.x 와 동일 선상에 존재하는 p[i], p[j] 선분 사이의 한 점
			if (q.x < atX) cross++;
		}
	}
	// 짝수 : False (포함 X), 홀수 : True (포함 O)
	return cross % 2;
}

bool _insidePolygon(point q, vector<point> p) {
	int sz = p.size(), cross = 0;
	point origin = point(0, 0);

	for (int i = 0; i < sz; ++i) p[i] = point(p[i].x - q.x, p[i].y - q.y);
	for (int i = 0; i < sz; ++i) {
		int j = (i + 1) % sz;
		// q가 p의 엣지에 놓여 있을 경우 q가 내부에 있다고 가정
		if (ccw(p[i], p[j], origin) == 0) {
			point a = p[i], b = p[j], c = origin;
			if (a.x != b.x) {
				if (a.x > b.x) swap(a, b);
				return a.x <= c.x && c.x <= b.x;
			}
			else {
				if (a.y > b.y) swap(a, b);
				return a.y <= c.y && c.y <= b.y;
			}
		}
		if (p[i].y < 0 && p[j].y >= 0 && ccw(p[i], p[j], origin) > 0 ||
			p[j].y < 0 && p[i].y >= 0 && ccw(p[j], p[i], origin) > 0) cross++;
	}
	// 짝수 : False (포함 X), 홀수 : True (포함 O)
	return cross % 2;
}

// 도형이 컨벡스헐로 이루어졌을 경우
bool hull_insidePolygon(point q, vector<point> p) {
	for (int i = 1; i < p.size(); ++i) {
		if (ccw(p[i - 1], p[i], q) < 0) return false; // 포함 X
	}
	return true; // 포함 O
}

// 다각형 면적 구하기
double area(vector<point> p) {
	double ret = 0;
	for (int i = 1; i < p.size() - 1; ++i) {
		ret += ccw(p[0], p[i], p[i + 1]);
	}
	return ret / 2;
}

int dist(point a, point b) {
	int dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}

double rotatingCalipers(vector<point> p) {
	int ret = 0, sz = p.size();
	for (int i = 0, j = 1; i < sz; ++i) {
		//구간의 양 끝이 [A,B]라고 가정한다면
		//A번째 점과 A+1번째 점을 잇는 선분과 B번째 점과 B+1번째 점을 잇는 선분의
		//외적을 계산, https://degurii.tistory.com/47
		while (j + 1 < sz && ccw(point(0, 0), p[i + 1] - p[i], p[j + 1] - p[j]) >= 0) ret = max(ret, dist(p[i], p[j++]));
		ret = max(ret, dist(p[i], p[j]));
	}
	return sqrt(ret);
}