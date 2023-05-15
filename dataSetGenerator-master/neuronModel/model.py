from sys import argv

from PIL import Image
import numpy as np

import os
dirApp = os.path.dirname(os.path.abspath(__file__))  # путь к исп. файлу

import tensorflow.compat.v1 as tf
tf.disable_eager_execution()  # чтобы не выдавало RuntimeError старой версии

dir_fileInput  = argv[1]  # входное изображение
dir_fileOutput = argv[2]  # файл для выходной информации
dir_fileModel  = argv[3]  # файл модели

image = Image.open(dir_fileInput)
data = np.array(image)

with tf.Session() as sess:
    saver = tf.train.import_meta_graph(dir_fileModel)

    patchModel, filename = os.path.split(dir_fileModel)
    print(patchModel, filename)

    saver.restore(sess, tf.train.latest_checkpoint(patchModel+'\\'))

    graph = tf.get_default_graph()
    input_x = graph.get_tensor_by_name("input:0")
    result = graph.get_tensor_by_name("result:0")

    feed_dict = {input_x: data, }

    predictions = result.eval(feed_dict=feed_dict)

    predictions = np.squeeze(predictions)

    maxV = max(predictions)

    numPix = list(predictions).index(maxV)

    x = numPix % 200  # X - это остаток, a 
    y = numPix // 200 # Y - это целая часть от общего кол-ва решений

    print("X: " + str(x))
    print("Y: " + str(y))

    text = str(x) + ' ' + str(y)
    with open(dir_fileOutput, 'w') as txtFile:
        txtFile.write(text)