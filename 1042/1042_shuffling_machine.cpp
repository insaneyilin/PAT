#include <iostream> 
#include <vector>

using namespace std;

void shuffle_cards(const vector<int> &src, vector<int> &dst, const vector<int> &order, int K)
{
    for (int i = 0; i < 54; ++i)
    {
        int t = i;
        for (int k = 0; k < K; ++k)
        {
            t = order[t];
        }
        dst[t] = src[i];
    }
}

void print_cards(const vector<int> &nums)
{
    static char *SUITS = "SHCDJ";

    for (int i = 0; i < 54; ++i)
    {
        cout << (i == 0 ? "" : " ");
        
        cout << SUITS[static_cast<int>(nums[i] / 13)];
        cout << (nums[i] % 13 + 1);
    }
    cout << endl;
}

int main(int argc, char * const argv[])
{
    int K;
    cin >> K;

    vector<int> nums(54, 0);
    vector<int> res(54, 0);
    for (int i = 0; i < 54; ++i)
    {
        nums[i] = i;
    }

    vector<int> order(54, 0);
    for (int i = 0; i < 54; ++i)
    {
        cin >> order[i];
        --(order[i]);
    }

    shuffle_cards(nums, res, order, K);

    print_cards(res);

    return 0;
}