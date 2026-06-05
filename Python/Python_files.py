my_file = open(r'C:\Users\choud\OneDrive\Desktop\Coding\data.txt', 'r')  # r stands for reading
file_content=my_file.read()
my_file.close()
print(file_content)
user_name=input('Enter your name: ')
my_file_writing=open(r'C:\Users\choud\OneDrive\Desktop\Coding\data.txt', 'w')
my_file_writing.write(user_name)
my_file_writing.close()