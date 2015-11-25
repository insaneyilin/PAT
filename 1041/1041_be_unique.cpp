#include <iostream> 
#include <vector>
#include <map>

#include <stdio.h>

using namespace std;

int main(int argc, char * const argv[])
{
    int N;
    cin >> N;
    vector<int> nums(N, 0);

    map<int, int> h;
    for (int i = 0; i < N; ++i)
    {
        cin >> nums[i];
        if (h.find(nums[i]) == h.end())
        {
            h[nums[i]] = 0;
        }
        ++(h[nums[i]]);
    }

    bool found = false;
    for (int i = 0; i < N; ++i)
    {
        if (h[nums[i]] == 1)
        {
            cout << nums[i] << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "None\n";
    }

    return 0;
}