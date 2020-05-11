def initialisation_deplacees(nb_poupees):
    deplacees = []
    for i in range(nb_poupees):
        deplacees.append(0)
    return deplacees

def Matryoshka(data):
    nb_poupees = data[0]
    poupees = data[1]
    deplacees = initialisation_deplacees(nb_poupees)
    moves = 0
    while 1:
        changements = 0
        # De gauche a droite
        for i in range(nb_poupees):
            # Si la poupee n'a pas encore ete deplacee et n'est pas la derniere
            if deplacees[i] == 0 and i != (nb_poupees - 1):
                if poupees[i] < poupees[i + 1]:
                    changements += 1
                    deplacees[i] = 1
        # De droite a gauche
        for i in range(nb_poupees):
            # Si la poupee n'a pas encore ete deplacee et n'est pas la premiere
            if deplacees[i] == 0 and i != 0:
                if poupees[i] < poupees[i - 1]:
                    changements += 1
                    deplacees[i] = 1
        if changements == 0:
            break
        moves += changements
    return moves

def getData(filename):
    # Lecture du fichier
    file = open(filename, 'r')
    data = []
    nb_poupees = file.readline()
    data.append(int(nb_poupees))
    tailles_poupees = file.readline()
    data.append(tailles_poupees)
    file.close()
    data[1] = data[1].split()
    for i in range(len(data[1])):
        data[1][i] = int(data[1][i])

    return data

data = getData('input.txt')
print(Matryoshka(data))