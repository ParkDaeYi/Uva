#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int t, n, ans = 0;

void solve(int s, int e) {
   for (int i = 2; i * i < e + 1; ++i) {
      if (e % i || i < s) continue;
      ans++;
      solve(i, e / i);
   }
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("mult.inp", "r", stdin);
   freopen("mult.out", "w", stdout);

   cin >> t;
   while (t--) {
      cin >> n;
      ans = 0;
      solve(1, n);
      cout << n << ' ' << ans << '\n';
   }
   return 0;
}