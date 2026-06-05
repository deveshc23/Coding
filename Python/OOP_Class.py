my_student={
    'name':'Rolf Smith',
    'grades':(89,90,93,78,90)
}

def average_grade(student):
    return sum(student['grades'])/len(student['grades'])

class Student:
    def __init__(self,new_name,new_grade): #dunder functions
        self.name=new_name
        self.grades=new_grade
    def average(self):
        return sum(self.grades)/len(self.grades)

student_one=Student('Rolf Smith',(89,90,93,78,90))

print(student_one.name)
print(student_one.average())

class Movie:
    def __init__(self,name,year):
        self.name=name
        self.year=year
        self.actors=[]
    def add_actor(self,actor):
        self.actors.append(actor)

class Garage:
    def __init__(self):
        self.cars=[]
    def __len__(self):
        return len(self.cars)
    def __getitem__(self,i):
        return self.cars[i]
    def __repr__(self):
        return f'<Garage {self.cars}>'
    def __str__(self):
        return f'Garage with {len(self)} cars'
    def length(self):
        return len(self.cars)

ford=Garage()
ford.cars.append('Fiesta')
ford.cars.append('Focus')
print(len(ford))
print(ford.length())
print(repr(ford))
print(str(ford))
