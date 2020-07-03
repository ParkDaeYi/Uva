// 정수론 ( 소수, 최대 공약수, 최소 공배수, 확장 유클리드 알고리즘, 중국인의 나머지 정리, 원시 피타고라스 수 )

// 에라토스테네스의 체
#include <iostream>
#define MAX 1000001
using namespace std;

int prime[MAX];

void Sieve_of_Eratosthenes() {
	for (int i = 1; i < MAX; ++i) prime[i] = i;	// 배열에 인덱스 번호를 저장

	for (int i = 2; i * i < MAX; ++i) {
		if (prime[i] == i) {	// 갱신되지 않은 숫자
			for (int j = i * i; j < MAX; j += i) {
				if (prime[j] == j) prime[j] = i;	// 소수가 아니라면 해당 인덱스에 소수를 저장
			}
		}
	}
}

// 최대 공약수, 최소 공배수(feat. 최대공약수와 최소공배수)
// GCD: 최대 공약수
int GCD(int a, int b) { return b ? GCD(b, a % b) : a; }

// LCM: 최소 공배수
int LCM(int a, int b) {
	int g = GCD(a, b);
	return a * b / g;
}

// 확장 유클리드 알고리즘
void Extended_Euclidean_Algorithm(int a,int b) {
	// a * s + b * t = gcd(a, b) == r1
	// 초기 세팅
	int q = 0, tmp = 0, r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1;
	// 계산 식
	// q[i] <-- r[i - 1] / r[i]
	// r[i] <-- r[i - 2] - r[i - 1] * q[i] (== r[i] <-- r[i - 2] % r[i - 1] (a >= b))
	// s[i] <-- s[i - 2] - s[i - 1] * q[i]
	// t[i] <-- t[i - 2] - t[i - 1] * q[i]
	while (r2) {	// r2(나머지)가 0이 될 때까지 진행
		q = r1 / r2;
		tmp = r1;
		r1 = r2;
		r2 = tmp - r2 * q;
		tmp = s1;
		s1 = s2;
		s2 = tmp - s2 * q;
		tmp = t1;
		t1 = t2;
		t2 = tmp - t2 * q;
	}
	// ex. 69x + 30y = 12 ==> A = 69, B = 30, C = 12
	//	q	r1	r2	r	s1	s2	s	t1	t2	t
	//	2	69	30	9	1	0	1	0	1	-2
	//	3	30	9	3	0	1	-3	1	-2	7
	//	3	9	3	0	1	-3	10	-2	7	-23
	//		3	0		-3	10		7	-23
	//	A * s + B * t = r (= D)가 성립
	// |s2| = |B / D|, |t2| = |A / D|
	// 정수 해 방정식 Ax + By = C 의 한 해 (x[0], y[0]) 는
	// x[0] = s * C / D
	// y[0] = t * C / D
	// 기존 식에 삽입 ==> A * s * C / D + B * t * C / D =(A * s + B * t) * C / D = C 가 성립함
	// 일반해 (x, y) 는
	// x = x[0] + k * B / D
	// y = y[0] - k * A / D	(k는 아무 정수)
}

// 모듈러 역원 + 합동식
// 정수 a, b, n이 주어질 때, a*x ≡ b (mod n)을 만족하는 x 는?
// ex. 3x ≡ 2 (mod 5)
// ==> x ≡ 2 * 3^-1 (mod 5)
// ==> 3^-1 에 대한 값을 구하면 된다
// ====> 3s + 5t = 1 에서 확장 유클리드 호제법으로 s 값만 구하면 끝
int Modular_Operations(int a, int b, int n) {

	int g = gcd(a, gcd(b, n));
	if (g != 1) a /= g, b /= g, n /= g;
	if (gcd(a, n) != 1) return -1;	// a와 n은 서로소여야 한다

	// a'*x ≡ b' (mod n')
	// x ≡ b' * a'^-1 (mod n')
	// a's + n't = 1 에서 s 값을 구해야 함
	int q = 0, tmp, r1 = a, r2 = n, s1 = 1, s2 = 0;
	while (r2) {
		q = r1 / r2;
		tmp = r1;
		r1 = r2;
		r2 = tmp - r2 * q;
		tmp = s1;
		s1 = s2;
		s2 = tmp - s2 * q;
	}
	// s1의 값은 양수로 유지
	while (s1 < 0) s1 += n;
	b = ((b % n) * (s1 % n)) % n;	// b 는 mod n' 보다 크면 안됨
	return b;	// x = b, 양수 중 최소 값
}

// 중국인의 나머지 정리 (Chinese Remainder Theorem)
// CRT 기원: 3으로 나누면 1이 남고 5로 나누면 2가 남고 7로 나누면 3이 남는 수 중에서 가장 작은 수는?
// x ≡ a[1] (mod m[1])
// x ≡ a[2] (mod m[2])
// .....
// x ≡ a[k] (mod m[k])
#define r first
#define m second
typedef long long int llt;
typedef pair<llt, llt> pll;

