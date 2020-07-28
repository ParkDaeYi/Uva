// Disjoint-set(서로소 집합, 유니온 파인드), 위상 정렬, 최소 신장 트리(MST), 최소 공통 조상(LCA)

// Disjoint-set(서로소 집합, 유니온 파인드)
// 유니온 파인드는 기본적으로 union 연산과 find 연산 기능을 갖춤
// disjoint한 집합들을 표현하는 자료구조임
// ==> ex. 어떤 두 집합 사이에도 교집합의 원소가 하나도 없고,
//      모든 집합의 합집합은 전체 집합임
#include <iostream>
#define N 100000
using namespace std;

int parent[1000001];

// 초기에는 1 ~ n 까지 각자 자기 자신을 가리키고 있음
// (자신의 부모는 자기 자신으로 설정)
void init_1() {
	for (int i = 1; i <= N; ++i) parent[i] = i;
}

// find 연산   O(lgN)
int getParent(int x) {
	// x가 자신의 부모 값과 같을 경우 return
	if (x == parent[x]) return x;
	// 그렇지 않을 경우 자신의 최상위 부모까지 탐색 및 갱신
	return parent[x] = getParent(parent[x]);
}

// union 연산   O(lgN)
void merge(int a, int b) {
	// a와 b의 최상위 부모 값을 가져옴
	a = getParent(a);
	b = getParent(b);
	// a와 b의 값이 같을 경우는 서로 같은 트리에 속해 있음
	// (안해줘도 됨)
	if (a == b) return;
	// 큰 값, 혹은 작은 값에 넣어줌 (정하기 나름, 그냥 넣어도 상관은 없음)
	if (a > b) swap(a, b);
	parent[b] = a;
}

// 위상 정렬(Topological Sort)
// DAG(비순환 방향 그래프)에서 그래프의 방향성을 거스르지 않고 정점들을 나열하는 것
// ==> 싸이클이 존재하지 않으며 유향 그래프이다
#include <vector>

int indegree[N], outdegree[N];
vector<int> graph[N];

// 위상 정렬은 주로 indegree를 사용하지만 outdegree도 잊으면 안됨
void init_2() {
	for (int i = 0, from, to; i < N; ++i) {
		cin >> from >> to;
		graph[from].push_back(to);	// from -> to
		indegree[to]++;
		outdegree[from]++;
	}
}

// 최소 신장 트리(Minimum Spanning Tree / MST)
// 무향 연결 가중 그래프 G에서 간선의 가중치의 합이 최소인 신장(Spanning) 트리
// 크루스칼	O(ElogE)
// => 간선 위주의 알고리즘
// ==> 모든 간선에 대해 가중치가 가장 작은 것들을 우선으로하여 MST의 조건을 만족할 수 잇는
//		간선을 V - 1개 선택하는 방법
// ==> 아직 선택되지 않은 간선들 중에 가중치가 가장 작으면서 사이클을 만들지 않는
//		간선을 탐욕적으로 선택하도록 구현

// 1.1. 유니온 파인드에 사용할 배열 초기화
// 1.2. 그래프 정보 입력
// 1.3. 간선들을 가중치 순으로 오름차순 정렬
// 2.1. 간선을 훑으면서 연결되어 있지 않은 정점들을 연결하고
//		가중치를 추가
// 2.2. 간선의 개수가 V - 1 개가 되면 종료
#include <algorithm>
struct Node {
	int from, to, cost;
}adj_1[100001];
int n, m, parent[1001], ans;

int getParent(int x) {
	if (x == parent[x]) return x;
	return parent[x] = getParent(parent[x]);
}

void init_3() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) parent[i] = i;	// 자기 자신을 저장 (초기 값)
	for (int i = 0, a, b, c; i < m; ++i) cin >> adj_1[i].from >> adj_1[i].to >> adj_1[i].cost;
	// 가중치를 기준으로 오름차순 정렬
	sort(adj_1, adj_1 + m, [](const Node& n1, const Node& n2) {
		return n1.cost < n2.cost;
	});
}

void Kruskal() {
	for (int i = 0; i < m; ++i) {
		int from = adj_1[i].from, to = adj_1[i].to, cost = adj_1[i].cost;
		from = getParent(from);
		to = getParent(to);
		// from 과 to의 부모가 같다는 말은
		// from 과 to가 연결되어 있다는 뜻
		if (from == to) continue;
		ans += cost;
		if (from < to) swap(from, to);
		parent[to] = from;
	}
	cout << ans;
}

