#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char * const argv[])
{
    char r[3] = { 'W', 'T', 'L' };
    float max_profit = 1.0;
    for (int i = 0; i < 3; ++i)
    {
        float max_odd = 0;
        int max_j = 0;
        for (int j = 0; j < 3; ++j)
        {
            float odd;
            cin >> odd;
            if (odd > max_odd)
            {
                max_odd = odd;
                max_j = j;
            }
        }
        cout << r[max_j] << " ";
        max_profit *= max_odd;
    }

    max_profit = (max_profit * 0.65 - 1) * 2;

    printf("%.2f\n", max_profit);

    return 0;
}