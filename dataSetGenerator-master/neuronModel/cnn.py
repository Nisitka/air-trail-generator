import tensorflow as tf
tf.compat.v1.disable_eager_execution()  # чтобы не выдавало RuntimeError старой версии

import tensorflow as tf2

import numpy as np

from PIL import Image
import glob

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

def run_cnn():
    trainData = get_trainData()
    longImg = 200

    learning_rate = 0.0001
    epochs = 10
    batch_size = 5

    countActions = longImg * longImg

    x = tf.compat.v1.placeholder(tf.float32, [None, longImg * longImg])
    x_shaped = tf.reshape(x, [-1, longImg, longImg, 3])
    y = tf.compat.v1.placeholder(tf.float32, [None, countActions])

    # создание сверточных слоев
    layer1 = createConvLayer(x_shaped, 3, 32, [5, 5], [2,2], name='layer1')
    layer2 = createConvLayer(layer1, 32, 64, [5, 5], [2, 2], name='layer2')

    flattened = tf.reshape(layer2, [-1, 7*7*64])

    wd1 = tf.Variable(tf.random.truncated_normal([7*7*64, 1000], stddev = 0.03), name='wd1')
    bd1 = tf.Variable(tf.random.truncated_normal([1000], stddev = 0.01), name='bd1')

    denseLayer1 = tf.matmul(flattened, wd1) + bd1
    denseLayer1 = tf.nn.relu(denseLayer1)

    wd2 = tf.Variable(tf.random.truncated_normal([1000, countActions], stddev = 0.03), name='wd2')
    bd2 = tf.Variable(tf.random.truncated_normal([countActions], stddev = 0.01), name='bd2')

    denseLayer2 = tf.matmul(denseLayer1, wd2) + bd2
    y_ = tf.nn.softmax(denseLayer2)

    cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits = denseLayer2, labels = y))

    optimiser = tf.compat.v1.train.AdagradOptimizer(learning_rate = learning_rate).minimize(cross_entropy)

    correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

    init_op = tf.global_variables_initializer()

    tf.summary.scalar('accuracy', accuracy)
    merged = tf.summary.merge_all()
    writer = tf.summary.FileWriter('')

    with tf.Session() as sess:
        sess.run(init_op)
        total_batch = 10

    print("\nПолный курс обучения!")

def createConvLayer(
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

if __name__ == "__main__":
    run_cnn()


