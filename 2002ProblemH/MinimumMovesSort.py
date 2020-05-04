def GetMinMovesToSort(toSort):
    n = len(toSort)
    # Création d'un tableau de tuples, la première valeur correspond à l'index et la seconde à la valeur
    array_pos = [*enumerate(toSort)]
    # On trie les éléments par ordre croissant
    array_pos.sort(key=lambda it: it[1])
    # On garde une trace des éléments visités ou non
    visited = {k: False for k in range(n)}

    operations = 0
    # Boucle sur les éléments du tableau initial à trier
    for i in range(n):
        # Si on a déjà "swap" ou que l'élement est déjà à la bonne position
        if visited[i] or array_pos[i][0] == i:
            continue
        cycle_size = 0
        j = i

        # Boucle sur les éléments non visités
        while not visited[j]:
            visited[j] = True
            # On passe au noeud suivant
            j = array_pos[j][0]
            cycle_size += 1

        if cycle_size > 0:
            operations += (cycle_size - 1)
    return operations

def getData(filename):
    # Lecture du fichier
    file = open(filename, 'r')
    data = []
    line = file.readline()
    while line:
        data.append(line)
        line = file.readline()
    file.close()
    return data


data = getData('input.txt')
c = 1
for i in range(len(data)):
    # On récupère les listes à trier
    if i%2 != 0:
        # On convertit en listes d'entiers
        list = [int(j) for j in data[i].split()]
        print('Case ' + str(c) + ': ' + str(GetMinMovesToSort(list)) + '\n')
        c += 1
