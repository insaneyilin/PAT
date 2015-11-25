# 1039. Course List for Student

http://www.patest.cn/contests/pat-a-practise/1039

题目非常简单，按顺序输出每个学生选择的课程号即可，但是最后一个 case 一直超时，实在不知道怎么优化了。

> http://blog.csdn.net/iaccepted/article/details/39273311

> 刚开始直接简单写了个map<string, vector<int> > 直接做，最后一组case超时，继续审题，发现名字格式很标准，只有4位而且前三位为大写字母最后一位为数组，以前做过类似哈希的题目，因为字符创的各种操作都是相当费时的，如果能哈希为对应的一个唯一的整数就速度快很多，这样直接写过就可以了。

我完全没有想到要用 Hash 表，以后要注意类似的情况。

