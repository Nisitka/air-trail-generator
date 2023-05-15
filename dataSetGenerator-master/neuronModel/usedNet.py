import tensorflow.compat.v1 as tf
tf.disable_eager_execution()  # чтобы не выдавало RuntimeError старой версии

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

if __name__ == '__main__':
    print('Hello, Diplom!')

    data = get_trainData()

    with tf.Session() as sess:
        saver = tf.train.import_meta_graph('model1.meta')
        saver.restore(sess, tf.train.latest_checkpoint('./'))

        graph = tf.get_default_graph()
        input_x = graph.get_tensor_by_name("input:0")
        result = graph.get_tensor_by_name("result:0")

        feed_dict = {input_x: data[78], }

        predictions = result.eval(feed_dict=feed_dict)

        predictions = np.squeeze(predictions)
        print(predictions)

        maxV = max(predictions)
        print(maxV)

        numPix = list(predictions).index(maxV)

        print("X: " + str(numPix % 200))
        print("Y: " + str(numPix // 200))
