#include <iostream>
#pragma warning(disable:4996)
#define r first
#define m second
using namespace std;
typedef long long int llt;
typedef pair<llt, llt> pll;

int t, k;
pll crt[51];

llt gcd(llt a, llt b) {
   return b == 0 ? a : gcd(b, a % b);
}

pll CRT(pll p1, pll p2) {
   //   p1         p2
   // as + b  ≡ c (mod d)
   // as ≡ (c - b) (mod d)
   // rr == (c - b), (c - b)는 d의 나머지여야 함(모듈러 연산)
   llt rr = (p2.r - (p1.r % p2.m)) % p2.m;
   // rr이 음수일 경우 + d, 위에서 mod d를 하였기 때문에 한 번만 더하면 됨.(하지만 혹시 모르므로 while)
   while (rr < 0) rr += p2.m;

   llt g, a = p1.m, b = p2.m;

   g = gcd(gcd(a, b), rr);

   if (g != 1) a /= g, b /= g, rr /= g;
   
   // a'와 b'가 서로소가 아닐 경우 
   // 확장 유클리드 호제법을 통해 원하는 값을 얻을 수 없음
   if (gcd(a, b) != 1) return pll(-1, -1);

   // 확장 유클리드 호제법을 통해 역원(a'^-1)을 구함
   // => a'x + b'y = 1 형태이므로 s의 값을 구하면 됨
   llt q = 0, tmp = 0, r1 = a, r2 = b, s1 = 1, s2 = 0;
   while (r2) {
      q = r1 / r2;
      tmp = r1;
      r1 = r2;
      r2 = tmp - r2 * q;
      tmp = s1;
      s1 = s2;
      s2 = tmp - s2 * q;
   }
   // rr 값을 양수로 유지하기 위해 s1이 음수일 경우 양수로 변환
   while (s1 < 0) s1 += b;
   rr = ((rr % b) * (s1 % b)) % b;

   // s ≡ rr (mod b') => s = b't + rr 을 p1(x = as + b) 에 대입
   return pll(p1.m * rr + p1.r, p1.m * b);
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("crt.inp", "r", stdin);
   freopen("crt.out", "w", stdout);

   cin >> t;
   while (t--) {
      cin >> k;
      for (int i = 0; i < k; ++i) {
         cin >> crt[i].r >> crt[i].m;
      }
      for (int i = 1; i < k; ++i) {
         crt[0] = CRT(crt[0], crt[i]);
         if (crt[0].r == -1 && crt[0].m == -1) break;
      }
      cout << crt[0].r << '\n';
   }

   return 0;
}