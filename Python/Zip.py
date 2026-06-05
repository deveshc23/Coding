friends=["Rolf", "Anne", "Bob", "Jen"]
time_since_seen=[3, 7, 15, 11]

dict_friends=dict(zip(friends, time_since_seen))
print(dict_friends)

long_timers= list(zip(friends, time_since_seen,(1,2,3,4)))
print(long_timers)

# Zip is a function that takes two or more iterables and creates a new iterable with pairs of elements from the original iterables.
# The new iterable is only as long as the shortest iterable.
# In the example above, the zip function takes two lists, friends and time_since_seen, and creates a new iterable with pairs of elements from the original lists.
# The new iterable is a list of tuples, where each tuple contains an element from the friends list and an element from the time_since_seen list at the same index.
