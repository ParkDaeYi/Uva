// 자료구조 (이진 트리, 힙, 트라이, 셋 & 맵)

#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> adj[26];

// 이진 트리(feat. 트리 순회)
void preorder(int itr) {	// 전위 순회 (루트 -> 왼쪽 -> 오른쪽)
	if (itr == -1) return;
	cout << (char)('A' + itr);
	preorder(adj[itr][0]);
	preorder(adj[itr][1]);
}

void inorder(int itr) {	// 중위 순회 (왼쪽 -> 루트 -> 오른쪽)
	if (itr == -1) return;
	inorder(adj[itr][0]);
	cout << (char)('A' + itr);
	inorder(adj[itr][1]);
}

void postorder(int itr) {	// 후위 순회 (왼쪽 -> 오른쪽 -> 루트)
	if (itr == -1) return;
	postorder(adj[itr][0]);
	postorder(adj[itr][1]);
	cout << (char)('A' + itr);
}

void solve() {
	cin >> n;
	char c, x;
	for (int i = 0; i < n; ++i) {
		cin >> c;
		for (int j = 0; j < 2; ++j) {
			cin >> x;
			if (x == '.') adj[c - 'A'].push_back(-1);
			else adj[c - 'A'].push_back(x - 'A');
		}
	}
	preorder(0); cout << '\n';
	inorder(0); cout << '\n';
	postorder(0);
}

// 힙(Heap)
#include <queue>
#include <algorithm>
#include <functional>
typedef pair<int, int> pii;

void heap() {
	priority_queue<int, vector<int>, less<int>> pq;	// 큐의 기본 형태(내림차순)
	priority_queue<pii, vector<pii>, greater<pii>> gpq;	// 오름차순(pair 사용 가능, 대신 key 값을 기준으로 정렬)
	// (greater에 에러가 뜰 경우 #include <functional> 추가하면 됨)
	// pq.push(element): 원소 추가, pq.pop(): top의 원소 삭제, pq.top(): top에 있는 원소를 반환(queue의 경우는 front())
	// pq.empty(): 비어있으면 true 아니면 false, pq.size(): 원소들의 수를 반환
	int arr[100];
	sort(arr, arr + 100, less<int>());	// sort의 기본 형태(오름차순)
	sort(arr, arr + 100, greater<int>());	// 내림차순
	// priority_queue(우선 순위 큐)는 sort와 정렬 기준이 반대라고 생각하면 됨
}

// 구조체를 사용할 경우
struct point {
	int x, y, v;
	point(int x = 0, int y = 0, int v = 0) :x(x), y(y), v(v) {}
};
struct cmp {
	bool operator()(point p1, point p2) {
		return p1.x > p2.x;
	}
};
priority_queue<point, vector<point>, cmp> pp;

// 비교 연산자만 사용할 경우
bool operator<(point& p1, point& p2) {
	return p1.x < p2.x;
}
priority_queue<point> ppq;

// 트라이(Trie) (feat. 전화번호 목록)
#include <memory.h>

int n;
char num[10000][11];

class Trie {
private:
	Trie* nxt[10];
	bool term;
public:
	Trie() : term(0) {
		memset(nxt, 0, sizeof(nxt));	// 초기화(fill 사용하니까 에러 뜸)
	}
	void insert(const char* key) {
		if (*key == '\0') term = 1;	// 배열의 끝까지 갔을 경우 끝났음을 표시
		else {
			int cur = *key - '0';
			if (nxt[cur] == NULL) nxt[cur] = new Trie();	// 해당 번호가 없는 경우 새로 생성
			nxt[cur]->insert(key + 1);	// 배열 한 칸 이동
		}
	}
	bool find(const char* key) {
		if (*key == '\0') return 0;	// 겹치는 번호 없음
		if (term) return 1;	// 겹치는 번호 있음
		int cur = *key - '0';
		return nxt[cur]->find(key + 1);	// 배열 한 칸 이동
	}
};

void init() {
	cin >> n;
	Trie* root = new Trie();
	for (int i = 0; i < n; ++i) { cin >> num[i]; root->insert(num[i]); }	// Trie에 삽입
	bool ans = 0;
	for (int i = 0; i < n; ++i) {
		if (root->find(num[i])) {
			ans = 1;
			break;
		}
	}
	cout << (ans ? "NO\n" : "YES\n");
}

// set, map
#include <set>	// 자동 정렬, 기본 정렬기준은 less(오름차순)
#include <map>
#include <unordered_set>	// 자동 정렬 X (대신 더 빠름)
#include <unordered_map>
// set과 map의 key 값은 중복이 허용 되지 않음 (중복 불가능)

set<int, less<int>> s;	// default
set<int, greater<int>> sg;	// 내림차순
set<pii> ss;
map<int, char, less<int>> mp;
map<int, char, greater<int>> mpg;	// key 값을 기준으로 하기 때문
map<pii, pii> mpp;
// map과 set의 멤버 함수는 동일함
// https://blockdmask.tistory.com/79

void Set_Map() {
	// set 원소 접근하기
	for (auto itr = s.begin(); itr != s.end(); itr++) {
		cout << *itr << ' ';
	}
	for (auto itr : s) {
		cout << itr << ' ';
	}

	// set 원소 존재 여부
	if (s.find(10) == s.end());	// 없음
	if (s.count(10));	// s.count(10)의 값은 무조건 0 또는 1 ==> 중복을 허용하지 않기 때문

	// map 원소 접근하기
	for (auto itr = mp.begin(); itr != mp.end(); itr++) {
		cout << itr->first << ' ' << itr->second << ' ';
	}
	for (auto itr : mp) {
		cout << itr.first << ' ' << itr.second << ' ';
	}
}
