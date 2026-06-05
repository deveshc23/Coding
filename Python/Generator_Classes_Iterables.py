class FirstHundredGenerator:
    def __init__(self):
        self.number=0
    def __next__(self):
        if self.number<100:
            current=self.number
            self.number+=1
            return current
        else:
            raise StopIteration()


my_gen=FirstHundredGenerator()
print(my_gen.number)
next(my_gen)
print(my_gen.number)

"""Iterators have a dunder next function i.e. you can call the next function on it
   whereas iterables have a dunder iter method 
"""

class FirstHundredIterable:
    def __iter__(self):
        return FirstHundredGenerator()

print(sum(FirstHundredIterable()))



class AnotherIterable:
    def __init__(self):
        self.cars=['Fiesta','Focus']
    def __len__(self):
        return len(self.cars)
    def __getitem__(self, i):
        return self.cars[i]

"""Whenever a class has a len and getitem function a for loop can be used"""

for car in AnotherIterable():
    print(car)

"""The function Another Iterable does not have a iter method but still it is an iterable.
   So in Python an iterable has either a dunder iter method or a len and getitem functions """

"""REMEMBER !!!
   An iterator is used to get the next value
   An iterable is used to go over all the values of the iterator"""

