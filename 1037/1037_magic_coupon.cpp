#include <iostream> 
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <numeric>

using namespace std;

int main(int argc, char * const argv[])
{
    int NC, NP;

    cin >> NC;
    vector<long long> coupons_p;
    vector<long long> coupons_n;
    for (int i = 0; i < NC; ++i)
    {
        long long _c;
        cin >> _c;
        if (_c > 0)
            coupons_p.push_back(_c);
        else
            coupons_n.push_back(_c);
    }

    cin >> NP;
    vector<long long> products_p;
    vector<long long> products_n;
    for (int i = 0; i < NP; ++i)
    {
        long long _p;
        cin >> _p;
        if (_p > 0)
            products_p.push_back(_p);
        else
            products_n.push_back(_p);
    }

    std::sort(coupons_p.begin(), coupons_p.end(), std::greater<long long>());
    std::sort(coupons_n.begin(), coupons_n.end(), std::less<long long>());

    std::sort(products_p.begin(), products_p.end(), std::greater<long long>());
    std::sort(products_n.begin(), products_n.end(), std::less<long long>());

    long long res = 0;
    for (int i = 0, j = 0; i < coupons_p.size() && j < products_p.size(); ++i, ++j)
    {
        res += (coupons_p[i] * products_p[j]);
    }

    for (int i = 0, j = 0; i < coupons_n.size() && j < products_n.size(); ++i, ++j)
    {
        res += (coupons_n[i] * products_n[j]);
    }

    cout << res << endl;

    return 0;
}