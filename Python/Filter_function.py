def starts_with_r(friend):
    return friend.startswith('R')


friends=['Ross','Rachel','Monica','Chandler','Joey','Phoebe']
start_with_r=filter(starts_with_r,friends)

# print(next(start_with_r))
print(list(start_with_r))

"""Instead of writing a function for starts_with_r you can use the lambda function"""

starting_with_r=filter(lambda friend:friend.startswith('R'),friends)
print(next(starting_with_r))
print(list(starting_with_r))

"""Filter function returns a generator object, hence the next keyword has to used"""