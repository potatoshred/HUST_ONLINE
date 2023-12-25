'''

'''
#encoding=utf8 
import numpy as np
def mse_score(y_predict,y_test):
    '''
    input:y_predict(ndarray):预测值
          (ndarray):真实值
    ouput:mse(float):mse损失函数值
    '''
    #********* Begin *********#
    M = y_test - y_predict
    mse = np.dot(M.T, M)/len(y_predict)
    #********* End *********#
    return mse
class LinearRegression :
    def __init__(self):
        '''初始化线性回归模型'''
        self.theta = None
    def fit_normal(self,train_data,train_label):
        '''
        input:train_data(ndarray):训练样本
              train_label(ndarray):训练标签
        '''
        #********* Begin *********#
        X_b = np.hstack([np.ones((len(train_data), 1)), train_data])
        self.theta = np.linalg.inv(X_b.T.dot(X_b)).dot(X_b.T).dot(train_label)
        #********* End *********#
        return self.theta
    def predict(self,test_data):
        '''
        input:test_data(ndarray):测试样本
        '''
        #********* Begin *********#
        X_b = np.hstack([np.ones((len(test_data), 1)), test_data])
        return X_b.dot(self.theta)
        #********* End *********#
    
    