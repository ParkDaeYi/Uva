#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define MAX_N 20001
using namespace std;
typedef long long int llt;
ifstream fin;
ofstream fout;

class point {
public:
    llt x, y, dx, dy;
    point(llt x = 0, llt y = 0) :x(x), y(y), dx(0), dy(0) {}
    bool operator<(const point& p) const {
        if (dy * p.dx != dx * p.dy) return dy * p.dx < dx * p.dy;
        //return y == p.y ? x < p.x : y < p.y;
        return x == p.x ? y < p.y : x < p.x;
    }
}pos[MAX_N];
vector<point> hull;
int n, x, y;

bool cmp(const point& p1, const point& p2) {
    return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
}

llt ccw(point a, point b, point c) {
    return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}

int main() {
    fin.open("hull.inp");
    fout.open("hull.out");
    ios_base::sync_with_stdio(0);
    fin.tie(0); fout.tie(0);

    fin >> n;
    for (int i = 0; i < n; ++i) fin >> pos[i].x >> pos[i].y;
    sort(pos, pos + n);
    for (int i = 1; i < n; ++i) pos[i].dx = pos[i].x - pos[0].x, pos[i].dy = pos[i].y - pos[0].y;
    sort(pos + 1, pos + n);
    for (int i = 0; i < n; ++i) {
        while (hull.size() > 1 && ccw(hull[hull.size() - 2], hull.back(), pos[i]) <= 0)
            hull.pop_back();
        hull.push_back(pos[i]);
    }
    fout << hull.size() << '\n';
    for (int i = 0; i < hull.size(); ++i) fout << hull[i].x << ' ' << hull[i].y << '\n';
    return 0;
}