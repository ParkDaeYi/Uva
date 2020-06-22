#include <iostream>
#include <vector>
#include <algorithm>
#define EOF 1000000
#pragma warning(disable:4996)
using namespace std;

int T, N;
vector<int> arr;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("rectangles.inp", "r", stdin);
   freopen("rectangles.out", "w", stdout);
   
   // m, n은 자연수이고, m > n 이며, 둘 중 하나는 짝수, 하나는 홀수이다.
   int i, j, sum = 0;
   for (i = 2; i <= 600; ++i) {
      for (int j = 1; j < i; ++j) {
         if ((i + j) % 2 == 0 || gcd(i, j) != 1) continue;
         arr.push_back(i * i - j * j + 2 * i * j);
      }
   }
   sort(arr.begin(), arr.end());
   for (i = 1;; i++) {
      arr[i] += arr[i - 1];
      if (arr[i] > EOF) break;
   }

   cin >> T;
   while (T--) {
      cin >> N;

      for (i = 0;; ++i) {
         if (arr[i] * 2 > N) break;
      }
      cout << i << '\n';
   }

   return 0;
}

// (a, b, c) 가 원시 피타고라스 수일 필요충분조건
// - (m^2 - n^2, 2mn, m^2 + n^2) => (a, b, c) : c는 대각
// - m, n은 자연수이고, m > n 이며, 둘 중 하나는 짝수, 하나는 홀수이다.
// 따름 정리
// 1. a, c는 항상 홀수이고 b는 4의 배수이다.
// 2. a 또는 b 중 적어도 하나는 3의 배수이다.
// 3. a, b, c 중 적어도 하나는 5의 배수이다.
// 4. ab는 12의 배수이고 abc는 60의 배수이다.
