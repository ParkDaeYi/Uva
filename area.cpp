#include <iostream>
#include <cmath>
#pragma warning(disable:4996)
using namespace std;
typedef pair<pair<int, int>, int> pipii;
typedef pair<double, double> pdd;

int t;
pipii circle[3];
pdd tri[3];

double dist(int x, int y) {
   return sqrt((x * x) + (y * y));
}

double triArea(pdd a, pdd b, pdd c) {
   return fabs(a.first * b.second + b.first * c.second + c.first * a.second - a.second * b.first - b.second * c.first - c.second * a.first) / 2;
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("area.inp", "r", stdin);
   freopen("area.out", "w", stdout);

   cin >> t;
   while (t--) {
      for (int i = 0; i < 3; ++i) cin >> circle[i].first.first >> circle[i].first.second >> circle[i].second;   
      for (int i = 0, k = 2; i < 2; ++i) {
         for (int j = i + 1; j < 3; ++j) {
            double x1, y1, x2, y2, r1, r2, v, w, a, b, c;
            x1 = circle[i].first.first, y1 = circle[i].first.second, r1 = circle[i].second;
            x2 = circle[j].first.first, y2 = circle[j].first.second, r2 = circle[j].second;
            
            // 원의 방정식을 사용해서 연립을 통해 답을 유추(근의 방정식 사용)
            // (x - x1)^2 + (y - y1)^2 = r^2
            // (x - x2)^2 + (y - y2)^2 = r^2
            // x에 대해 풀 경우 (조건: x1 != x2)
            // x = (r1^2 - r2^2 - x1^2 - y1^2 + x2^2 + y2^2 - 2*(y2 - y1)*y) / (2*(x2 - x1)) 정리하면 이렇게 나옴
            // v = (r1^2 - r2^2 - x1^2 - y1^2 + x2^2 + y2^2) / (2*(x2 - x1))
            // w = (y2 - y1) / (x2 - x1) 으로 정의
            // (x - x1)^2 + (y - y1)^2 = r^2 에서 x 를 v - w*y 로 대치
            // (1 + w^2) * y^2 + 2*(x1*w - v*w - y1) * y + (x1^2 + y1^2 - 2*x1*v + v^2 - r1^2) = 0 으로 정리된다.
            // (~~~)부분을 각각 a,b,c로 하고 근의 방정식을 통해 값을 구한다.
            double X1, Y1, X2, Y2;
            if (x1 != x2) {
               v = (r1 * r1 - r2 * r2 - x1 * x1 - y1 * y1 + x2 * x2 + y2 * y2) / (2 * (x2 - x1));
               w = (y2 - y1) / (x2 - x1);

               a = 1 + w * w;
               b = 2 * (x1 * w - v * w - y1);
               c = x1 * x1 + y1 * y1 - 2 * x1 * v + v * v - r1 * r1;

               Y1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
               Y2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
               X1 = v - w * Y1;
               X2 = v - w * Y2;
            }
            else {
               v = (r1 * r1 - r2 * r2 - x1 * x1 - y1 * y1 + x2 * x2 + y2 * y2) / (2 * (y2 - y1));
               w = (x2 - x1) / (y2 - y1);

               a = 1 + w * w;
               b = 2 * (y1 * w - v * w - x1);
               c = x1 * x1 + y1 * y1 - 2 * y1 * v + v * v - r1 * r1;

               X1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
               X2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
               Y1 = v - w * X1;
               Y2 = v - w * X2;
            }

            double t1 = dist(circle[k].first.first - X1, circle[k].first.second - Y1);
            double t2 = dist(circle[k].first.first - X2, circle[k].first.second - Y2);
            tri[k--] = t1 < t2 ? pdd(X1, Y1) : pdd(X2, Y2);
         }
      }

      double ans = triArea(tri[0], tri[1], tri[2]);
      cout.precision(2);
      cout << fixed << ans << '\n';
   }

   return 0;
}