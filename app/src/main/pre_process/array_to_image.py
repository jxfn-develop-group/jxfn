import numpy as np
from PIL import Image


def loads(s, n=1280, m=960):
    li = []
    with open(s, 'r') as input_data:
        for line in input_data:
            li.extend(map(int, line.split()))
    arr = np.array(li)
    print(arr)
    arr = arr.reshape((m, n))
    arr = arr.astype('uint8')
    img = Image.fromarray(arr)
    img.save('out.png', 'png')


if __name__ == '__main__':
    n, m = map(int, input().split())
    loads('out2', n, m)
