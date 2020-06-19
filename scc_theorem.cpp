#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define VERTEX 20002
using namespace std;

// SCC
// sn_cnt: SCC 개수, sn[i]: i가 속한 SCC 번호
// cycle: SCC 번호에 속한 정점 갯수, (in_degree, out_degree): SCC에서의 인, 아웃 Degree
int v, e, cnt, dfsn[VERTEX], sn_cnt, sn[VERTEX], cycle[VERTEX], in_degree[VERTEX], out_degree[VERTEX];
stack<int> node;
vector<int> graph[VERTEX], adj[VERTEX];
vector<vector<int>> scc;

void init() {
	cin >> v >> e;
	for (int i = 0, a, b; i < e; ++i) {
		cin >> a >> b;
		graph[a].push_back(b);
	}
}

// 자신의 결과값을 리턴하는 DFS 함수
int dfs(int cur) {
	dfsn[cur] = ++cnt;	// dfsn 결정
	node.push(cur);	// 스택에 자신을 push

	// 자신의 dfsn, 자식들의 결과나 dfsn 중 가장 작은 번호를 ret에 저장
	int ret = dfsn[cur];
	for (int nxt : graph[cur]) {
		// 아직 방문하지 않은 이웃
		if (!dfsn[nxt]) ret = min(ret, dfs(nxt));
		// 방문은했으나 아직 SCC로 추출되지 않은 이웃
		else if (!sn[nxt]) ret = min(ret, dfsn[nxt]);
	}

	// 자신 또는, 자신의 자손들이 도달 가능한 제일 높은 정점이 자신일 경우 SCC 추출
	if (ret == dfsn[cur]) {
		sn_cnt++;
		vector<int> scc_tmp;
		// 스택에서 자신이 나올 때까지 pop
		while (1) {
			int t = node.top(); node.pop();
			scc_tmp.push_back(t);
			cycle[sn_cnt]++;	// 해당 번호에 속하는 정점을 카운팅
			sn[t] = sn_cnt;		// 각 정점에 SCC 번호를 메김
			if (t == cur) break;
		}
		sort(scc_tmp.begin(), scc_tmp.end());
		scc.push_back(scc_tmp);	// 형성된 SCC 추가
	}
	return ret;
}

void solve() {
	init();

	// DFS를 통해 SCC 추출
	for (int i = 1; i <= v; ++i) if (!dfsn[i]) dfs(i);

	for (int i = 1; i <= v; ++i) {
		for (int j : graph[i]) {
			// sn[i] == sn[j]: 같은 SCC에 속함
			if (sn[i] == sn[j]) continue;

			adj[sn[i]].push_back(sn[j]);
			in_degree[sn[j]]++;

			adj[sn[j]].push_back(sn[i]);
			out_degree[sn[i]]++;
		}
	}
}

// feat. 2-SAT - 4
// 2-SAT은 SCC가 기반이 됨.
int neg(int x) { return x > v ? x - v : x + v; }

void _init() {
	cin >> v >> e;
	for (int i = 0, a, b; i < e; ++i) {
		cin >> a >> b;
		if (a < 0) a = -a + v;
		if (b < 0) b = -b + v;

		// (X V Y) == ㄱX->Y == ㄱY->X
		graph[neg(a)].push_back(b);
		graph[neg(b)].push_back(a);
	}
}

void _solve() {
	_init();

	for (int i = 1; i <= v * 2; ++i) if (!dfsn[i]) dfs(i);

	bool flag = 0;
	for (int i = 1; i <= v; ++i) {
		if (sn[i] == sn[neg(i)]) {
			flag = 1;
			break;
		}
	}

	if (flag) cout << 0 << '\n';
	else {
		cout << 1 << '\n';
		// X -> Y 경우 X가 거짓 => Y는 참 or 거짓, X가 참 => Y는 무조건 참
		// X -> Y가 되는 경우는 (ㄱX V Y)임. 위의 조건이 만족하면 이 식은 항상 참
		// sn[i] < sn[neg(i)] 로 한 이유를 간단히 설명하자면
		// (X V X)인 경우 ㄱX -> X 형태가 됨.
		// 이 식을 SCC를 통해 번호를 메기면 ㄱX보다 X가 SCC 특성상 더 작은 번호를 갖게 됨
		// (X V X)가 참이 되려면 당연히 X가 참이여야함
		for (int i = 1; i <= v; ++i) cout << (sn[i] < sn[neg(i)]) << ' ';
		cout << '\n';
	}
}