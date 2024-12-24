friends=[
    {
        'name':'Rolf',
        'location':'Washington D.C.'
    },
    {
        'name':'Ross',
        'location':'New York.'
    },
    {
        'name':'Rolf',
        'location':'Boston'
    },
]
your_location=input("Enter your location: ")
friends_nearby=[friend for friend in friends if friend['location']==your_location]

if any(friends_nearby):
    print("You are not alone!")

print(all([0,1,2,3,4,5]))# it will be false as it has a 0