#include <iostream>
#include <algorithm>
#include <cmath>
#pragma warning(disable:4996)
#define MAX_N 100001
#define MAX_Y 1000001
using namespace std;
typedef pair<int, int> pii;
typedef long long int llt;

class point {
public:
   llt x, y1, y2, v;
   point(llt x = 0, llt y1 = 0, llt y2 = 0, llt v = 0) :x(x), y1(y1), y2(y2), v(v) {}
   bool operator <(const point& p) const {
      if (x == p.x) return v > p.v;
      return x < p.x;
   }
}pos[MAX_N + MAX_N];
int n, cnt[1 << 21], t = 1, lx, h, rx, arrY[MAX_N + MAX_N];
llt seg[1 << 21];

int lower_bd(int left, int right, int target) {
   int mid;
   while (left < right) {
      mid = (left + right) >> 1;
      if (arrY[mid] < target) left = mid + 1;
      else right = mid;
   }
   return right;
}

void update_tree(int node, int start, int end, int left, int right, int val) {
   if (end < left || right < start) return;
   if (left <= start && end <= right) cnt[node] += val;
   else {
      int mid = (start + end) >> 1;
      update_tree(node * 2, start, mid, left, right, val);
      update_tree(node * 2 + 1, mid + 1, end, left, right, val);
   }
   if (cnt[node]) seg[node] = arrY[end + 1] - arrY[start];
   else seg[node] = start == end ? 0 : seg[node * 2] + seg[node * 2 + 1];
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("contour.inp", "r", stdin);
   freopen("contour.out", "w", stdout);

   while ((cin >> lx >> h >> rx)) {
      if (lx || h || rx) {
         pos[n] = point(lx, 0, h, 1);
         pos[n + 1] = point(rx, 0, h, -1);
         arrY[n] = 0;
         arrY[n + 1] = h;
         n += 2;
      }
      else {
         cout << "Test Case #" << t++ << " : ";
         sort(arrY, arrY + n);
         int szY = unique(arrY, arrY + n) - arrY;
         sort(pos, pos + n);
         const int sz = pow(2, (int)log2(n - 1) + 1);
         llt ans = 0;
         for (int i = 0, prev; i < n; ++i) {
            if (i) ans += (pos[i].x - prev) * seg[1];
            update_tree(1, 0, sz - 1, lower_bd(0, szY, pos[i].y1), lower_bd(0, szY, pos[i].y2) - 1, pos[i].v);
            if (!seg[1]) {
               cout << ans << ' ';
               ans = 0;
            }
            prev = pos[i].x;
         }
         cout << '\n';
         n = 0;
      }
   }
   return 0;
}