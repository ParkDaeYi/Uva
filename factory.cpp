#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX_K 2001
#pragma warning(disable:4996)
using namespace std;
typedef pair<int, int> pii;

int t, n, d, cnt, dfsn[MAX_K], sn[MAX_K], sn_cnt;
stack<int> node;
vector<int> graph[MAX_K];
pii mc[MAX_K];

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
   freopen("factory.inp", "r", stdin);
   freopen("factory.out", "w", stdout);

   cin >> t;
   for (int T = 0; T < t; ++T) {
      cin >> n >> d;

      cnt = sn_cnt = 0;
      fill(dfsn, dfsn + n * 2, 0);
      fill(sn, sn + n * 2, 0);
      for (int i = 0; i < n * 2; ++i) graph[i].clear();

      for (int i = 0, a, b; i < n; ++i) {
         cin >> a >> b;
         if (a > b) swap(a, b);
         mc[i] = pii(a, i);
         mc[i + n] = pii(b, i + n);
      }
      sort(mc, mc + n + n);
      for (int i = 0; i < n * 2; ++i) {
         for (int j = i + 1, u, v; j < n * 2; ++j) {
            if (mc[j].first - mc[i].first >= d) break;
            u = mc[i].second < n ? mc[i].second + n : mc[i].second - n;
            v = mc[j].second;
            graph[u].push_back(v);
            u = mc[i].second;
            v = mc[j].second < n ? mc[j].second + n : mc[j].second - n;
            graph[v].push_back(u);
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
      cout << "Test Case #" << T + 1 << ": " << (flag ? "Impossible" : "Possible") << '\n';
   }
   return 0;
}