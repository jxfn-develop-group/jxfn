import numpy as np
from PIL import Image


def read(s):
    im = Image.open(s)
    im = im.convert('L')
    im = im.resize((28, 28))
    data = im.getdata()
    data = np.matrix(data)
    data = np.reshape(data, (28, 28))
    data = data.astype('uint8')
    try:
        fileout = open('out1', 'a+')
    except FileNotFoundError:
        fileout = open('out1', 'w+')

    st = str(data)
    st = st.replace('[', '')
    st = st.replace(']', '')
    fileout.write(st)
    fileout.close()


if __name__ == '__main__':
    for i in range(500, 1000):
        read('data' + '/' + 'img001-00' + str(i) + '.png')
