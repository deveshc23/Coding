import random

def quickselect(arr, k, key=lambda x: x):
    if len(arr) == 1:
        return arr[0]

    pivot = key(random.choice(arr))
    lows = [el for el in arr if key(el) < pivot]
    highs = [el for el in arr if key(el) > pivot]
    pivots = [el for el in arr if key(el) == pivot]

    if k < len(lows):
        return quickselect(lows, k, key)
    elif k < len(lows) + len(pivots):
        return pivots[0]  # return any pivot (all same key)
    else:
        return quickselect(highs, k - len(lows) - len(pivots), key)

def get_middle_age_person(data):
    n = len(data)
    mid_index = n // 2
    return quickselect(data, mid_index, key=lambda x: x[2])  # age is at index 2

people = [
    ("Alice", "F", 30),
    ("Bob", "M", 25),
    ("Carol", "F", 35),
    ("Dave", "M", 40),
    ("Eve", "F", 28)
]

print(get_middle_age_person(people))  # returns the person with median age
