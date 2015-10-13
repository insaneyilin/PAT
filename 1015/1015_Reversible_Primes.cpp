#include <iostream>
#include <string>

using namespace std;

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

bool judge(int n, int d)
{
    if (!is_prime(n))
        return false;
    
    int rev = 0;
    while (n)
    {
        rev = d * rev + (n % d);
        n /= d;
    }

    return is_prime(rev);
}

int main()
{
    int n, d;

    while (cin >> n && n >= 0)
    {
        cin >> d;
        cout << (judge(n, d) ? "Yes" : "No") << endl;
    }

    return 0;
}