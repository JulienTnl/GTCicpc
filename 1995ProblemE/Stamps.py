def GetLine(file):
    line = file.readline()
    if not line:
        exit()
    return line.strip()

def CheckData(S, N, L):
    # Verification du nombre maximal de timbres et du nombre de types de timbres differents
    if S > 10 or N > 10:
        return 0

    # Verification de la valeur des timbres
    i = 0
    while i < len(L):
        if int(L[i]) > 100:
            return 0
        i = i + 1

    # Verification du nombre de timbres du jeu donne
    if (len(L) - 1) != int(L[0]):
        return 0

    return 1

def GetCombinations(res, stamps):
    list = []
    for elem in res:
        for stamp in stamps:
            list.append(elem + ' ' + stamp)
    return list

def IsAPossibleCombination(number, orderedList):
    values = orderedList.split()
    values = [int(i) for i in values]
    if number == sum(values):
        return True
    return False

def FindMaxCoverage(maxStamps, setsOfStamps, stamps):
    coverage = 0
    i = 2
    j = 1
    # On garde uniquement les timbres
    del(stamps[0])
    res = stamps
    allCombinations = []
    allCombinations.append(res)
    # On enregistre toutes les combinaisons possibles
    while i < maxStamps + 1:
        while j < i:
            res = GetCombinations(res, stamps)
            j = j + 1
        allCombinations.append(res)
        i = i + 1
    i = 1
    # On verifie pour chaque combinaison enregistree jusqu'a qu'un nombre ne soit pas possible a atteindre
    while True:
        possible = False
        j = 0
        while j < len(allCombinations) and possible is False:
            k = 0
            while k < len(allCombinations[j]):
                if IsAPossibleCombination(i, allCombinations[j][k]) is True:
                    possible = True
                k = k + 1
            j = j + 1
        if possible is False:
            return i - 1
        i = i + 1
    return 0

def Stamps(filename):
    file = open(filename, 'r')

    while True:
        coverage = 0
        case = 1
        max = 0
        while case == 1:
            # Recuperation du nombre maximum de timbres sur l'enveloppe
            maxStamps = int(GetLine(file))
            # Recuperation du nombre de jeux de timbres
            setsOfStamps = int(GetLine(file))
            # On recupere chaque jeu de timbre
            while setsOfStamps > 0:
                stamps = GetLine(file).split()
                # On verifie que les donnees ne sont pas erronnees
                if CheckData(maxStamps, setsOfStamps, stamps) == 0:
                    print('Donnees erronnees')
                    break
                tmp = FindMaxCoverage(maxStamps, setsOfStamps, stamps)
                if tmp >= max:
                    max = tmp
                setsOfStamps = setsOfStamps - 1
            print("")
            print"max coverage = " + str(max) + " : ",
            for val in stamps:
                print val,
            # On passe au cas suivant
            case = case + 1
Stamps('test.txt')
