# 1023. Have Fun with Numbers

http://www.patest.cn/contests/pat-a-practise/1023

判断一个数乘以2后的数中的数字是否和原数中的数字一样。用数组保存每一位数字，可以排序判断乘以2前后两组数字是否相同。

我用一个 Hash 表`h`记录数字出现情况，原数中出现数字 `d`，则 `h[d]` 加一，乘以2后的数中出现 `d`，则 `h[d]` 减一。如果最高位有进位或者 Hash 表中有数字的次数记录非 0，说明原数和乘以2后的数中的数字有差异