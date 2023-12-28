'''
任务描述
本关任务：编写迭代程序，从键盘输入n，计算n的阶乘并正确输出。

相关知识
为了完成本关任务，你需要掌握：1.迭代程序的基本结构，2.循环语句。

输入
从键盘输入n,n为大于等于0的整数。
迭代计算n的阶乘n！
测试说明
平台会对你编写的代码进行测试：

测试输入：0
预期输出：1

测试输入：2
预期输出：2

测试输入：5
预期输出：120

平台会使用下列代码调用你编写的函数：

import sample1
n = int(input())
product = sample1.fact(n)
print(product)
'''

def fact(n):
    product = 1
    #********* Begin *********#
    # 在此处补全代码#
    while(n):
        product*= n
        n-=1
    #********* End *********#
    return product
n = int(input())
product = fact(n)
print(product)