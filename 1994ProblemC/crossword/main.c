#include <stdio.h>

int main() {
    int n, m, i, j, cases = 0;
    char grid[20][20];
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < n; i++) {
            scanf("%s", grid[i]);
        }
        if(cases)
            puts("");
        printf("puzzle #%d:\n", ++cases);

        int num[20][20] = {}, cnt = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(i-1 < 0 || grid[i-1][j] == '*' || j-1 < 0 || grid[i][j-1] == '*') {
                    if(grid[i][j] != '*')
                        num[i][j] = ++cnt;
                }
            }
        }
        puts("Across");
        for(i = 0; i < n; i++) {
            int g = 0;
            for(j = 0; j < m; j++) {
                if(grid[i][j] != '*') {
                    if(g == 0)
                        printf("%3d.", num[i][j]);
                    putchar(grid[i][j]);
                    g = 1;
                } else {
                    if(g) {
                        puts("");
                        g = 0;
                    }
                }
            }
            if(g)   puts("");
        }
        puts("Down");
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if((i-1 < 0 || grid[i-1][j] == '*') && grid[i][j] != '*') {
                    int ti = i;
                    printf("%3d.", num[i][j]);
                    while(ti < n && grid[ti][j] != '*')
                        putchar(grid[ti++][j]);
                    puts("");
                }
            }
        }
    }
    return 0;
}
