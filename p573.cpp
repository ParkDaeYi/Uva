#include <stdio.h>
#include <math.h>
#pragma warning(disable:4996)

int main() {
	freopen("p573.inp", "r", stdin);
	freopen("p573.out", "w", stdout);

	int day;
	double U, diff, ans, H, D, F;
	
	while (1) {
		scanf("%lf %lf %lf %lf", &H, &U, &D, &F);
		if (!H) break;
		diff = U * F / 100.0;
		ans = 0;
		day = 0;
		while (1) {
			day++;
			ans += U;
			if (ans > H) break;			
			ans -= D;
			if (fabs(ans) <= 1e-9 || ans < 0) break;
			U -= diff;
			if (U <= 0) U = 0;
		}
		if (ans > H) printf("success on day %d\n", day);
		else printf("failure on day %d\n", day);
	}

	return 0;
}

