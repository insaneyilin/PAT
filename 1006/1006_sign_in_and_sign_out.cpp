#include <iostream>
#include <string>

using namespace std;

int main(int argc, char * const argv[])
{
    int m;
    cin >> m;

    string id, come_time, go_time;
    string min_come_id = "";
    string max_go_id = "";
    string min_come_time = "99:99:99";
    string max_go_time = "00:00:00";
    
    for (int i = 0; i < m; ++i)
    {
        cin >> id >> come_time >> go_time;
        if (come_time < min_come_time)
        {
            min_come_time = come_time;
            min_come_id = id;
        }
        if (go_time > max_go_time)
        {
            max_go_time = go_time;
            max_go_id = id;
        }
    }

    cout << min_come_id << " " << max_go_id << endl;

    return 0;
}