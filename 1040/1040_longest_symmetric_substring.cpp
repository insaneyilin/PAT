#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>

#include <stdio.h>
#include <string.h>

using namespace std;

void longest_palindrome(const string &s, int head, int tail, int &ret_head, int &ret_tail)
{
    int len = s.length();
    while (head >= 0 && tail < len && s[head] == s[tail])
    {
        --head, ++tail;
    }
    ++head, --tail;

    if (tail - head > ret_tail - ret_head)
    {
        ret_head = head;
        ret_tail = tail;
    }
}

int length_of_longest_palindrome(const string &s)
{
    if (s.empty())
    {
        return 0;
    }

    int ret_head = 0, ret_tail = 0;
    for (int i = 0; i < s.length(); ++i)
    {
        longest_palindrome(s, i, i, ret_head, ret_tail);
        longest_palindrome(s, i, i + 1, ret_head, ret_tail);
    }

    return ret_tail - ret_head + 1;
}

int main(int argc, char * const argv[])
{
    string str;
    std::getline(cin, str);

    cout << length_of_longest_palindrome(str) << endl;

    return 0;
}