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