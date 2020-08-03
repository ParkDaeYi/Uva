// 다익스트라, 벨만-포드, 플로이드 와샬

// 다익스트라
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#define VERTEX 20001
#define INF 1e9
using namespace std;
typedef pair<int, int> pii;

int v, e, k;
bool visit[VERTEX];
vector<pii> graph[VERTEX];

void init() {
	for (int i = 0, from, to, cost; i < e; ++i) {
		cin >> from >> to >> cost;
		graph[from].push_back({ cost,to });
	}
}

// 방문 배열 사용
void dijkstra_1() {
	// 시작점을 제외하고 나머지는 INF로 처리
	vector<int> dist(v, INF);
	dist[k] = 0;
	// 최단 거리를 알고 싶기 때문에 오름차순
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push(pii(0, k));
	while (!pq.empty()) {
		int cost = pq.top().first, cur = pq.top().second;
		pq.pop();
		if (visit[cur]) continue;
		visit[cur] = 1;
		dist[cur] = cost;
		for (pii& nxt : graph[cur]) {
			if (visit[nxt.second]) continue;
			// dist 배열에 가중치를 더해줘도 되고
			// nxt 변수에 더한 상태로 pq에 넣어도 됨
			nxt.first += cost;
			pq.push(nxt);
		}
	}
}

// 방문 배열 사용 안함
// 다익스트라는 최단 경로를 구하는 알고리즘이기 때문에
// dist 배열을 통해 거리 비교만 해줘도 된다
void dijkstra_2() {
	vector<int> dist(v, INF);
	dist[k] = 0;
	// greater 를 써서 오름차순으로 해도 되지만
	// less를 사용해도 된다
	priority_queue<pii, vector<pii>, less<pii>> pq;
	pq.push(pii(0, k));
	while (!pq.empty()) {
		// pq에 cost는 음수로 넣었으므로
		// 값을 가져올 때는 - 를 꼭 해야함
		int cost = -pq.top().first, cur = pq.top().second;
		pq.pop();
		if (dist[cur] < cost) continue;
		// (&를 쓰는 이유는 그냥 좀 더 빨라지기 위함)
		for (pii& i : graph[cur]) {
			int nxt = i.second;
			int d = i.first + cost;
			if (dist[nxt] > d) {
				dist[nxt] = d;
				// less를 사용했으므로 가중치를 - 해서 넣음
				// ==> 음수로 변환하여 오름차순과 같은 방식으로 사용
				pq.push({ -d,nxt });
			}
		}
	}
}

// 벨만-포드
// 음의 사이클을 검증하기 위한 알고리즘
bool Bellman_Ford() {
	vector<int> dist(v + 1, INF);
	dist[1] = 0;
	bool isCycle = 0;
	int loop = 1;
	// 최단 경로 알고리즘을 감안하면
	// 같은 정점을 두 번 지날 일은 없고
	// 최단 경로의 간선 개수는 많아 봐야 V - 1 개임
	// 즉 V - 1 번에 최단 경로를 구할 수 있다
	// 그리고 마지막 V 번에 한 번 더 최단 경로를 구하는데
	// 이미 다 구해진 최단 경로에서 값이 갱신이 된다면
	// 음의 사이클이 존재한다고 판단한다
	while (loop <= v) {
		for (int i = 1; i <= v; ++i) {
			if (dist[i] == INF) continue;
			for (pii nxt : graph[i]) {
				if (dist[nxt.first] > dist[i] + nxt.second) {
					// 마지막 루프에서도 값이 갱신된다면
					// 음의 사이클이 존재한다고 판단
					if (loop == v) {
						isCycle = 1;
						break;
					}
					dist[nxt.first] = dist[i] + nxt.second;
				}
			}
		}
		loop++;
	}
}

int adj[101][101];

// 플로이드 와샬
// 암기
void Floyd_Warshall(){

	for (int i = 0, from, to, cost; i < e; ++i) {
		cin >> from >> to >> cost;
		if (!adj[from][to]) adj[from][to] = cost;
		else adj[from][to] = min(adj[from][to], cost);
	}
	for (int via = 1; via <= v; ++via)
		for (int from = 1; from <= v; ++from) {
			if (!adj[from][via]) continue;	// 없어도 됨
			for (int to = 1; to <= v; ++to) {
				if (from == to || !adj[via][to]) continue;	// 없어도 됨
				if (!adj[from][to] || adj[from][to] > adj[from][via] + adj[via][to])
					adj[from][to] = adj[from][via] + adj[via][to];
			}
		}

}