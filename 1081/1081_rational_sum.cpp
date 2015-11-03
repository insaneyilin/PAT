#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <math.h>
#include <stdio.h>
#include <limits.h>

using namespace std;

struct RationalNum
{
    RationalNum()
    {
        is_negative = false;
        numerator = 0;
        denominator = 1;
    }

    RationalNum(const RationalNum& that)
    {
        is_negative = that.is_negative;
        numerator = that.numerator;
        denominator = that.denominator;
    }

    RationalNum(long long numerator_, long long denominator_)
        : numerator(numerator_), denominator(denominator_)
    {
        if (numerator > 0  && denominator > 0 || 
            numerator < 0 && denominator < 0 ||
            numerator == 0 || denominator == 0)
        {
            is_negative = false;
        }
        else
        {
            is_negative = true;
        }

        numerator = abs(numerator);
        denominator = abs(denominator);

        long long tmp = gcd(numerator, denominator);
        if (tmp > 1)
        {
            numerator /= tmp;
            denominator /= tmp;
        }
    }

    bool is_negative;
    long long numerator;
    long long denominator;

    inline long long gcd(long long a, long long b)
    {
        long long r;
        while (b > 0)
        {
            r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    void print() const
    {
        if (numerator == 0)
        { 
            cout << "0" << endl;
            return;
        }

        if (is_negative)
        {
            cout << "-";
        }

        if (numerator > denominator)
        {
            cout << numerator / denominator;

            long long tmp = numerator % denominator;
            if (tmp != 0)
            {
                cout << " " << tmp << "/" << denominator;
            }
        }
        else
        {
            cout << numerator << "/" << denominator;
        }
        cout << endl;
    }

    RationalNum operator+(const RationalNum &that) const
    {
        long long n1, d1, n2, d2;
        n1 = is_negative ? -numerator : numerator;
        d1 = denominator;
        n2 = that.is_negative ? -that.numerator : that.numerator;
        d2 = that.denominator;

        return RationalNum(
            n1 * d2 + d1 * n2,
            d1 * d2);
    }
};

int main(int argc, char * const argv[])
{
    int N;
    cin >> N;
    RationalNum sum;
    while (N--)
    {
        long long n, d;
        scanf("%lld/%lld", &n, &d);
        RationalNum tmp(n, d);
        sum = sum + tmp;
    }

    sum.print();

    return 0;
}