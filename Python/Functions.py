def greet():
    name=input('Enter your name: ')
    print(f'Hello, {name}!')

greet()
#Function can be called only after it is defined.
#Function can be defined inside another function.
#Function can be passed as an argument to another function.
#Function can be returned from another function.
#Function can be assigned to a variable.

cars=[
    {'make': 'Ford', 'model': 'Fiesta', 'mileage': 23000, 'fuel_consumed': 460},
      {'make': 'Ford', 'model': 'Focus', 'mileage': 17000, 'fuel_consumed': 350},
      {'make': 'Mazda', 'model': 'MX-5', 'mileage': 49000, 'fuel_consumed': 900},
      {'make': 'Mini', 'model': 'Cooper', 'mileage': 31000, 'fuel_consumed': 235}
]

def calculate_mpg(car):
    mpg=car['mileage']/car['fuel_consumed']
    name=f"{car['make']} {car['model']}"
    print(f'{name} does {mpg} miles per gallon.')
    return mpg
for car in cars:
    calculate_mpg(car)

#Named Arguments
print('Hello', end='-')
print('World', end='!')
print([1, 2, 3, 4], sep=';')


def greet():
    print('Hello')

def before_and_after(func):
    print('Before...')
    func()
    print('After...')

before_and_after(greet)
#Function can be passed as an argument to another function.


