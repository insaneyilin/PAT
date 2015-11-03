#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits.h>

using namespace std;

int main(int argc, char * const argv[])
{
    int r, g, b;
    cin >> r >> g >> b;

    // 10 进制转 13 进制
    auto cvt_to_color_in_Mars = [](int v) {
        string res;
        do 
        {
            int t = v % 13;
            if (t < 10)
            {
                res.push_back('0' + t);
            }
            else
            {
                res.push_back('A' + t - 10);
            }
            v /= 13;
        } while (v);

        if (res.length() == 1)
        {
            res.push_back('0');
        }

        std::reverse(res.begin(), res.end());

        return res;
    };

    cout << "#" 
        << cvt_to_color_in_Mars(r) 
        << cvt_to_color_in_Mars(g) 
        << cvt_to_color_in_Mars(b) << endl;

    return 0;
}