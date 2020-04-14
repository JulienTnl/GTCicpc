import re

def getOrder(wordList):
    order = []
    i = 0
    while i < len(wordList):
        # On ignore le 0 de fin
        if wordList[i] != '0':
            # Si on a un nombre
            if wordList[i].isdigit():
                # On ajoute le mot correspondant en debut de liste
                order.insert(0, order[int(wordList[i]) - 1])
                # Et on supprime son ancien emplacement
                order.pop(int(wordList[i]))
                print(order[0])
            else:
                print(wordList[i])
                # Si le mot etait deja dans la liste, on le deplace au debut
                if wordList[i] in order:
                    order.insert(0, order.pop(order.index(wordList[i])))
                # Sinon, on l'ajoute simplement
                else:
                    order.insert(0, wordList[i])
        i = i + 1
    return order

def Uncompress(filename):
    # Lecture du fichier
    with open(filename, 'r') as file:
        data = file.read()
    # On recupere tous les mots en supprimant les caracteres inutiles (-, ., espaces, etc)
    wordList = re.sub('[^\w]', ' ', data).split()

    order = getOrder(wordList)

Uncompress('uncomp.in')
