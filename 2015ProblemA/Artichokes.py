import math as m

def Artichokes(data):
    p = data[0]
    a = data[1]
    b = data[2]
    c = data[3]
    d = data[4]
    n = data[5]

    vector = [None] * (n+1)
    i = 1
    while i <= n:
        vector[i] = p * (m.sin(a * i + b) + m.cos(c * i + d) + 2)
        i += 1
    mx = vector[1]
    ret = 0.0
    i = 1
    while i <= n:
        if vector[i] > mx:
            mx = vector[i]
        else:
            ret = max(ret, mx - vector[i])
        i += 1
    print("%.6f" % ret)


def getData(filename):
    # Lecture du fichier
    file = open(filename, 'r')
    data = []
    line = file.readline()
    data.append(line)
    file.close()
    data = data[0].split()
    for i in range(len(data)):
        data[i] = int(data[i])

    return data

data = getData('input.txt')
Artichokes(data)