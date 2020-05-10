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
            if sum >= ans:
                if sum > ans or (sum == ans and (i - tmp > end - start)):
                    start = tmp + 2
                    end = i + 2
            ans = sum
        i += 1
        routes += 1
        if ans > 0:
            print("The nicest part of route {} is between stops {} and {}".format(routes, start, end))
        else:
            print("Route {} has no nice parts".format(routes))
        essai -= 1

main()