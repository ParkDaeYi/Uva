#include <iostream>
using namespace std;

int n;

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("p10127.inp", "r", stdin);
   freopen("p10127.out", "w", stdout);

   while (cin >> n) {
      for (int i = 1, d = 0; i <= n; ++i) {
         d = d * 10 + 1;
         d %= n;
         if (!d) {
            cout << i << '\n';
            break;
         }
      }
   }
   return 0;
}