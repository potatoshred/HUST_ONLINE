'''
任务描述
本关任务：编写一个贪心算法程序解决TSP问题

相关知识
为了完成本关任务，你需要掌握：1.贪心算法。2.矩阵（此处为二维列表）

贪心算法
是一种在每一步选择中都采取在当前状态下最好或最优（即最有利）的选择，从而希望导致结果是最好或最优的算法。比如在旅行推销员问题中，如果旅行员每次都选择最近的城市，那这就是一种贪心算法。

矩阵
本题目中每一行的数据表示当前节点到所有其他节点的距离（将一个城市视为一个节点），以下方示例输入为例第一行数据0,3,6,7分别表示该行的索引为0表示城市0到其他城市（第一列城市0，第二列城市1，第三列城市2...）的距离分别为0、3、6、7，显然城市0到城市0的距离为0。对于第二行则为城市1到城市0、1、2、3的距离，显然对角线上的数据为0。

编程要求
根据提示，在右侧编辑器补充代码，输出最终路径。

测试说明
平台会对你编写的代码进行测试：

测试输入：

[
    [0, 3, 6, 7],
    [3, 0, 2, 3],
    [6, 2, 0, 2],
    [7, 3, 2, 0]
]
预期输出：
0-1-2-3-0
'''
import math

# TSP问题贪心算法版本

result_path = list()    # 节点列表
matrix = list()
left_node = list()# 保存所有节点
node_list = list()# 节点坐标列表
start_node = 0# 开始节点

#也可自己写代码实现算法，但请不要修改输入和输出，避免影响评测。
def tsp_greedy_agr(matrix: list, start_node: int)-> int:
    """
    tsp贪心算法，可能结果会有误差
    :param matrix:  满秩矩阵
    :param start_node:  出发节点
    :return:    最短距离
    """
    # 0   3   6   7
    # 3   0   2   3
    # 6   2   0   2
    # 7   3   2   0

    result_path = list()
    result_path.append(start_node)# 将开始节点加入列表
    now_node = start_node   # 当前节点
    min_path = 0
    while len(result_path) < len(matrix):# 如果没有走过所有节点
        min_node_index = now_node   # 最小距离节点索引
        matrix[now_node][now_node] = 0xFFFFFF
        for col_index in range(len(matrix[now_node])):
            # 请在此添加代码
            #-----------Begin----------
            if col_index not in result_path:
                if matrix[now_node][col_index] < matrix[now_node][min_node_index]:
                    min_node_index = col_index
            #------------End-----------
        matrix[now_node][now_node] = 0
        min_path += matrix[now_node][min_node_index]     
        result_path.append(min_node_index)
        now_node = min_node_index

    result_path.append(start_node)
    for index in range(len(result_path)):
        result_path[index] = str(result_path[index])
    print('-'.join(result_path))
    # 添加最后节点返回开始节点距离
    return


if __name__ == "__main__":
    matrix = [
        [0.0, 94.54099639838793, 268435455, 268435455, 138.05795884337854, 268435455],
        [94.54099639838793, 0.0, 33.13608305156178, 61.032778078668514, 71.00704190430693, 99.92497185388645],
        [268435455, 33.13608305156178, 0.0, 72.94518489934754, 38.2099463490856, 268435455],
        [268435455, 61.032778078668514, 72.94518489934754, 0.0, 94.49338601193207, 48.27007354458868],
        [138.05795884337854, 71.00704190430693, 38.2099463490856, 94.49338601193207, 0.0, 142.76203977248295],
        [268435455, 99.92497185388645, 268435455, 48.27007354458868, 142.76203977248295, 0.0]
    ]
    tsp_greedy_agr(matrix, 0)

