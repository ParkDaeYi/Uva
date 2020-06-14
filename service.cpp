#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>
#pragma warning(disable:4996)
#define MAX_N 100
#define MAX_P 2500
#define MAX_NP 2600
#define MAX 2652
using namespace std;

int t, n, p, m, c[MAX][MAX], f[MAX][MAX], s = MAX - 2, e = MAX - 1;
vector<int> adj[MAX];

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("service.inp", "r", stdin);
   freopen("service.out", "w", stdout);

   cin >> t;
   while (t--) {
      cin >> n >> p >> m;
      for (int i = 0; i < MAX; ++i) 
         adj[i].clear();
      fill(&c[0][0], &c[MAX - 1][MAX], 0);
      fill(&f[0][0], &f[MAX - 1][MAX], 0);
      int fj[51] = { 0, };
      for (int i = 1; i <= p; ++i) cin >> fj[i], fj[i] += fj[i - 1];
      for (int i = 0, a; i < n; ++i) {
         c[s][i] = m;
         adj[s].push_back(i);
         adj[i].push_back(s);
         unordered_set<int> us;
         cin >> a;
         for (int j = 0, x, y; j < a; ++j) {
            cin >> x >> y;
            if (y > fj[x] - fj[x - 1]) continue;
            x--, y += MAX_N - 1;
            us.insert(x);
            int tmp = y + fj[x];
            c[x + MAX_NP][tmp] = 1;
            adj[x + MAX_NP].push_back(tmp);
            adj[tmp].push_back(x + MAX_NP);
         }
         for (int s : us) {
            c[i][s + MAX_NP] = 1;
            adj[i].push_back(s + MAX_NP);
            adj[s + MAX_NP].push_back(i);
         }
      }
      for (int i = MAX_N; i < MAX_N + fj[p]; ++i) {
         c[i][e] = 1;
         adj[i].push_back(e);
         adj[e].push_back(i);
      }

      int ans = 0;
      while (1) {
         int prev[MAX];
         fill(prev, prev + MAX, -1);
         queue<int> q;
         q.push(s);
         while (!q.empty() && prev[e] == -1) {
            int cur = q.front(); q.pop();
            for (int nxt : adj[cur]) {
               if (c[cur][nxt] > f[cur][nxt] && prev[nxt] == -1) {
                  q.push(nxt);
                  prev[nxt] = cur;
                  if (nxt == e) break;
               }
            }
         }
         if (prev[e] == -1) break;
         int flow = 1e9;
         for (int i = e; i != s; i = prev[i]) flow = min(flow, c[prev[i]][i] - f[prev[i]][i]);
         for (int i = e; i != s; i = prev[i]) {
            f[prev[i]][i] += flow;
            f[i][prev[i]] -= flow;
         }
         ans += flow;
      }
      if (ans != fj[p]) cout << 0 << '\n';
      else cout << 1 << '\n';
   }

   return 0;
}