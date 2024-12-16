#Ask the user for a list of 3 friends
# For each friend, we will tell the user whether they are nearby
# For each nearby friend we will save their name in nearby_friends.txt

friends=input('Enter 3 friends: ').split(',')
people=open(r'C:\Users\choud\OneDrive\Desktop\Coding\people.txt','r')
people_nearby=[line.strip() for line in people.readlines()]
people.close()

friends_set=set(friends)
people_nearby_set=set(people_nearby)
#print(friends_set)
friends_nearby_set=friends_set.intersection(people_nearby_set)

nearby_friends_file=open(r'C:\Users\choud\OneDrive\Desktop\Coding\nearby_files.txt','w')
for friend in friends_nearby_set:
    print(f'{friend} is nearby! Meet up with them ')
    nearby_friends_file.write(f'{friend}\n')

nearby_friends_file.close()


