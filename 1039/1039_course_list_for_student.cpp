#include <iostream> 
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <functional>

#include <stdio.h>

using namespace std;

int myhash(char name[5])
{
    return (name[0] - 'A') * 26 * 26 * 10 +
        (name[1] - 'A') * 26 * 10 +
        (name[2] - 'A') * 10 +
        (name[3] - '0');
}

int main(int argc, char * const argv[])
{
    int num_students = 0, num_courses = 0;
    scanf("%d%d", &num_students, &num_courses);

    //map<string, priority_queue<int, vector<int>, greater<int>>> course_list;
    map<int, set<int>> course_list;  // 用 set 不会超时，用 priority_queue 会超时（pop 操作耗时）

    for (int k = 0; k < num_courses; ++k)
    {
        int idx_course = 0, num_cur_students = 0;
        scanf("%d%d", &idx_course, &num_cur_students);
        for (int i = 0; i < num_cur_students; ++i)
        {
            char name[5];
            scanf("%s", name);

            int name_hash_code = myhash(name);
            course_list[name_hash_code].insert(idx_course);
        }
    }

    char query_name[5];
    for (int i = 0; i < num_students; ++i)
    {
        scanf("%s", query_name);
        int name_hash_code = myhash(query_name);

        printf("%s %d", query_name, course_list[name_hash_code].size());

        for (const auto &elem : course_list[name_hash_code])
        {
            printf(" %d", elem);
        }
        printf("\n");
    }

    return 0;
}
