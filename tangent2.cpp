#include <iostream>
#include <vector>
#include <cmath>
#pragma warning(disable:4996)
#define VERTEX 10001
using namespace std;
typedef long long int llt;

struct point {
   int x, y;
}p[VERTEX], q[VERTEX], s, e;
int t, n, m;
vector<point> convex;

llt ccw(point a, point b, point c) {
   return 1LL * (a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x);
}

int dist(point a, point b, point c) {
   llt ab = 1LL * ((a.x - b.x) * (a.x - b.x)) + 1LL * ((a.y - b.y) * (a.y - b.y));
   llt cb = 1LL * ((c.x - b.x) * (c.x - b.x)) + 1LL * ((c.y - b.y) * (c.y - b.y));
   return ab == cb ? 0 : ab > cb ? 1 : -1;
}

int main() {
   ios_base::sync_with_stdio(0);   
   cin.tie(0); cout.tie(0);
   freopen("tangent2.inp", "r", stdin);
   freopen("tangent2.out", "w", stdout);

   cin >> t;
   while (t--) {
      cin >> n;
      for (int i = 0, x, y; i < n; ++i) cin >> p[i].x >> p[i].y;
      cin >> m;
      for (int i = 0, x, y; i < m; ++i) cin >> q[i].x >> q[i].y;
      int pidx = 0, qidx = 0;
      // s 찾기
      while (1) {
         int cp = pidx, cq = qidx;
         for (int i = 0; i < n; ++i) {
            if (pidx == i) continue;
            int chk = ccw(q[qidx], p[pidx], p[i]);
            if (chk < 0) pidx = i;
            else if (!chk && dist(p[pidx], q[qidx], p[i]) > 0) pidx = i;
         }
         for (int i = 0; i < m; ++i) {
            if (qidx == i) continue;
            int chk = ccw(p[pidx], q[qidx], q[i]);
            if (chk < 0) qidx = i;
            else if (!chk && dist(q[qidx], p[pidx], q[i]) > 0) qidx = i;
         }
         if (pidx == cp && qidx == cq) {
            s.x = pidx;
            s.y = qidx;
            break;
         }
      }
      pidx = qidx = 0;
      // e 찾기
      while (1) {
         int cp = pidx, cq = qidx;
         for (int i = 0; i < n; ++i) {
            if (pidx == i) continue;
            int chk = ccw(q[qidx], p[pidx], p[i]);
            if (chk > 0) pidx = i;
            else if (!chk && dist(p[pidx], q[qidx], p[i]) > 0) pidx = i;
         }
         for (int i = 0; i < m; ++i) {
            if (qidx == i) continue;
            int chk = ccw(p[pidx], q[qidx], q[i]);
            if (chk > 0) qidx = i;
            else if (!chk && dist(q[qidx], p[pidx], q[i]) > 0) qidx = i;
         }
         if (pidx == cp && qidx == cq) {
            e.x = pidx;
            e.y = qidx;
            break;
         }
      }
      for (int i = e.x;; i = (i + 1) % n) {
         convex.push_back(p[i]);
         if (i == s.x) break;
      }
      for (int i = e.y;; i = (i + 1) % m) {
         convex.push_back(q[i]);
         if (i == s.y) break;
      }
      double ans = 0;
      for (int i = 1; i < convex.size() - 1; ++i) ans += ccw(convex[0], convex[i], convex[i + 1]);
      cout.precision(1);
      cout << fixed << fabs(ans / 2) << '\n';
      convex.clear();
   }
   return 0;
}