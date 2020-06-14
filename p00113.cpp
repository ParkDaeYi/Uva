#include <iostream>
#include <cmath>
#pragma warning(disable:4996)
using namespace std;

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("p00113.inp", "r", stdin);
   freopen("p00113.out", "w", stdout);

   double n, p;
   while (cin >> n >> p) {
      cout.precision(0);
      cout << fixed << pow(p, 1 / n) << '\n';
   }

   return 0;
}