import numpy as np
from PIL import Image


def read(s):
    im = Image.open(s)
    im = im.convert('L')
    data = im.getdata()
    data = np.matrix(data)
    data = np.reshape(data, (1200, 900))
    data = data.astype('uint8')
    try:
        fileout = open('out1', 'a+')
    except FileNotFoundError:
        fileout = open('out1', 'w+')

    data = data.tolist()
    st = str(data)
    st = st.replace('[', '').replace(']', '').replace(',', '')
    fileout.write(st)
    fileout.write(' ')
    fileout.close()


if __name__ == '__main__':
    read('data/'+'img001-007.png')
