#include <iostream>
#include <map>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char * const argv[])
{
    map<int, double> a;
    map<int, double> b;
    map<int, double> res;

    int k;
    int n;
    double coeff;

    cin >> k;
    while (k--)
    {
        cin >> n >> coeff;
        a[n] = coeff;
    }

    cin >> k;
    while (k--)
    {
        cin >> n >> coeff;
        b[n] = coeff;
    }

    // 相乘
    for (auto &item_a : a)
    {
        for (auto &item_b : b)
        {
            n = item_a.first + item_b.first;
            coeff = item_a.second * item_b.second;

            if (res.find(n) == res.end())
            {
                res[n] = coeff;
            }
            else
                res[n] += coeff;
        }
    }

    // 清除系数为0的项
    for (auto iter_result = res.begin(); iter_result != res.end(); ++iter_result)
    {
        if (fabs(iter_result->second) < 1e-8)
            iter_result = res.erase(iter_result);
    }

    cout << res.size();
    for (auto ritr = res.rbegin(); ritr != res.rend(); ++ritr)
    {
        cout << " " << ritr->first << " " << std::fixed << std::setprecision(1) << ritr->second;
    }
    cout << endl;

    return 0;
}