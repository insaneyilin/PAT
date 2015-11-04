#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits.h>

using namespace std;

int main(int argc, char * const argv[])
{
    int n;
    cin >> n;

    vector<string> usr_names(n);
    vector<string> pwds(n);

    vector<int> modified_indices;

    
    for (int i = 0; i < n; ++i)
    {
        cin >> usr_names[i] >> pwds[i];
        
        bool modified = false;
        for (int j = 0; j < pwds[i].size(); ++j)
        {
            if (pwds[i][j] == '1')
            {
                if (!modified)
                {
                    modified = true;
                }
                pwds[i][j] = '@';
            }
            else if (pwds[i][j] == '0')
            {
                if (!modified)
                {
                    modified = true;
                }
                pwds[i][j] = '%';
            }
            else if (pwds[i][j] == 'l')
            {
                if (!modified)
                {
                    modified = true;
                }
                pwds[i][j] = 'L';
            }
            else if (pwds[i][j] == 'O')
            {
                if (!modified)
                {
                    modified = true;
                }
                pwds[i][j] = 'o';
            }
        }

        if (modified)
        {
            modified_indices.push_back(i);
        }
    }

    int m = modified_indices.size();

    if (m == 0)
    {
        if (n == 1)
        {
            cout << "There is 1 account and no account is modified" << endl;
        }
        else
        {
            cout << "There are " << n << " accounts and no account is modified" << endl;
        }
    }
    else
    {
        cout << m << endl;
        for (int i = 0; i < m; ++i)
        {
            int idx = modified_indices[i];
            cout << usr_names[idx] << " " << pwds[idx] << endl;
        }
    }

    return 0;
}