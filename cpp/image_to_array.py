import numpy as np
from PIL import Image


def read(s, n=1280, m=960):
    im = Image.open(s)
    im = im.convert('L')
    data = im.getdata()
    data = np.matrix(data)
    data = np.reshape(data, (n, m))
    data = data.astype('uint8')
    fileout = open('out1', 'w+')

    data = data.tolist()
    st = str(data)
    st = st.replace('[', '').replace(']', '').replace(',', '')
    fileout.write(st)
    fileout.write(' ')
    fileout.close()


if __name__ == '__main__':
    n, m = map(int, input().split())
    # read('data/'+'xiaoluoxi.jpg', n, m)
    read('data/'+'Jxfn.jpg', n, m)
