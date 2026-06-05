class Student:
    def  __init__(self,name,school):
        self.name=name
        self.school=school
        self.marks=[]
    def average(self):
        return sum(self.marks)/len(self.marks)

class WorkingStudent(Student):
    def __init__(self,name,school,salary):
        super().__init__(name,school)
        self.salary=salary
    @property#property decorator
    def weekly_salary(self):
        return self.salary*37.5

rolf=WorkingStudent('Rolf','MIT',15.50)
print(rolf.salary)
rolf.marks.append(57)
rolf.marks.append(99)
print(rolf.average())#instance method as it takes the object 'rolf' as the first argument

print(rolf.weekly_salary)#function in the class used as property
#can only be used if the function has one argument that is self

class Foo:
    @classmethod#classmethod decorator
    def hi(cls):
        print(cls.__name__) #cls is the class itself

my_object=Foo()
my_object.hi()#class method as it takes the class itself as the first argument
print(Foo.hi())

