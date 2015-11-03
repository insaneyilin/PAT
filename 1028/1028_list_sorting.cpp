#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits.h>

using namespace std;

struct Student
{
    Student()
    {}

    Student(string id_, string name_, int score_) 
        : id(id_), name(name_), score(score_)
    {}

    Student(const Student &that)
    {
        id = that.id;
        name = that.name;
        score = that.score;
    }

    string id;
    string name;
    int score;
};

int main(int argc, char * const argv[])
{
    int n, c;
    //cin >> n >> c;
    scanf("%d%d", &n, &c);

    vector<Student> records(n);

    for (int i = 0; i < n; ++i)
    {
        char id[10];
        char name[10];
        int score;
        //cin >> id >> name >> score;
        scanf("%s%s%d", id, name, &score);

        records[i] = Student(string(id), string(name), score);
    }

    auto cmp = [&c](const Student &a, const Student &b) {
        if (c == 1)
        {
            return a.id < b.id;
        }
        
        if (c == 2)
        {
            if (a.name == b.name)
            {
                return a.id < b.id;
            }
            else
            {
                return a.name < b.name;
            }
        }

        if (c == 3)
        {
            if (a.score == b.score)
            {
                return a.id < b.id;
            }
            else
            {
                return a.score < b.score;
            }
        }

        return a.id < b.id;
    };

    sort(records.begin(), records.end(), cmp);

    for (const auto &r : records)
    {
        //cout << r.id << " " << r.name << " " << r.score << endl;
        printf("%s %s %d\n", r.id.c_str(), r.name.c_str(), r.score);
    }

    return 0;
}