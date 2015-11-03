#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits.h>

using namespace std;

struct Student
{
    Student() {}

    Student(string name_, string id_, int score_) 
        : name(name_), id(id_), score(score_)
    {}

    Student(const Student &that)
    {
        name = that.name;
        id = that.id;
        score = that.score;
    }

    string name;
    string id;
    int score;
};

int main(int argc, char * const argv[])
{
    int n;
    cin >> n;

    vector<Student> records;
    for (int i = 0; i < n; ++i)
    {
        string name;
        string id;
        int score;
        cin >> name >> id >> score;
        records.push_back(Student(name, id, score));
    }

    int low_bound, up_bound;
    cin >> low_bound >> up_bound;

    auto cmp = [](const Student &a, const Student &b) {
        return a.score > b.score;
    };

    sort(records.begin(), records.end(), cmp);

    bool found = false;
    for (const auto &r : records)
    {
        if (r.score >= low_bound && r.score <= up_bound)
        {
            if (!found)
            {
                found = true;
            }
            cout << r.name << " " << r.id << endl;
        }
    }

    if (!found)
    {
        cout << "NONE" << endl;
    }

    return 0;
}
