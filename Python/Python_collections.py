"""
* counter
* defaultdict
* ordereddict
* namedtuple
* deque
"""

from collections import Counter
from collections import defaultdict
from collections import OrderedDict
from collections import namedtuple
from collections import deque
from pandas.core.window.doc import template_returns

#Counter
device_temperatures=[13.5,14,15,14,14.5,14.5,14.5,16.0]
temperature_counter=Counter(device_temperatures)
print(temperature_counter[14.0])

#DefaultDict
coworkers=[('Rolf','MIT'),('Jen','Oxford'),('Rolf','Cambridge'),('Charlie','Manchester')]
alma_maters=defaultdict(list)
for coworker,place in coworkers:
    alma_maters[coworker].append(place)

print(alma_maters['Rolf'])
print(alma_maters['Chandler'])

my_company='Jane Street'
coworkers=['Jen','Li','Chandler','Joey']
other_coworkers=[('Rolf','Apple'),('Monica','Amazon')]
coworker_companies=defaultdict(lambda:my_company)
for person,company in other_coworkers:
    coworker_companies[person]=company

print(coworker_companies[coworkers[0]])
print(coworker_companies['Rolf'])

#OrderedDict
o=OrderedDict()
o['Ross']=9
o['Monica']=5
o['Chandler']=12
print(o)
o.move_to_end('Ross')
o.move_to_end('Chandler',last=False)
print(o)
o.popitem()
print(o)


#NamedTuple
account=('checking',1850.90)
print(account[0]) # name
print(account[1]) # balance
Account=namedtuple('Account',['name','balance'])
account=Account('checking',1850.90)
print(account)


#Deque
friends=deque(('Ross','Monica','Chandler','Joey'))
friends.append('Rachel')
friends.appendleft('Phoebe')
print(friends)
friends.pop()
friends.popleft()
print(friends)