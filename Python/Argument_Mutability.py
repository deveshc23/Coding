friends_last_seen={
    'Rolf':31,
    'Ross':7,
    'Chandler':5
}

def see_friends(friends,name):
    print(id(friends))
    friends[name]=0

print(id(friends_last_seen))
print(id(friends_last_seen['Rolf']))
see_friends(friends_last_seen,'Rolf')
print(id(friends_last_seen['Rolf']))
print(id(friends_last_seen))

"""Even during the function call the argument has 
    the same dictionary hence the id is same """

"""The id of the value friend_last_seen['Rolf'] has changed because it was an integer"""

primes=[2,3,5]
print(id(primes))

primes=primes+[7,11]
print(id(primes))

"""If primes += is used then it is just mutated but if primes=primes+[7,11] is used,
    then two lists are being added and the id changes"""