import os

class Person:
    count = 0

    def __init__(self, data):
        Person.count += 1
        self.__father = data[0]
        self.__mother = data[1]
        self.__child = data[2]
        self.__types = {'father': self.__father, 'mother': self.__mother, 'child': self.__child}

        self.set_blood_types()

    def get_child_blood(self, father, mother):
        if father == "O+":
            if mother == "O+":
                return "O+"
            elif mother == "O-":
                return "{O+, O-}"
            elif mother == "A+":
                return "{A+, A-}"
            elif mother == "B":
                return "A"
        elif father == "AB-":
            if mother == "AB+":
                return "{A+, A-, B+, B-, AB+, AB-}"
        return '?'

    def get_parent_blood(self, parent, child):
        if parent == "O+":
            if child == "O-":
                return "{A-, A+, B-, B+, O-, O+}"
        elif parent == "AB+":
            if child == "O+":
                return "IMPOSSIBLE"
        return '?'

    def get_blood_types(self):
        return self.__types

    def set_blood_types(self):
        if self.__father == "?":
            self.__types["father"] = self.get_parent_blood(self.__mother, self.__child)
        elif self.__mother == "?":
            self.__types["mother"] = self.get_parent_blood(self.__father, self.__child)
        elif self.__child == "?":
            self.__types["child"] = self.get_child_blood(self.__father, self.__mother)

def consanguine_calculations(filename):
    # Lecture du fichier
    file = open(filename, 'r')
    line = file.readline()
    i = 0
    while line:
        if line != 'E N D':
            person = Person(line.split())
            types = person.get_blood_types()
            print('Case ' + str(i) + ': ', end='')
            print(types['father'] + ' ' + types['mother'] + ' ' + types['child'])
        line = file.readline()
        i += 1
    file.close()

if __name__ == "__main__":
    consanguine_calculations('input.txt')
