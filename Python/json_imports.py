import json

file=open(r'C:\Users\choud\OneDrive\Desktop\Coding\friends_json.txt','r')
file_contents=json.load(file)# Converts string into a dictionary
file.close()

"""The above set of lines can be written in a different way with the 'with' keyword"""
with open(r'C:\Users\choud\OneDrive\Desktop\Coding\friends_json.txt','r') as file:
    file_contents_2 = json.load(file)
#with is knows as a context manager

print(file_contents['friends'][0])

cars=[
    {'make':'Ford','model':'Fiesta'},
    {'make':'Ford','model':'Focus'},
]

# file=open(r'C:\Users\choud\OneDrive\Desktop\Coding\cars_json.txt','w')
# json.dump(cars,file)
# file.close()

my_json_string='[{"name":"Alfa Romeo","released":"1950"}]'
incorrect_car=json.loads(my_json_string)# Helps convert string into a dictionary
print(incorrect_car[0]['name'])