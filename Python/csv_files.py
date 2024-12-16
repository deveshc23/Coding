file=open(r'C:\Users\choud\OneDrive\Desktop\Coding\csv_data_ex.csv','r')
lines=file.readlines()
file.close()

lines=[line.strip() for line in lines[1:]]

for line in lines:
    person_data=line.split(',')
    name=person_data[0]
    age=person_data[1]
    university=person_data[2]
    degree=person_data[3]
    print(f'{name.title()} is {age} years old, and is studying {degree.capitalize()} at {university.title()}')
    # Title makes first letter of each word uppercase
    # Capitalize makes only the first letter capital