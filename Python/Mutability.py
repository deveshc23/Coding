friends_last_seen={
    'Rolf':31,
    'Ross':7,
    'Chandler':5
}

another_variable=friends_last_seen

print(id(friends_last_seen))
print(id(another_variable))
"""Same id value as the dictionary is the same.
   The id function is used to give id of any object"""

friends_last_seen={
    'Rolf':31,
    'Ross':7,
    'Chandler':5
}
print(id(friends_last_seen))

"""There is a change in id as these are 2 different dictionaries
    with the same items in it"""

friends_last_seen['Rolf']=25
print(id(friends_last_seen))

"""On mutating the id has not been changed hence these are mutable objects.
    The dictionary calls the __setitem__(self, function which mutates"""

"""But there are some immutable objects whose id changes on editing them"""

my_int=5
print(id(my_int))
my_int+=1
print(id(my_int))
"""These are not immutable similarly floats,tuples,strings are immutable"""


friends=['Rolf','Jose']
print(id(friends))

friends.append('Jen')
print(id(friends))

"""Lists are mutable hence see the change does not have a change on the id """

"""Strings
    Ints
    Floats
    Tuples
    These are the immutable types"""