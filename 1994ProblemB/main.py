def lire():
    fichier = open("input.txt", "r")
    nombre_test = fichier.read().count("-1") -1
    cpt = 0
    liste_essais=[]
    for i in range(0,nombre_test):
        liste_essais.append([])
    fichier = open("input.txt", "r")
    for line in fichier:
        if(line.rstrip()!='-1'):
            liste_essais[cpt].append(int(line.rstrip()))
        else:
            if(cpt == nombre_test):
                break
            else:
              cpt += 1
    return liste_essais

def recu_essais_maximum(liste, nombre_test,dernier_nombre):
    nombre_max = nombre_test
    for i in range(0,len(liste)):
        if(liste[i]<dernier_nombre):
           nombre_recu = recu_essais_maximum(liste[i+1:],nombre_test+1,liste[i])
           if(nombre_recu>nombre_max):
               nombre_max= nombre_recu
    return nombre_max

def essais_maximum(liste):
    nombre_max = recu_essais_maximum(liste[1:],1,liste[0])
    return(nombre_max)

def print_result(nombre_max, num_essai):
    print("Test #"+str(num_essai)+":")
    print(" maximum possible interceptions: "+ str(nombre_max) +"\n")

def main():
    liste_essais = lire()
    for i in range(0, len(liste_essais)):
        print_result(essais_maximum(liste_essais[i]),i+1)


if __name__ == '__main__':
    main()