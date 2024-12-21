#include<cstdio>
#include<algorithm>
#include<cstring>
#define oo 2147483647//是个好习惯，使程序显得有条理一点 
using namespace std;
int B[101][101][11], S[101][101][11];//区间[l,r]内分成i段的最大/小值 
int n, m;
int a[101];//a存放前缀和 
int mod(int a)//写成函数方便一点 
{
    return ((a % 10) + 10) % 10;
}
int main()
{
    scanf_s("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf_s("%d", &a[i]);
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; i++)
        a[i] += a[i - 1];//前缀和 
    for (int l = 1; l <= 2 * n; l++)
        for (int r = l; r <= 2 * n; r++)
            B[l][r][1] = S[l][r][1] = mod(a[r] - a[l - 1]);//初始化不分段的状态 
    for (int i = 2; i <= m; i++)
        for (int l = 1; l <= 2 * n; l++)
            for (int r = l + i - 1; r <= 2 * n; r++)
                S[l][r][i] = oo;//求最小值时记得把数组初始化为极大值 
    for (int i = 2; i <= m; i++)//枚举分段数 
        for (int l = 1; l <= 2 * n; l++)//枚举左端点 
            for (int r = l + i - 1; r <= 2 * n; r++)//枚举右端点 
            {
                for (int k = l + i - 2; k < r; k++)//枚举区间断点 注意范围 
                {
                    S[l][r][i] = min(S[l][r][i], S[l][k][i - 1] * mod(a[r] - a[k]));
                    B[l][r][i] = max(B[l][r][i], B[l][k][i - 1] * mod(a[r] - a[k]));
                }
            }
    int Max = 0, Min = oo;//答案初始化 
    for (int i = 1; i <= n; i++)
    {
        Max = max(Max, B[i][i + n - 1][m]);//从前往后扫一遍 
        Min = min(Min, S[i][i + n - 1][m]);
    }
    printf("%d\n%d", Min, Max);
    return 0;
}