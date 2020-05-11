#include <stdio.h>
#include <math.h>

int main() {
	int n, m, cases = 0;
	while(scanf("%d %d", &n, &m) == 2 && n+m) {
		double row[128] = {}, col[128] = {};
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				double x;
				scanf("%lf", &x);
				row[i] += x, col[j] += x;
			}
		}
		double left = 0, right = 0;
		double diff = 1e+30;
		int cx, cy;
###########################




	}
	return 0;
}
