'''
任务描述
本关任务：编写一个能计算斐波那契数列的小程序。

相关知识
为了完成本关任务，你需要掌握：1.递归函数的基本使用，2.递归终止条件。

斐波那契数列
指的是这样一个数列：0、1、1、2、3、5、8、13、21、34、……在数学上，斐波那契数列以如下被以递推的方法定义：F(0)=0，F(1)=1, F(n)=F(n - 1)+F(n - 2)（n ≥ 2，n ∈ N*）

编程要求
根据提示，在右侧编辑器补充代码，计算并输出第n个斐波那契数列的值和对应的递归次数。在本关中，斐波那契数列实现函数只需要返回第n个斐波那契数列的值即可。对应的递归次数系统自动计算，同学们在做这一关的时候，可以和第3关的迭代的结果进行对比，在计算相同斐波那契数列阶数时，两者计算次数上的差异。

测试说明
平台会对你编写的代码进行测试：

测试输入：5
预期输出：5 15

测试输入：10
预期输出：55 177

注：输出的第一项为第n个斐波那契数列的值，第二项为递归的次数。

平台会使用下列代码调用你编写的函数：

import sample4
n = int(input())
product, count = sample4.Fibonacci(n)
print(product, count)
'''

class Counter(object) :
    def __init__(self, fun) :
        self._fun = fun
        self.counter=0
    def __call__(self,*args, **kwargs) :
        self.counter += 1
        return self._fun(*args, **kwargs)

@Counter
def Fibonacci(n):
   #********* Begin *********#
   # 在此处补全代码#
    if n == 0:
        return 0,0
    if n == 1:
        return 1,1
    else:
        return  Fibonacci(n-1)[0]+Fibonacci(n-2)[0], Fibonacci.counter
   #********* End *********#
n = int(input())
product, count = Fibonacci(n)
print(product, count)