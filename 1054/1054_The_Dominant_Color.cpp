#include <iostream>

using namespace std;

int main(int argc, char * const argv[])
{
    int n = 0, m = 0;

    scanf("%d%d", &n, &m);

    int count = 0;
    int color = -1;
    int new_color = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &new_color);
            if (new_color == color)
            {
                ++count;
            }
            else
            {
                if (count == 0)
                {
                    color = new_color;
                }
                else
                {
                    --count;
                }
            }
        }
    }

    cout << color << endl;

    return 0;
}