// 조합론 ( 이항 계수, 카탈란 수, 완전순열(교란순열), 제 1종 스털링 수 )

// 순열(nPk): n가지의 물건 중 k개의 물건을 순서 구분하여 고르는 경우의 수
// ==> n! / (n - k)!

// 중복순열: n가지의 물건 중 중복을 허용하여 k개의 물건을 순서 있게 고르는 경우의 수
// ==> n^k

// 조합(nCk, nCn-k): n가지의 물건 중 k개의 물건을 순서 구분 없이 고르는 경우의 수
// ==> n! / (n - k)! * k!
// == 이항 계수
#include <iostream>
#include <algorithm>
using namespace std;

int dp[201][201];

void Binomial_Coefficients(int n) {
	dp[1][0] = dp[1][1] = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (i == j || !j) dp[i][j] = 1;
			else dp[i][j] = min((int)1e9, dp[i - 1][j - 1] + dp[i - 1][j]);
			//	1
			//	1	1
			//	1	2	1
			//	1	3	3	1
			//	1	4	6	4	1
			//	1	5	10	10	5	1
			//	....
		}
	}
}

// 조합_모듈러 역원
// A: N!, B: K!(N - K)! => (A / B) % MOD 로 식을 세울 수 있지만 MOD를 분자, 분모에 나눠서 적용하지 못한다.
// 그러므로, 이것을 풀어 쓰면 (A * B^-1) % MOD로 바꿀 수 있다.
// 여기서 B^-1 의 역원을 구한 후 A와 곱하면 값을 구할 수 있다.
#define MOD 1000000007
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

// 중복조합(nHk): n가지의 물건 중 중복을 허용하여 k개의 물건을 순서 구분 없이 고르는 경우
// ==> nHk == n+k-1Ck => (n + k - 1)! / (n - 1)! * k!

// 카탈란 수 (Catalan Number) (feat. 미팅의 저주)
// 오일러가 "(n + 2) 각형을 n개의 삼각형으로 나눌 수 있는 경우의 수"를
// 세는 문제를 제안하면서 처음 나타남
// 점화식: Cn ==> (2n)! / n! * (n + 1)!
// Cn+1 ==> (2 * (2n + 1) / (n + 2)) * Cn
#define MOD 987654321
typedef long long int llt;

llt d[5001] = { 1 };

llt Catalan_Number_1(int n) {
	// 카탈란 수 0~10
	// 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, ....

	for (int i = 1; i < n + 1; ++i) {
		for (int j = 0; j < i; ++j) {
			d[i] += (d[j] % MOD) * (d[i - 1 - j] % MOD) % MOD;
			d[i] %= MOD;
		}
		d[i] %= MOD;
	}
	return d[n];
}

llt Catalan_Number_2(int n) {
	// Cn+1 ==> (2 * (2n + 1) / (n + 2)) * Cn 을 구현하면
	// 밑과 같이 구현할 순 있지만
	// 카탈란 수는 급격하게 커지기 때문에 이렇게 구현할 경우
	// 올바른 답을 구할 수 없음
	
	for (int i = 1; i < n; i++) {
		d[i + 1] = (((2 * d[i]) % MOD * (2 * i + 1)) % MOD / (i + 2)) % MOD;
	}

	return d[n];
}

// 완전순열 (Complete Permutation) (feat. 선물 전달)
// == 교란순열 (Derangement)
// 순열의 모든 요수를 바꾼 순열 (제자리에 원소가 있지 않는 순열)
// 완전수열은 !n(subfactorial)으로 표시하며,
// !1 = 0, !2 = 1, !3 = 2, !4= 9, !5 = 44, !6 = 265, !7 = 1854, ....
// !n = d(n) 이라면 d(n) = (n - 1) * (d[n-1] + d[n-2]) 이다.
// 1. i번째의 선물이 j에게 갔고, j의 선물이 i에게 온 경우 (1대 1 교환)
// ==> n명이 있다고 가정, n명 중 이미 2명은 서로 교환했으므로 총 n-2명이 선물을 교환하는 경우의 수로 치환
// 2. i번째의 선물이 j에게 갔지만, j의 선물은 i에게 오지 않은 경우 (일방적 교환)
// ==> n명이 있다고 가정, n명 중 1명만 선물이 정해진 상태이므로 나머지 n-1개의 선물을 나눠주면 됨.
//		총 n-1명이 선물을 교환하는 경우의 수로 치환
// 1, 2번 모든 경우에서 i번 사람이 j번만을 선택한 경우임 ==> j를 제외하면 총 경우의 수는 n-1
// 따라서 d(n) = (n - 1) * (d[n-1] + d[n-2])의 점화식을 가짐
#define MOD 1000000000

llt Complete_Permutation(int n) {
	llt a = 0, b = 1, c;
	for (llt i = 3; i <= n; ++i) {
		c = (i - 1) * (a + b) % MOD;
		a = b, b = c;
	}
	return n == 1 ? 0 : n == 2 ? 1 : c;
}

// 제 1종 스털링 수 (Stirling Numbers) (feat. 박스 안의 열쇠)
// 1 ~ n 까지의 수가 있을 때, k 개의 사이클을 만들 수 있는 경우의 수 [n, k]
// [1, 1] = 1, [n, 0] = 0, [n, 1] = (n - 1)!, [n, n] = 1,
// [n, k] = [n - 1, k - 1] + (n - 1) * [n - 1, k]
// [n - 1, k - 1] : 새로운 사이클에 끼어드는 경우, [n - 1, k] : 기존 사이클에 끼어드는 경우

llt stn[21][21] = { 1 };

llt gcd(llt a, llt b) {
	return b ? gcd(b, a % b) : a;
}

void Stirling_Numbers(int n, int m) {
	for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++)
		dp[i][j] = dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j]; //제 1종 스털링 수 점화식
	for (int i = 1; i <= n; i++) dp[n][i] += dp[n][i - 1]; // 모든 k 갯수의 사이클을 더함
	llt g = gcd(dp[n][m], dp[n][n]);
	cout << dp[n][m] / g << "/" << dp[n][n] / g;
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
