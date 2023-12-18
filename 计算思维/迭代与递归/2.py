'''
任务描述
本关任务：编写递归程序，从键盘输入n，计算n的阶乘并正确输出。

相关知识
为了完成本关任务，你需要掌握：1.如何使用递归函数，2.如何设置递归终止条件。

输入
从键盘输入n,n为大于等于0的整数。

n = input()
递归函数f(n)计算n的阶乘n！
,

测试说明
平台会对你编写的代码进行测试：

测试输入：0
预期输出：1

测试输入：2
预期输出：2

测试输入：5
预期输出：120

平台会使用下列代码调用你编写的函数：

import sample2
n = int(input())
product = sample2.fact(n)
print(product)
'''

def fact(n):
    #  ********* Begin *********#
    #  在此处补全代码#
    if n==0:
        return 1
    else:
        return n*fact(n-1)
    #  ********* End *********#

n = int(input())
product = fact(n)
print(product)