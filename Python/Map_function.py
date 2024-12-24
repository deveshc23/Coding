friends=['Ross','Rachel','Monica','Chandler','Joey','Phoebe']
friends_lower=map(lambda x:x.lower(),friends)
print(next(friends_lower))
friends_lower_list=[friend.lower() for friend in friends]
friends_lower_gen=(friend.lower for friend in friends)
"""The map function also returns a generator object"""

class User:
    def __init__(self,username,password):
        self.username=username
        self.password=password

    @classmethod
    def from_dict(cls,data):
        return cls(data['username'],data['password'])

users=[
    {'username':'rolf','password':'123'},
    {'username': 'ross', 'password': '1234'},
]

users_1=[User.from_dict(user) for user in users]
users_2=map(User.from_dict,users)
"""Here the map function method is more readable"""