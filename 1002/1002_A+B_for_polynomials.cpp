#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

#define MAXN 1005

double res[MAXN] = {0.0};

int main()
{
    int k;  // 非零项个数
    int n;  // 每一项的阶数
    double coeff;  // 每一项的系数

    // 输入第一个多项式
    cin >> k;
    while (k--)
    {
        cin >> n >> coeff;
        res[n] += coeff;
    }

    // 输入第二个多项式
    cin >> k;
    while (k--)
    {
        cin >> n >> coeff;
        res[n] += coeff;
    }

    // 统计非零项，输出
    int non_zero_cnt = 0;
    ostringstream oss;
    for (int i = 1000; i >= 0; --i)
    {
        if (fabs(res[i] - 0.0) > 1e-6)  // 注意要使用 fabs()，容易直接写成 res[i] - 0.0 > 1e-6
        {
            ++non_zero_cnt;
            oss << " " << i << " " << std::fixed << std::setprecision(1) << res[i];
        }
    }

    cout << non_zero_cnt << oss.str() << endl;

    return 0;
}