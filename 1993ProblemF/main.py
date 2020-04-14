def get_puzzle(f):
    matrix = [[0 for x in range(5)] for y in range(5)]
    for j in range(0, 5):
        li = f.readline()
        print(li)
        for k in range(0, 5):
            matrix[j][k] = li[k]
    return matrix


if __name__ == '__main__':
    f = open("input.txt", "r")
    count = 0
    for line in f:
        count += 1
    for i in range(0, 3):
        puz = get_puzzle(f)
        print(puz)
    f.close()