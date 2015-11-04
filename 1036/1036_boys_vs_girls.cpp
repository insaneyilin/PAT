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

    void input(istream &in)
    {
        in >> name >> gender >> id >> score;
    }

    string name;
    string gender;
    string id;
    int score;
};

int main(int argc, char * const argv[])
{
    int n;
    cin >> n;

    vector<Student> boys;
    vector<Student> girls;

    for (int i = 0; i < n; ++i)
    {
        Student tmp;
        tmp.input(cin);
        if (tmp.gender == "M")
        {
            boys.push_back(tmp);
        }
        else
        {
            girls.push_back(tmp);
        }
    }

    auto cmp = [](const Student &a, const Student &b) {
        return a.score < b.score;
    };

    // Girl with the highest score
    auto itr_max_score_girl = std::max_element(girls.begin(), girls.end(), cmp);
    if (itr_max_score_girl == girls.end())
    {
        cout << "Absent" << endl;
    }
    else
    {
        cout << itr_max_score_girl->name << " " << itr_max_score_girl->id << endl;
    }

    // Boy with the lowest score
    auto itr_min_score_boy = std::min_element(boys.begin(), boys.end(), cmp);
    if (itr_min_score_boy == boys.end())
    {
        cout << "Absent" << endl;
    }
    else
    {
        cout << itr_min_score_boy->name << " " << itr_min_score_boy->id << endl;
    }

    // Difference
    if (itr_max_score_girl == girls.end() ||
        itr_min_score_boy == boys.end())
    {
        cout << "NA" << endl;
    }
    else
    {
        cout << itr_max_score_girl->score - itr_min_score_boy->score << endl;
    }

    return 0;
}
