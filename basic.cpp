#include <iostream>
#include <algorithm>
using namespace std;

int n, m, arr[100000];

// 이분탐색 (feat. 수 찾기)
bool Binary_Search(int target) {
	int mid, left = 0, right = n;
	while (left <= right) {
		mid = (left + right) >> 1;
		if (arr[mid] == target) return 1;	// 찾았을 경우 return
		else if (arr[mid] < target) left = mid + 1;	// target이 arr[mid]보다 클 경우 더 오른쪽으로 이동을 해야하므로 left를 mid+1로 이동
		else right = mid - 1;	// target이 arr[mid]보다 작을 경우 더 왼쪽으로 이동해야 함
	}
	return 0;	// 못 찾음
}

void init() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> arr[i];
	sort(arr, arr + n);	// 이분탐색을 수월하게 하기 위해 정렬을 해줌
	cin >> m;
	for (int i = 0, x; i < m; ++i) {
		cin >> x;
		cout << Binary_Search(x) << '\n';
	}
}

// Lower Bound: target보다 크거나 같은 첫번째 위치(이상)를 반환
int Lower_Bound(int arr[], int left, int right, int target) {
	int mid;
	while (left < right) {
		mid = (left + right) / 2;
		if (arr[mid] < target) left = mid + 1;	// 중간 값이 원하는 값보다 작을 경우, 시작 값을 중간 값+1로 설정하여 다시 탐색
		else right = mid;	// 중간 값이 원하는 값보다 크거나 같을 경우, 끝 값을 중간 값으로 설정하여 다시 탐색
	}
	return right;
}

// Upper Bound: target보다 큰 첫번째 위치(초과)를 반환
int Upper_Bound(int arr[], int left, int right, int target) {
	int mid;
	while (left < right) {
		mid = (left + right) >> 1;
		if (arr[mid] <= target) left = mid + 1;	// 중간 값이 원하는 값보다 작거나 같을 경우, 시작 값을 중간 값+1로 설정하여 다시 탐색
		else right = mid;	// 중간 값이 원하는 값보다 클 경우, 끝 값을 중간 값으로 설정하여 다시 탐색
	}
	return right;
}

#include <queue>

int n, m, v, graph[1001][1001];
bool visit[1001];

// DFS, BFS (feat. DFS와 BFS)
// DFS( Depth-First Search ), 깊이 우선 탐색
void dfs(int idx) {
	cout << idx << ' ';
	visit[idx] = 1;	// 방문한 노드 체크
	for (int i = 1; i <= n; ++i) {
		if (visit[i] || !graph[idx][i]) continue;	// 이미 방문했거나 연결되지 않았을 경우 continue
		dfs(i);
	}
}

// BFS( Breadth-First Search ), 너비 우선 탐색
void bfs() {
	queue<int> q;
	q.push(v); visit[v] = 0;	// 시작 지점 queue에 삽입 및 방문 체크
	while (!q.empty()) {	// queue가 소진될 때까지 계속
		int cur = q.front();	// queue의 앞에 노드 추출
		q.pop();
		cout << cur << ' ';
		for (int i = 1; i <= n; ++i) {
			if (!visit[i] || !graph[cur][i]) continue;	// 이미 방문햇거나 연결되지 않았을 경우 continue
			q.push(i);  visit[i] = 0;	// 큐에 노드 추가 및 방문 체크
		}
	}
}

void init_() {
	cin >> n >> m >> v;
	for (int i = 0, from, to; i < m; ++i) {
		cin >> from >> to;
		graph[from][to] = graph[to][from] = 1;
	}

	dfs(v);
	cout << '\n';
	bfs();
}

int n, m, arr[10001];

// 투 포인터 (feat. 수들의 합 2)
int Two_Pointers() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> arr[i];

	int low = 0, high = 0, sum = arr[0], cnt = 0;

	while (low <= high && high < n) {
		if (sum < m) sum += arr[++high];	// m보다 작을 경우 '+'
		else if (sum == m) {
			cnt++; sum += arr[++high];	// m과 같을 경우 '+' ( '-' 도 가능, 소스짜기 나름 )
		}
		else {
			sum -= arr[low++];	// m보다 클 경우 '-'
			if (low > high && low < n) {	// 만약 low가 high보다 클 경우
				high = low;
				sum = arr[low];
			}
		}
	}
	return cnt;
}