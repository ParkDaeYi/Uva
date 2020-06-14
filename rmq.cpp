#include <iostream>
#include <cmath>
#include <algorithm>
#define MAX_N 1000002
#define INF 2147483647
#pragma warning(disable:4996)
using namespace std;
typedef long long int llt;

int n, seg[MAX_N * 4], arr[MAX_N], a, b;
char c;
llt sum;

int query(int node, int s, int e, int l, int r) {
   if (l <= s && e <= r) return seg[node];
   if (e < l || r < s) return MAX_N - 1;

   int mid = (s + e) >> 1, ret = MAX_N - 1, q1 = query(node * 2, s, mid, l, r), q2 = query(node * 2 + 1, mid + 1, e, l, r);
   if (arr[q1] != arr[q2]) return arr[q1] < arr[q2] ? q1 : q2;
   else return q1;
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("rmq.inp", "r", stdin);
   freopen("rmq.out", "w", stdout);

   cin >> n;
   const int sz = pow(2, (int)log2(n - 1) + 1);
   for (int i = 0; i < n; ++i) cin >> arr[i], seg[sz + i] = i;
   for (int i = n; i < sz; ++i) seg[sz + i] = MAX_N - 1;
   arr[MAX_N - 1] = INF;
   for (int i = sz - 1; i > 0; --i) {
      if (arr[seg[i * 2]] != arr[seg[i * 2 + 1]]) seg[i] = arr[seg[i * 2]] < arr[seg[i * 2 + 1]] ? seg[i * 2] : seg[i * 2 + 1];
      else seg[i] = seg[i * 2];
   }
   while ((cin >> c >> a >> b)) {
      if (c == 's' && a == -1 && b == -1) break;

      if (c == 'q') sum += query(1, 0, sz - 1, a, b);
      else if (c == 'c') {
         int node = sz + a;
         arr[a] = b;
         for (node /= 2; node > 0; node /= 2) {
            if (arr[seg[node * 2]] != arr[seg[node * 2 + 1]]) seg[node] = arr[seg[node * 2]] < arr[seg[node * 2 + 1]] ? seg[node * 2] : seg[node * 2 + 1];
            else seg[node] = seg[node * 2];
         }
      }
   }
   cout << sum % 100000;
   return 0;
}