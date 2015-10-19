#include <iostream>
#include <algorithm>  // std::max
#include <limits.h>  // INT_MIN

using namespace std;

int a[10000 + 5];

void dp(int a[], int n)
{
    int sum = 0;
    int first_idx = 0;
    int max_sum = a[0];
    int max_seq_start_idx = 0, max_seq_end_idx = 0;

    for (int i = 0; i < n; ++i)
    {
        if (sum < 0)
        {
            sum = a[i];
            first_idx = i;
        }
        else
            sum += a[i];

        if (max_sum < sum)
        {
            max_sum = sum;
            max_seq_start_idx = first_idx;
            max_seq_end_idx = i;
        }
    }

    if (max_sum < 0)
        cout << 0 << " " << a[0] << " " << a[n - 1] << endl;
    else
        cout << max_sum << " " << a[max_seq_start_idx] << " " << a[max_seq_end_idx] << endl;

    return;
}

int main(int argc, char * const argv[])
{
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i)
    {
        cin >> a[i];
    }

    dp(a, k);

    return 0;
}
