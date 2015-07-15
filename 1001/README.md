# 1001. A+B Format

http://www.patest.cn/contests/pat-a-practise/1001

简单题。我第一次用了一个字符串数组，遇到三个数字就加一个`,`。最后打印这个字符串。

由于题目告诉了取值范围，直接用除法和取余运算就可以了。

```cpp
	if (c >= 1000000)
		printf("%d,%03d,%03d\n", c/1000000, (c/1000)%1000, c%1000);
	else if (c >= 1000)
		printf("%d,%03d\n", c/1000, c%1000);
	else
		printf("%d\n", c);
```

