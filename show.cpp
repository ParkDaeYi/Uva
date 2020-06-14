#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX_K 5000*2+1
#define MAX_N 10001
#pragma warning(disable:4996)
using namespace std;
typedef pair<int, char> pic;
typedef pair<int, int> pii;

int t, m, n, cnt, dfsn[MAX_K], sn[MAX_K], sn_cnt;
stack<int> node;
vector<int> graph[MAX_K];
pic tmp[3];
pii tmp2[3];

int dfs(int cur) {
   dfsn[cur] = ++cnt;
   node.push(cur);
   
   int ret = dfsn[cur];
   for (int nxt : graph[cur]) {
      if (!dfsn[nxt]) ret = min(ret, dfs(nxt));
      else if (!sn[nxt]) ret = min(ret, dfsn[nxt]);
   }

   if (ret == dfsn[cur]) {
      sn_cnt++;
      while (1) {
         int t = node.top(); node.pop();
         sn[t] = sn_cnt;
         if (t == cur) break;
      }
   }
   return ret;
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("show.inp", "r", stdin);
   freopen("show.out", "w", stdout);

   cin >> t;
   while (t--) {
      cin >> n >> m;
      for (int i = 0; i < n * 2; ++i) graph[i].clear();
      fill(dfsn, dfsn + n + n, 0);
      fill(sn, sn + n + n, 0);
      cnt = sn_cnt = 0;
      for (int i = 0, a; i < m; ++i) {   
         for (int j = 0; j < 3; ++j) cin >> tmp[j].first >> tmp[j].second;
         for (int j = 0, a1, a2, b1, b2; j < 2; ++j) {
            // 1 : x, 2: ㄱx
            if (tmp[j].second == 'R') {
               a1 = tmp[j].first;
               a2 = a1 + n;
            }
            else {
               a2 = tmp[j].first;
               a1 = a2 + n;
            }
            for (int k = j + 1; k < 3; ++k) {
               if (tmp[k].second == 'R') {
                  b1 = tmp[k].first;
                  b2 = b1 + n;
               }
               else {
                  b2 = tmp[k].first;
                  b1 = b2 + n;
               }
               graph[a2 - 1].push_back(b1 - 1);
               graph[b2 - 1].push_back(a1 - 1);
            }
         }
      }

      for (int i = 0; i < n * 2; ++i) if (!dfsn[i]) dfs(i);

      bool flag = 0;
      for (int i = 0; i < n; ++i) {
         if (sn[i] == sn[i + n]) {
            flag = 1;
            break;
         }
      }
      cout << (flag ? -1 : 1) << '\n';
   }
   return 0;
}