'''
任务描述
自然对数是以常数 e 为底的对数，在物理、生物等科学中具有非常重要的应用。本关任务要求利用 Python 编程实现自然对数函数。

相关知识
自然对数与麦克劳林级数
泰勒级数在近似计算中有重要作用，在上一关卡中也有提到用泰勒级数对arctg函数做近似计算。通过函数在自变量零点的导数求得的泰勒级数又叫做麦克劳林级数。

自然对数的麦克劳林级数的公式如下所示：
ln(x+1)=∑ 
n=1
∞
​
  
n
(−1) 
n+1
 
​
 x 
n
 ,  ∀x∈(−1,1]
公式展开如下所示，迭代项数越多，近似计算的值越精确：
ln(x+1)≈x− 
2
x 
2
 
​
 + 
3
x 
3
 
​
 −⋯+ 
n
(−1) 
n+1
 
​
 x 
n
 ,  ∀x∈(−1,1]

python函数返回值
Python 函数可以返回多个值，比如在游戏中经常需要从一个点移动到另一个点，给出坐标、位移和角度，就可以计算出新的坐标。其函数定义如下：

def move(x, y, step, angle=0):
    nx = x + step * math.cos(angle)
    ny = y - step * math.sin(angle)
    return nx, ny
命令行调用运行结果如下：

>>> x, y = move(100, 100, 60, math.pi / 6)
>>> print(x, y)
151.96152422706632 70.0
该函数返回值是一个元组tuple。在语法上，返回一个tuple可以省略括号，而多个变量可以同时接收一个tuple，按位置赋给对应的值。所以，Python 的函数返回多值其实就是返回一个tuple，但写起来更方便。

编程要求
请在右侧代码框中编写程序实现ln函数，根据输入的x和迭代项数N（默认为 50 ）计算对数值，并分析真实误差（相对于 math 库自然对数函数的计算结果）。

ln函数将返回两个值：计算结果与误差的绝对值。

提示
在math库中自然对数的函数名是log
计算真实误差时需要调用绝对值函数fabs
测试说明
本实训的测试样例如下：
测试输入：2
预期输出：ln(2.00)=0.68324716 error=0.00990002

平台会使用下列代码调用你编写的函数：

from sample import ln
x = float(input())
value, error = ln(x)
print('ln(%.2f)=%.8f error=%.8f'% (x, value, error))
'''

import math


def ln(x, N=50):
    '''
    :param x: 输入值
    :param N: 迭代项数，缺省值为50
    :return: 对数值，误差的绝对值
    '''
    #   请在此添加实现代码   #
    # ********** Begin *********#
    x-=1
    out = x
    for i in range(1, N):
        out += ((-1)**i)*(x**(i+1))/(i+1)
    return out, math.fabs(math.log(x+1)-out)
    # ********** End **********#
x = float(input())
value, error = ln(x)
print('ln(%.2f)=%.8f error=%.8f'% (x, value, error))