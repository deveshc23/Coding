operations={
    "average": lambda x: sum(x)/len(x),
    "total": lambda x:sum(x),
    "top": lambda x:max(x),
}

students = [
    {'name': 'Rolf', 'grades': (67, 90, 95, 100)},
    {'name': 'Bob', 'grades': (56, 78, 80, 90)},
    {'name': 'Jen', 'grades': (98, 90, 95, 99)},
    {'name': 'Anne', 'grades': (100, 100, 95, 100)}
]

for student in students:
    name = student['name']
    grades = student['grades']
    print(f"Student: {name}")
    operation=input('Enter "average", "total", or "top": ')
    result=operations[operation](grades)
    print(result)

