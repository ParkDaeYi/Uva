#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define VERTEX 52
#define INF 1e9
using namespace std;

// 네트워크 플로우 (feat. 최대 유량)	O(V * E^2)
// ==> 그래프에서 각 노드들 간의 용량(Capacity)이 정의되어 있을 시,
//		시작점(source)에서 끝점(target)까지 흐를 수 있는 최대 유량을 구함.
// - 소스(S, source) : 시작점
// - 싱크(T, sink) : 끝점
// - 정점(Vertex) : 유량이 모이는 위치
// - 간선(Edge) : 유량이 흐르는 파이프 역할
// - 용량(Capacity) : 유량이 흐를 수 있는 크기
// - 유량(Flow) : 간선에 흐르는 현재 유량의 크기
// - 잔류 유량(Residual Flow) : Capacity-Flow로써 현재 간선에 흐를 수 있는
//								유량이 얼마인지를 나타냄
int n, ans;
int c[VERTEX][VERTEX];	// c[i][j]: i에서 j로 가는 간선의 용량
int f[VERTEX][VERTEX];	// f[i][j]: i에서 j로 현재 흐르는 유량
vector<int> adj[VERTEX];	// 인접 리스트

// 1. 특정 경로를 따라 유량을 보낼 때는 그 경로에 포함된 간선 중
//	가장 용량이 작은 간선에 의해 결정 됨.
// 2. 용량 제한 속성 : f(u,v) <= c(u,v)
// 3. 유량의 대칭성 : f(u,v) = -f(v,u) (핵심!)
// 4. 나오는 유량과 들어오는 유량의 합은 항상 같아야 한다.

inline int ctoi(char x) {
	if (x <= 'Z') return x - 'A';
	return x - 'a' + 26;
}

int _solve() {
	cin >> n;
	for (int i = 0, w; i < n; ++i) {
		char u, v;
		cin >> u >> v >> w;
		u = ctoi(u), v = ctoi(v);
		c[u][v] = c[v][u] += w;	// 같은 간선이 여러 번 들어올 수 있으므로 +=
		adj[u].push_back(v);
		adj[v].push_back(u);	// 역방향 간선도 추가
	}
	int s = ctoi('A'), e = ctoi('Z');
	while (1) {
		int prev[VERTEX];
		fill(prev, prev + VERTEX, -1);
		queue<int> q;
		q.push(s);
		while (!q.empty() && prev[e] == -1) {
			int cur = q.front();
			q.pop();
			for (int nxt : adj[cur]) {
				// c[cur][nxt] > f[cur][nxt]: i에서 j로 유량을 흘릴 여유가 있는가?
				// prev[nxt] == -1: nxt 정점을 아직 방문하지 않았는가?
				if (c[cur][nxt] > f[cur][nxt] && prev[nxt] == -1) {
					prev[nxt] = cur;	// 경로를 기억하기 위해 prev 배열 사용
					q.push(nxt);
					if (nxt == e) break;	// 싱크에 도달할 경우 break
				}
			}
		}
		// 싱크로 가는 경로가 없을 경우 루프 탈출
		if (prev[e] == -1) break;

		// 경로상에서 가장 허용치가 낮은 곳을 찾음
		int flow = INF;
		for (int i = e; i != s; i = prev[i]) flow = min(flow, c[prev[i]][i] - f[prev[i]][i]);
		// 찾은 flow만큼 해당 경로에 유량을 흘려줌
		for (int i = e; i != s; i = prev[i]) {
			f[prev[i]][i] += flow;
			f[i][prev[i]] -= flow;
		}
		ans += flow;
	}
	return ans;
}

