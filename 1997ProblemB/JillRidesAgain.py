def main():
    routes = 0
    essai = int(input('le nombre de route: '))
    while essai > 0:
        s = int(input('nombre darret de la route {}: '.format(essai)))
        tmp = 1
        start = 0
        end = 0
        sum = 0
        ans = 0
        i = 2
        for i in range(s-1):
            x = int(input('note de la route: '))
            sum += x
            if sum < 0:
                sum = 0
                tmp = i
##








#main()