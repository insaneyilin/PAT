#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <math.h>
#include <stdio.h>
#include <limits.h>

using namespace std;

struct Book
{
    string title;
    string author;
    vector<string> keywords;
    string publisher;
    string year;

    void input()
    {
        string keywords_str;
        std::getline(cin, title);
        std::getline(cin, author);
        std::getline(cin, keywords_str);
        std::getline(cin, publisher);
        std::getline(cin, year);

        istringstream iss(keywords_str);
        string tmp_kw;
        while (iss >> tmp_kw)
        {
            keywords.push_back(tmp_kw);
        }
    }

    void print() const
    {
        cout << "Title:\t" << title << endl;
        cout << "Author:\t" << author << endl;
        cout << "Keywords:\t";
        for (const auto &kw : keywords)
        {
            cout << kw << " ";
        }
        cout << endl;
        cout << "Publisher:\t" << publisher << endl;
        cout << "Year:\t" << year << endl;
    }
};

int main(int argc, char * const argv[])
{
    int n, m;
    cin >> n;
    getchar(); // 处理换行符

    map<string, Book> book_lib;  // 保存所有图书信息记录，ID 作为 key

    string id;
    for (int i = 0; i < n; ++i)
    {
        std::getline(cin, id);
        Book book;
        book.input();
        //book.print();
        book_lib[id] = book;
    }

    cin >> m;
    getchar(); // 处理换行符

    string query;
    for (int i = 0; i < m; ++i)
    {
        std::getline(cin, query);
        cout << query << endl;

        bool found = false;
        if (query[0] == '1')  // 按标题查询
        {
            string title = query.substr(3);
            for (const auto &record : book_lib)
            {
                const auto &book_info = record.second;
                if (book_info.title == title)
                {
                    if (!found)
                    {
                        found = true;
                    }
                    cout << record.first << endl;
                }
            }
        }
        else if (query[0] == '2')  // 按作者查询
        {
            string author = query.substr(3);
            for (const auto &record : book_lib)
            {
                const auto &book_info = record.second;
                if (book_info.author == author)
                {
                    if (!found)
                    {
                        found = true;
                    }
                    cout << record.first << endl;
                }
            }
        }
        else if (query[0] == '3')  // 按关键词查询
        {
            string keyword = query.substr(3);
            for (const auto &record : book_lib)
            {
                const auto &book_info = record.second;
                for (const auto &kw : book_info.keywords)
                {
                    if (keyword == kw)
                    {
                        if (!found)
                        {
                            found = true;
                        }
                        cout << record.first << endl;
                        break;
                    }
                }
            }
        }
        else if (query[0] == '4')  // 按出版商查询
        {
            string publisher = query.substr(3);
            for (const auto &record : book_lib)
            {
                const auto &book_info = record.second;
                if (book_info.publisher == publisher)
                {
                    if (!found)
                    {
                        found = true;
                    }
                    cout << record.first << endl;
                }
            }
        }
        else if (query[0] == '5')  // 按年份查询
        {
            string year = query.substr(3);
            for (const auto &record : book_lib)
            {
                const auto &book_info = record.second;
                if (book_info.year == year)
                {
                    if (!found)
                    {
                        found = true;
                    }
                    cout << record.first << endl;
                }
            }
        }

        if (!found)  // 未查询到记录
        {
            cout << "Not Found" << endl;
        }
    }

    return 0;
}