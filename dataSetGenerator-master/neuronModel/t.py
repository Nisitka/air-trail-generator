from matplotlib import pyplot as plt
import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()
tf.disable_eager_execution()  # чтобы не выдавало RuntimeError старой версии

import tensorflow as tf2
# from tensorflow import keras
# import tensorflow as tf
# import keras

# from keras import models

import random

import glob

from PIL import Image
import numpy as np

def imageToArray(dir, name, format='jpg'):
    image = Image.open(dir + '\\' + name + '.' + format)
    array = np.array(image)

    #print(array)
    return array

# функция для полчения данных внешней среды
def get_trainData():
    print('загружаются изображения и значения ЦФ')

    dirData = 'C:\\Users\\20-konkova.a.n\\Desktop\\trainImages'
    name = 'netImg_'

    listDirPhotos = glob.glob(dirData + "\\*.jpg")
    data = []
    for i in range(0, len(listDirPhotos)):
        data.append(imageToArray(dirData, name + str(i)))

    return data

# построение графика биржевого курса
def plot_data(data):
    print('отображаем случайные картинки входных образов')

# суперкласс для всех стратегий принятия решений
class DecisionPolicy:
    # для заданного состояния используемая стратегия принятия решений
    # определит следующее действие
    def select_action(self, current_data):
        pass

    # улучшение Q-функции из нового опыта или выполнение определенного действия
    def update_q(self, data, action, reward):
        pass

# наследует стратегию принятия решений для использования её функций
class RandomDecisionPolicy(DecisionPolicy):
    def __init__(self, actions):
        self.actions = actions  # инициализация вариантов действий агента

    # случайным образом выбираем следующее действие
    def select_action(self, current_data):
        action = random.choice(self.actions)
        return action

def run_simulations(policy, trainData):
    countEpoch = 5 # кол-во эпох обучения
    for i in range(0, countEpoch):
        run_simulation(policy, trainData, i)

    # сохраняем модель после симуляции
    policy.saveModel()

def run_simulation(policy, trainData, numEpoch): # стратегия, данные для работы агента
    print('epoch ' + str(numEpoch + 1) + ':')

    # прогоняем по обучающей выборке (одна эпоха)
    for i in range(len(trainData)):
        # каждые n пар обновляем процент обучения эпохи
        n = 2
        if i % n == 0:
            print(' {:.2f}%'.format(float(100 * i) / len(trainData)))

        data = trainData[i]

        # корректируем нейронную сеть (обучаем)
        policy.update_q(data, i)

class QLearningDecisionPolicy(DecisionPolicy):
    def __init__(self, actions):
        self.longImg = 200

        self.epsilon = 0.95
        self.gamma = 0.3
        self.actions = actions
        self.output_dim = len(actions)

        self.run_cnn()

    def run_cnn(self):
        longImg = 200

        countActions = longImg * longImg

        self.x = tf.compat.v1.placeholder(tf.float32, [longImg, longImg, 3], name="input")
        x_shaped = tf.reshape(self.x, [-1, longImg, longImg, 3])
        self.y = tf.compat.v1.placeholder(tf.float32, [countActions])

        # создание сверточных слоев
        layer1 = self.createConvLayer(x_shaped, 3, 32, [5, 5], [2, 2], name='layer1')
        layer2 = self.createConvLayer(layer1, 32, 64, [5, 5], [2, 2], name='layer2')

        flattened = tf.reshape(layer2, [-1, 50 * 50 * 64])

        wd1 = tf.Variable(tf.random.truncated_normal([50 * 50 * 64, 1000], stddev=0.03), name='wd1')
        bd1 = tf.Variable(tf.random.truncated_normal([1000], stddev=0.01), name='bd1')

        denseLayer1 = tf.matmul(flattened, wd1) + bd1
        denseLayer1 = tf.nn.relu(denseLayer1)

        wd2 = tf.Variable(tf.random.truncated_normal([1000, countActions], stddev=0.03), name='wd2')
        bd2 = tf.Variable(tf.random.truncated_normal([countActions], stddev=0.01), name='bd2')

        denseLayer2 = tf.matmul(denseLayer1, wd2) + bd2
        self.q = tf.nn.relu(denseLayer2, name='result')

        loss = tf.square(self.y - self.q)
        self.train_op = tf.train.AdagradOptimizer(0.01).minimize(loss)
        self.sess = tf.Session()
        self.sess.run(tf.global_variables_initializer(), options=tf.RunOptions(report_tensor_allocations_upon_oom=True))

        # определяем модуль сохранения
        self.saver = tf.train.Saver()

    def createConvLayer(self,
            input_data, num_input_channels, num_filters, filter_shape, pool_shape, name):
        conv_filt_shape = [
            filter_shape[0], filter_shape[1], num_input_channels, num_filters]

        weights = tf.Variable(
            tf.random.truncated_normal(conv_filt_shape, stddev=0.03), name=name + '_W')
        bias = tf.Variable(tf.random.truncated_normal([num_filters]), name=name + '_b')

        outLayer = tf.nn.conv2d(input_data, weights, [1, 1, 1, 1], padding='SAME')

        outLayer += bias
        outLayer = tf.nn.relu(outLayer)
        ksize = [1, pool_shape[0], pool_shape[1], 1]
        strides = [1, 2, 2, 1]
        outLayer = tf.nn.max_pool(
            outLayer, ksize=ksize, strides=strides, padding='SAME')
        return outLayer

    # выбоор действия
    def select_action(self, current_data):  # , step):
        threshold = self.epsilon  # min(self.epsilon, step / 1000.)
        # с вероятностью epsilon выбираем наилучшее дейсвие
        if random.random() < threshold:
            action_q_vals = self.sess.run(self.q, feed_dict={self.x: current_data})
            action_idx = np.argmax(action_q_vals) # узнаем индекс наилучшего действия
            action = self.actions[action_idx]
        # иначе дейсвуем случайным образом (получаем опыт)
        else:
            action = self.actions[random.randint(0, len(self.actions) - 1)]

        return action

    # тренеровка сети
    def update_q(self, data, idData):
        action_q_vals = self.sess.run(self.q, feed_dict={self.x: data})

        current_action_idx = self.actions.index(self.select_action(data))  # узнаем индекс выбранного дейсвия

        # получаем награду за дейсвие
        action_q_vals[0, current_action_idx] = self.getReward(idData, current_action_idx)  # + self.gamma *

        action_q_vals = np.squeeze(np.asanyarray(action_q_vals))
        self.sess.run(self.train_op, feed_dict={self.x: data, self.y: action_q_vals})

    def saveModel(self):
        print("Сохранение модели...")
        self.saver.save(self.sess, 'model2') # Сохранение модели

    def getReward(self, idImg, idAction):
        # получаем объект файла
        file = open('C:\\Users\\20-konkova.a.n\\Desktop\\rewardValues\\valQFun_' + str(idImg) + '.txt', "r")

        # считываем строку
        lines = file.readlines()

        reward = lines[idAction // 200].split(' ')[idAction % 200]
        #print(reward)

        return reward

if __name__ == '__main__':
    print('Hello, Diplom!')

    # импортируем данные, хар-ие внешнию среду
    trainData = get_trainData()
    plot_data(trainData)  # визуализируем данные для обучения сети

    # варианты действий сети
    actions = []
    sizeMap = 200
    for i in range(0, sizeMap*sizeMap):
        actions.append(i)

    policy = QLearningDecisionPolicy(actions)
    run_simulations(policy, trainData)