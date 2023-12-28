'''
任务描述
本关任务：编写一个能计算斐波那契数列的小程序。

相关知识
为了完成本关任务，你需要掌握：1.迭代程序的基本结构，2.循环语句。

斐波那契数列
指的是这样一个数列：0、1、1、2、3、5、8、13、21、34、……在数学上，斐波那契数列以如下被以递推的方法定义：F(0)=0，F(1)=1, F(n)=F(n - 1)+F(n - 2)（n ≥ 2，n ∈ N*）

编程要求
根据提示，在右侧编辑器补充代码，计算并输出第n个斐波那契数列的值

测试说明
平台会对你编写的代码进行测试：

测试输入：5
预期输出：5 5

测试输入：10
预期输出：55 10

注：输出的第一项为第n个斐波那契数列的值，第二项为递归的次数。

平台会使用下列代码调用你编写的函数：

import sample3
n = int(input())
product, count = sample3.Fibonacci(n)
print(product, count)

'''


def Fibonacci(n):
    """
    输入： 
       n：斐波那契数列的阶数
    输出：返回两个结果
       Fib[n]：第n个斐波那契数列的值
       count：迭代的次数
    """
    Fib = [0, 1]
    count = 1
    while count < n:
        Fib.append(Fib[count-1]+Fib[count])
        count += 1
    return Fib[n], count


n = int(input())
product, count = Fibonacci(n)
print(product, count)
