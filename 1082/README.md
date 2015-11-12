# 1082. Read Number in Chinese

http://www.patest.cn/contests/pat-a-practise/1082

这题我做得都快恶心了，非常繁（烦）。


> http://blog.csdn.net/xyzchenzd/article/details/36385567

> 把数字表达成中文发音。规则：

> 1、每4位后要补相应的亿、万；

> 2、每4位中的千、百、十如果数字不为0，则要补相应位的发音；

> 3、每4位中每当0出现在非0数字前时，需要补零的发音；

> 注意本身为0的特殊情况

现在的代码虽然能通过 PAT 上的测评，但是还是有问题，比如对 `100001234`，当前代码输出的是 `yi Yi Wan yi Qian er Bai san Shi si`，明显不对，正确答案应该是 `yi Yi ling yi Qian er Bai san Shi si`。