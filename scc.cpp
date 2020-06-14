#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
#define MAX_V 10001
using namespace std;

int v, e, cnt, dfsn[MAX_V], sn[MAX_V], sn_cnt;
stack<int> info;
vector<int> graph[MAX_V];

int dfs(int cur) {
   dfsn[cur] = ++cnt;
   info.push(cur);

   int ret = dfsn[cur];
   for (int nxt : graph[cur]) {
      if (!dfsn[nxt]) ret = min(ret, dfs(nxt));
      else if (!sn[nxt]) ret = min(ret, dfsn[nxt]);
   }

   if (ret == dfsn[cur]) {
      sn_cnt++;
      while (1) {
         int t = info.top(); info.pop();
         sn[t] = sn_cnt;
         if (t == cur) break;
      }
   }
   return ret;
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("scc.inp", "r", stdin);
   freopen("scc.out", "w", stdout);

   cin >> v >> e;
   for (int i = 0, a, b; i < e; ++i) {
      cin >> a >> b;
      graph[a].push_back(b);
   }
   for (int i = 0; i < v; ++i) {
      if (!dfsn[i]) dfs(i);
   }
   cout << sn_cnt;
   return 0;
}