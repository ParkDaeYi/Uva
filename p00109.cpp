#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#pragma warning(disable:4996)
using namespace std;
typedef pair<int, int> pii;

struct kingdom {
   int x, y, dx, dy;
   kingdom(int x = 0, int y = 0) : x(x), y(y), dx(0), dy(0) {}
   bool operator<(const kingdom& k) const {
      if (dy * k.dx != dx * k.dy) return dy * k.dx < dx * k.dy;
      return y == k.y ? x < k.x : y < k.y;
   }
}pos[20][101];

int n, m;
vector<kingdom> hull[20];
vector<int> sz;
bool visit[101];
double ans;

int ccw(kingdom& a, kingdom& b, kingdom& c) {
   return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("p00109.inp", "r", stdin);
   freopen("p00109.out", "w", stdout);

   while (cin >> m) {
      if (m == -1) break;
      for (int i = 0; i < m; ++i) cin >> pos[n][i].x >> pos[n][i].y;
      sort(pos[n], pos[n] + m);
      sz.push_back(m);
      n++;
   }
   for (int i = 0; i < n; ++i) {
      for (int j = 1; j < sz[i]; ++j) pos[i][j].dx = pos[i][j].x - pos[i][0].x, pos[i][j].dy = pos[i][j].y - pos[i][0].y;
      sort(pos[i] + 1, pos[i] + sz[i]);
      for (int j = 0; j < sz[i]; ++j) {
         while (hull[i].size() > 1 && ccw(hull[i][hull[i].size() - 2], hull[i].back(), pos[i][j]) <= 0)
            hull[i].pop_back();
         hull[i].push_back(pos[i][j]);
      }
      hull[i].push_back(pos[i][0]);
   }

   kingdom booom;
   while (cin >> booom.x >> booom.y) {
      bool flag = 0;
      for (int i = 0; i < n; ++i) {
         if (visit[i]) continue;
         if (flag) break;
         bool isKD = 1;
         for (int j = 1; j < hull[i].size(); ++j) {
            if (ccw(hull[i][j - 1], hull[i][j], booom) >= 0) continue;
            isKD = 0;
            break;
         }
         if (isKD) {
            visit[i] = 1;
            flag = 1;
            double area = 0;
            for (int j = 1; j < hull[i].size() - 1; ++j) area += ccw(hull[i][0], hull[i][j], hull[i][j + 1]);
            ans += area / 2;
         }
      }
   }
   cout.precision(2);
   cout << fixed << fabs(ans) << '\n';

   return 0;
}