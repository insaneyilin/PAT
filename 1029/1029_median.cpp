#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits.h>

using namespace std;

int main(int argc, char * const argv[])
{
    int n1, n2;
    //cin >> n1;
    scanf("%d", &n1);
    vector<long long> nums1(n1);
    for (auto &num : nums1)
    {
        //cin >> num;
        scanf("%lld", &num);
    }

    //cin >> n2;
    scanf("%d", &n2);
    vector<long long> nums2(n2);
    for (auto &num : nums2)
    {
        //cin >> num;
        scanf("%lld", &num);
    }

    // 这里减一是为了符合题目要求，当元素数为偶数时取中线左边的元素
    int half_size = (nums1.size() + nums2.size() - 1) / 2;
    int i, j, k;

    for (i = 0, j = 0, k = 0; i < nums1.size() && j < nums2.size();)
    {
        if (nums1[i] < nums2[j])
        {
            if (k == half_size)
            {
                cout << nums1[i] << endl;
                return 0;
            }
            ++i;
        }
        else
        {
            if (k == half_size)
            {
                cout << nums2[j] << endl;
                return 0;
            }
            ++j;
        }
        ++k;
    }

    // 这里原来多加了下面的判断，导致 PAT 上 4 号测试点无法通过
    // 4 号测试点的测试应该如下所示（即第一个数组长度为 0 ）：
    /*
    0
    2 1 3
    */
    //if (k < half_size) 
    //{
    //    ...
    //}

    for (; i < nums1.size(); ++i, ++k)
    {
        if (k == half_size)
        {
            cout << nums1[i] << endl;
            return 0;
        }
    }

    for (; j < nums2.size(); ++j, ++k)
    {
        if (k == half_size)
        {
            cout << nums2[j] << endl;
            return 0;
        }
    }

    return 0;
}