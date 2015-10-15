# 1032. Sharing

http://www.patest.cn/contests/pat-a-practise/1032

![](http://www.patest.cn/upload/1w_m16pjsommxz.jpg)

找出两个链表共享空间时的起始地址。

先遍历第一个链表的节点，对访问到的节点进行标记。

再遍历第二个链表的节点，如果遇到第一个链表的标记，说明此时已经开始公共部分了，当前地址即为首次汇合的地址。

可以开辟一个大数组，用数组下标表示节点地址。也可以使用 C++ 的 `map`。