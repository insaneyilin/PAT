#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits.h>

using namespace std;

// 模拟大整数
struct BigInt
{
    BigInt() {}
    
    BigInt(long long n)  // n 量级可达 10^10，需要用 long long
    {
        // 逆序保存数字
        do 
        {
            data.push_back(n % 10);
            n /= 10;
        } while (n);
    }

    BigInt(const vector<long long> &vec)
    {
        data.assign(vec.begin(), vec.end());
    }

    vector<long long> data;

    // 大数加法
    BigInt operator+(const BigInt &that) const 
    {
        if (that.data.size() > this->data.size())
        {
            return that + *this;
        }

        BigInt sum(this->data);
        int carry = 0;  // 保存进位
        int i;
        for (i = 0; i < that.data.size(); ++i)
        {
            int d = this->data.at(i) + that.data.at(i) + carry;
            sum.data[i] = d % 10;
            carry = d / 10;
        }
        for (; i < sum.data.size(); ++i)
        {
            if (carry == 0)
            {
                break;
            }
            int d = this->data.at(i) + carry;
            sum.data[i] = d % 10;
            carry = d / 10;
        }
        if (carry > 0)
        {
            sum.data.push_back(carry);
        }

        return sum;
    }

    // 获取数字逆序后的大数
    BigInt get_reverse() const
    {
        vector<long long> rdata(data.begin(), data.end());
        reverse(rdata.begin(), rdata.end());

        return BigInt(rdata);
    }

    // 判断 palindromic
    bool is_palindromic() const
    {
        int half_size = data.size() / 2;
        for (int i = 0; i < half_size; ++i)
        {
            if (data[i] != data[data.size() - 1 - i])
            {
                return false;
            }
        }

        return true;
    }

    void print()
    {
        for (auto ritr = data.rbegin(); ritr != data.rend(); ++ritr)
        {
            cout << *ritr;
        }
        cout << endl;
    }
};

int main(int argc, char * const argv[])
{
    long long n, k;
    cin >> n >> k;

    BigInt sum(n);
    if (sum.is_palindromic())  // 处理 PAT 上的 case 2 和 case 3，即输入的数本身就是 palindromic
    {
        sum.print();
        cout << 0 << endl;
        return 0;
    }
    for (int j = 1; j <= k; ++j)
    {
        sum = sum + sum.get_reverse();
        if (sum.is_palindromic())
        {
            sum.print();
            cout << j << endl;
            return 0;
        }
    }
    sum.print();
    cout << k << endl;

    return 0;
}