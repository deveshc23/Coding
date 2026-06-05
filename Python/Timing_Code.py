import time

def powers(limit):
    return [x**2 for x in range(limit)]
def measure_time(func):
    start=time.time()
    func()
    end=time.time()
    print(end-start)

measure_time(lambda :powers(5000000))