// 디닉		O(V^2 * E)
// 1. 레벨 그래프 (Level Graph)
//	- 모든 정점에 대해 레벨을 매겨 놓은 그래프
//	- Source가 되는 정점은 레벨이 0이고,
//	 소스와 인접한 정점들의 레벨은 1, 레벨 1 정점과 인접한 정점들은 레벨 2....
//	 마지막 Sink의 레벨은 n 이 된다.
// 2. 차단 유량 (Blocking Flow)
//  - 레벨 그래프를 형성할 때
//   레벨 그래프를 형성하는  조건에 맞지 않는 간선들을 제외한 것들을 의미함.
int n, c[VERTEX][VERTEX], f[VERTEX][VERTEX], ans;
int level[VERTEX];	// 레벨 그래프에서 각 정점의 레벨을 저장 (S는 0)
int work[VERTEX];	// DFS 중 해당 정점이 몇 번째 간선까지 탐색했는지 기억하는 용도
vector<int> adj[VERTEX];

int ctoi(char c) {
	if (c <= 'Z') return c - 'A';
	return c - 'a' + 26;
}

// 디닉 전용 BFS 함수
// 우선적으로 BFS를 이용하여 잔여용량이 0 이상인 간선에 대하여
// 레벨 그래프를 만들어 준다.
bool bfs(int S,int E) {
	// 레벨 값 초기화
	fill(level, level + VERTEX, -1);
	level[S] = 0;
	
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (int nxt : adj[cur]) {
			// 레벨 값이 설정되지 않았고, 간선에 잔여량이 남아있을 경우 이동
			if (level[nxt] == -1 && c[cur][nxt] > f[cur][nxt]) {
				level[nxt] = level[cur] + 1;	// next의 레벨은 current + 1
				q.push(nxt);
			}
		}
	}
	// 싱크에 도달하면 true
	return level[E] != -1;
}

// 디닉 전용 DFS 함수, cur에서 dest까지 최대 flow만큼 유량을 보냄
// DFS 함수는 차단 유량이라는 개념을 이용한다.
// 레벨 그래프에서의 차이가 딱 1만큼 클 때만 유량을 흘려줄 수 있다.
// 더 이상 흘릴 수 있는 유량이 없을 때까지 탐색한다.
// 차단 유량만큼 간선의 용량을 줄여주고 역방향 간선에 차단 유량만큼 용량을 확장시켜 주면 된다.
int dfs(int cur, int dest, int flow) {
	if (cur == dest) return flow;

	// 현재 정점에서 인접한 정점들을 탐색
	// 이때, 이번 단계에서 이미 쓸모없다고 판단한 간선은 다시 볼 필요가 없기 때문에
	// work 배열로 탐색한 간선의 수를 카운팅함
	for (int& i = work[cur]; i < adj[cur].size(); ++i) {
		int nxt = adj[cur][i];
		// nxt의 레벨이 cur의 레벨 + 1 이고, 간선에 잔여량이 남아있으면 이동
		if (level[nxt] == level[cur] + 1 && c[cur][nxt] > f[cur][nxt]) {
			// ret: flow와 다음 dfs함수의 결과 중 최솟값
			// 결과적으로 경로상의 간선들 중 가장 작은 유량이 됨
			int ret = dfs(nxt, dest, min(c[cur][nxt] - f[cur][nxt], flow));
			// 싱크까지의 경로가 있다면 유량을 ret만큼 흘리고 종료
			if (ret > 0) {
				f[cur][nxt] += ret;
				f[nxt][cur] -= ret;
				return ret;
			}
		}
	}
	return 0;
}

int solve() {
	cin >> n;
	for (int i = 0, u, v, w; i < n; ++i) {
		char a, b;
		cin >> a >> b >> w;
		u = ctoi(a), v = ctoi(b);
		c[u][v] = c[v][u] += w;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int S = ctoi('A'), E = ctoi('Z');
	// 디닉 알고리즘 수행
	// 레벨 그래프를 구축하여 싱크에 도달 가능한 동안 반복
	while (bfs(S, E)) {
		fill(work, work + VERTEX, 0);
		// 차단 유량(blocking flow) 구하기
		while (1) {
			int flow = dfs(S, E, INF); // DFS를 사용하여 각 경로를 찾음
			if (!flow) break; // 경로가 없을 경우 종료
			ans += flow;
		}
	}
	return ans;
}
