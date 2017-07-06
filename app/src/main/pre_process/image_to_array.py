import numpy as np
from PIL import Image


def read(s, n=1200, m=900):
    im = Image.open(s)
    im = im.convert('L')
    data = im.getdata()
    data = np.matrix(data)
    data = np.reshape(data, (n, m))
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
    n, m = map(int, input().split())
    read('data/'+'xiaoluoxi.jpg', n, m)
