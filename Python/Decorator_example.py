# def my_decorator(func):
#     def wrapper():
#         print("Something happened before the function is called.")
#         func()
#         print("Something happened after the function is called.")
#     return wrapper

# @my_decorator
# def say_hello():
#     print("Hello!")

# if __name__ == "__main__":
#     say_hello()

def my_decorator(func):
    def wrapper(*args,**kwargs):
        print("Something happened before the function is called.")
        result = func(*args, **kwargs)
        print("Something happened after the function is called.")
        return result
    return wrapper

@my_decorator
def say_hello(name):
    print(f"Hello, {name}!")