int k;
pll crt[51];

pll CRT(pll p1, pll p2) {
	//   p1         p2
	// a: p1.m, b: p1.r, c: p2.r, d: p2.m
	// as + b  ≡ c (mod d)
	// as ≡ (c - b) (mod d)
	// rr == (c - b), (c - b)는 d의 나머지여야 함(모듈러 연산)
	llt rr = (p2.r - (p1.r % p2.m)) % p2.m;
	// rr이 음수일 경우 + d, 위에서 mod d를 하였기 때문에 한 번만 더하면 됨.(하지만 혹시 모르므로 while)
	while (rr < 0) rr += p2.m;

	llt g, a = p1.m, b = p2.m;

	g = gcd(gcd(a, b), rr);

	if (g != 1) a /= g, b /= g, rr /= g;

	// a'와 b'가 서로소가 아닐 경우 
	// 확장 유클리드 호제법을 통해 원하는 값을 얻을 수 없음
	if (gcd(a, b) != 1) return pll(-1, -1);

	// a's ≡ rr' (mod b') 인 상황
	// s ≡ rr' * (a'^-1) (mod b') 이므로
	// 확장 유클리드 호제법을 통해 역원(a'^-1)을 구함
	// => a's + b't = 1 형태이므로 s의 값만 구하면 됨
	llt q = 0, tmp = 0, r1 = a, r2 = b, s1 = 1, s2 = 0;
	while (r2) {
		q = r1 / r2;
		tmp = r1;
		r1 = r2;
		r2 = tmp - r2 * q;
		tmp = s1;
		s1 = s2;
		s2 = tmp - s2 * q;
	}
	// rr 값을 양수로 유지하기 위해 s1이 음수일 경우 양수로 변환
	while (s1 < 0) s1 += b;
	rr = ((rr % b) * (s1 % b)) % b;	// mod b' 보다 크면 안됨

	// s ≡ rr'' (mod b') => s = b't + rr'' 을 p1(x = as + b) 에 대입
	return pll(p1.m * rr + p1.r, p1.m * b);
}

void init() {
	cin >> k;
	for (int i = 0; i < k; ++i) cin >> crt[i].r >> crt[i].m;	
	for (int i = 1; i < k; ++i) {
		crt[0] = CRT(crt[0], crt[i]);
		if (crt[0].r == -1 && crt[0].m == -1) break;	// 예외 처리
	}
	cout << crt[0].r << '\n';
}

// 원시 피타고라스 수(원시 피타고라스 삼조) (feat. 직사각형 집합)
// 따름 정리
// 1. a, c는 항상 홀수이고 b는 4의 배수이다
// 2. a 또는 b 중 적어도 하나는 3의 배수이다
// 3. a, b, c 중 적어도 하나는 5의 배수이다
// 4. ab는 12의 배수이고 abc는 60의 배수이다
#include <vector>
#include <algorithm>

int T, N;
vector<int> arr;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }	// 최대 공약수

void Primitive_Pythagorean_Triple() {
	// (a, b, c) 가 원시 피타고라스 수일 필요충분조건
	// --> (m^2 - n^2, 2mn, m^2 + n^2) => (a, b, c) : c는 대각, a b c 는 서로소 관계
	// --> m, n은 자연수이고, m > n 이며, 둘 중 하나는 짝수, 하나는 홀수이다
	// --> m과 n은 '서로소' 이다
	int i;
	for (i = 2; i <= 600; ++i) {
		for (int j = 1; j < i; ++j) {
			if ((i + j) % 2 == 0 || gcd(i, j) != 1) continue;	// 원시 피타고라스 수 필요충분 조건
			// m과 n이 서로소 관계
			// => m의 약수는 n^2의 약수가 안됨 : a와 c는 약수가 안됨
			// => n의 약수는 m^2의 약수가 안됨 : a와 c는 약수가 안됨
			// ===>> a, b, c의 약수가 가능한 것은 2 뿐이다.
			// 따라서 a, b, c가 서로소를 만족하려면 a, c가 홀수가 되면 된다. => m + n 이 홀수
			arr.push_back(i * i - j * j + 2 * i * j);	// 직사각형 둘레 값만 알면 되므로 c 값은 필요 없음
		}
	}
	sort(arr.begin(), arr.end());	// 정확한 연산을 위해 정렬
	for (i = 1;; i++) {
		arr[i] += arr[i - 1];
		if (arr[i] > EOF) break;
	}

	cin >> T;
	while (T--) {
		cin >> N;
		for (i = 0;; ++i) {
			if (arr[i] * 2 > N) break;
		}
		cout << i << '\n';
	}
}