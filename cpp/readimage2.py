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
    for j in range(10, 56):
        for i in range(2):
            read('data' + '/' + 'img00' + str(2-i) + '-0' + str(j) + '.png')
            # (55-9)*2 = 92

    for i in range(2):
        for j in range(1, 10):
            read('data' + '/' + 'img00' + str(2-i) + '-00' + str(j) + '.png')
            # 9*2 = 18
