import sys
import numpy as np
from PIL import Image
from PIL import ImageFilter
from PIL import ImageEnhance
import pytesseract


def read(s):
    im = Image.open(s)
    im = im.convert('L')
    im = im.resize((28,28))
    data = im.getdata()
    data = np.matrix(data)
    data = np.reshape(data,(28,28))
    data = data.astype('uint8')
    fileout = open('out1','w+')
    # print(data)
    st = str(data)
    st = st.replace('[','')
    st = st.replace(']','')
    fileout.write(st)
    fileout.close()

    #new_im = Image.fromarray(data)

if __name__ == "__main__":
    filein = open('addressofpic','r+')
    for i in filein.readlines():
        s = i[:-1]
        read(s)
    filein.close()
