#include <iostream>  
#include <string>  

using namespace std;

int main(int argc, char * const argv[])
{
    string h_num[10] = { "ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu" };
    string h_wei[5] = { "Shi", "Bai", "Qian", "Wan", "Yi" };

    string num_str;
    cin >> num_str;

    int start = 0, end = num_str.size();
    int next_start; // 下一个 4 位数据的起始

    if (num_str[0] == '-')
    {
        start = 1;
    }

    if (end - start <= 1 && num_str[start] == '0')  // 处理 0 的特殊情况
    {
        cout << "ling" << endl;
        return 0;
    }

    if (num_str[0] == '-')
    {
        cout << "Fu";
    }

    while (start < end)
    {
        next_start = end;
        while (next_start - 4 > start)  // 取 4 位
            next_start -= 4;

        bool last_zero = false;  // 4 位数据中一个非 0 数字之前是否为 0
        while (start < next_start)  // 处理当前 4 位
        {
            if (num_str[start] - '0' > 0)
            {
                if (last_zero)  // 非 0 数字前有 0，输出一个 ling
                {
                    cout << " ling";
                    last_zero = 0;
                }

                cout << (start > 0 ? " " : "") << h_num[num_str[start] - '0'];

                if (next_start - start >= 2) // 输出 "千"、"百" 位
                {
                    cout << " " << h_wei[next_start - start - 2];
                }
            }
            else
            {
                last_zero = true;
            }
            ++start;
        }
        if (end - next_start > 0)  // 输出 "万"、"亿"
        {
            cout << " " << h_wei[(end - next_start) / 4 + 2];
        }
    }
    cout << endl;
    
    return 0;
}

