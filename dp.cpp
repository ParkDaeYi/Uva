// 동적 계획법 중 LCS, LIS, TSP만 정리함

// LCS(Longest Common Subsequence, 최장 공통 부분 수열)
// ==> 수열이 주어졌을 때, 모두의 부분 수열이 되는 수열 중 가장 긴 것을 찾아야 함
#include <iostream>
#include <string>
#include <algorithm>
#define N 1001
using namespace std;

int dp[N][N];

void LCS(string str1, string str2) {

	// ex.
	// ACAYKP 와 CAPCAK의 LCS를 구해야 한다고 가정
	//	2차원 배열을 이용하여 아래와 같이 완성 시킨다.
	//	str			A	C	A	Y	K	P
	//		i	0	1	2	3	4	5	6
	//		0	0	0	0	0	0	0	0	
	//	C	1	0	0	1	1	1	1	1
	//	A	2	0	1	1	2	2	2	2
	//	P	3	0	1	1	2	2	2	3
	//	C	4	0	1	2	2	2	2	3
	//	A	5	0	1	2	3	3	3	3
	//	K	6	0	1	2	3	3	4	4
	// 완성된 2차원 배열을 통해 
	// 최장 공통 부분 수열과 그 길이를 구할 수 있다.
	// (현재 인덱스 번호에서 같은 문자를 만났을 경우
	// 대각에 있는 값 + 1을 해줌, dp[i][j] = dp[i - 1][j - 1] + 1
	// 그 외의 경우는 위  중 큰 수를 채택하면 됨)
	for (int i = 1;i <= str1.length();++i) {
		for (int j = 1;j <= str2.length();++j) {
			if (str1[i - 1] == str2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

}

// LIS(Longest Increasing Subsequence, 최장 증가 수열)
// ==> 수열이 주어졌을 때, 앞에서부터 뒤로 숫자를 선택하며 부분 수열을 구성한다.
//		이 때 부분 수열은 증가하는 순서대로 숫자를 고르면서,
//		고른 부분 수열의 길이가 최대 길이가 되도록 숫자를 선택해야 한다.
typedef pair<int, int> pii;

int arr[N];	// 문제에서 주어진 수열
int cnt[N];	// LIS의 길이를 구하는 배열
pii lis[N];	// LIS를 출력하는 배열

int lower_bd(int, int, int);	// Lower_bound

void LIS(int n) {

	cnt[0] = arr[0];
	lis[0] = { 0,arr[0] };
	int l = 0, h = 1;
	// ex. arr[] = { 10, 20, 10, 30, 20, 50 }
	// h = 1, l = 0, arr[h] = 20, cnt[l] = 10
	//		0		1
	// cnt	10		20'			': 갱신
	// lis	0,10	1,20

	// h = 2, l = 1, arr[h] = 10, cnt[l] = 20
	//		0		1		2
	// cnt	10'		20		
	// lis	0,10	1,20	2,10

	// h = 3, l = 1, arr[h] = 30, cnt[l] = 20
	//		0		1		2		3
	// cnt	10		20		30'
	// lis	0,10	1,20	0,10	2,30

	// h = 4, l = 2, arr[h] = 20, cnt[l] = 30
	//		0		1		2		3		4
	// cnt	10		20'		30
	// lis	0,10	1,20	0,10	2,30	1,20

	// h = 5, l = 2, arr[h] = 50, cnt[l] = 30
	//		0		1		2		3		4		5
	// cnt	10		20		30		50'
	// lis	0,10	1,20	0,10	2,30	1,20	3,50
	while (h < n) {
		if (cnt[l] < arr[h]) {
			cnt[++l] = arr[h];
			lis[h] = { l,arr[h] };
		}
		else {
			int itr = lower_bd(0, l, arr[h]);
			cnt[itr] = arr[h];
			lis[h] = { itr,arr[h] };
		}
		h++;
	}

}

int lower_bd(int left, int right, int target) {
	int mid;
	while (left < right) {
		mid = (left + right) / 2;
		if (arr[mid] < target) left = mid + 1;
		else right = mid;
	}
	return right;
}

// TSP(Traveling Salesman problem, 외판원 순회)
// ==> 한 외판원이 어느 한 도시에서 출발해 N개의 도시를 모두 거쳐 
//		다시 원래의 도시로 돌아오는 순회 여행 경로를 계획하려고 한다.
//		이 때 가장 적은 비용을 들이는 여행 계획을 세워야 한다.
#define INF 0x7fffffff

int n, dist[16][16], cache[16][1 << 16];

// 비트 마스크를 통해 정점을 체크한다.
int TSP(int here, int visited) {
	if (visited == (1 << n) - 1) {
		if (dist[here][0]) return dist[here][0];
		else return INF;
	}
	int& ret = cache[here][visited];
	if (ret) return ret;
	ret = INF;
	for (int next = 1; next < n; ++next) {
		if (visited & (1 << next)) continue;
		if (!dist[here][next]) continue;
		ret = min(ret, TSP(next, visited | (1 << next)) + dist[here][next]);
	}
	return ret;
}
