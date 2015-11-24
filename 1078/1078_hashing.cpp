#include <iostream> 
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>

#include <stdio.h>
#include <string.h>

using namespace std;

bool is_prime(int num)
{
    if (num <= 1)
        return false;

    for (int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
            return false;
    }

    return true;
}

int main(int argc, char * const argv[])
{
    int MSize, N;
    cin >> MSize >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> nums[i];
    }

    if (!is_prime(MSize))
    {
        while (!is_prime(MSize))
        {
            ++MSize;
        }
    }

    vector<int> h(MSize, -1);
    for (int i = 0; i < N; ++i)
    {
        const int addrs_orig = nums[i] % MSize;

        int addrs;
        bool found = false;
        for (int j = 0; j < MSize; ++j)  // 从 0 开始最多探测 MSize 次
        {
            addrs = (addrs_orig + j * j) % MSize;
            if (h[addrs] == -1)
            {
                h[addrs] = 1;
                found = true;
                break;
            }
        }

        cout << (i == 0 ? "" : " ");
        if (found)
        {
            cout << addrs;
        }
        else
        {
            cout << "-";
        }
    }
    cout << endl;

    return 0;
}
