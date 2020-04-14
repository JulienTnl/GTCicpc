import re

def getOrder(wordList):
    order = []
    i = 0
    while i < len(wordList):
        if wordList[i] != '0':
            if wordList[i].isdigit():
                order.insert(0, order[int(wordList[i]) - 1])
                order.pop(int(wordList[i]))
                print(order[0])
            else:
                print(wordList[i])
                if wordList[i] in order:
                    order.insert(0, order.pop(order.index(wordList[i])))
                else:
                    order.insert(0, wordList[i])
        i = i + 1
    return order

def Uncompress(filename):
    with open(filename, 'r') as file:
        data = file.read()
    wordList = re.sub('[^\w]', ' ', data).split()

    order = getOrder(wordList)

Uncompress('uncomp.in')
