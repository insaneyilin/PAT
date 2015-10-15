#include <iostream>
#include <string>

using namespace std;

int main(int argc, char * const argv[])
{
    int n, n1, n2; // n1 == n3

    string str;
    cin >> str;

    n = str.length();

    // 确定 n1, n2 和 n3 的值
    //  n1 = n3 = max { k| k <= n2 for all 3 <= n2 <= N } with n1 + n2 + n3 - 2 = N.
    bool found = false;
    for (n2 = 3; n2 <= n; ++n2)
    {
        for (n1 = n2; n1 >= 1; --n1)
        {
            if (n1 + n2 + n1 - 2 == n)
            {
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    // 按 U 形输出
    // 左右两列
    for (int i = 0; i < n1 - 1; ++i)
    {
        cout << str[i];
        for (int j = 0; j < n2 - 2; ++j)
        {
            cout << " ";
        }
        cout << str[n - i - 1] << endl;
    }

    // 底部一行
    cout << str.substr(n1 - 1, n2) << endl;

    return 0;
}