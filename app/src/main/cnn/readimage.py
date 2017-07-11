import sys
import numpy as np
from PIL import Image
from PIL import ImageFilter
from PIL import ImageEnhance
import pytesseract


def read(s,fileout):
    im = Image.open(s)
    im = im.convert('L')
    im = im.resize((28,28))
    data = im.getdata()
    data = np.matrix(data)
    data = np.reshape(data,(28,28))
    data = data.astype('uint8')

    # print(data)
    st = str(data)
    st = st.replace('[','')
    st = st.replace(']','')
<<<<<<< HEAD
    fileout.write(st)
<<<<<<< HEAD
    fileout.write('\n\n')
=======
>>>>>>> 3bb7805d5699b6877f89cd018ab6e372136e1c2a
=======
    fileout.write(st+'\n')
>>>>>>> cnn-dev
    # fileout.close()

    #new_im = Image.fromarray(data)

if __name__ == "__main__":
    print('Please input the address of picture:')
    s = input()
    try :
        filein = open(s, 'r')
    except FileNotFoundError as err:
        print('please input the valid filename!')
        sys.exit(0)
    print('Please input the filename of output:')
    s = input()
    fileout = open(s,'w')
    for i in filein.readlines():
        s = i[:-1]
        print(s)
        read(s,fileout)
    filein.close()
    fileout.close()
