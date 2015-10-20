#include <iostream>
#include <string>

#include <limits.h>

using namespace std;

long long to_decimal(string s, long long radix)
{
    long long res = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            // 数字中出现了超出当前进制表示的数，比如二进制出现了 'a'
            if (s[i] - '0' >= radix)
            {
                return -1;
            }

            res = res * radix + (s[i] - '0');
        }
        else
        {
            if (s[i] - 'a' + 10 >= radix)
            {
                return -1;
            }

            res = res * radix + (s[i] - 'a' + 10);
        }
    }

    return res;
}

int main(int argc, char * const argv[])
{
    string n1, n2;
    long long tag, radix;

    cin >> n1 >> n2 >> tag >> radix;

    string query, train;
    if (tag == 1)
    {
        query = n1;
        train = n2;
    }
    else
    {
        query = n2;
        train = n1;
    }

    int val_decimal_query = to_decimal(query, radix);
    for (long long rad = 2; rad <= 100000; ++rad)  // 遍历 radix ，这里上限 100000 不够大，有 3 个 case 过不了
    {
        if (val_decimal_query == to_decimal(train, rad))
        {
            cout << rad << endl;
            return 0;
        }
    }

    cout << "Impossible" << endl;

    return 0;
}
