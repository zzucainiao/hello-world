#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define inf ((LL)1<<40)
#define lson k<<1, L, mid
#define rson k<<1|1, mid+1, R
#define mem0(a) memset(a,0,sizeof(a))
#define mem1(a) memset(a,-1,sizeof(a))
#define mem(a, b) memset(a, b, sizeof(a))
#define FOPENIN(IN) freopen(IN, "r", stdin)
#define FOPENOUT(OUT) freopen(OUT, "w", stdout)
template<class T> T ABS ( T a) { return a >= 0 ? a : -a;   }
template<class T> T CMP_MIN ( T a, T b ) { return a < b;   }
template<class T> T CMP_MAX ( T a, T b ) { return a > b;   }
template<class T> T MAX ( T a, T b ) { return a > b ? a : b; }
template<class T> T MIN ( T a, T b ) { return a < b ? a : b; }
template<class T> T GCD ( T a, T b ) { return b ? GCD ( b, a % b ) : a; }
template<class T> T LCM ( T a, T b ) { return a / GCD ( a, b ) * b;     }
template<class T> void SWAP( T& a, T& b ) { T t = a; a = b;  b = t;     }

typedef __int64 LL;
typedef long long LL;
const int MAXN = 310;
const int MAXM = 110000;
const double eps = 1e-14;
const double PI = 4.0 * atan(1.0);

char str[7][10] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

int findNum(char *s)
{
    for(int i = 0; i < 7; i ++ )
    {
        if(strcmp(str[i], s) == 0) return i;
    }
    return 0;
}
int n, m, k, cnt[MAXN];
int var, equ, a[MAXN][MAXN], ans[MAXN];

void init()
{
    int x;
    char st[10], ed[10];
    mem0(a);
    var = n;
    equ = m;
    for(int i = 0; i < m; i ++ )
    {
        mem0(cnt);
        scanf("%d %s %s", &k, st, ed);
        for(int j = 0; j < k; j ++ )
        {
            scanf("%d", &x);
            cnt[x-1] ++;
        }
        a[i][var] = findNum(ed) - findNum(st) + 1;
        for(int j = 0; j < var; j ++ )
            a[i][j] = cnt[j] % 7;
    }
}

void exgcd(int a, int b, int& x, int& y)
{
    if(!b) { x = 1; y = 0; }
    else { exgcd(b, a % b, y, x); y -= x*(a/b); }
}

int gauss()
{
    int x, y;
    int k, col = 0;
    for(k = 0; k < equ && col < var; k ++, col ++)
    {
        int Max = 0, row = -1;
        for(int r = k ; r < equ; r ++)
        {
            if( Max < ABS(a[r][col]) )
                Max = ABS( a[r][col] ), row = r;
        }
        if(row == -1)
        {
            k--;
            continue;
        }
        for(int c = col; c <= var; c ++)
            SWAP(a[k][c], a[row][c]);
        for(int r = k + 1; r < equ; r ++)
        {
            if(a[r][col])
            {
                int lcm = LCM(ABS(a[k][col]), ABS(a[r][col]));
                int ta = lcm / a[r][col];
                int tb = lcm / a[k][col];
                if(a[r][col] * a[k][col] < 0) tb = -tb;
                for(int c = col; c <= var; c ++ )
                {
                    a[r][c] = a[r][c] * ta - a[k][c] * tb;
                    a[r][c] = (a[r][c] % 7 + 7) % 7;
                }
            }
        }
    }
    for(int r = k; r < equ; r ++)
    {
        if(a[r][var]) return -1;
    }
    if(k < var) return 1;
    for(int r = var - 1; r >= 0; r --)
    {
        int tmp = a[r][var];
        for(int c = var - 1; c > r; c -- )
        {
            tmp -= ans[c] * a[r][c] % 7;
        }
        tmp = (tmp % 7 + 7) % 7;
        exgcd(a[r][r], 7, x, y);
        ans[r] = (tmp * x % 7 + 7) % 7;
        if(ans[r] < 3) ans[r] += 7;
    }
    return 0;
}

int main()
{
    FOPENIN("in.txt");
    while(~scanf("%d %d", &n, &m) && (n || m))
    {
        init();
        int free_num = gauss();
        if(free_num == -1)
        {
            printf("Inconsistent data.\n");
        }
        else if(free_num == 1)
        {
            printf("Multiple solutions.\n");
        }
        else
        {
            for(int i = 0; i < var; i ++ )
            {
                printf("%d%c", ans[i], i == var-1 ? '\n' : ' ');
            }
        }
    }
    return 0;
}
