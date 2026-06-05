#Destructuring in tuples
currencies = 0.8, 1.2
usd, eur = currencies
print(usd, eur)

friends = [('Rolf', 25), ('Anne', 37), ('Charlie', 31), ('Bob', 22)]
for friend, age in friends:
    print(f'{friend} is {age} years old.')

#Iterating in Dictionaries
friends = {'Rolf': 25, 'Anne': 37, 'Charlie': 31, 'Bob': 22}
for friend in friends:
    print(f'{friend} is {friends[friend]} years old.')

#Destructuring in Dictionaries
friend_ages = {'Rolf': 25, 'Anne': 37, 'Charlie': 31, 'Bob': 22}
for friend, age in friend_ages.items():
    print(f'{friend} is {age} years old.')

#List Slicing
friends = ['Rolf', 'Jose', 'Randy', 'Anna', 'Mary']
print(friends[2:4])

#List Comprehension
numbers = [0, 1, 2, 3, 4]
doubled_numbers=[]
for number in numbers:
    doubled_numbers.append(number * 2)
    print(doubled_numbers)
#OR
doubled_numbers = [number * 2 for number in numbers]

#List Comprehension with Conditional
names = ['Rolf', 'Bob', 'Jen']
lower = [name.lower() for name in names]
print(lower)
friend = input('Enter your friend name: ')
friends = ['Rolf', 'Jose', 'Randy', 'Anna', 'Mary']
friends_lower = [friend.lower() for friend in friends]
if friend.lower() in friends_lower:
    print(f"{friend.title()} is one of your friends.")

ages=[22, 35, 27, 21]
odds = [age for age in ages if age % 2 == 1]
print(odds)
