def hundred_numbers():
    i=0
    while i<100:
        yield i
        i+=1

if __name__== '__main__':
    g=hundred_numbers()
    print(next(g))
    print(next(g))
    print(list(g))
    """The generator itself remembers where it left off hence it continues from 2."""