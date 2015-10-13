# 1002. A+B for Polynomials

http://www.patest.cn/contests/pat-a-practise/1002

多项式加法。利用 Hash 表，开辟一个数组，数组的下标作为多项式系数，对应下标的元素为多项式的指数。

第一次提交有一个 test case 没有过，检查后发现自己判断 double 变量为 0 的地方忘了用 `fabs()`。