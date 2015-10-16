#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int main(int argc, char * const argv[])
{
    vector<string> digit_2_word = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    string num;
    cin >> num;

    // num 最大 10^1000，最多 1000 位；数据最大为 9 * 1000 = 9000
    int sum = 0;
    for (const auto &ch : num)
    {
        sum += (ch - '0');
    }

    stack<int> s;  // 从低位到高位获取数字，从高位到地位输出。用栈。

    // 用 do...while 可以处理 sum == 0 的情况；否则当 sum == 0 时什么都不会输出。
    do
    {
        s.push(sum % 10);
        sum /= 10;
    } while (sum);

    while (!s.empty())
    {
        int t = s.top();

        cout << digit_2_word[t];
        cout << (s.size() == 1 ? "\n" : " ");

        s.pop();
    }

    return 0;
}