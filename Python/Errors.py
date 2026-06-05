class Car:
    def __init__(self,make,model):
        self.make = make
        self.model = model
    def __repr__(self):
        return '<Car {self.make} {self.model}>'

class Garage:
    def __init__(self):
        self.cars=[]
    def __len__(self):
        return len(self.cars)
    def add_car(self,car):
        if not isinstance(car,Car):#if the car(parameter) is not an instance of the Car class
            raise TypeError(f'Tried to add a {car.__class__.__name__} to the garage, but you can only add Car objects')
        self.cars.append(car)
ford=Garage()
car=Car('Ford','Fiesta')
print(ford.add_car(car))

try:
    ford.add_car('Ford')
except TypeError:
    print('Your car was not a Car!')