#include <iostream>
#include <cmath>
#pragma warning(disable:4996)
#define EOF 1e-9
using namespace std;
typedef long long int llt;

llt h, c, n, l, r; // h: 첫 번째 고양이 높이, c: 일하는 고양이 수

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("p00107.inp", "r", stdin);
   freopen("p00107.out", "w", stdout);

   while (cin >> h >> c) {
      if (!h && !c) break;

      l = 0, r = c;
      while (1) {
         n = (l + r + 1) >> 1;
         // 고양이들의 키는 모자를 쓰고 있는 고양이의 키의 1/(n+1),
         // => h * (1 / n+1)^k = 1 --> h = (n + 1)^k --> log(h) = k * log(n + 1) --> log(h) / log(n + 1) = k 
         // 모자엔 각각 n마리 고양이가 있다.
         // => c = n^k --> log(c) = k * log(n) --> log(c) / log(n) = k
         // ==> log(h) / log(n + 1) = log(c) / log(n) --> log(h) * log(n) = log(c) * log(n + 1)
         double tmp = log(h) * log(n) - log(c) * log(n + 1);
         if (fabs(tmp) < EOF) break;
         else if (tmp > 0) r = n;
         else l = n;
      }
      // s: 나머지 고양이
      // 모든 고양이의 갯수는 n^0 + n^1 + n^2 + ... + n^k 이다.
      // 여기에 일하는 고양이(n^k)를 빼면 나머지 고양이가 된다.
      // s = n^0 + n^1 + n^2 + ... + n^(k-1)
      // (n != 1) s = (1 - n^k) / (1 - n) = (1 - c) / (1 - n)
      // (n == 1) s = 1 * k --> k = log(h) / log(1 + 1) = log2(h)
      // t: 모든 고양이 높이
      // 고양이 수 * 모자를 쓰고 있는 고양이의 키 * 1/(n+1)
      // t = 1*h + n*h/(n+1) + n^2*h/(n+1)^2 + .... + n^k*h/(n+1)^k
      // t = h * (1 - (n / (n + 1))^(k + 1)) / (1 - (n / (n + 1)))
      // t = h * (1 - (n / (n + 1))^(k + 1)) / (1 / (n + 1))
      // t = h * (1 - n^(k + 1) / (n + 1)^(k + 1)) * (n + 1)
      // t = h * (n + 1 - n^(k + 1) / (n + 1)^k)
      // t = h * n + h - h * (n^(k + 1) / (n + 1)^k)
      // t = h * n + h - (n + 1)^k * (n^(k + 1) / (n + 1)^k)
      // t = h * n + h - n^(k + 1)
      // t = h * n + h - c * n
      // t = (h - c)*n + h
      cout << (n == 1 ? llt(log2(h) + 0.5) : (1 - c) / (1 - n)) << ' ' << (h - c) * n + h << '\n';
   }

   return 0;
}