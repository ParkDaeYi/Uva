#include <iostream>
#include <algorithm>
#define MOD 1000000007
using namespace std;

// 조합
int dp[1001][1001], n, m;

void nCk() {
	cin >> n >> m;

	dp[1][0] = dp[1][1] = 1;
	for (int i = 2; i <= n + m; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (i == j || j == 0) dp[i][j] = 0;
			dp[i][j] = min((int)1e9, dp[i - 1][j - 1] + dp[i - 1][j]);
		}
	}
}

// 조합_모듈러 역원
// A: N!, B: K!(N - K)! => (A / B) % MOD 로 식을 세울 수 있지만 MOD를 분자, 분모에 나눠서 적용하지 못한다.
// 그러므로, 이것을 풀어 쓰면 (A * B^-1) % MOD로 바꿀 수 있다.
// 여기서 B^-1 의 역원을 구한 후 A와 곱하면 값을 구할 수 있다.
typedef long long int llt;
llt fac[10001], n, m, ans;

void nCk_Inverse() {
	cin >> n >> m;
	fac[0] = fac[1] = 1;
	for (int i = 2; i < n + 1; ++i) fac[i] = ((fac[i - 1] % MOD) * i) % MOD;
	llt q = 0, tmp = 0, r1 = MOD, r2 = (fac[n - m] * fac[m]) % MOD, t1 = 0, t2 = 1;
	while (r2) {
		q = r1 / r2;
		tmp = r1;
		r1 = r2;
		r2 = tmp - r2 * q;
		tmp = t1;
		t1 = t2;
		t2 = tmp - t2 * q;
	}
	if (t1 < 0)t1 += MOD;
	ans = (fac[n] * (t1 % MOD)) % MOD;
	cout << ans;
}

// 카탈란 수
// Cn : (2n)! / (n! * (n + 1)!)
// 오일러가 (n + 2)-가형을 n개의 삼각형으로 나눌 수 있는 경우의 수
// C0 = 1, C1 = 1, C2 = 2, C3 = 5, C4 = 14......................
llt d[5001] = { 1 };
int n;

void catalanNumber() {
	cin >> n;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 0; j < i; j++) {
			d[i] += (d[j] % MOD) * (d[i - 1 - j] % MOD) % MOD;
			d[i] %= MOD;
		}
		d[i] %= MOD;
	}

	cout << d[n];
}

// 완전(교란) 순열
// 점화식
// 1) D(n) = n * D(n - 1) + (-1)^n
// 2) D(n) = (n - 1)(D(n - 1) + D(n - 2))
// 동일한 원소로 이루어진 순열 중 서로 다른 A, B가 동일한 위치에 같은 원소가 하나도 없을 경우에
// A 순열과 B 순열은 완전순열 관계라 한다.
int n;
llt a, b = 1, c;

void completePermutation() {
	cin >> n;
	for (llt i = 3; i <= n; ++i) {
		c = (i - 1) * (a + b) % MOD;
		a = b, b = c;
	}
	if (n == 1) cout << 0;
	else if (n == 2) cout << 1;
	else cout << c;
}

// 제 1종 스털링 수 ( 1 ~ n 까지의 수가 있을 때, k 개의 사이클을 만들 수 있는 경우의 수 [n, k] )
// 1 ~ n 까지의 수가 있을 때, k 개의 사이클을 만들 수 있는 경우의 수 [n, k]
// [1, 1] = 1, [n, 0] = 0, [n, 1] = (n - 1)!, [n, n] = 1,
// [n, k] = [n - 1, k - 1] + (n - 1) * [n - 1, k]
// [n - 1, k - 1] : 새로운 사이클에 끼어드는 경우, [n - 1, k] : 기존 사이클에 끼어드는 경우
int n, m;
llt dp[21][21] = { 1 };

llt gcd(llt a, llt b) {
	return b ? gcd(b, a % b) : a;
}

void stirlingNumbers_1stType() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++)
		dp[i][j] = dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j]; //제 1종 스털링 수 점화식
	for (int i = 1; i <= n; i++) dp[n][i] += dp[n][i - 1]; // 모든 k 갯수의 사이클을 더함
}

// 제 2종 스털링 수 ( n 개의 수를 k 개의 파티션으로 나누는 방법 {n, k} )
// {1, 1} = 1, {n, 0} = 0, {n, 1} = 1, {n, n} = 1,
// {n, k} = {n - 1, k - 1} + k * {n - 1, k}
// {n - 1, k - 1} : n 번째 원소를 싱글그룹으로 만든다, k * {n - 1, k} : n - 1 개의 k 개의 그룹 중 하나에 삽입

// Integer Partition ( 정수를 다른 정수들의 합으로 표현 ex. 5: [5], [4][1], [3][2], [3][1][1].....)
// 이 때, f(n, k)는 n을 덧셈으로 표현하되, 제일 큰 수는 k 이하인 파티션의 개수
// f(n, k), if(k > n) = f(n, n)
// f(n, 1) = 1, f(n, 0) = 0, f(1, 1) = 1,
// f(n, k) = f(n - k, k) + f(n, k - 1)
// f(n - k , k) : 제일 큰 수가 k 일 때, f(n, k - 1) : 제일 큰 수가 k가 아닐 때