// 프림	O(ElogV)
// => 정점 위주의 알고리즘, 프림은 크루스칼과 다르게 시작점을 정하고 시작함
// ==> 시작 정점을 기준으로 가중치가 가장 작은 간선과 연결된 정점을 선택하여
//		트리를 확장시켜나가는 방법

// 1. 그래프 연결
// 2. 현재 정점과 연결된(아직 방문하지 않은) 정점(들)을
//		우선 순위 큐에 삽입
// 3. 모든 정점을 방문하고 종료
#include <queue>
typedef pair<int, int> pii;
int n, m, cnt, ans;
bool visit[1001];
vector<pii> adj_2[1001];

void Prim() {
	cin >> n >> m;
	for (int i = 0, a, b, c; i < m; ++i) {
		// a, b 정점, c 가중치
		cin >> a >> b >> c;
		// 우선 순위 큐에서 가중치를 기준으로 정렬할 것이므로
		// c 를 first에 저장
		adj_2[a].push_back({ c,b });
		adj_2[b].push_back({ c,a });
	}

	priority_queue<pii, vector<pii>, greater<pii>> pq;
	// 출발 지점을 1로 선택
	// (문제에서 주어졌을 경우가 아니면 아무거나 상관 없음)
	pq.push({ 0,1 });
	while (!pq.empty()) {
		int cur = pq.top().second, cost = pq.top().first;
		pq.pop();
		if (visit[cur]) continue;
		visit[cur] = 1;
		ans += cost;
		// 모든 정점을 방문 했을 경우
		if (++cnt == n) break;
		for (pii nxt : adj_2[cur]) {
			if (visit[nxt.second]) continue;
			pq.push(nxt);
		}
	}
	cout << ans;
}

// 최소 공통 조상(Lowest Common Ancestor / LCA)		(feat. LCA 2)
// LCA란, 트리상에서 어떤 두 정점 u, v가 있을 때,
// u이거나 u의 조상이면서 동시에 v이거나 v의 조상인 노드들 중 가장 깊은 노드를 뜻함
// 트리의 깊이를 H라 할 때,
// 시간복잡도는 O(H), 최악의 경우 O(N)
#include <cmath>
const int max_level = (int)floor(log2(N));
int n, m, depth[N], ac[N][20];
vector<int> gp[N];

void makeTree(int now, int parent) {
	// 예제 입력을 토대로 하면 depth 배열은
	//	i	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15
	//	d	0	1	1	2	2	2	2	2	3	3	3	3	3	3	4

	//	ac 배열은
	//		0	1	2	==> 2^n 위에 있는 조상의 번호로 이루어져 있음
	//	1	0
	//	2	1	0
	//	3	1	0
	//	4	2	1	0
	//	5	2	1	0
	//	6	2	1	0
	//	7	3	1	0
	//	8	3	1	0
	//	9	4	2	0
	//	10	4	2	0
	//	11	5	2	0
	//	12	5	2	0
	//	13	7	3	0
	//	14	7	3	0
	//	15	11	5	1	0

	// depth의 현재는 부모 바로 밑에 있으므로 + 1
	depth[now] = depth[parent] + 1;
	// now의 바로 위 조상이 parent
	ac[now][0] = parent;
	for (int i = 1, tmp; i <= max_level; ++i) {
		tmp = ac[now][i - 1];
		ac[now][i] = ac[tmp][i - 1];
	}
	for (int nxt : graph[now]) {
		if (nxt != parent) makeTree(nxt, now);
	}
}

void init_4() {
	cin >> n;
	for (int i = 1, from, to; i < n; ++i) {
		cin >> from >> to;
		gp[from].push_back(to);
		gp[to].push_back(from);
	}
	// 트리의 루트의 depth를 0으로 할 것임
	// 정점들은 1부터 시작하므로 depth 배열의 0번째 인덱스에 -1을 넣음
	depth[0] = -1;
	makeTree(1, 0);
}

int LCA(int a, int b) {
	// 우선 depth 먼저 비교
	if (depth[a] != depth[b]) {
		// 연산의 편의를 위해 b가 a보다 깊은 것으로 설정
		if (depth[a] > depth[b]) swap(a, b);
		for (int i = max_level; i >= 0; --i) {
			// b의 조상 값을 통해 비교
			if (depth[a] <= depth[ac[b][i]]) b = ac[b][i];
		}
	}
	int lca = a;
	// 깊이는 같은데 서로 값이 다를 경우 서로의 조상을 비교
	if (a != b) {
		for (int i = max_level; i >= 0; --i) {
			if (ac[a][i] != ac[b][i]) {
				a = ac[a][i];
				b = ac[b][i];
			}
			lca = ac[a][i];
		}
	}
	return lca;
}