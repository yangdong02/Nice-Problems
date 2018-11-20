# Dilworth Theorem
教程博客在此 [Nice Blog][1]。定理内容：$DAG$中最长反链长度=最小链覆盖

## 在序列上应用有这些：
  - 序列中由最长不下降子序列的划分数量等于最长上升子序列的长度（$NOIP1998$导弹拦截）
  - 一个长为$n$序列的LIS与LDS长度中的最大值 $\geq \sqrt{n}$。
  - 一个序列由LIS与LDS进行贪心划分，则划分成的序列数量为$O(\sqrt{n})$的。（这两个结论来自莫涛 Hose解题报告）


结论2可以由结论1推出来，结论3是利用结论2解递归方程$T(n)=T(n-\sqrt{n})+1$得到的

[1]: https://blog.csdn.net/qq_34564984/article/details/52993626?tdsourcetag=s_pcqq_aiomsg        "Nice Blog"
